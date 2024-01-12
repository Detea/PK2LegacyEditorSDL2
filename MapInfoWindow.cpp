#include "MapInfoWindow.h"
#include "Button.h"
#include "Component.h"
#include "VerticalLayout.h"
#include "ArrowsButton.h"

MapInfoWindow::MapInfoWindow(std::string title, int x, int y, int width, int height, bool visible, SDL_Scancode shortcutKey, SDL_Keymod shortcutMod)
	: Window(title, x, y, width, height, visible, shortcutKey, shortcutMod) {
	setupUI();
}

MapInfoWindow::~MapInfoWindow() {

}

// TODO Reorginize and clean this code up, make it more readable
// TODO it'd be best if no absolute positioning would be used, so that the components positions can be more dynamic, but it'll do for now.
void MapInfoWindow::setupUI() {
	Label* lblVersion = new Label("version");
	lblVersionStr = new Label("", 3 + lblVersion->getWidth() + 16, 19);

	Label* lblName = new Label("name:");
	Label* lblFileName = new Label("file name:");
	Label* lblAuthor = new Label("creator:");
	Label* lblTileset = new Label("tile picture:");
	Label* lblBackground = new Label("background picture:");
	Label* lblMusic = new Label("background music:");

	Component* comp = new Component();
	setComponent(comp);

	// TODO Again, use layouts for this... eventhough the UI seems kinda too messy for that, but whatever
	lblTilesetVal = new Label("", 3 + lblTileset->getWidth() + 16, 67);
	lblBackgroundVal = new Label("", 3 + lblBackground->getWidth() + 16, 79);

	tfMusicFile = new TextField("", 12, 3 + lblMusic->getWidth() + 16, 91);

	tfMapName = new TextField(16);
	tfFilename = new TextField(12);
	tfAuthor = new TextField(29);

	VerticalLayout* layoutValues = new VerticalLayout(83, 31);
	layoutValues->setSpacing(2);
	layoutValues->add(tfMapName);
	layoutValues->add(tfFilename);
	layoutValues->add(tfAuthor);

	VerticalLayout* layout = new VerticalLayout(3, 19);
	layout->setSpacing(4);
	layout->add(lblVersion);
	layout->add(lblName);
	layout->add(lblFileName);
	layout->add(lblAuthor);
	layout->add(lblTileset);
	layout->add(lblBackground);
	layout->add(lblMusic);

	// Display "level:" label, the map's level number and the arrow button
	Label* lblLevel = new Label("Level:", 3, 103);
	lblLevelNrVal = new Label("", lblLevel->getWidth() + 3 + 16, 103);
	ArrowsButton* abLevelNr = new ArrowsButton(108, 103, ArrowsButton::Orientation::HORIZONTAL);
	
	comp->addComponent(lblLevel);
	comp->addComponent(lblLevelNrVal);
	comp->addComponent(abLevelNr);

	// Display "time:" label, the map time and the arrow button 
	Label* lblTime = new Label("time:", 3, 125);
	lblTimeVal = new Label("", 3 + lblTime->getWidth() + 16, 125);

	ArrowsButton* abTime = new ArrowsButton(108, 125, ArrowsButton::Orientation::HORIZONTAL);
	
	comp->addComponent(lblTime);
	comp->addComponent(lblTimeVal);
	comp->addComponent(abTime);

	// Display "background scrolling:" label and the scrolling type button
	Label* lblBGScrolling = new Label("background scrolling:", 3, 141);
	btnScrolling = new Button("", 3 + lblBGScrolling->getWidth() + 16, 141);
	btnScrolling->setAction([this]() {
		newScrollingValue++;

		// A pretty clever way to keep the value in bounds. Props to Janne!
		newScrollingValue %= 4; // TODO Don't hardcode this value

		btnScrolling->setText(getScrollingDescription(newScrollingValue));
	});

	comp->addComponent(lblBGScrolling);
	comp->addComponent(btnScrolling);

	// Display "special:" label and the weather type button
	Label* lblWeather = new Label("special:", 3, 157);
	btnWeather = new Button("", 3 + lblWeather->getWidth() + 16, 157);
	btnWeather->setAction([this]() {
		newWeatherValue++;

		newWeatherValue %= 5; // TODO Don't hardcode this

		btnWeather->setText(getWeatherDescription(newWeatherValue));
	});

	comp->addComponent(lblWeather);
	comp->addComponent(btnWeather);
	
	// TODO use the map->time, weather, etc. value instead of new...?

	// Display "map icon:" label, the map icon value and the arrows button
	Label* lblMapIcon = new Label("map icon:", 3, 176);
	lblMapIconVal = new Label("", 3 + lblMapIcon->getWidth() + 16, 176);
	ArrowsButton* abMapIcon = new ArrowsButton(118, 176, ArrowsButton::Orientation::HORIZONTAL);

	// TODO Add functionality to abMapIcon

	comp->addComponent(lblMapIcon);
	comp->addComponent(lblMapIconVal);
	comp->addComponent(abMapIcon);

	// Display "map x:" label, the level's x position on the map and the arrows button
	Label* lblMapX = new Label("map x:", 3, 192);
	lblMapXVal = new Label("", lblMapX->getWidth() + 9, 192);
	ArrowsButton* abMapX = new ArrowsButton(100, 192, ArrowsButton::Orientation::HORIZONTAL);
	
	// TODO Add functionality to arrows
	comp->addComponent(lblMapX);
	comp->addComponent(lblMapXVal);
	comp->addComponent(abMapX);

	// Display "map y:" label, the level's y position on the map and the arrows button
	Label* lblMapY = new Label("map y:", 3 + 150, 192);
	lblMapYVal = new Label("", lblMapY->getWidth() + 9 + 150, 192);
	ArrowsButton* abMapY = new ArrowsButton(100 + 150, 192, ArrowsButton::Orientation::HORIZONTAL);

	// TODO Add functionality to arrows
	comp->addComponent(lblMapY);
	comp->addComponent(lblMapYVal);
	comp->addComponent(abMapY);

	comp->addComponent(lblVersionStr);
	comp->addComponent(lblTilesetVal);
	comp->addComponent(lblBackgroundVal);
	comp->addComponent(tfMusicFile);
	comp->addLayout(layout);
	comp->addLayout(layoutValues);
}

void MapInfoWindow::setMap(PK2::Game::Map* currentMap, std::string_view filename) {
	map = currentMap;

	mapFilename = filename;

	if (map) {
		lblVersionStr->setText(map->getVersionString());

		tfMapName->setText(map->getName());
		tfFilename->setText(filename); // TODO Check when this actually gets set
		tfAuthor->setText(map->getAuthor());

		lblTilesetVal->setText(map->getFileTileset());
		lblBackgroundVal->setText(map->getFileBackground());

		tfMusicFile->setText(map->getFileMusic());

		lblLevelNrVal->setText(std::to_string(map->getLevelNr()));

		// TODO Put this into it's own function?
		std::string timeStr = "";
		int minutes = map->getTime() / 60;
		int seconds = map->getTime() % 60;

		if (minutes < 10) {
			timeStr += "0";
		}

		timeStr += std::to_string(minutes);

		timeStr += ":";

		if (seconds < 10) {
			timeStr += "0";
		}

		timeStr += std::to_string(seconds);

		lblTimeVal->setText(timeStr);

		newScrollingValue = map->getScrolling();
		newWeatherValue = map->getWeather();

		btnScrolling->setText(getScrollingDescription(newScrollingValue));
		btnWeather->setText(getWeatherDescription(newWeatherValue));

		lblMapIconVal->setText(std::to_string(map->getMapIcon() + 1));
		lblMapXVal->setText(std::to_string(map->getMapX()));
		lblMapYVal->setText(std::to_string(map->getMapY()));
	}
}

std::string MapInfoWindow::getScrollingDescription(int scrolling) {
	// TODO Don't hardcode the max scrolling value
	if (scrolling >= 0 && scrolling < 4) {
		return scrollingDescriptions[scrolling];
	}

	return "Invalid";
}

std::string MapInfoWindow::getWeatherDescription(int weather) {
	// TODO Don't hardcode max weather amount value
	if (weather >= 0 && weather < 5) {
		return weatherDescriptions[weather];
	}

	return "Invalid";
}