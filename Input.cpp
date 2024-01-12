#include "Input.h"

#include <iostream>

using namespace PK2::Engine;

bool Input::keyPressed(SDL_Scancode scancode) {
	return keyStates && keyStates[scancode];
}

bool Input::keyPressed(SDL_Scancode key, SDL_Keymod modifier) {
	return keyPressed(key) && (keymod & modifier);
}

void Input::updateKeymod(SDL_Keymod mod) {
	keymod = mod;
}

bool Input::mouseDown(int button) {
	return mouseButton == button;
}

void Input::updateMouseButton(Uint32 buttonMask) {
	if (buttonMask & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		mouseButton = MB_LEFT;
	} else if (buttonMask & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
		mouseButton = MB_MIDDLE;
	} else if (buttonMask & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		mouseButton = MB_RIGHT;
	} else {
		mouseButton = 0;
	}
}

bool Input::anyMouseDown() {
	return mouseDown(MB_LEFT) || mouseDown(MB_MIDDLE) || mouseDown(MB_RIGHT);
}

int* Input::getMouseXPointer() {
	return &mouseX;
}

int* Input::getMouseYPointer() {
	return &mouseY;
}

int Input::getMouseX() {
	return mouseX;
}

int Input::getMouseY() {
	return mouseY;
}

void Input::setTypedChar(char c) {
	typedChar = c;
}

char Input::getTypedChar() {
	return typedChar;
}