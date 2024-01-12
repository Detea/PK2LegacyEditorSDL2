#include "GFX.h"
#include "Logger.h"

#include <SDL.h>
#include <SDL_pixels.h>
#include <cstring>

#include "Files.h"

namespace PK2::Engine {
    using Logger = PK2::Engine::Logger;

    GFX::GFX(const char* title, int width, int height) {
        init(title, width, height);
    }

    GFX::~GFX() {
        Logger::info("Cleaning up GFX...");

        SDL_FreePalette(backgroundPalette);
        backgroundPalette = nullptr;

        for (auto const& [key, val] : textures) {
            SDL_DestroyTexture(val);
        }

        textures.clear();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();
    }

    bool GFX::init(const char* title, int width, int height) {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            Logger::error(SDL_GetError(), "GFX::init");

            return false;
        } else {
            window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

            if (!window) {
                Logger::error(SDL_GetError(), "GFX::init"); 

                return false;
            } else {
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

                if (!renderer) {
                    Logger::error(SDL_GetError(), "GFX::init"); 

                    return false;
                } 

                screenWidth = width;
                screenHeight = height;
                setupPalette();
            }
        }

        return true;
    }

    bool GFX::loadImage(std::string_view filename, bool setPaletteToBackground) {
        bool result = false;

        SDL_Surface* surface = SDL_LoadBMP(filename.data());

        if (!surface) {
            Logger::warn(SDL_GetError(), "GFX::loadImage");
        } else {
            SDL_Color color = surface->format->palette->colors[255];
            SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, color.r, color.g, color.b));

            if (setPaletteToBackground) {
                int setPaletteResult = SDL_SetPaletteColors(backgroundPalette, surface->format->palette->colors, 0, surface->format->palette->ncolors);

                if (setPaletteResult < 0) {
                    Logger::warn("Unable to set image's palette to background palette");
                    
                    return false;
                }
            }

            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

            if (!texture) {
                Logger::warn(SDL_GetError(), "GFX::loadImage");
            } else {
                textures[std::string(filename)] = texture;

                result = true;
            }

            SDL_FreeSurface(surface);
        }

        return result;
    }

    void GFX::loadFont(std::string_view filename, const std::string& fontName) {
        Font font;

        if (font.load(filename)) {
            if (loadImage(font.getFontImage())) { // TODO Path?
                fonts[fontName] = font;
            } else {
                Logger::error("Unable to load font image: " + std::string(font.getFontImage()));
            }
        } else {
            std::string msg = "Unable to load font: " + std::string(filename);

            Logger::error(msg, "GFX");
        }
    }

    void GFX::setupPalette() {
        backgroundPalette = SDL_AllocPalette(256);
    }

    SDL_Texture* GFX::getImage(std::string& filename) {
        if (textures.count(filename)) {
            return textures[filename];
        }

        std::string warningStr = "Image file '" + filename + "' has not been loaded!\n";
        Logger::warn(warningStr);
        return nullptr;
    }
        
    void GFX::drawImage(std::string& filename, int x, int y) {
        SDL_Rect dest = { x, y, 0, 0 };
        int res = SDL_QueryTexture(textures[filename], nullptr, nullptr, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, textures[filename], nullptr, &dest);
    }

    void GFX::drawImage(std::string& filename, const SDL_Rect& src, const SDL_Rect& dest) {
        SDL_RenderCopy(renderer, textures[filename], &src, &dest);
    }

    void GFX::drawString(const std::string& string, int x, int y, const PisteFontAttributes& fontAttributes, std::string& fontImageFile) {
        for (int i = 0; i < string.size(); i++) {
            int fontX = fontAttributes.getImageX();
            int fontY = fontAttributes.getImageY();
            int charXOffset = fontAttributes.getCharXOffset(string[i]);
            int letterX = i * fontAttributes.getLetterWidth();

            const SDL_Rect src = { fontX + charXOffset, fontY, fontAttributes.getLetterWidth(), fontAttributes.getLetterHeight()};
            const SDL_Rect dest = { x + letterX, y, src.w, src.h };

            /*
                TODO Not sure about this solution, especially because I'm only checking for spaces right now.
                Should probably check for \t and handle that one.
            */
            if (string[i] != ' ') drawImage(fontImageFile, src, dest);
        }
    }

    void GFX::drawString(const std::string& string, int x, int y) {
        drawString(string, x, y, currentFont);
    }

    void GFX::drawString(const std::string& string, int x, int y, const std::string& fontName) {
        // TODO Should I check if the font exists? The programmer should know what font they are using. If the font doesn't exist the program probably crashes, so it should be obvious?
        Font& font = fonts[fontName];

        drawString(string, x, y, font.getFontAttributes(), font.getFontImage());
    }

    void GFX::drawStringTransparent(const std::string& string, int x, int y, int transparency) {
        drawString(string, x, y);
    }

    void GFX::drawRect(int x, int y, int width, int height, SDL_Color& color) {
        SDL_Rect rect = { x, y, width, height };

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(renderer, &rect);
    }
  
    void GFX::fillRect(int x, int y, int width, int height, SDL_Color& color) {
        SDL_Rect rect = { x, y, width, height };

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }

    void GFX::drawLine(int startX, int startY, int endX, int endY, SDL_Color color) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
    }

    void GFX::setClearColor(SDL_Color color) {
        clearColor = color;
    }

    void GFX::drawPoint(int x, int y, SDL_Color color) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(renderer, x, y);
    }

    void GFX::clear() {
        // TODO For testing only, background color of the original is black(?)
        SDL_SetRenderDrawColor(renderer, clearColor.r, clearColor.g, clearColor.b, 0xFF);
        SDL_RenderClear(renderer);
    }

    void GFX::render() {
        SDL_RenderPresent(renderer);
    }

    SDL_Color GFX::getColorInBackgroundPalette(int index) {
        SDL_Color col = { 0, 0, 0, 0xFF};

        if (backgroundPalette) {
            if (index >= 0 && index < 256) {
                col = backgroundPalette->colors[index];
            }
        }

        return col;
    }

    PK2::Engine::Font& GFX::getFont(const std::string& fontName) {
        return fonts[fontName];
    }

    void GFX::setCurrentFont(const std::string& fontName) {
        currentFont = fontName;
    }

    PK2::Engine::Font& GFX::getCurrentFont() {
        return fonts[currentFont];
    }

    int GFX::getScreenWidth() {
        return screenWidth;
    }
    
    int GFX::getScreenHeight() {
        return screenHeight;
    }
}
