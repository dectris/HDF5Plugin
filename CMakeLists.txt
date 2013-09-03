cmake_minimum_required(VERSION 2.6)
include(GNUInstallDirs)
project(LZ4-HDF5-Filter)

#================need to setup the version of the module=======================
set(MAJOR_VERSION "0")
set(MINOR_VERSION "2")
set(PATCH_VERSION "0")
set(LIBRARY_VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")
set(SO_VERSION "0")

add_definitions("-std=c99")

include_directories("./include")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
add_subdirectory("src")
