cmake_minimum_required(VERSION 2.8)
project(hdf5-plugin-lz4)
include(GNUInstallDirs)
include(FindPkgConfig)

if(NOT DEFINED PKG_CONFIG_FOUND)
    message(FATAL_ERROR "Could not find pkg-config -- aborting!")
endif()


#================need to setup the version of the module=======================
set(MAJOR_VERSION "0")
set(MINOR_VERSION "2")
set(PATCH_VERSION "0")
set(LIBRARY_VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")
set(SO_VERSION "0")

set(PLUGIN_INSTALL_DIR "${CMAKE_INSTALL_FULL_LIBDIR}/hdf5/plugins")

add_definitions("-std=c99")

#check for HDF5 installation
pkg_search_module(HDF5 REQUIRED hdf5)

if(NOT DEFINED HDF5_FOUND)
    message(FATAL_ERROR "Could not find HDF5 installation -- aborting!")
endif()


include_directories("./include")
include_directories($HDF5_INCLUDE_DIRS)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
add_subdirectory("src")
add_subdirectory("doc")
