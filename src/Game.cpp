#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <time.h>
#include <string>
#include <fstream>

#include "DungeonGenerator.h"
#include "Console.h"
#include "KeyPressSurfaces.h"
#include "Components.h"
#include "GameObject.h"
#include "Message.h"
#include "MessageLog.h"
#include "Pathfind.h"
#include "Game.h"
#include "Renderer.h"
#include "EventTypes.h"
#include "Events.h"
#include "EventManager.h"
#include "MoveSystem.h"
#include "CombatSystem.h"
#include "InventorySystem.h"
#include "PlayerSystem.h"
#include "Scene.h"
#include "StartScene.h"
#include "GameScene.h"
#include "InventoryScene.h"
#include "CharacterScene.h"
#include "TargetingScene.h"

Game::Game()
{
  //ctor
  m_console = nullptr;
  m_dungeon = nullptr;
  m_messageLog = nullptr;
  m_camera = nullptr;
  m_renderer = nullptr;
  m_eventManager = nullptr;
  m_moveSystem = nullptr;
  m_combatSystem = nullptr;
  m_inventorySystem = nullptr;
	m_playerSystem = nullptr;
  m_startScene = nullptr;
  m_gameScene = nullptr;
	m_inventoryScene = nullptr;
	m_characterScene = nullptr;
	m_targetingScene = nullptr;
  m_sceneManager = nullptr;

}

Game::~Game()
{
  //dtor
  delete m_console;
  m_console = nullptr;

  delete m_dungeon;
  m_dungeon = nullptr;

  delete m_messageLog;
  m_messageLog = nullptr;

  delete m_camera;
  m_camera = nullptr;

  delete m_renderer;
  m_renderer = nullptr;

  delete m_eventManager;
  m_eventManager = nullptr;

  delete m_moveSystem;
  m_moveSystem = nullptr;

  delete m_combatSystem;
  m_combatSystem = nullptr;

  delete m_inventorySystem;
  m_inventorySystem = nullptr;
	
	delete m_playerSystem;
	m_playerSystem = nullptr;

  delete m_startScene;
  m_startScene = nullptr;

  delete m_gameScene;
  m_gameScene = nullptr;

	delete m_inventoryScene;
	m_inventoryScene = nullptr;

	delete m_characterScene;
	m_characterScene = nullptr;

	delete m_targetingScene;
	m_targetingScene = nullptr;

  delete m_sceneManager;
  m_sceneManager = nullptr;

	std::map<int, GameObject*>::iterator it;
  for (it = m_actors.begin(); it != m_actors.end(); ++it){
    delete it->second;
  }
}

void Game::createConsole(int width, int height, const char* title, int tilesize)
{
	std::ifstream file;
	std::string line;
	std::string path = "./resources/";
	
	file.open("./resources/font.txt");
	if (file.is_open()){
		getline(file, line);
		path += line;
		m_console = new Console(width, height, title, path.c_str(), tilesize);
	}
}

bool Game::init(int mapWidth, int mapHeight, int width, int height, int tileSize, const char* title)
{
  m_dungeon = new DungeonGenerator(mapWidth, mapHeight);
  m_camera = new Camera(width, height, mapWidth, mapHeight);
	createConsole(width, height, title, tileSize);

  m_eventManager = new EventManager();
  m_messageLog = new MessageLog(width, 8, m_eventManager, &m_actors);
  m_combatSystem = new CombatSystem(m_eventManager, &m_actors);
  m_inventorySystem = new InventorySystem(m_eventManager, &m_actors);
  m_moveSystem = new MoveSystem(m_eventManager, &m_actors, m_dungeon);
	m_playerSystem = new PlayerSystem(m_eventManager, &m_actors);
  m_renderer = new Renderer(m_console);

  m_sceneManager = new GameStateManager(m_eventManager, &m_actors);
  m_startScene = new StartScene(m_eventManager, m_renderer);
  m_gameScene = new GameScene(m_eventManager, m_renderer, &m_actors, m_camera, m_dungeon, m_messageLog);
	m_inventoryScene = new InventoryScene(m_eventManager, m_renderer, &m_actors);
	m_characterScene = new CharacterScene(m_eventManager, m_renderer, &m_actors);
  m_targetingScene = new TargetingScene(m_eventManager, m_renderer, &m_actors, m_camera, m_dungeon, m_messageLog);
  m_sceneManager->m_startScene = m_startScene;
  m_sceneManager->m_gameScene = m_gameScene;
	m_sceneManager->m_inventoryScene = m_inventoryScene;
	m_sceneManager->m_characterScene = m_characterScene;
	m_sceneManager->m_targetingScene = m_targetingScene;

  m_width = width;
  m_height = height;
  m_mapWidth = mapWidth;
  m_mapHeight = mapHeight;
  m_tileSize = tileSize;

  if (m_dungeon == nullptr || m_console == nullptr){
      return false;
  } else {
      return true;
  }
}

void Game::run()
{
  SDL_Event e;

  Uint32 currentTime;
  Uint32 lastTime = 0;
  Uint32 dt = 0;

  m_eventManager->pushEvent(PushScene(STARTMENU));

  while(m_sceneManager->playing){
    currentTime = SDL_GetTicks();

    m_sceneManager->render();
    m_sceneManager->processInput(&e);

    dt = (currentTime - lastTime);
    lastTime = currentTime;

    m_sceneManager->update(dt);
    m_sceneManager->onTick();
  }

  m_console->closeSDL();
}
