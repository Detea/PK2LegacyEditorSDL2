#pragma once
#include "LogOutput.h"
#include "LogEntry.h"

#include <string_view>
#include <string>
#include <functional>
#include <vector>

class LevelEditorLogOutput : public PK2::Engine::LogOutput {
public:
	LevelEditorLogOutput();

	virtual void write(const PK2::Engine::LogEntry& entry) override;
	
	void setOnWriteFunction(std::function<void()> function);

	std::vector<PK2::Engine::LogEntry>* getEntries();

private:
	static constexpr int MAX_ENTRIES = 55;

	std::vector<PK2::Engine::LogEntry> logEntries;

	std::function<void(void)> onWriteFunction;
};

