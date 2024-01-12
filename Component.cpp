#include "Component.h"

#include <iostream>
#include "Input.h"

Component::Component() : relativeX(0), relativeY(0) {

}

Component::Component(int x, int y, int width, int height) : x(x), y(y), width(width), height(height), relativeX(x), relativeY(y) {}

Component::~Component() {
	for (Component* c : components) {
		c->freeComponents();
	}

	components.clear();

	for (Layout* l : layouts) {
		delete l;

		l = nullptr;
	}

	layouts.clear();
}

void Component::freeComponents() {
	for (Component* c : components) {
		c->freeComponents();

		delete c;
		c = nullptr;
	}
}

void Component::freeLayouts() {
	// TODO Implement this?
}

void Component::draw(PK2::Engine::GFX& gfx) {
	for (Component* c : components) {
		c->draw(gfx);
	}
}

void Component::addComponent(Component* c) {
	c->updatePosition(x, y);

	components.push_back(c);

	for (Component* cc : c->components) {
		cc->updatePosition(x, y);

		components.push_back(cc);
	}
}

void Component::addLayout(Layout* l) {
	l->calculate();

	for (Component* c : l->getComponents()) {
		c->updatePosition(x, y);
		
		components.push_back(c);
	}

	layouts.push_back(l);
}

void Component::onMove(int newX, int newY) {
	updatePosition(newX, newY);

	for (Component* c : components) {
		c->updatePosition(x, y);
	}
}

void Component::onClick(int mouseX, int mouseY, int mouseButton) {
	for (Component* c : components) {
		using Input = PK2::Engine::Input;
		if (Input::mouseDown(Input::MB_LEFT) ||
			Input::mouseDown(Input::MB_MIDDLE) ||
			Input::mouseDown(Input::MB_RIGHT)) {
			
			if (c->isVisible()) {
				if (c->positionInBounds(mouseX, mouseY)) {
					c->setFocused(true);

					c->onClick(mouseX, mouseY, mouseButton);
				} else {
					c->setFocused(false);
				}
			}
		}
	}
}

void Component::setFocused(bool focused) {
	this->focused = focused;

	if (focused) {
		onFocusGained();
	} else {
		onFocusLost();
	}

	for (Component* c : components) {
		c->setFocused(focused);
	}
}

void Component::onWindowFocusGained() {
	for (Component* c : components) {
		c->onWindowFocusGained();
	}
}

void Component::onWindowFocusLost() {
	for (Component* c : components) {
		c->onWindowFocusLost();
	}
}

void Component::onMouseOver(int mouseX, int mouseY) {
	for (Component* c : components) {
		if (visible) c->onMouseOver(mouseX, mouseY);
	}
}

bool Component::positionInBounds(int posX, int posY) {
	return posX >= x &&
		posX <= x + width &&
		posY >= y &&
		posY <= y + height;
}

void Component::updatePosition(int newX, int newY) {
	x = newX + relativeX;
	y = newY + relativeY;
}

void Component::setFont(PK2::Engine::Font& font) {
	Component::font = font;
}

void Component::setX(int x) {
	this->x = x;
}

void Component::setY(int y) {
	this->y = y;
}

void Component::setWidth(int w) {
	width = w;
}

void Component::setHeight(int h) {
	height = h;
}

void Component::setRelativeX(int x) {
	this->relativeX = x;
}

int Component::getX() {
	return x;
}

int Component::getY() {
	return y;
}

int Component::getWidth() {
	return width;
}

int Component::getHeight() {
	return height;
}

void Component::setRelativePosition(int x, int y) {
	relativeX = x;
	relativeY = y;
}

void Component::onKeyDown(SDL_Scancode key, SDL_Keymod mod) {
	for (Component* c : components) {
		c->onKeyDown(key, mod);
	}
}

void Component::onKeyTyped(char c) {
	for (Component* comp : components) {
		comp->onKeyTyped(c);
	}
}

void Component::onFocusGained() {

}

void Component::onFocusLost() {

}

void Component::setVisible(bool isVisible) {
	visible = isVisible;
}

bool Component::isVisible() {
	return visible;
}