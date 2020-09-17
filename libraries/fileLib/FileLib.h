//
// Created by cysiu on 20.10.2019.
//

#ifndef LIBRARIES1_FILELIB_H
#define LIBRARIES1_FILELIB_H

#pragma once

#include <experimental/filesystem>
#include <string>
#include <chrono>

using namespace std;
namespace fs = experimental::filesystem;


class FileLib {
public:
    /**
     * @brief Convert relative file path to static file path
     * @param path relative path to file/directory
     * @return static path to file/directory (directory have on end '/')
     */
    static string getFullPath(string path);

    /**
     * @brief CHeck existing of file/directory
     * @param path static path to file/directory
     * @return 1 - exists, 0 - no exist
     */
    static bool fileExist(string path);

    /**
     * @brief Return file modification time
     * @param path static path to file
     * @return last modification time
     */
    static time_t fileTime(string path);

    /**
     * @brief Creating directory
     * @param name name of new directory
     * @param path static path to directory, where directory be created
     * @return 1 - successfully, 0 - error
     */
    static bool createDirectory(string name, string path);

    /**
     * @brief Creating directory
     * @param path static path to new directory
     * @return 1 - successfully, 0 - error
     */
    static bool createDirectory(string path);

    /**
     * @brief Remove file/directory
     * @param path static path to removed file/directory
     * @return 1 - successfully, 0 - error
     */
    static bool removeFile(string path);

    /**
     * @brief Remove all files from directory
     * @param path static file to directory
     * @return 1 - successfully, 0 - error
     */
    static bool emptyingDirectory(string path);

    /**
     * @brief rename file/directory
     * @param oldName old name of file
     * @param newName new name of file
     * @param path static path to directory, where this file is
     */
    static void rename(string oldName, string newName, string path);

    /**
     * @brief Rename file/directory
     * @param oldFilePath static path to old file with name
     * @param newFilePath static path to new file with name
     */
    static void rename(string oldFilePath, string newFilePath);

    /**
     * @brief Copy file/firectory
     * @param oldPath static path to source file
     * @param newPath static path to paste file
     */
    static void copy(string oldPath, string newPath);

    /**
     * @brief Move file/directory
     * @param oldPath static path to actually file
     * @param newPath static path to new file location
     */
    static void move(string oldPath, string newPath);

    /**
     * @brief Return file and directory list in path
     * @param path static path to get list
     * @return list of file/dirs name
     */
    static vector<string> dirFiles(string path);


private:
    static bool isStaticPath(string path);

    static bool isStaticDirPath(string path);

};


#endif //LIBRARIES1_FILELIB_H
