#include "MapReader.h"

using MapReader = PK2::Game::MapReader;

bool MapReader::versionMatch(const unsigned char expect[5], unsigned char provided[5]) {
	for (int i = 0; i < 5; i++) {
		if (expect[i] != provided[i]) {
			return false;
		}
	}

	return true;
}

#include <iostream>

bool MapReader::isPK2StringTerminator(char c) {
	return c == (char)0x0 || c == (char)0xCD || c == (char)0xCC;
}

std::string MapReader::readString(std::ifstream& in, int size) {
	std::string str = "";
	std::vector<char> buffer(size);

	for (int i = 0; i < size; i++) {
		char c = 0;

		in.read(reinterpret_cast<char *>(&c), sizeof(c));
	
		buffer.push_back(c);
	}

	// Cut anything after the null terminator off, because sometimes the string isn't actually of size "size" and gets padded with nonsense.
	int i = 0;
	while (i < buffer.size()) {
		char c = buffer[i];
		if (!isPK2StringTerminator(c)) {
			str += c;
		}

		i++;
	}

	return str;
}

int MapReader::readPK2Int(std::ifstream& in) {
	int val = -1;

	std::string str = "";

	for (int i = 0; i < 8; i++) {
		char c = 0;

		in.read(reinterpret_cast<char*>(&c), sizeof(c));

		str += c;
	}

	val = std::stoi(str);

	return val;
}

void MapReader::readLayer(std::ifstream& in, std::vector<int>& layer, int mapWidth, int mapHeight) {
	if (layer.size() == mapWidth * mapHeight) {
		std::fill(layer.begin(), layer.end(), 255);

		int startX = readPK2Int(in);
		int startY = readPK2Int(in);
		
		int width = readPK2Int(in);
		int height = readPK2Int(in);

		for (int y = startY; y <= startY + height; y++) {
			for (int x = startX; x <= startX + width; x++) {
				unsigned char tile = 255;

				in.read(reinterpret_cast<char*>(&tile), sizeof(tile));

				layer[x + mapWidth * y] = tile;
			}
		}
	}
}