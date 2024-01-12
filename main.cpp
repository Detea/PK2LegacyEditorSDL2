#include <SDL.h>

#include "GFX.h"
#include "PisteLanguage.h"
#include "PisteFontAttributes.h"
#include "Files.h"
#include "Logger.h"

#include "LevelEditor.h"

#include "Input.h"

int main(int argc, char* argv[]) {
	PK2::Engine::Files::setGamePath(R"(D:\Downloads\PK2_1.4.3\)");

	PK2::Engine::GFX gfx("PK2 Level Editor SDL2", 1024, 768);

	LevelEditor levelEditor;
	levelEditor.init(gfx);

	SDL_Event e;
	bool quit = false;

	while (!quit) {
		SDL_PollEvent(&e);

		Uint64 start = SDL_GetPerformanceCounter();

		switch (e.type) {
			case SDL_QUIT:
				quit = true;
				break;
			
			// TODO do levelEditor.keyPressed & levelEditor.keyReleased
			case SDL_KEYUP: [[fallthrough]];
			case SDL_KEYDOWN: {
					levelEditor.keyPressed(e.key.keysym.scancode, e.key.keysym.mod);
				}
				break;

			case SDL_MOUSEBUTTONDOWN: [[fallthrough]];
			case SDL_MOUSEBUTTONUP: [[fallthrough]];
			case SDL_MOUSEMOTION:
				{
					using namespace PK2::Engine;

					Uint32 mouseButton = SDL_GetMouseState(Input::getMouseXPointer(), Input::getMouseYPointer());
					Input::updateMouseButton(mouseButton);
				}
				break;

			case SDL_TEXTINPUT:
				levelEditor.onKeyTyped(e.text.text[0]);
				break;
		}

		PK2::Engine::Input::updateKeymod(SDL_GetModState());
		PK2::Engine::Input::keyStates = SDL_GetKeyboardState(nullptr);

		levelEditor.update();

		gfx.clear();
		levelEditor.render(gfx);
		gfx.render();

		Uint64 end = SDL_GetPerformanceCounter();

		//float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.f;

		// TODO This sometimes might cause the game to freeze, find a better way to cap the framerate
		// TODO Gonna do 60 fps for now, not sure exactly about the framerate of the original editor
		//SDL_Delay(floor(16.666f - elapsed));
	}

	SDL_Quit();

	return 0;
}