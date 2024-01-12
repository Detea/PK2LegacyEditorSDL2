#include "LogWindow.h"
#include "LogEntry.h"

using namespace PK2::Engine;

LogWindow::~LogWindow() {

}

// Should probably create a component with labels and what ever, but I'm lazy right now
void LogWindow::render(PK2::Engine::GFX& gfx) {
	if (visible) {
		Window::render(gfx);

		for (size_t i = 0; i < logEntries->size(); i++) {
			LogEntry& e = (*logEntries)[i];

			SDL_Color col = gfx.getColorInBackgroundPalette(RECT_COLOR_ERROR);

			if (e.getLevel() == LogLevel::WARN || e.getLevel() == LogLevel::INFO) {
				col = gfx.getColorInBackgroundPalette(RECT_COLOR_INFO);
			}

			gfx.fillRect(x + RECT_OFFSET_X, y + 16 + RECT_OFFSET_Y + i * 9, RECT_WIDTH, RECT_HEIGHT, col);

			gfx.drawString(e.getMessage().data(), x + 11, y + 16 + 3 + (i * 9));
		}
	}
}

void LogWindow::update(std::vector<PK2::Engine::LogEntry>* entries) {
	logEntries = entries;
}