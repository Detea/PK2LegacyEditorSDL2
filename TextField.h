#pragma once
#include "Component.h"

#include <string>
#include <string_view>

class TextField : public Component {
public:
	using Component::Component;

	TextField(const std::string& text, int maxChar, int x = 0, int y = 0);
	TextField(int maxChar = 16, int x = 0, int y = 0);

	virtual void draw(PK2::Engine::GFX& gfx) override;

	virtual void onClick(int mouseX, int mouseY, int mouseButton) override;

	void setText(std::string_view text);
	std::string_view getText();

	virtual void onKeyDown(SDL_Scancode key, SDL_Keymod modifier) override;
	virtual void onKeyTyped(char c) override;

	virtual void onFocusGained() override;
	virtual void onFocusLost() override;

	virtual void onWindowFocusGained() override;
	virtual void onWindowFocusLost() override;

private:
	static constexpr int RESPONSE_DELAY = 10;
	static constexpr int RESPONSE_DELAY_SHORT = 5;

	static constexpr int COLOR_INACTIVE = 10;
	static constexpr int COLOR_ACTIVE = 46;
	static constexpr int COLOR_CURSOR = 20;

	static constexpr int CURSOR_WIDTH = 8;
	static constexpr int CURSOR_HEIGHT = 10;

	bool editing = false;
	bool hasWindowFocus = false;

	int maxChars = 0;
	int cursorPos = 0;

	std::string text;
};

