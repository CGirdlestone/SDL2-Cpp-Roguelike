#ifndef CONSOLE_H
#define CONSOLE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

class Console
{
    public:
        Console(int width, int height, char* title, char* path, int fontSize);
        virtual ~Console();

        int Getm_width() { return m_width; }
        void Setm_width(int val) { m_width = val; }
        int Getm_height() { return m_height; }
        void Setm_height(int val) { m_height = val; }

        bool init(char* path, int fontSize);
        bool createWindow();
        bool createRenderer();
        bool initFont(char* path, int fontSize);
        bool initImage();
        bool setFont(char* path, int fontSize);
        void render(char* c, int x, int y, SDL_Color colour);
        void update();
        void closeSDL();
        void flush();
        void setFullscreen();
        void setBackgroundColour(Uint8 r, Uint8 g, Uint8 b);

    protected:

    private:
        SDL_Window *m_root;
        SDL_Surface *m_rootSurface;
        SDL_Renderer *m_renderer;
        TTF_Font *m_font;
        SDL_Color m_backgroundColour;
        int m_width;
        int m_height;
        char *m_title;
        int m_fontSize;
        int m_textWidth;
        int m_textHeight;
        int m_fullscreen;
};

#endif // CONSOLE_H
