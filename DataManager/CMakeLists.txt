include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(DataManager STATIC
        src/DataAccess.cpp
        src/DataContainer.cpp
        src/DataManager.cpp
        src/EliminatedPositionShape.cpp
        ../src/Logger.cpp)

target_precompile_headers(DataManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/rapidjson_pch.h)
#target_precompile_headers(dataManager PUBLIC ${CMAKE_SOURCE_DIR}/../include/spdlog_pch.h)
target_precompile_headers(DataManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../libraries/configLib/ConfigFile.h)
target_precompile_headers(DataManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../libraries/fileLib/FileLib.h)

target_link_libraries(DataManager PUBLIC fileLib)
target_link_libraries(DataManager PUBLIC configLib)
target_link_libraries(DataManager PRIVATE spdlog::spdlog)