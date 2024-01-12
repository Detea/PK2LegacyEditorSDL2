#include "VerticalLayout.h"

#include <iostream>

VerticalLayout::VerticalLayout() {

}

VerticalLayout::VerticalLayout(int x, int y) : Layout(x, y) {

}

VerticalLayout::~VerticalLayout() {
}

void VerticalLayout::calculate() {
	int adjustedY = 0;
	for (int i = 0; i < components.size(); i++) {
		components[i]->setRelativePosition(x, y + adjustedY);
		
		adjustedY += components[i]->getHeight() + spacing;
	}
}

void VerticalLayout::setSpacing(int spacing) {
	this->spacing = spacing;
}
