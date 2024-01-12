#include "Separator.h"

Separator::Separator(int x, int y, int length, Orientation orientation, int color)
	: Component(x, y), length(length), orientation(orientation), color(color) {

}

void Separator::draw(PK2::Engine::GFX& gfx) {
	SDL_Color col = gfx.getColorInBackgroundPalette(color);

	if (orientation == Orientation::VERTICAL) {
		gfx.drawLine(x, y, x, y + length, col);
	} else if (orientation == Orientation::HORIZONTAL) {
		gfx.drawLine(x, y, x + length, y, col);
	}
}