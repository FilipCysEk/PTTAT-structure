#add_library(configLib STATIC IMPORTED)
#set_property(TARGET configLib PROPERTY IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/libConfigLib.a)
#set_property(TARGET configLib PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR})
##target_link_libraries(configLib INTERFACE stdc++fs)
#message(${CMAKE_CURRENT_SOURCE_DIR}/libConfigLib.a)

if(NOT TARGET configLib)
add_library(configLib INTERFACE)
target_link_libraries(configLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libConfigLib.a)
endif()

#add_library(configLib ${CMAKE_CURRENT_SOURCE_DIR}/cygConfigLibShared.dll)
#add_library(configLib ${CMAKE_CURRENT_SOURCE_DIR}/libConfigLib.a)
#set_target_properties(configLib PROPERTIES LINKER_LANGUAGE CXX)

