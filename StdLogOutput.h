#pragma once
#include <string_view>

#include "LogOutput.h"
#include "LogLevel.h"
#include "LogEntry.h"

namespace PK2::Engine {
	class StdLogOutput : public LogOutput {
	public:
		StdLogOutput();

		virtual void write(const LogEntry& entry) override;
	};
}