#ifndef PK2_ENGINE_LOGGER_OUTPUT_H
#define PK2_ENGINE_LOGGER_OUTPUT_H
#include <string_view>

#include "LogLevel.h"
#include "LogEntry.h"

namespace PK2::Engine {
	class LogOutput {
	public:
		LogOutput();

		virtual void write(const LogEntry& entry) = 0;
	};
}
#endif