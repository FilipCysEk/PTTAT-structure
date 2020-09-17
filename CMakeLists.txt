cmake_minimum_required(VERSION 3.16)
project(TramHoldupBasics VERSION "0.5" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking, see edit2
endif (CCACHE_FOUND)

include_directories(libraries)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libraries)

if (NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


if (NOT TARGET DataManager)
    # Stand-alone build
    add_subdirectory(DataManager)
endif ()