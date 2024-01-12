#pragma once
#include "Window.h"
#include "Label.h"

#include <string>

class HelpMenu : public Window {
public:
	HelpMenu(std::string title,
			 int x, int y,
			 int width, int height,

			 bool visible,

			 SDL_Scancode shortcutKey = PK2::Engine::Input::KEY_NONE,
			 SDL_Keymod shortcutMod = PK2::Engine::Input::MOD_NONE);

	virtual ~HelpMenu();

	virtual void render(PK2::Engine::GFX& gfx) override;

private:
	void setupUI();

private:
	Label* lblHelp;
	Label* lblMap;
	Label* lblTilePalette;
	Label* lblSprites;
	Label* lblLoadMap;
	Label* lblSaveMap;
	Label* lblMapInfo;
	Label* lblClearMap;
	Label* lblQuickSave;
	Label* lblUndo;
	Label* lblAnimateTiles;
	Label* lblShift;
	Label* lblDraw;
	Label* lblRemove;
	Label* lblPaint;
	Label* lblGoto;
	Label* lblSelectArea;
	Label* lblCopy;
	Label* lblPasteSimple;
	Label* lblPastePattern;
	Label* lblCut;
	Label* lblScrollMap;
	Label* lblExist;
};

