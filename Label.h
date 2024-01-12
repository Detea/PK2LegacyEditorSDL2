#pragma once
#include <string>

#include "GFX.h"
#include "Font.h"
#include "Component.h"

class Label : public Component {
public:
	Label(const std::string& text = "", int x = 0, int y = 0);
	Label(const std::string& text, PK2::Engine::Font& font);

	~Label();

	void setText(std::string_view text);

	virtual void draw(PK2::Engine::GFX& gfx) override;
private:
	std::string text;
};

