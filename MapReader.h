#pragma once

// TODO Cleanup: remove this
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif


#include "Map.h"

#include <string_view>
#include <fstream>

namespace PK2::Game {
	class MapReader {
	public:
		// Reads the the map file "filename" into the map object "mapTarget"
		virtual void read(PK2::Game::Map& mapTarget, std::string_view filename) = 0;

	protected:
		bool versionMatch(const unsigned char expect[5], unsigned char provided[5]);

		std::string readString(std::ifstream& in, int size);

		int readPK2Int(std::ifstream& in);

		void readLayer(std::ifstream& in, std::vector<int>& layer, int width, int height);

		bool isPK2StringTerminator(char c);
	};
}