#pragma once
#include "Component.h"

#include <functional>

class ArrowsButton : public Component {
public:
	enum class Orientation {
		VERTICAL,
		HORIZONTAL
	};

	ArrowsButton(int x, int y, Orientation orientation = Orientation::VERTICAL);

	virtual void draw(PK2::Engine::GFX& gfx) override;

	virtual void onClick(int mouseX, int mouseY, int mouseButton);

	void setScrollUpAction(std::function<void()> function);
	void setScrollDownAction(std::function<void()> function);

private:
	Orientation orientation;

	static constexpr int RESPONSE_DELAY = 8;

	static constexpr SDL_Rect VERTICAL_CROP = { 324, 1, 13, 27 };
	static constexpr SDL_Rect HORIZONTAL_CROP_UP = { 324, 1, 13, 13 };
	static constexpr SDL_Rect HORIZONTAL_CROP_DOWN = { 324, 15, 13, 13 };

	std::function<void()> scrollUpAction;
	std::function<void()> scrollDownAction;
};

