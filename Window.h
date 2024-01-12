#pragma once
#include <string>
#include <string_view>
#include <vector>

#include "GFX.h"
#include "Font.h"
#include "Component.h"
#include "Input.h"

// TODO Cleanup: remove this
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif


/*
	This class represents the "MENU" struct in the original level editor code.
*/
class Window {
public:
	// TODO Creating a window without setting it's component will probably crash, because then component == nullptr
	Window(std::string title, 
		   int x, int y, 
		   int width, int height, 
		   
		   bool visible, 

		   SDL_Scancode shortcutKey = PK2::Engine::Input::KEY_NONE, 
		   SDL_Keymod shortcutMod = PK2::Engine::Input::MOD_NONE);

	virtual ~Window();

	std::string_view getTitle() const;

	void setX(int x);
	int getX() const;
	
	void setY(int y);
	int getY() const;

	int getWidth() const;
	int getHeight() const;

	void setVisible(bool visible);
	bool isVisible() const;

	void setFocused(bool focus);
	bool isFocused();

	void setGrabbed(bool grabbed);
	bool isGrabbed();

	/*
		Sets the window's component.
		
		Once the component is set it belongs to the window and the window will take care of deleting it.
		Calling this method will also delete the previosuly set component.
	*/
	void setComponent(Component* c);

	virtual void render(PK2::Engine::GFX& gfx);
	virtual void updateMousePosition(int mouseX, int mouseY);

	virtual void updateKeyboard(SDL_Scancode key, SDL_Keymod mod);
	virtual void onKeyTyped(char c);

	static void update();

	static void setBorderColor(SDL_Color borderColor);

	static void setEditorImageFile(const std::string& image);
	static std::string& getEditorImageFile();

	// Only having one font is limiting, but it'll do for this project
	static void setFont(PK2::Engine::Font& font);

	static void setScreenSize(int width, int height);

	// TODO Separate this into onWindowClick and onTitlebarClick?
	// Important: When you override this method in a derived class, you need to call Window::onClick(), because this method handles part of moving/closing of a window.
	virtual void onClick(int clickX, int clickY);

	// Returns true if the x and y positions lie within the titlebar bounds
	bool isOnTitlebar(int x, int y);

	// Returns true if the user clicks on the x in the titlebar.
	bool isOnCloseButton(int x, int y);

	// Returns true if position x,y in within the window, titlebar included.
	bool isOnWindow(int x, int y);

	void move(int newX, int newY);

	// TODO I don't like this implementation, there should be a better way to do this, but it'll do for now.
	static int getResponseDelay();
	static void setResponseDelay(int delay);

private:
	void renderTitleBar(PK2::Engine::GFX& gfx);
	void renderBorder(PK2::Engine::GFX& gfx);
	void renderBackgroundGradient(PK2::Engine::GFX& gfx);

	void keepInBounds();

protected:
	// keyDelay in the original level editor
	inline static int responseDelay = 0;

	std::string title;

	inline static int screenWidth = 0;
	inline static int screenHeight = 0;

	int x = 0;
	int y = 0;

	int clickX = -1;
	int clickY = -1;
	int xPosAtClick = -1;
	int yPosAtClick = -1;

	int width = 0;
	int height = 0;

	bool visible = true;

	SDL_Scancode shortcutKey;
	SDL_Keymod shortcutModifier;

	bool focused = false;	// Is this the selected window?
	bool grabbed = false;	// Is the user clicking and dragging the window?

	// Color in the color palette
	static constexpr int GRADIENT_COLOR = 32;
	static constexpr int GRADIENT_SEGMENTS = 6;

	// Default border color is black
	inline static SDL_Color borderColor = { 0, 0, 0, 0xFF };

	static constexpr SDL_Rect TITLEBAR_LEFT_SIDE = { 1, 1, 4, 16 };
	static constexpr SDL_Rect TITLEBAR_RIGHT_SIDE = { 311, 1, 12, 16 };
	SDL_Rect titlebarMiddle = { 6, 1, 0, 0 };

	static PK2::Engine::Font font;

	Component* component = nullptr;

private:
	static std::string editorImageFile;
	// TOOL_List
};

