#include "StdLogOutput.h"

#include <iostream>

using namespace PK2::Engine;

StdLogOutput::StdLogOutput() {

}

void StdLogOutput::write(const LogEntry& entry) {
	switch (entry.getLevel()) {
		case LogLevel::INFO:
			std::cout << "[INFO] " << entry.getMessage() << "\n";
			break;

		case LogLevel::WARN:
			std::cout << "[WARN] " << entry.getMessage() << "\n";
			break;

		case LogLevel::ERROR:
			std::cerr << "[ERROR] " << entry.getMessage() << "\n";
			break;
	}
}