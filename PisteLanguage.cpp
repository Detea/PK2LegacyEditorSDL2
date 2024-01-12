#include "PisteLanguage.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace PK2::Engine;

PisteLanguage::PisteLanguage() {}

bool PisteLanguage::readFile(std::string_view filename) {
	std::ifstream in(filename.data());

	if (!in) {
		// TODO Log
		std::cerr << "Unable to open file: " << filename << "!\n";
		
		return false;
	}

	// Read whole file into memory. The files should be pretty small. Might wanna test/check that.
	std::ostringstream buf;
	buf << in.rdbuf();
	
	fileContents = buf.str();
	parseFile();

	return true;
}

void PisteLanguage::parseFile() {
	currentPosition = 0;

	std::string titleStr = "";
	std::string textStr = "";
	
	while (currentPosition < fileContents.length()) {
		char currentChar = fileContents[currentPosition];

		switch (currentChar) {
			case SEP_BEGIN_ID: {
				while (peek() != SEP_BEGIN_TEXT) {
					titleStr += peek();

					currentPosition++;
				}
			}
			break;

			case SEP_BEGIN_TEXT: {
				bool textFound = false;

				while (peek() != TEXT_END) {
					if (!skipChar(peek())) textFound = true;

					if (textFound) {
						textStr += peek();
					}

					currentPosition++;
				}

				currentPosition++; // Skip new line
			}
			break;

			default:
				currentPosition++;
				break;
		}

		if (!titleStr.empty() && !textStr.empty()) {
			titleTextMap[titleStr] = textStr;

			titleStr = "";
			textStr = "";
		}
	}

	fileContents.clear();
}

char PisteLanguage::peek() {
	return fileContents[currentPosition + 1];
}

bool PisteLanguage::skipChar(char c) {
	return c == ' ' || c == '\t' || c == '\v';
}

std::string_view PisteLanguage::getText(const std::string& title) {
	if (titleTextMap.find(title) != titleTextMap.end()) {
		return titleTextMap[title];
	}

	return "";
}

const std::map<std::string, std::string>& PisteLanguage::getTitleAndTextMap() {
	return titleTextMap;
}

int PisteLanguage::getIndex(std::string_view title) {
	// TODO implement

	return -1;
}

void PisteLanguage::replaceText(int index, std::string& text) {
	// TODO implement?
}