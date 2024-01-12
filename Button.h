#pragma once
#include "Component.h"
#include "Label.h"

#include <string>
#include <SDL.h>

#include <functional>

class Button : public Component {
public:
	Button(const std::string& text);
	Button(const std::string& text, int x, int y);

	virtual void draw(PK2::Engine::GFX& gfx) override;

	virtual void onMouseOver(int mouseX, int mouseY) override;
	virtual void onClick(int mouseX, int mouseY, int mouseButton) override;

	void setText(std::string_view newText);

	void setAction(std::function<void()> a);
private:
	static constexpr int LABEL_OFFSET_X = 2;
	static constexpr int LABEL_OFFSET_Y = 2;

	static constexpr int RESPONSE_DELAY = 20;

	std::string text;

	// The color when the button isn't being clicked
	int color = 18;

	// The color when the button is being clicked
	int colorClicked = 29;
	
	// The actual color of the border being drawn
	int borderColor = color;

	std::function<void()> action;
};

