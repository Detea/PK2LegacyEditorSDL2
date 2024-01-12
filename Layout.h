#pragma once

#include <vector>

#include "Component.h"

class Component;

/*
	IMPORTANT Layout does not own the components you add to it. You need to add the layout to another component to make sure that they are deleted!

	Components in a layout will use the layouts x and y position, components will ignore their own x and y position when they are laid out by a layout.
*/
class Layout {
public:
	Layout();
	Layout(int x, int y);
	virtual ~Layout();

	void add(Component* c);
	
	virtual void calculate() = 0;

	void setSize(int width, int height);
	void setPosition(int x, int y);

	int getX();
	int getY();

	std::vector<Component*>& getComponents();

protected:
	std::vector<Component*> components;

	int x;
	int y;

	int width;
	int height;
};

