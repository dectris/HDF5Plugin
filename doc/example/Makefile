CPPFLAGS = -fPIC -g -O3 -std=c++0x
CPP = g++
# install directory of HDF5 1.8.11 #
HDF5_INSTALL = /home/det/hdf5-1.8.11-snap16/hdf5/

#note: The filter is not linked in the compile step, but plugged in when executing
PluginExample: PluginExample.cpp
	$(CPP) $(CPPFLAGS) PluginExample.cpp -o PluginExample -L$(HDF5_INSTALL)/lib -I$(HDF5_INSTALL)/include -lhdf5