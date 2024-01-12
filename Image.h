#pragma once
#include "Component.h"
#include "GFX.h"

#include <SDL.h>

#include <iostream>

class Image : public Component {
public:
	// imageFile refers to a file that's already been loaded via gfx.loadImage()
	Image(std::string_view imageFile, int x, int y, int cropX = 0, int cropY = 0, int cropWidth = 0, int cropHeight = 0);

	virtual void draw(PK2::Engine::GFX& gfx) override;

private:
	std::string imageFileName;

	SDL_Rect rectSource;
	SDL_Rect rectTarget;
};

