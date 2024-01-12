#include "FileBrowser.h"
#include "VerticalLayout.h"
#include "Logger.h"

#include <iostream>

FileBrowser::FileBrowser(std::string_view initialPath, int x, int y) : Component(x, y) {
	currentPath.assign(initialPath);

	width = 200;
	height = 33 * 9;

	addFilter(".bmp");
	addFilter(".map");
	addFilter(".spr");
	// TODO Add music, etc.

	setupUI();
}

FileBrowser::~FileBrowser() {}

void FileBrowser::setupUI() {
	VerticalLayout* layout = new VerticalLayout(5, 3);
	layout->setSpacing(1);

	for (int i = 0; i < MAX_FILES_DISPLAYED; i++) {
		Link* link = new Link("");
		link->setAction([this, i]() {
			onLinkClick(i);

			PK2::Engine::Logger::info(getSelectedFile());
		});

		layout->add(link);

		pathLinks.push_back(link);
	}

	addLayout(layout);

	VerticalLayout* arrowLayout = new VerticalLayout(5, 3);
	arrowLayout->setSpacing(2);
	for (int i = 0; i < MAX_FILES_DISPLAYED; i++) {
		// TODO Don't hardcode this image file
		Image* img = new Image("PK2EDIT.bmp", 0, 0, 338, 1, 8, 7);
		img->setVisible(false);

		arrowLayout->add(img);

		directoryArrowImages.push_back(img);
	}

	addLayout(arrowLayout);
}

std::string FileBrowser::getSelectedFile() {
	return selectedFile.generic_string();
}
 
void FileBrowser::onClick(int mouseX, int mouseY, int mouseButton) {
	for (Component* c : components) {
		if (c->positionInBounds(mouseX, mouseY)) {
			c->onClick(mouseX, mouseY, mouseButton);
		}
	}
}

void FileBrowser::onLinkClick(int linkNumber) {
	using Logger = PK2::Engine::Logger;

	// TODO Clicking on a path/link sometimes freezes the program?

	if (linkNumber == 0) {
		setCurrentPath(std::filesystem::current_path().string());
	} else if (linkNumber == 1) {
		setCurrentPath(currentPath.parent_path().string());
	}

	if (linkNumber >= 2 && linkNumber < currentDirectoryPaths.size()) {
		if (!std::filesystem::is_directory(currentDirectoryPaths[linkNumber])) {
			// TODO hard code this shit...

			std::string extension = currentDirectoryPaths[linkNumber].extension().string();

			if (extension == ".bmp") {
				Logger::info("Set tileset");
			} else if (extension == ".spr") {
				Logger::info("set sprite");
			} else if (extension == ".map") {
				Logger::info("Set map");
			} // TOOD music
		} else {
			setCurrentPath(currentDirectoryPaths[linkNumber].string());
		}
	}
}

void FileBrowser::setCurrentPath(std::string_view path) {
	currentPath.assign(path);

	std::filesystem::current_path(currentPath);

	currentDirectoryPaths.clear();

	currentDirectoryPaths.push_back(std::filesystem::path("."));
	currentDirectoryPaths.push_back(std::filesystem::path(".."));

	for (auto const& dir_entry : std::filesystem::directory_iterator(currentPath)) {
		if (dir_entry.is_directory()) {
			currentDirectoryPaths.push_back(dir_entry.path());
		} else {
			for (const std::string& extension : fileFilter) {
				if (dir_entry.path().extension().string() == extension) {
					currentDirectoryPaths.push_back(dir_entry.path());
				}
			}
		}
	}

	size_t directoryAmount = currentDirectoryPaths.size();

	if (directoryAmount < MAX_FILES_DISPLAYED) {
		for (size_t i = 0; i < directoryAmount; i++) {
			pathLinks[i]->setText(currentDirectoryPaths[i].filename().string());
			pathLinks[i]->setVisible(true);

			if (std::filesystem::is_directory(currentDirectoryPaths[i])) {
				directoryArrowImages[i]->setVisible(true);

				pathLinks[i]->setRelativeX(15);
			} else {
				directoryArrowImages[i]->setVisible(false);
				
				pathLinks[i]->setRelativeX(5);
			}

			// TODO probably need to update the position of the links here... or something
		}

		for (size_t i = directoryAmount; i < MAX_FILES_DISPLAYED; i++) {
			pathLinks[i]->setText("");
			pathLinks[i]->setVisible(false);

			directoryArrowImages[i]->setVisible(false);
			
			pathLinks[i]->setRelativeX(15);
		}
	}
}

void FileBrowser::addFilter(std::string extension) {
	fileFilter.push_back(extension);
}