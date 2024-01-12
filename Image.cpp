#include "Image.h"

Image::Image(std::string_view imageFile, int x, int y, int sourceX, int sourceY, int cropWidth, int cropHeight) : Component(x, y), imageFileName(imageFile) {
	rectSource.x = sourceX;
	rectSource.y = sourceY;

	rectSource.w = cropWidth;
	rectSource.h = cropHeight;

	rectTarget.x = x;
	rectTarget.y = y;

	if (cropWidth > 0 && cropHeight > 0) {
		rectTarget.w = cropWidth;
		rectTarget.h = cropHeight;

		width = cropWidth;
		height = cropHeight;
	}
}

void Image::draw(PK2::Engine::GFX& gfx) {
	if (visible) {
		if (rectTarget.w == 0 || rectTarget.h == 0) {
			SDL_QueryTexture(gfx.getImage(imageFileName), nullptr, nullptr, &rectTarget.w, &rectTarget.h);

			width = rectTarget.w;
			height = rectTarget.h;
		}

		rectTarget.x = x;
		rectTarget.y = y;

		gfx.drawImage(imageFileName, rectSource, rectTarget);
	}
}