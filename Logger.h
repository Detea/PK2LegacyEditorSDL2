#ifndef PK2_ENGINE_LOGGER_H
#define PK2_ENGINE_LOGGER_H

#include <string_view>
#include <vector>

#include "LogOutput.h"
#include "LogLevel.h"

namespace PK2::Engine {
    class Logger final {
        public:
            static void write(LogLevel logLevel, std::string_view message, std::string_view file);
            static void info(std::string_view message, std::string_view file = "");
            static void warn(std::string_view message, std::string_view file = "");
            static void error(std::string_view message, std::string_view file = "");

            static void addOutputTarget(LogOutput* target);

    private:
        inline static std::vector<LogOutput*> outputTargets;
    };
}
#endif
