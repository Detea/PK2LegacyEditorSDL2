#pragma once
#include "Window.h"
#include "LogEntry.h"

#include <vector>

class LogWindow : public Window {
public:
	using Window::Window;

	virtual ~LogWindow();

	virtual void render(PK2::Engine::GFX& gfx) override;

	void update(std::vector<PK2::Engine::LogEntry>* entries);

private:
	static constexpr int RECT_OFFSET_X = 3;
	static constexpr int RECT_OFFSET_Y = 6;

	static constexpr int RECT_WIDTH = 4;
	static constexpr int RECT_HEIGHT = 4;

	static constexpr int RECT_COLOR_ERROR = 84;
	static constexpr int RECT_COLOR_INFO = 116;

	std::vector<PK2::Engine::LogEntry>* logEntries;
};

