#pragma once
#include "LogLevel.h"

#include <string>
#include <string_view>

namespace PK2::Engine {
	class LogEntry {
	public:
		LogEntry(LogLevel level, std::string_view message);
		
		LogLevel getLevel() const;

		std::string_view getMessage() const;
	private:
		LogLevel level;
		
		std::string message;
	};
}