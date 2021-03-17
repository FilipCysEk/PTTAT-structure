//
// Created by krzysiu on 24.08.2020.
//

#include "Logger.h"

std::shared_ptr<spdlog::logger> Logger::createLogger(std::string loggerName, unsigned int maxFileSize,
                                                     unsigned short maxFileAmount,
                                                     std::string filePath, std::string consolLogLevel,
                                                     std::string fileLogLevel) {

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::from_str(consolLogLevel));

    if (console_sink->level() == spdlog::level::off && consolLogLevel != "off") {
        throw spdlog::spdlog_ex("Passed console log level is incorrect!\n"
                                "You can use: trace, debug, info, warning, error, critical, off");
    }

    auto file_sink = make_shared<spdlog::sinks::rotating_file_sink_mt>(filePath, maxFileSize, maxFileAmount);
    file_sink->set_level(spdlog::level::from_str(fileLogLevel));
    file_sink->set_pattern("%Y-%m-%d %T.%e\t%l\t%v");

    if (file_sink->level() == spdlog::level::off && fileLogLevel != "off") {
        throw spdlog::spdlog_ex("Passed file log level is incorrect!\n"
                                "You can use: trace, debug, info, warning, error, critical, off");
    }

    spdlog::sinks_init_list sink_list = {file_sink, console_sink};

    auto loggerMain = make_shared<spdlog::logger>(loggerName, sink_list);
    loggerMain->flush_on(spdlog::level::debug);
    spdlog::flush_every(std::chrono::seconds(3));
    loggerMain->set_level(spdlog::level::trace);
    spdlog::register_logger(loggerMain);
    return loggerMain;
}

std::shared_ptr<spdlog::logger> Logger::getLogger(std::string name) {
    return spdlog::get(name);;
}
