#pragma once
#include "Component.h"

#include <string>
#include <functional>

class Link : public Component {
public:
	Link(const std::string& text, int x = 0, int y = 0);
	~Link();

	virtual void onClick(int mouseX, int mouseY, int mouseButton) override;
	virtual void onMouseOver(int mouseX, int mouseY) override;

	virtual void draw(PK2::Engine::GFX& gfx) override;

	void setAction(std::function<void()> function);

	void setText(std::string_view text);

private:
	static constexpr int RESPONSE_DELAY = 20;
	static constexpr int COLOR_MOUSE_OVER = 41;

	// Gets set to true, when the mouse is over this component
	bool mouseOver = false;

	std::string text;

	// Function that gets called, when the user clicks on this link
	std::function<void()> action;
};

