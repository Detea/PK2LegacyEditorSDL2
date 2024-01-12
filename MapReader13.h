#pragma once
#include "MapReader.h"

namespace PK2::Game {
	class MapReader13 : public MapReader {
	public:
		MapReader13();

		virtual void read(PK2::Game::Map& mapTarget, std::string_view filename) override;

	private:
		void resetLayers(PK2::Game::Map& mapTarget);
	};
}

