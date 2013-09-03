
#gather all source files for the library
file(GLOB SOURCES *.c)

add_library(lz4module MODULE ${SOURCES})
set_target_properties(lz4module PROPERTIES VERSION "${LIBRARY_VERSION}"
                                       SOVERSION "${SO_VERSION}")

#install code
install(TARGETS lz4module LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/hdf5/plugins")

