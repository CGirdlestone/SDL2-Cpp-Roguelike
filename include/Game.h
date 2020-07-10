#ifndef GAME_H
#define GAME_H

#include "DungeonGenerator.h"
#include "Console.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Components.h"
#include "GameObject.h"
#include "KeyPressSurfaces.h"
#include "MessageLog.h"
#include "Camera.h"
#include "EventManager.h"
#include "MoveSystem.h"
#include "CombatSystem.h"
#include "InventorySystem.h"
#include "GameStateManager.h"
#include "StartScene.h"
#include "GameScene.h"

enum GameState
{
    PLAYER,
    AI,
    GAMEOVER,
};

extern GameState State;

class Game
{
  public:
    Game();
    virtual ~Game();

    bool init(int mapWidth, int mapHheight, int width, int height, int tileSize, char* title);
    void run();
    void processEntities();
    void processInput(KeyPressSurfaces keyPress);
    void onTick();
    void update(Uint32 dt);

  protected:

  private:
    DungeonGenerator* m_dungeon;
    Console* m_console;
    InputHandler* m_input;
    MessageLog* m_messageLog;
    Camera *m_camera;
    Renderer* m_renderer;
    EventManager* m_eventManager;
    MoveSystem* m_moveSystem;
    CombatSystem* m_combatSystem;
    InventorySystem* m_inventorySystem;
    std::vector<Scene*> sceneStack;
    bool m_isPlaying;
    int m_width;
    int m_height;
    int m_mapWidth;
    int m_mapHeight;
    int m_tileSize;
    std::vector<GameObject*> m_actors;
    GameState m_state;
    SDL_Color m_defaultColour;
    SDL_Color m_inViewColour;
    GameStateManager *m_sceneManager;
    StartScene *m_startScene;
    GameScene *m_gameScene;
};



#endif // GAME_H
