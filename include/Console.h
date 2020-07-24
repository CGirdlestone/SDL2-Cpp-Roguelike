#ifndef CONSOLE_H
#define CONSOLE_H

#include "SDL2/SDL.h"
#include <vector>

#include "Tile.h"

class Console
{
    public:
        Console(int width, int height, const char* title, const char* path, int tileSize);
        virtual ~Console();

        int Getm_width() { return m_width; }
        void Setm_width(int val) { m_width = val; }
        int Getm_height() { return m_height; }
        void Setm_height(int val) { m_height = val; }
				int getTileSize() { return m_tileSize; } 
        int getXBuffer(){return m_xBuffer;}
        int getYBuffer(){return m_yBuffer;}

        bool init(const char* path);
        bool createWindow();
        bool createRenderer();
        bool initImage();
        bool loadMedia(const char* path);
        void createTiles();
        void render(char* c, int x, int y, SDL_Color colour);
        void render(int i, int x, int y, SDL_Color colour);
        void update();
        void closeSDL();
        void flush();
        void setFullscreen();
        SDL_Renderer* getRenderer(){return m_renderer;};
				void fillBackgroundTile(int x, int y, SDL_Color colour);
				void fillBackgroundTile(int x, int y, SDL_Color colour, int alpha, int tileSize, int originX, int originY);

    protected:

    private:
        SDL_Window *m_root;
        SDL_Surface *m_rootSurface;
        SDL_Renderer *m_renderer;
        SDL_Texture *m_texture;
        int m_width;
        int m_height;
        const char *m_title;
        int m_fullscreen;
        int m_tileSize;
        int m_xBuffer;
        int m_yBuffer;
        std::vector<Tile> m_glyphs;
};

#endif // CONSOLE_H
