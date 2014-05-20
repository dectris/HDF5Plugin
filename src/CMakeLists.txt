#gather all source files for the library
set(SOURCES h5zlz4.c lz4.c)

add_library(lz4module MODULE ${SOURCES})
set_target_properties(lz4module PROPERTIES 
                      VERSION "${LIBRARY_VERSION}"
                      SOVERSION "${SO_VERSION}")

#install code
install(TARGETS lz4module LIBRARY 
        DESTINATION ${PLUGIN_INSTALL_DIR})

