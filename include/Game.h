#ifndef GAME_H
#define GAME_H

#include "DungeonGenerator.h"
#include "Console.h"
#include "Renderer.h"
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
#include "InventoryScene.h"

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

  protected:

  private:
    DungeonGenerator* m_dungeon;
    Console* m_console;
    MessageLog* m_messageLog;
    Camera *m_camera;
    Renderer* m_renderer;
    EventManager* m_eventManager;
    MoveSystem* m_moveSystem;
    CombatSystem* m_combatSystem;
    InventorySystem* m_inventorySystem;
    std::vector<Scene*> sceneStack;
    int m_width;
    int m_height;
    int m_mapWidth;
    int m_mapHeight;
    int m_tileSize;
    std::vector<GameObject*> m_actors;
    GameStateManager *m_sceneManager;
    StartScene *m_startScene;
    GameScene *m_gameScene;
		InventoryScene *m_inventoryScene;
};



#endif // GAME_H
