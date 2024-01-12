#include "LevelEditor.h"
#include "HelpMenu.h"
#include "MapInfoWindow.h"
#include "TestWindow.h"
#include "FileListWindow.h"

#include "Input.h"

#include "Logger.h"

#include "Map.h"
#include "MapReader.h"
#include "MapReader13.h"

#include <functional>
#include <iostream>
#include <fstream>

LevelEditor::LevelEditor() {
	PK2::Engine::Logger::addOutputTarget(&stdLogOut);
	PK2::Engine::Logger::addOutputTarget(&leOutput);
}

LevelEditor::~LevelEditor() {
	
}

void LevelEditor::onLog() {
	if(logWindow) logWindow->update(leOutput.getEntries());
}

void LevelEditor::init(PK2::Engine::GFX& gfx) {
	leOutput.setOnWriteFunction(std::bind(&LevelEditor::onLog, this));

	using PK_FILES = PK2::Engine::Files;
	using Logger = PK2::Engine::Logger;

	editorGFXFile = "PK2EDIT.bmp";
	/*
		The font image should be loaded by loadFont shouldn't it?

		I'm doing this here, because I needed the palette of the image anyway, I think?
	*/
	gfx.loadImage(editorGFXFile.c_str(), true);
	gfx.loadFont("LatinEditor.txt", "editorFont");

	gfx.setCurrentFont("editorFont");

	gfx.setClearColor(gfx.getColorInBackgroundPalette(BACKGROUND_COLOR));

	Component::setFont(gfx.getCurrentFont());

	Window::setEditorImageFile(editorGFXFile);
	Window::setFont(gfx.getFont("editorFont"));
	Window::setScreenSize(gfx.getScreenWidth(), gfx.getScreenHeight());

	createWindows();
	loadPK2Path();

	fileListWindow->setContentPaths(contentPaths);

	// TODO Update when window size changes?
	camera.x = 0;
	camera.y = 0;
	camera.width = gfx.getScreenWidth();
	camera.height = gfx.getScreenHeight();

	miniMapWindow->setCamera(&camera);

	// TODO Fade in fast: PisteDraw_Fade_Paletti_In(PD_FADE_NOPEA);

	Logger::info("Created windows");
	Logger::info("init done");

	loadMap(R"(D:\PK2_1.4.3\episodes\rooster island 1\level001.map)");

	// TODO This should be done in the load map method
	std::string ts = std::string(loadedMap.getFileTileset());
	fileTileset = contentPaths.getFileTileset(ts);
	gfx.loadImage(fileTileset);

	fileBackground = contentPaths.getFileBackground(std::string(loadedMap.getFileBackground()));
	gfx.loadImage(fileBackground, true);

	mapRenderer.setMap(loadedMap);
	mapRenderer.setImageTileset(fileTileset);
	mapRenderer.setImageBackground(fileBackground);

	tilesetWindow->setTilesetImage(fileTileset);

	// TODO TESTING ONLY!!!
	mapInfoWindow->setMap(&loadedMap, "level001.map");
}

void LevelEditor::loadPK2Path() {
	using Logger = PK2::Engine::Logger;

	Logger::info("loading pk2le_dir.ini");

	std::ifstream in(PK2_INI_FILE.data(), std::ios::in);

	if (!in) {
		Logger::error("no pk2le_dir.ini found.");

		std::string programPath = std::filesystem::current_path().string();
		
		contentPaths.setBase(programPath);
	} else {
		char path[255];

		in.read(path, sizeof(path)); // sizeof path * sizeof char?
		
		if (!in) {
			Logger::error("loading pk2le_dir.ini failed.");

			std::string programPath = std::filesystem::current_path().string();

			if (!contentPaths.setBase(programPath)) {
				Logger::error("Unable to set base path");
			}
		} else {
			if (contentPaths.setBase(path)) {
				std::filesystem::current_path(contentPaths.getBase());

				Logger::info("Loaded pk2 path: ");
				Logger::info(contentPaths.getBase());
				Logger::info(contentPaths.getTiles());
				Logger::info(contentPaths.getBackgrounds());
				Logger::info(contentPaths.getSprites());
			} else {
				Logger::info("Unable to load PK2 path");
			}
		}
	}
}

void LevelEditor::loadMap(std::string_view filename) {
	mapReader->read(loadedMap, filename); // TODO Should probably return a bool
	
	// TODO This seems kinda hacky, maybe find a better solution to this
	if (mapInfoWindow) {
		std::filesystem::path mapFilePath = filename;
		
		mapInfoWindow->setMap(&loadedMap, mapFilePath.filename().string());
	}

	if (miniMapWindow) {
		miniMapWindow->setLayers(loadedMap.getTileLayers());
		miniMapWindow->setSpritesLayer(loadedMap.getSpritesLayer());

		SDL_Surface* surface = SDL_LoadBMP(contentPaths.getFileTileset(loadedMap.getFileTileset()).c_str());
		
		miniMapWindow->setTilesetPixels(surface->pixels, surface->w);

		SDL_FreeSurface(surface);
	}
}

std::string_view LevelEditor::getPK2Path() {
	return pk2Path;
}

void LevelEditor::update() {
	using Input = PK2::Engine::Input;

	ui.updateMouse(Input::getMouseX(), Input::getMouseY());

	Window::update(); // TODO this should probably be in UI?
}

void LevelEditor::keyPressed(SDL_Scancode key, Uint16 mod) {
	SDL_Keymod m = SDL_Keymod::KMOD_NONE;

	// TODO Implement more keymods? I think these are the only ones needed
	if (mod & SDL_Keymod::KMOD_CTRL) {
		m = SDL_Keymod::KMOD_CTRL;
	} else if (mod & SDL_Keymod::KMOD_ALT) {
		m = SDL_Keymod::KMOD_ALT;
	} else if (mod & SDL_Keymod::KMOD_SHIFT) {
		m = SDL_Keymod::KMOD_SHIFT;
	}

	ui.updateKeyboard(key, m);

	using Logger = PK2::Engine::Logger;
	if (key == SDL_Scancode::SDL_SCANCODE_I) {
		Logger::info("Logging info");
	} else if (key == SDL_Scancode::SDL_SCANCODE_E) {
		Logger::error("Logging error");
	}
}

void LevelEditor::onKeyTyped(char c) {
	ui.onKeyTyped(c);
}

void LevelEditor::render(PK2::Engine::GFX& gfx) {
	mapRenderer.drawBackground(gfx, 0, 0);
	mapRenderer.drawTileLayer(gfx, 0, camera.x * 32, camera.y * 32, camera.x * 32 + camera.width, camera.y * 32 + camera.height);
	mapRenderer.drawTileLayer(gfx, 1, camera.x * 32, camera.y * 32, camera.x * 32 + camera.width, camera.y * 32 + camera.height);

	ui.render(gfx);

	std::string pos = "X: ";
	pos += std::to_string(camera.x);
	pos += " Y: ";
	pos += std::to_string(camera.y);

	gfx.drawString(pos, 10, 10);
}

void LevelEditor::createWindows() {
	using Input = PK2::Engine::Input;

	mapInfoWindow = new MapInfoWindow("map information (f7)", 150, 40, 320, 240, true, SDL_Scancode::SDL_SCANCODE_F7, Input::MOD_NONE);

	// TODO Should probably put the "visible" parameter at the end of the constructor, because SDL_Scancode can be converted to bool. Or make constructor explicit? Would that work?
	ui.addWindow(new HelpMenu("help    (f1)", 192, 120, 256, 240, false, SDL_Scancode::SDL_SCANCODE_F1, Input::MOD_NONE));
	ui.addWindow(mapInfoWindow);
	ui.addWindow(new TestWindow("TestWindow", 800, 600, 256, 240, true, SDL_Scancode::SDL_SCANCODE_F2, Input::MOD_NONE));
	
	logWindow = new LogWindow("log     (f9)", 222, 110, 320, 500, false, SDL_Scancode::SDL_SCANCODE_F9);
	ui.addWindow(logWindow);

	// TODO Rewrite FileListWindow
	fileListWindow = new FileListWindow("files   (f5)", 192, 40, 320, 300, true, SDL_Scancode::SDL_SCANCODE_F5);
	// This seems to be the cause of the freezing
	//ui.addWindow(fileListWindow);

	tilesetWindow = new TilesetWindow("tiles   (f3)", 592, 145, 320, 480, true, SDL_Scancode::SDL_SCANCODE_F3);
	ui.addWindow(tilesetWindow);

	miniMapWindow = new MiniMapWindow("map     (f2)", 492, 130, 256, 224, true, SDL_Scancode::SDL_SCANCODE_F2);
	ui.addWindow(miniMapWindow);
}