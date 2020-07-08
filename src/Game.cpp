#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <time.h>
#include <string>

#include "DungeonGenerator.h"
#include "Console.h"
#include "InputHandler.h"
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


Game::Game()
{
  //ctor
  m_console = nullptr;
  m_dungeon = nullptr;
  m_input = nullptr;
}

Game::~Game()
{
  //dtor
  delete m_console;
  m_console = nullptr;

  delete m_dungeon;
  m_dungeon = nullptr;

  delete m_input;
  m_input = nullptr;

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

  for (int i = 0; i < static_cast<int>(m_actors.size()); i++){
    delete m_actors[i];
  }
}

bool Game::init(int mapWidth, int mapHeight, int width, int height, int tileSize, char* title, int fps)
{
  m_dungeon = new DungeonGenerator(mapWidth, mapHeight);
  m_camera = new Camera(width, height, mapWidth, mapHeight);
  m_console = new Console(width, height, title, (char*)"./resources/Cheepicus_8x8x2.png", tileSize);
  m_input = new InputHandler();
  m_eventManager = new EventManager();
  m_messageLog = new MessageLog(width, 8, m_eventManager, &m_actors);
  m_combatSystem = new CombatSystem(m_eventManager, &m_actors);
  m_inventorySystem = new InventorySystem(m_eventManager, &m_actors);
  m_moveSystem = new MoveSystem(m_eventManager, &m_actors, m_dungeon);
  m_renderer = new Renderer(m_console);
  m_width = width;
  m_height = height;
  m_mapWidth = mapWidth;
  m_mapHeight = mapHeight;
  m_tileSize = tileSize;
  m_defaultColour = {0x18, 0x79, 0x87};
  m_inViewColour = {0xef, 0xd8, 0xa1};

  if (m_dungeon == nullptr || m_console == nullptr || m_input == nullptr){
      return false;
  } else {
      return true;
  }
}

void Game::processEntities()
{
  int j;
  int x, y;

  for (int i = 1; i < static_cast<int>(m_actors.size()); ++i){
    if (m_actors.at(i)->ai != nullptr && m_actors.at(i)->fighter != nullptr){
      if (m_actors.at(i)->fighter->isAlive){
        if (m_dungeon->m_fovMap[m_actors.at(i)->position->x + m_actors.at(i)->position->y * m_dungeon->Getm_width()] == 1){
          m_actors.at(i)->ai->path.clear();
          aStar(m_dungeon->m_level, &m_actors.at(i)->ai->path, m_dungeon->Getm_width(), m_dungeon->Getm_height(), m_actors.at(i)->position->x, m_actors.at(i)->position->y, m_actors.at(0)->position->x, m_actors.at(0)->position->y);

          j = m_actors.at(i)->ai->path.back();
          m_actors.at(i)->ai->path.pop_back();

          x = j % m_dungeon->Getm_width();
          y = j / m_dungeon->Getm_width();

          MoveEvent moveEvent = MoveEvent(x - m_actors.at(i)->position->x, y - m_actors.at(i)->position->y, i);
          m_eventManager->pushEvent(moveEvent);

        } else {
          if (m_actors.at(i)->ai->path.size() > 0){
            j = m_actors.at(i)->ai->path.back();
            m_actors.at(i)->ai->path.pop_back();

            x = j % m_dungeon->Getm_width();
            y = j / m_dungeon->Getm_width();

            MoveEvent moveEvent = MoveEvent(x - m_actors.at(i)->position->x, y - m_actors.at(i)->position->y, i);
            m_eventManager->pushEvent(moveEvent);
          }
        }
      }
    }
  }
  m_state = PLAYER;
}

void Game::processInput(KeyPressSurfaces keyPress)
{
  if (keyPress == ESCAPE){
      m_isPlaying = false;
  } else if (keyPress == WEST){
    MoveEvent moveEvent = MoveEvent(-1, 0, 0);
    m_eventManager->pushEvent(moveEvent);
    m_state = AI;
  } else if (keyPress == EAST){
    MoveEvent moveEvent = MoveEvent(1, 0, 0);
    m_eventManager->pushEvent(moveEvent);
    m_state = AI;
  } else if (keyPress == NORTH){
    MoveEvent moveEvent = MoveEvent(0, -1, 0);
    m_eventManager->pushEvent(moveEvent);
    m_state = AI;
  } else if (keyPress == SOUTH){
    MoveEvent moveEvent = MoveEvent(0, 1, 0);
    m_eventManager->pushEvent(moveEvent);
    m_state = AI;
  } else if (keyPress == NORTHWEST){
    MoveEvent moveEvent = MoveEvent(-1, -1, 0);
    m_eventManager->pushEvent(moveEvent);
    m_state = AI;
  } else if (keyPress == NORTHEAST){
    MoveEvent moveEvent = MoveEvent(1, -1, 0);
    m_eventManager->pushEvent(moveEvent);
    m_state = AI;
  } else if (keyPress == SOUTHWEST){
    MoveEvent moveEvent = MoveEvent(-1, 1, 0);
    m_eventManager->pushEvent(moveEvent);
    m_state = AI;
  } else if (keyPress == SOUTHEAST){
    MoveEvent moveEvent = MoveEvent(1, 1, 0);
    m_eventManager->pushEvent(moveEvent);
    m_state = AI;
  } else if (keyPress == WAIT){
    m_state = AI;
  }else if (keyPress == GRAB){
    TakeEvent takeEvent = TakeEvent(0, m_actors.at(0)->position->x, m_actors.at(0)->position->y);
    m_eventManager->pushEvent(takeEvent);
    m_state = AI;
  } else if (keyPress == F1){
    m_console->setFullscreen();
  }
}

void Game::onTick()
{
  // to do
  if (m_dungeon->recomputeFOV){
    m_dungeon->doRecomputeFOV(m_actors.at(0)->position->x, m_actors.at(0)->position->y, 10);
  }

  m_camera->updatePosition(m_actors.at(0)->position->x, m_actors.at(0)->position->y);

  if (!(m_actors.at(0)->fighter->isAlive)){
    m_state = GAMEOVER;
    m_isPlaying = false;
  }
}

void Game::update(Uint32 dt)
{
  m_messageLog->ageMessages(dt);
}


void Game::run()
{
  SDL_Event e;
  KeyPressSurfaces keyPress;
  m_isPlaying = true;
  Uint32 currentTime;
  Uint32 lastTime = 0;
  Uint32 dt = 0;
  m_state = PLAYER;

  m_dungeon->createMap(60, 6, 2, 5);
  m_dungeon->createPlayer(&m_actors);
  m_dungeon->createEntities(&m_actors);
  m_dungeon->createItems(&m_actors);
  m_dungeon->shadowCast(m_actors.at(0)->position->x, m_actors.at(0)->position->y, 10);
  m_camera->updatePosition(m_actors.at(0)->position->x, m_actors.at(0)->position->y);

  while(m_isPlaying){
    currentTime = SDL_GetTicks();

    m_console->flush();
    m_renderer->drawGameScreen(m_camera, m_dungeon, &m_actors, m_messageLog, m_height);
    m_console->update();

    keyPress = m_input->getEvent(&e);
    processInput(keyPress);

    if (m_state == AI){
      processEntities();
    }

    dt = (currentTime - lastTime);
    lastTime = currentTime;

    onTick();
    update(dt);
  }

  m_console->closeSDL();
}
