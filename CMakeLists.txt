cmake_minimum_required(VERSION 2.8)
project(hdf5-plugin-lz4)

if(CMAKE_HOST_UNIX)

    #on Unix/Linux systems we do configuration with pkg-config and use 
    #GNUInstallDirs to get the appropriate installation paths    
    include(GNUInstallDirs)
    include(FindPkgConfig)

    if(NOT DEFINED PKG_CONFIG_FOUND)
        message(FATAL_ERROR "Could not find pkg-config -- aborting!")
    endif()

    #check for HDF5 installation
    pkg_search_module(HDF5 REQUIRED hdf5)

    #set compiler options for GCC on Unix/Linux systems
    add_definitions("-std=c99")

    include_directories($HDF5_INCLUDE_DIRS)

elseif(CMAKE_HOST_WIN32)
	
    #on windows we need to rely on the CMAKE installation of HDF5
    FIND_PACKAGE(HDF5 NAMES hdf5)

    set(CMAKE_INSTALL_DOCDIR "${CMAKE_INSTALL_PREFIX}/doc")

    
    include_directories(${HDF5_INCLUDE_DIR})
    message("Header files below: ${HDF5_INCLUDE_DIR}")
endif()


#================need to setup the version of the module=======================
set(MAJOR_VERSION "0")
set(MINOR_VERSION "2")
set(PATCH_VERSION "0")
set(LIBRARY_VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")
set(SO_VERSION "0")

set(PLUGIN_INSTALL_DIR "${CMAKE_INSTALL_FULL_LIBDIR}/hdf5/plugins")



if(NOT DEFINED HDF5_FOUND)
    message(FATAL_ERROR "Could not find HDF5 installation -- aborting!")
endif()


include_directories("./include")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
add_subdirectory("src")
add_subdirectory("doc")
