#add_library(fileLib STATIC IMPORTED)
#set_property(TARGET fileLib PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libFileLib.a)
#target_link_libraries(fileLib INTERFACE stdc++fs)

add_library(fileLib INTERFACE)
target_link_libraries(fileLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libFileLib.a)
target_link_libraries(fileLib INTERFACE stdc++fs)

#add_library(fileLib ${CMAKE_CURRENT_SOURCE_DIR}/cygFileLibShared.dll)
#set_target_properties(fileLib PROPERTIES LINKER_LANGUAGE CXX)
#target_link_libraries(fileLib INTERFACE stdc++fs)