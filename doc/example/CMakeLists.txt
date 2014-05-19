set(EX_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/Makefile"
              "${CMAKE_CURRENT_SOURCE_DIR}/Makefile"
              "${CMAKE_CURRENT_SOURCE_DIR}/PluginExample.cpp"
              "${CMAKE_CURRENT_SOURCE_DIR}/README")
install(FILES ${EX_SOURCE}
    DESTINATION "${CMAKE_INSTALL_DOCDIR}/hdf5-plugin-lz4/examples")
