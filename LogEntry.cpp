#include "LogEntry.h"

using namespace PK2::Engine;

LogEntry::LogEntry(LogLevel level, std::string_view message) : level(level), message(message) {
}

LogLevel LogEntry::getLevel() const {
	return level;
}

std::string_view LogEntry::getMessage() const {
	return message;
}