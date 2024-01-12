#include "Layout.h"
#include <iostream>

Layout::Layout() {

}

Layout::Layout(int x, int y) {
	this->x = x;
	this->y = y;
}

Layout::~Layout() {

}

void Layout::add(Component* c) {
	c->setRelativePosition(x, y);

	components.push_back(c);
}

std::vector<Component*>& Layout::getComponents() {
	return components;
}

void Layout::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

void Layout::setSize(int width, int height) {
	this->width = width;
	this->height = height;
}

int Layout::getX() {
	return x;
}

int Layout::getY() {
	return y;
}