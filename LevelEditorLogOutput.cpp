#include "LevelEditorLogOutput.h"
#include "LogEntry.h"

using namespace PK2::Engine;

LevelEditorLogOutput::LevelEditorLogOutput() {

}

void LevelEditorLogOutput::write(const LogEntry& entry) {
	if (logEntries.size() >= MAX_ENTRIES) {
		logEntries.erase(logEntries.begin());
	}

	logEntries.push_back(entry);

	if (onWriteFunction) onWriteFunction();
}

void LevelEditorLogOutput::setOnWriteFunction(std::function<void(void)> function) {
	onWriteFunction = function;
}

std::vector<PK2::Engine::LogEntry>* LevelEditorLogOutput::getEntries() {
	return &logEntries;
}