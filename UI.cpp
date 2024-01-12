#include "UI.h"
#include "Input.h"

UI::UI() {

}

UI::~UI() {
	for (Window* w : windows) {
		delete w;
		w = nullptr;
	}
}

void UI::addWindow(Window* w) {
	windows.push_back(w);

	activeWindow = w; // TODO Not sure if this is a good idea, this might cause trouble?
}

void UI::render(PK2::Engine::GFX& gfx) {
	for (Window* w : windows) {
		if (w->isVisible() && w != activeWindow) w->render(gfx);
	}
	
	// Render the active window infront of all the others
	if (activeWindow) {
		if (activeWindow->isVisible()) {
			activeWindow->render(gfx);
		}
	}
}

void UI::updateMouse(int mouseX, int mouseY) {
	using Input = PK2::Engine::Input;
	
	for (Window* w : windows) {
		if (w->isVisible()) {
			if (w->isOnWindow(mouseX, mouseY)) {
				if (!activeWindow) {
					w->setFocused(true);
					activeWindow = w;

					break;
				} else {
					if (!activeWindow->isGrabbed() && !activeWindow->isOnWindow(mouseX, mouseY)) {
						activeWindow->setFocused(false);

						w->setFocused(true);
						activeWindow = w;

						break;
					}
				}
			} else {
				w->setFocused(false);
			}
		}
	}

	if (activeWindow) {
		if (Input::anyMouseDown()) {
			if (activeWindow->isGrabbed()) {
				activeWindow->move(mouseX, mouseY);
			} else {
				activeWindow->onClick(mouseX, mouseY);
			}
		} else{
			activeWindow->setGrabbed(false);
		}

		if (activeWindow->isOnWindow(mouseX, mouseY)) {
			activeWindow->setFocused(true);
		} else {
			activeWindow->setFocused(false);
		}
		activeWindow->updateMousePosition(mouseX, mouseY);
	}
}

void UI::updateKeyboard(SDL_Scancode key, SDL_Keymod mod) {
	for (Window* w : windows) {
		w->updateKeyboard(key, mod);
	}
}

// TODO Delete this?
void UI::handleTitlebar(Window* window, int clickX, int clickY) {
	if (!activeWindow->isGrabbed()) {
		if (window->isOnTitlebar(clickX, clickY)) {
			if (window != activeWindow) {
				activeWindow->setFocused(false);
				activeWindow->setGrabbed(false);
				
				window->setFocused(true);
				window->setGrabbed(true);

				// Once the activeWindow has been set the loop should stop/return
				// because this causes issues when multiple windows are overlapping
				activeWindow = window;
			}
		} else {
			window->setFocused(false);
			window->setGrabbed(false);
		}

		if (window->isOnCloseButton(clickX, clickY)) {
			window->setVisible(false);
		}
	}
}

void UI::onKeyTyped(char c) {
	if (activeWindow) activeWindow->onKeyTyped(c);
}