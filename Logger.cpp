#include "Logger.h"
#include "LogLevel.h"
#include "LogOutput.h"

#include <string_view>
#include <string>
#include <iostream>

using namespace PK2::Engine;

void Logger::write(LogLevel logLevel, std::string_view message, std::string_view file) {
    for (LogOutput* out : outputTargets) {
        out->write(LogEntry(logLevel, message));
    }
}

void Logger::info(std::string_view message, std::string_view file) {
    write(LogLevel::INFO, message, file);
}

void Logger::warn(std::string_view message, std::string_view file) {
    write(LogLevel::WARN, message, file);
}

void Logger::error(std::string_view message, std::string_view file) {
    write(LogLevel::ERROR, message, file);
}

void Logger::addOutputTarget(LogOutput* target) {
    outputTargets.push_back(target);
}