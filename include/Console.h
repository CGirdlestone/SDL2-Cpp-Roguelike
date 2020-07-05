#ifndef CONSOLE_H
#define CONSOLE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <vector>

#include "Tile.h"

class Console
{
    public:
        Console(int width, int height, char* title, char* path, int tileSize);
        virtual ~Console();

        int Getm_width() { return m_width; }
        void Setm_width(int val) { m_width = val; }
        int Getm_height() { return m_height; }
        void Setm_height(int val) { m_height = val; }

        bool init(char* path);
        bool createWindow();
        bool createRenderer();
        bool initImage();
        bool loadMedia(char* path);
        void createTiles();
        void render(char* c, int x, int y, SDL_Color colour);
        void update();
        void closeSDL();
        void flush();
        void setFullscreen();
        SDL_Renderer* getRenderer(){return m_renderer;};

    protected:

    private:
        SDL_Window *m_root;
        SDL_Surface *m_rootSurface;
        SDL_Renderer *m_renderer;
        SDL_Texture *m_texture;
        int m_width;
        int m_height;
        char *m_title;
        int m_textWidth;
        int m_textHeight;
        int m_fullscreen;
        int m_tileSize;
        std::vector<Tile> m_glyphs;
};

#endif // CONSOLE_H
