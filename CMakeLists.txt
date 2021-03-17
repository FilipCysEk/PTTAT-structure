cmake_minimum_required(VERSION 3.16)
project(PTTAT_structure VERSION "0.5" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking, see edit2
endif (CCACHE_FOUND)

include_directories(libraries)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libraries)

#if (NOT TARGET spdlog)
#    # Stand-alone build
#    find_package(spdlog REQUIRED)
#endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(PTTAT_structure STATIC
        src/DataAccess.cpp
        src/DataContainer.cpp
        src/DataManager.cpp
        src/EliminatedPositionShape.cpp
        src/Logger.cpp)

target_precompile_headers(PTTAT_structure PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/rapidjson_pch.h)
#target_precompile_headers(PTTAT_structure PUBLIC ${CMAKE_SOURCE_DIR}/include/spdlog_pch.h)
target_precompile_headers(PTTAT_structure PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libraries/configLib/ConfigFile.h)
target_precompile_headers(PTTAT_structure PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libraries/fileLib/FileLib.h)

target_link_libraries(PTTAT_structure PUBLIC fileLib)
target_link_libraries(PTTAT_structure PUBLIC configLib)
target_link_libraries(PTTAT_structure PRIVATE spdlog::spdlog)