//
// Created by krzysiu on 24.08.2020.
//

#ifndef TRAMHOLDUP_LOGGER_H
#define TRAMHOLDUP_LOGGER_H

#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <chrono>
#include <vector>

class Logger {
private:

public:
    static std::shared_ptr<spdlog::logger> getLogger(std::string name);

    /**
     *
     * @param maxFileSize
     * @param maxFileAmount
     * @param filePath
     * @param consolLogLevel
     * @param fileLogLevel
     * @throws spdlog::spdlog_ex
     */
    static std::shared_ptr<spdlog::logger>
    createLogger(std::string loggerName, unsigned int maxFileSize, unsigned short maxFileAmount,
                 std::string filePath, std::string consolLogLevel, std::string fileLogLevel);

};


#endif //TRAMHOLDUP_LOGGER_H
