#ifndef PISTELANGUAGE_H
#define PISTELANGUAGE_H

#include <map>
#include <string>
#include <string_view>

namespace PK2::Engine {
	class PisteLanguage {
	public:
		PisteLanguage();

		bool readFile(std::string_view filename);

		int getIndex(std::string_view id);

		std::string_view getText(const std::string& title);

		const std::map<std::string, std::string>& getTitleAndTextMap();

		void replaceText(int index, std::string& text);

	private:
		void parseFile();
		
		// Returns the next character in fileContents, without advancing the currentPosition;
		char peek();

		// Returns true when c = single space, \t, \v
		bool skipChar(char c);

	private:

		constexpr static char SEP_BEGIN_ID = '*';
		constexpr static char SEP_BEGIN_TEXT = ':';
		constexpr static char TEXT_END = '\n';

		std::string fileContents;
		int currentPosition = 0;

		// TODO Use std::any for values? Most of the time the value is going to be a string, but when loading the language font file there are also ints
		std::map<std::string, std::string> titleTextMap;
	};
}
#endif