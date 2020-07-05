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
  m_messageLog = new MessageLog(width, 9);
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

bool Game::checkMove(int dx, int dy, int uid)
{
  std::string msg;

  if (m_actors.at(uid)->position->x + dx>= 0 && m_actors.at(uid)->position->x + dx < m_dungeon->Getm_width() && m_actors.at(uid)->position->y + dy >= 0 && m_actors.at(uid)->position->y + dy < m_dungeon->Getm_height()){
    if (m_dungeon->m_level[(m_actors.at(uid)->position->x + dx) + m_dungeon->Getm_width() * (m_actors.at(uid)->position->y + dy)] != '.'){
      return false;
    } else{
      for (int i = 0; i < static_cast<int>(m_actors.size()); i++){
        if (i == uid){ continue; }

        if (m_actors.at(uid)->position->x + dx == m_actors.at(i)->position->x && m_actors.at(uid)->position->y + dy == m_actors.at(i)->position->y){
          SDL_Color colour = {0x3f, 0x3a, 0x0c};
          if (uid == 0){
            msg = "You kicked the ";
            msg.append("bat.");
            m_messageLog->addMessage(msg, colour);
          }
          return false;
        }
      }
      return true;
    }
  } else {
    return false;
  }
}

void Game::movePlayer(int dx, int dy, int uid)
{
  if (checkMove(dx, dy, uid)){
    m_actors.at(uid)->position->x += dx;
    m_actors.at(uid)->position->y += dy;

    if (uid == 0){
      m_dungeon->recomputeFOV = true;
    }
  }
}

void Game::processEntities()
{
  int j;
  int x, y;

  for (int i = 1; i < static_cast<int>(m_actors.size()); i++){
    if (m_actors.at(i)->ai != nullptr){

      if (m_dungeon->m_fovMap[m_actors.at(i)->position->x + m_actors.at(i)->position->y * m_dungeon->Getm_width()] == 1){
        m_actors.at(i)->ai->path.clear();
        aStar(m_dungeon->m_level, &m_actors.at(i)->ai->path, m_dungeon->Getm_width(), m_dungeon->Getm_height(), m_actors.at(i)->position->x, m_actors.at(i)->position->y, m_actors.at(0)->position->x, m_actors.at(0)->position->y);

        j = m_actors.at(i)->ai->path.back();
        m_actors.at(i)->ai->path.pop_back();

        x = j % m_dungeon->Getm_width();
        y = j / m_dungeon->Getm_width();

        movePlayer(x - m_actors.at(i)->position->x, y - m_actors.at(i)->position->y, i);
      } else {
        if (m_actors.at(i)->ai->path.size() > 0){
          j = m_actors.at(i)->ai->path.back();
          m_actors.at(i)->ai->path.pop_back();

          x = j % m_dungeon->Getm_width();
          y = j / m_dungeon->Getm_width();

          movePlayer(x - m_actors.at(i)->position->x, y - m_actors.at(i)->position->y, i);
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
    movePlayer(-1, 0, 0);
    m_state = AI;
  } else if (keyPress == EAST){
    movePlayer(1, 0, 0);
    m_state = AI;
  } else if (keyPress == NORTH){
    movePlayer(0, -1, 0);
    m_state = AI;
  } else if (keyPress == SOUTH){
    movePlayer(0, 1, 0);
    m_state = AI;
  } else if (keyPress == NORTHWEST){
    movePlayer(-1, -1, 0);
    m_state = AI;
  } else if (keyPress == NORTHEAST){
    movePlayer(1, -1, 0);
    m_state = AI;
  } else if (keyPress == SOUTHWEST){
    movePlayer(-1, 1, 0);
    m_state = AI;
  } else if (keyPress == SOUTHEAST){
    movePlayer(1, 1, 0);
    m_state = AI;
  } else if (keyPress == WAIT){
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
