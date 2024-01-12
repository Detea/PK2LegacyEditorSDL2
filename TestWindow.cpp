#include "TestWindow.h"
#include "Button.h"
#include "Component.h"
#include "VerticalLayout.h"
#include "TextField.h"
#include "Link.h"

#include "Logger.h"

TestWindow::TestWindow(std::string title, int x, int y, int width, int height, bool visible, SDL_Scancode shortcutKey, SDL_Keymod shortcutMod)
	: Window(title, x, y, width, height, visible, shortcutKey, shortcutMod) {
	setupUI();
}

TestWindow::~TestWindow() {

}

void TestWindow::setupUI() {
	Label* lbl = new Label("TextField Test:");
	TextField* tf = new TextField("Test field", 20);
	TextField* tf2 = new TextField("Backup.map", 40);
	TextField* tf3 = new TextField("testasdasdasd", 10);

	Link* linkTest = new Link("Test link");
	linkTest->setAction([]() {
		PK2::Engine::Logger::info("link test clicked!");
	});

	arrowsVertical = new ArrowsButton(0, 0);
	arrowsHorizontal = new ArrowsButton(0, 0, ArrowsButton::Orientation::HORIZONTAL);

	using Logger = PK2::Engine::Logger;

	arrowsVertical->setScrollUpAction([]() {
									  Logger::info("Up vertical");
									  });

	arrowsVertical->setScrollDownAction([]() {
		Logger::info("Down vertical");
										});

	arrowsHorizontal->setScrollUpAction([]() {
		Logger::info("Up Horizontal");
										});

	arrowsHorizontal->setScrollDownAction([]() {
		Logger::info("Down Horizontal");
										  });

	VerticalLayout* layout = new VerticalLayout(2, 2);
	layout->setSpacing(5);
	layout->add(lbl);
	layout->add(tf);
	layout->add(tf2);
	layout->add(tf3);
	layout->add(linkTest);

	layout->add(arrowsVertical);
	layout->add(arrowsHorizontal);

	Component* comp = new Component();
	setComponent(comp);

	comp->addLayout(layout);
}