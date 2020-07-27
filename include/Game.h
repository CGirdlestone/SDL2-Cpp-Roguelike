#ifndef GAME_H
#define GAME_H

#include <map>
#include "EntityFactory.h"
#include "LootManager.h"
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
#include "PlayerSystem.h"
#include "GameStateManager.h"
#include "StartScene.h"
#include "GameScene.h"
#include "InventoryScene.h"
#include "CharacterScene.h"
#include "TargetingScene.h"
#include "PauseScene.h"

class Game
{
  public:
    Game();
    virtual ~Game();

    bool init(int mapWidth, int mapHheight, int width, int height, int tileSize, const char* title);
		void createConsole(int width, int height, const char* title, int tileSize);
    void run();

  protected:

  private:
		EntityFactory* m_factory;
    DungeonGenerator* m_dungeon;
    Console* m_console;
    MessageLog* m_messageLog;
    Camera *m_camera;
    Renderer* m_renderer;
    EventManager* m_eventManager;
		LootManager* m_lootManager;
    MoveSystem* m_moveSystem;
    CombatSystem* m_combatSystem;
    InventorySystem* m_inventorySystem;
		PlayerSystem* m_playerSystem;
    std::vector<Scene*> sceneStack;
    int m_width;
    int m_height;
    int m_mapWidth;
    int m_mapHeight;
    int m_tileSize;
    std::map<int, GameObject*> m_actors;
    GameStateManager *m_sceneManager;
    StartScene *m_startScene;
    GameScene *m_gameScene;
		InventoryScene *m_inventoryScene;
		CharacterScene *m_characterScene;
		TargetingScene *m_targetingScene;
		PauseScene *m_pauseScene;
		
};



#endif // GAME_H
