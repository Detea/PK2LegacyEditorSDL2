#pragma once
#include "GFX.h"
#include "Font.h"
#include "Layout.h"

#include <vector>

class Layout;

class Component {
public:
	Component();
	Component(int x, int y, int width = 0, int height = 0);
	virtual ~Component();

	// TODO Remove these two. updatePosition should be used instead, because it accounts for the relative position
	void setX(int x);
	void setY(int y);

	int getX();
	int getY();

	void setWidth(int w);
	void setHeight(int h);

	int getWidth();
	int getHeight();

	virtual void draw(PK2::Engine::GFX& gfx);

	static void setFont(PK2::Engine::Font& font);

	/* 
		When you add a component or a layout Component owns it. That means component will take care of freeing it.
		
		IMPORTANT: Call Window::setComponent() before adding any other components to this one. That method will update this components position, which will then be used to set it's child components.

		TODO Update all child components positions, when this method has been called?
	*/
	void addComponent(Component* c);
	void addLayout(Layout* l);

	// TODO Cleanup: Some of the on... functions should be protected, not public

	// This method handles mouse events
	virtual void onClick(int mouseX, int mouseY, int mouseButton);
	virtual void onMouseOver(int mouseX, int mouseY);

	virtual void onKeyDown(SDL_Scancode key, SDL_Keymod mod);
	virtual void onKeyTyped(char c);

	// This method gets called when the component, and so it's parent window, gets moved
	void onMove(int newX, int newY);

	void updatePosition(int newX, int newY);

	void setRelativePosition(int x, int y);

	void setRelativeX(int x);

	bool positionInBounds(int posX, int posY);

	void setFocused(bool focused);

	virtual void onFocusGained();
	virtual void onFocusLost();

	virtual void onWindowFocusGained();
	virtual void onWindowFocusLost();

	void setVisible(bool isVisible);
	bool isVisible();

private:
	void freeComponents();
	void freeLayouts();

protected:
	// Position on screen
	int x = 0;
	int y = 0;

	// Position in parent component or window.
	int relativeX;
	int relativeY;

	int width = 0;
	int height = 0;

	bool focused = false;

	inline static PK2::Engine::Font font;

	bool visible = true;

	std::vector<Component*> components;
	std::vector<Layout*> layouts;
};

