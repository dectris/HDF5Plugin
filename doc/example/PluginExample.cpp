#include <iostream>
#include <hdf5.h>

#include <vector>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

//#define IMG_DIMX 2463
//#define IMG_DIMY 2527


#define LZ4_FILTER 32004
#define IMG_DIMX 1280
#define IMG_DIMY 1280
int main(int argc, char* argv[])
{
  const int nimages = 15;
  srand (time(NULL));
   /// create some data ///
  std::cout<<"*** CREATE DATA ***"<<std::endl;
  std::vector< std::vector<int> > Images(nimages);
  for(int nimg; nimg<nimages; nimg++)
    {
      Images[nimg].resize(IMG_DIMY*IMG_DIMX);
    }
  // initialise
  for(int nimg=0; nimg<nimages; nimg++)
    {
      for(int pix=0; pix<IMG_DIMY*IMG_DIMX; pix++)
	//Images[nimg][pix] = pix;  /// this compresses pretty good
      Images[nimg][pix] = rand()%2048;  /// this compresses terribly bad
    }
 

  hsize_t dims[3] = {nimages, IMG_DIMY,IMG_DIMX};         //N x X*Y
  hsize_t  chunk[3] = {1, IMG_DIMY,IMG_DIMX};  // chunk is one image
  hsize_t  count[3] = {1, IMG_DIMY,IMG_DIMX};  // size of hyperslab: 1 chunk
  
 
  std::string filename = "test.h5";
  hid_t file_id = H5Fcreate(filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT); 
 
  /// DATASPACE IS CHUNKED ///
  hid_t space = H5Screate_simple (3, dims, NULL);
    hid_t dcpl = H5Pcreate (H5P_DATASET_CREATE);
  hid_t status = H5Pset_chunk(dcpl, 3, chunk);
  
  /// FILTER CHAIN. FILTER IS MANDATORY ///
  /// filter argument is the chunk size ///
  
  
  
  
  unsigned int flags = H5Z_FLAG_MANDATORY; 
  size_t nelements = 1;
  uint cd_values[1];
  /// compression block size. Choose it deliberately small to test functionality ///
  cd_values[0] = 123;
  status = H5Pset_filter(dcpl, LZ4_FILTER, flags, 0, NULL);

  hid_t HDF5_datatype;
  HDF5_datatype = H5T_NATIVE_UINT32;
  hid_t  memspace = H5Screate_simple(3, count, NULL);
  hid_t dataset_id = H5Dcreate2(file_id, "data", HDF5_datatype, space, H5P_DEFAULT, dcpl, H5P_DEFAULT);

  hsize_t offset[3];
  offset[0] = 0;
  offset[1] = 0;
  offset[2] = 0;
  
  std::cout<<"****** WRITE DATA ******"<<std::endl;
  for(offset[0]=0; offset[0]<nimages; offset[0] += count[0])
    {
      
      herr_t errstatus = H5Sselect_hyperslab(space, H5S_SELECT_SET, offset, NULL, count, NULL);
      status = H5Dwrite(dataset_id, HDF5_datatype, memspace, space, H5P_DEFAULT,  Images.at(offset[0]).data());
      if(status <0)
	return -1;
    }

  H5Sclose(memspace);
  H5Sclose(space);
  H5Dclose(dataset_id);
  H5Fclose(file_id);







  std::cout<<"********** READ BACK DATA ************"<<std::endl;

    /// ********** READ BACK DATA ************ ////

  std::vector< std::vector<int> > ReadBackImages(nimages);
  for(int nimg; nimg<nimages; nimg++)
    {
      ReadBackImages[nimg].resize(IMG_DIMY*IMG_DIMX);
    }
    
  file_id = H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
  dataset_id = H5Dopen1(file_id, "/data");
  hid_t space_id = H5Dget_space(dataset_id); //filespace id
  const int ndims = H5Sget_simple_extent_ndims(space_id);
  //hsize_t dims[ndims];
  hsize_t maxdims[ndims];
  H5Sget_simple_extent_dims(space_id, dims, maxdims);
  
  count[0] = 1; // hyperslab size is one image
  count[1] = dims[1]; // DIMX * DIMY
  count[2] = dims[2]; // DIMX * DIMY
  
  hid_t memspace_id =  H5Screate_simple(3, count, NULL); // corresponds to the hyperslab
  offset[0] = 0;
  offset[1] = 0;
  offset[2] = 0;
  
  for(offset[0]=0; offset[0] < nimages; offset[0] += count[0])
    {
      herr_t errstatus = H5Sselect_hyperslab(space_id, H5S_SELECT_SET, offset, NULL, count, NULL);
      hid_t status = H5Dread(dataset_id, HDF5_datatype, memspace_id, space_id , H5P_DEFAULT,   ReadBackImages[offset[0]].data());
    }
      

  H5Dclose(dataset_id);
  H5Fclose(file_id);
  

  std::cout<<"******* VERIFY *******"<<std::endl;
  /// check for consistency ///
    for(int nimg=0; nimg<nimages; nimg++)
    {
      for(int pix=0; pix<IMG_DIMY*IMG_DIMX; pix++)
	if(Images[nimg][pix] != ReadBackImages[nimg][pix])
	  {
	    std::cout<<"problem reading back data"<<std::endl;
	    std::cout<<Images[nimg][pix]<<" "<<ReadBackImages[nimg][pix]<<std::endl;
	    return -1;
	  }
    }
  std::cout<<"******* SUCCESS *******"<<std::endl;




}
