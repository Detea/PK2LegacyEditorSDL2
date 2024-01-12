#include "FileListWindow.h"

#include "Component.h"
#include "Separator.h"
#include "VerticalLayout.h"
#include "Logger.h"

FileListWindow::FileListWindow(std::string title, int x, int y, int width, int height, bool visible, SDL_Scancode shortcutKey, SDL_Keymod shortcutMod)
	: Window(title, x, y, width, height, visible, shortcutKey, shortcutMod) {
	setupUI();
}

FileListWindow::~FileListWindow() {

}

void FileListWindow::scrollFileListUp() {
	PK2::Engine::Logger::info("Scroll file list up...");
}

void FileListWindow::scrollFileListDown() {
	PK2::Engine::Logger::info("Scroll file list down...");
}

void FileListWindow::setupUI() {
	Component* c = new Component();
	setComponent(c);

	btnSave = new Button("save   ", width - 96, 2);

	btnMaps = new Button("maps   ");
	btnTiles = new Button("tiles  ");
	btnSprites = new Button("sprites");
	btnScenery = new Button("scenery");
	btnMusic = new Button("music  ");

	btnHideDirectories = new Button("hide dirs", width - 96, 110);

	fileListView = new FileBrowser("", x, y);

	btnTiles->setAction([&]() {
		fileListView->setCurrentPath(contentPaths.getTiles());
	});

	btnSprites->setAction([&]() {
		fileListView->setCurrentPath(contentPaths.getSprites());
	});

	btnScenery->setAction([&]() {
		fileListView->setCurrentPath(contentPaths.getBackgrounds());
	});

	// TODO maps & music

	VerticalLayout* layout = new VerticalLayout(width - 96, 24);
	layout->setSpacing(2);
	layout->add(btnMaps);
	layout->add(btnTiles);
	layout->add(btnSprites);
	layout->add(btnScenery);
	layout->add(btnMusic);

	Separator* sepVertical = new Separator(width - 102, 0, 300, Separator::Orientation::VERTICAL, SEPARATOR_COLOR);
	
	// This second separator should have a width of 100, but with this code it's 1 pixel to long. No idea why. Might be the line drawing algorithm or I missed something?
	Separator* sepHorizontal = new Separator(width - 102, 20, 99, Separator::Orientation::HORIZONTAL, SEPARATOR_COLOR);

	scrollButton = new ArrowsButton(width - 15, height - 30);
	scrollButton->setScrollUpAction(std::bind(&FileListWindow::scrollFileListUp, this));
	scrollButton->setScrollDownAction(std::bind(&FileListWindow::scrollFileListDown, this));
	
	c->addComponent(btnSave);
	c->addLayout(layout);
	c->addComponent(btnHideDirectories);

	c->addComponent(sepVertical);
	c->addComponent(sepHorizontal);

	c->addComponent(scrollButton);

	c->addComponent(fileListView);
}

void FileListWindow::setContentPaths(PK2::Game::ContentPaths& paths) {
	contentPaths = paths;

	PK2::Engine::Logger::info("base path:");
	PK2::Engine::Logger::info(contentPaths.getBase());

	fileListView->setCurrentPath(contentPaths.getBase());
}