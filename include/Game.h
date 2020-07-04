#ifndef GAME_H
#define GAME_H

#include "DungeonGenerator.h"
#include "Console.h"
#include "InputHandler.h"
#include "Components.h"
#include "GameObject.h"
#include "KeyPressSurfaces.h"
#include "MessageLog.h"

enum GameState
{
    PLAYER,
    AI,
};

extern GameState State;

class Game
{
  public:
    Game();
    virtual ~Game();

    bool init(int width, int height, int tileSize, char* title, int fps);
    void run();
    void drawMap();
    void drawLog();
    void drawActors();
    void movePlayer(int dx, int dy, int uid);
    bool checkMove(int dx, int dy, int uid);
    void processEntities();

  protected:

  private:
    DungeonGenerator* m_dungeon;
    Console* m_console;
    InputHandler* m_input;
    MessageLog* m_messageLog;
    bool m_isPlaying;
    int m_width;
    int m_height;
    int m_tileSize;
    int m_fps;
    std::vector<GameObject*> m_actors;
    Uint32 fpsInterval;
    GameState m_state;
};



#endif // GAME_H
