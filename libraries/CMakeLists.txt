#add_library(fileLib STATIC IMPORTED)
#set_property(TARGET fileLib PROPERTY IMPORTED_LOCATION fileLib/libFileLib.a)
##target_link_libraries(fileLib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/libs/libFileLib.a")
#target_link_libraries(fileLib INTERFACE stdc++fs)
#
##target_precompile_headers(fileLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/FileLib.h)
#
##target_include_directories(fileLib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
##target_include_directories(mainApp "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(configLib)
add_subdirectory(fileLib)
if(NOT TARGET spdlog)
add_subdirectory(spdlog)

endif()