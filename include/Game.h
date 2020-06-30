#ifndef GAME_H
#define GAME_H

#include "DungeonGenerator.h"
#include "Console.h"
#include "InputHandler.h"
#include "Components.h"
#include "KeyPressSurfaces.h"
#include "MessageLog.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        bool init(int width, int height, int tileSize, char* title);
        void run();
        void drawMap();
        void drawLog();
        void createPlayer();
        void movePlayer(int dx, int dy);
        bool checkMove(int dx, int dy);

    protected:

    private:
        DungeonGenerator* m_dungeon;
        Console* m_console;
        InputHandler* m_input;
        MessageLog* m_messageLog;
        bool m_isPlaying;
        Position* m_playerPos;
        Renderable* m_playerRender;
        int m_width;
        int m_height;
        int m_tileSize;
};

#endif // GAME_H
