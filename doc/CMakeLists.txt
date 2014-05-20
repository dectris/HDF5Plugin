#install documentation

message(${CMAKE_INSTALL_DOCDIR})
set(PDF_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/HDF5_LZ4.pdf")
install(FILES ${PDF_SOURCE} DESTINATION ${CMAKE_INSTALL_DOCDIR})
add_subdirectory("example")
