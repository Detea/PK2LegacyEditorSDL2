#include "HelpMenu.h"
#include <iostream>

#include "VerticalLayout.h"
#include "Button.h"

HelpMenu::HelpMenu(std::string title, int x, int y, int width, int height, bool visible, SDL_Scancode shortcutKey, SDL_Keymod shortcutMod)
	: Window(title, x, y, width, height, visible, shortcutKey, shortcutMod) {
	setupUI();
}

HelpMenu::~HelpMenu() {
	
}

// TODO This can be deleted
void HelpMenu::render(PK2::Engine::GFX& gfx) {
	Window::render(gfx);
}

// TODO Put components into a vector of smart pointers and use Window::add(Component)
void HelpMenu::setupUI() {
	Label* lblHelp = new Label("f1 = help");
	Label* lblMap = new Label("f2 = map");
	Label* lblTilePalette = new Label("f3 = tile palette");
	Label* lblSprites = new Label("f4 = sprites");
	Label* lblLoadMap = new Label("f5 = load map/files");
	Label* lblSaveMap = new Label("f6 = save map");
	Label* lblMapInfo = new Label("f7 = map information");
	Label* lblClearMap = new Label("f8 = clear map");
	Label* lblQuickSave = new Label("s  = quick save ");
	Label* lblUndo = new Label("u  = undo ");
	Label* lblAnimateTiles = new Label("a  = animate moving tiles");
	Label* lblShift = new Label("shift = background / foreground");
	Label* lblDraw = new Label("mouse left  = draw");
	Label* lblRemove = new Label("mouse right = remove");
	Label* lblPaint = new Label("mouse left  = paint (map menu)");
	Label* lblGoto = new Label("mouse right = go to (map menu)");
	Label* lblSelectArea = new Label("alt + mouse = select area");
	Label* lblCopy = new Label("ctrl + c = copy");
	Label* lblPasteSimple = new Label("ctrl + b = paste simple");
	Label* lblPastePattern = new Label("ctrl + v = paste pattern");
	Label* lblCut = new Label("ctrl + x = cut");
	Label* lblScrollMap = new Label("arrows = scroll map");
	Label* lblExist = new Label("esc = exit");

	VerticalLayout* layout = new VerticalLayout(3, 20);
	layout->setSpacing(1);

	layout->add(lblHelp);
	layout->add(lblMap);
	layout->add(lblTilePalette);
	layout->add(lblSprites);
	layout->add(lblLoadMap);
	layout->add(lblSaveMap);
	layout->add(lblMapInfo);
	layout->add(lblClearMap);
	layout->add(lblQuickSave);
	layout->add(lblUndo);
	layout->add(lblAnimateTiles);
	layout->add(lblShift);
	layout->add(lblDraw);
	layout->add(lblRemove);
	layout->add(lblPaint);
	layout->add(lblGoto);
	layout->add(lblSelectArea);
	layout->add(lblCopy);
	layout->add(lblPasteSimple);
	layout->add(lblPastePattern);
	layout->add(lblCut);
	layout->add(lblScrollMap);
	layout->add(lblExist);

	component = new Component();
	setComponent(component);

	component->addLayout(layout);
}