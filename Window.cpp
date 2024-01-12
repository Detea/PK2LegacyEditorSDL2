#include "Window.h"
#include "Logger.h"
#include "Input.h"

using namespace PK2::Engine;

std::string Window::editorImageFile;

PK2::Engine::Font Window::font;

Window::Window(std::string title, int x, int y, int width, int height, bool visible, SDL_Scancode key, SDL_Keymod modifier)
	: title(title), x(x), y(y), width(width), height(height), visible(visible), shortcutKey(key), shortcutModifier(modifier) {

	titlebarMiddle.w = width - 14;
	titlebarMiddle.h = 16;
}

Window::~Window() {
	delete component;
	component = nullptr;
}

void Window::renderTitleBar(PK2::Engine::GFX& gfx) {
	SDL_Rect leftSide = { x, y, TITLEBAR_LEFT_SIDE.w, TITLEBAR_LEFT_SIDE.h };
	gfx.drawImage(editorImageFile, TITLEBAR_LEFT_SIDE, leftSide);

	// TODO This will probably cause issues, when titlebarMiddle.w is greater than the width of the bar in the image (305 pixels). But it'll do for now 
	SDL_Rect middlebar = { x + 4, y, titlebarMiddle.w, TITLEBAR_LEFT_SIDE.h };
	gfx.drawImage(editorImageFile, titlebarMiddle, middlebar);

	SDL_Rect rightSide = { x + 2 + titlebarMiddle.w, y, TITLEBAR_RIGHT_SIDE.w, TITLEBAR_RIGHT_SIDE.h };
	gfx.drawImage(editorImageFile, TITLEBAR_RIGHT_SIDE, rightSide);

	// TODO Only draw at full alpha when this window is active, otherwise draw at 50%?
	gfx.drawString(title, x + 5, y + 3);
}

void Window::renderBorder(PK2::Engine::GFX& gfx) {
	// +17 to include the titlebar
	gfx.drawRect(x - 1, y - 1, width + 2, height + 17, borderColor);
}

void Window::renderBackgroundGradient(PK2::Engine::GFX& gfx) {
	/*
	for (int i = 0; i < GRADIENT_SEGMENTS; i++) {
		SDL_Color color = gfx.getColorInBackgroundPalette(6 - i + GRADIENT_COLOR);
		gfx.fillRect(x, y + titlebarMiddle.h + (i * segmentHeight), width, segmentHeight, color);
	}*/

	// TODO Fix this double shit, making the gradient skip a line in the log window

	double segmentHeight = height / 6.0000;
	double segmentY = 0;

	for (int i = 0; i < GRADIENT_SEGMENTS; i++) {
		SDL_Color color = gfx.getColorInBackgroundPalette(6 - i + GRADIENT_COLOR);
		gfx.fillRect(x, y + titlebarMiddle.h - 1 + int(segmentY), width, int(segmentHeight), color);

		segmentY += segmentHeight;
	}
}

void Window::render(PK2::Engine::GFX& gfx) {
	if (visible) {
		renderBackgroundGradient(gfx);
		renderBorder(gfx);
		renderTitleBar(gfx);

		if (component) component->draw(gfx);

		std::string str = focused ? "true" : "false";
		gfx.drawString("Focused?: " + str, x - 10, y - 10);

		std::string strVis = visible ? "true" : "false";
		gfx.drawString("Visible?:" + strVis, x + 120, y - 10);
	}
}

void Window::updateMousePosition(int mouseX, int mouseY) {
	if(component) component->onMouseOver(mouseX, mouseY);
}

void Window::onClick(int mouseX, int mouseY) {
	using Input = PK2::Engine::Input;

	if (visible) {
		if (Input::mouseDown(Input::MB_LEFT)) {
			if (clickX == -1) clickX = Input::getMouseX();
			if (clickY == -1) clickY = Input::getMouseY();

			if (xPosAtClick == -1) xPosAtClick = x;
			if (yPosAtClick == -1) yPosAtClick = y;

			if (isOnCloseButton(clickX, clickY)) {
				visible = false;
				
				return;
			}

			if (isOnTitlebar(clickX, clickY)) {
				grabbed = true;
			}
		}

		// TODO I don't like that this is in here, because it's getting called every frame, instead of only when the mouse is moved or pressed. Should change this.
		int mb = -1;

		if (Input::mouseDown(Input::MB_LEFT)) {
			mb = Input::MB_LEFT;
		} else if (Input::mouseDown(Input::MB_MIDDLE)) {
			mb = Input::MB_MIDDLE;
		} else if (Input::mouseDown(Input::MB_RIGHT)) {
			mb = Input::MB_RIGHT;
		}

		if (component) component->onClick(mouseX, mouseY, mb);
	}
}

void Window::updateKeyboard(SDL_Scancode key, SDL_Keymod mod) {
	if (key == shortcutKey && mod == shortcutModifier) {
		if (responseDelay == 0) {
			if (!visible) {
				visible = true;
			} else {
				visible = false;
			}

			responseDelay = 15;
		}
	}

	if (component) component->onKeyDown(key, mod);
}

void Window::move(int newX, int newY) {
	int xOffset = clickX - xPosAtClick;
	int yOffset = clickY - yPosAtClick;

	int xPos = newX - xOffset;
	int yPos = newY - yOffset;

	x = xPos;
	y = yPos;

	keepInBounds();

	if (component) component->onMove(x, y + titlebarMiddle.h);
}

void Window::update() {
	if (responseDelay > 0) responseDelay--;
}

bool Window::isOnWindow(int xPos, int yPos) {
	return xPos >= x &&
		xPos <= x + width &&
		yPos >= y &&
		yPos <= y + height;
}

bool Window::isOnTitlebar(int grabX, int grabY) {
	return grabX >= x &&
		grabY >= y &&
		grabX <= x + width &&
		grabY <= y + titlebarMiddle.h;
}

bool Window::isOnCloseButton(int clickX, int clickY) {
	return clickX > x + width - 10 &&
		clickX < x + width &&
		clickY > y &&
		clickY < y + 16;
}

void Window::keepInBounds() {
	if (x < 0) x = 0;
	if (y < 0) y = 0;

	// This is how it's supposed to be, but the original editor does differently
	if (x + width >= screenWidth) x = screenWidth - width;
	if (y + height + titlebarMiddle.h >= screenHeight) y = screenHeight - height - titlebarMiddle.h;
	
	/*
	* 
	* TODO This is how the original editor does it, but it doesn't work in this version.
	* Should do the old behavior and figure out how to.
	* 
	if (x + width > screenWidth) {
		x -= (x + width) - screenWidth;
	}

	if (y + height + 16 > screenHeight) {
		y -= (y + 16 + screenHeight) - screenHeight;
	}*/
}

bool Window::isFocused() {
	return focused;
}

void Window::setFocused(bool focus) {
	this->focused = focus;

	if (component) {
		if (focus) {
			component->onWindowFocusGained();
		} else {
			component->onWindowFocusLost();
		}
	}
}

void Window::setGrabbed(bool grabbed) {
	this->grabbed = grabbed;

	clickX = -1;
	clickY = -1;

	xPosAtClick = -1;
	yPosAtClick = -1;
}

bool Window::isGrabbed() {
	return grabbed;
}

std::string_view Window::getTitle() const {
	return title;
}

void Window::setX(int x) {
	this->x = x;
}

int Window::getX() const {
	return x;
}

void Window::setY(int y) {
	this->y = y;
}

int Window::getY() const {
	return y;
}

int Window::getWidth() const {
	return width;
}

int Window::getHeight() const {
	return y;
}

void Window::setVisible(bool visible) {
	this->visible = visible;
}

bool Window::isVisible() const {
	return visible;
}

void Window::setBorderColor(SDL_Color borderCol) {
	borderColor = borderCol;
}

void Window::setEditorImageFile(const std::string& image) {
	editorImageFile = image;
}

void Window::setFont(PK2::Engine::Font& font) {
	Window::font = font;
}

void Window::setComponent(Component* c) {
	//if (component) delete this->component;

	c->updatePosition(x, y + titlebarMiddle.h);

	this->component = c;
}

void Window::setScreenSize(int width, int height) {
	screenWidth = width;
	screenHeight = height;
}

int Window::getResponseDelay() {
	return responseDelay;
}

void Window::setResponseDelay(int delay) {
	responseDelay = delay;
}

void Window::onKeyTyped(char c) {
	if (component) component->onKeyTyped(c);
}

std::string& Window::getEditorImageFile() {
	return editorImageFile;
}