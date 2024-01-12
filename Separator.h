#pragma once
#include "Component.h"

#include <SDL.h>

class Separator : public Component {
public:
	enum class Orientation {
		HORIZONTAL,
		VERTICAL
	};

	Separator(int x, int y, int length, Orientation orientation, int color);

	virtual void draw(PK2::Engine::GFX& gfx) override;

private:
	Orientation orientation;
	
	int length = 0;

	int color = 0;
};

