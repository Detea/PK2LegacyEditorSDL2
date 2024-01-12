#pragma once

namespace PK2::Game {
	class Map13Constants {
	public:
		static constexpr unsigned char VERSION_ID[5] = {'1', '.', '3', 0, 0xCD};

		static constexpr int FILE_LENGTH = 13;
		static constexpr int NAME_AUTHOR_STR_LENGTH = 40;

		static constexpr int MAP_WIDTH = 256;
		static constexpr int MAP_HEIGHT = 224;

		static constexpr int MAP_SIZE = MAP_WIDTH * MAP_HEIGHT;

		static constexpr int LAYER_BACKGROUND = 0;
		static constexpr int LAYER_FOREGROUND = 1;

		static constexpr int LAYER_SPRITES = 0;

		static constexpr int MAX_SPRITE_PROTOTYPES = 100;

		static constexpr int SWITCH_INIT_VALUE = 2000;

		static constexpr int TILE_EMPTY = 255;

	};
}