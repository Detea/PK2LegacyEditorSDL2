#ifndef PK2_ENGINE_GFX_H
#define PK2_ENGINE_GFX_H

#include <SDL.h>
#include <map>
#include <string>
#include <string_view>

#include "PisteFontAttributes.h"
#include "Font.h"

namespace PK2::Engine {
    class GFX final {
        public: 
            GFX(const char* title, int width, int height);
            ~GFX();

            // Sets the stored backgroundPalette to the palette from the provided surface.
            void setBackgroundPalette(SDL_Surface* surface);

            // Tries to load the image from the file 'filename' and sets it's palette to palette, if palette != nullptr.
            // If palette is null, the image will be loaded as is, without any changes to it's palette.
            bool loadImage(std::string_view filename, bool setPaletteToBackground = false);

            void loadFont(std::string_view filename, const std::string& fontName);

            PK2::Engine::Font& getFont(const std::string& fontName);

            SDL_Texture* getImage(std::string& filename);

            // TODO Should use int instead of std::string, string is wasteful and unnecessary
            void drawImage(std::string& filename, int x, int y);
            void drawImage(std::string& filename, const SDL_Rect& src, const SDL_Rect& dest);

            void drawString(const std::string& string, int x, int y, const PisteFontAttributes& fontAttributes, std::string& fontImageFile);
            
            // Draws a string with the font loaded as "fontName".
            void drawString(const std::string& string, int x, int y, const std::string& fontName);
            
            // Draws a string with the currently set font.
            void drawString(const std::string& string, int x, int y);
            
            /*
                unsigned char color2 = 14;
	            unsigned char color3 = 0;

	            color3 = (color2 >> 5) << 5;
	            color2 -= color3;
	            unsigned char color = 28;
	            unsigned char alpha = 50;
	            color = (color * alpha + color2 * (100 - alpha)) / 100;

	            std::cout << "col: " << (int) color << " col2: " << (int)color2 << " col3: " << (int)color3 << "\n";
            */
            void drawStringTransparent(const std::string& string, int x, int y, int transparency = 100);

            void drawRect(int x, int y, int width, int height, SDL_Color &color);
            void fillRect(int x, int y, int width, int height, SDL_Color &color);

            void drawLine(int startX, int startY, int endX, int endY, SDL_Color color);

            void drawPoint(int x, int y, SDL_Color color);

            void clear();
            void render();

            SDL_Color getColorInBackgroundPalette(int index);

            void setCurrentFont(const std::string& fontName);
            PK2::Engine::Font& getCurrentFont();
        
            int getScreenWidth();
            int getScreenHeight();
        
            void setClearColor(SDL_Color color);
        private:
            void setupPalette();
            bool init(const char* title, int width, int height);

        private:
            SDL_Window* window = nullptr;
            SDL_Renderer* renderer = nullptr;

            SDL_Palette* backgroundPalette = nullptr;

            SDL_Color clearColor = { 0, 0, 0, 0xFF };

            // TODO Create a custom Texture class, to wrap the width, height in
            std::map<std::string, SDL_Texture*> textures;
            
            std::map<std::string, PK2::Engine::Font> fonts;
            std::string currentFont;

            int screenWidth;
            int screenHeight;
    };
}
#endif
