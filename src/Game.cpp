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

  for (int i = 0; i < static_cast<int>(m_actors.size()); i++){
    delete m_actors[i];
  }
}

bool Game::init(int mapWidth, int mapHeight, int width, int height, int tileSize, char* title, int fps)
{
  m_dungeon = new DungeonGenerator(mapWidth, mapHeight);
  m_console = new Console(width, height, title, (char*)"./resources/Cheepicus_8x8x2.png", tileSize);
  m_input = new InputHandler();
  m_messageLog = new MessageLog(width, 10);
  m_camera = new Camera(width, height, mapWidth, mapHeight);
  m_width = width;
  m_height = height;
  m_tileSize = tileSize;
  m_fps = fps;

  if (m_dungeon == nullptr || m_console == nullptr || m_input == nullptr){
      return false;
  } else {
      return true;
  }
}

void Game::drawLog()
{
  std::vector<Message> messages = m_messageLog->getMessages();

  if (messages.size() > 0){
    for(int j = 0; j < static_cast<int>(messages.size()); j++){
      Message msg = messages.at(j);
      for(int i = 0; i < static_cast<int>(msg.m_msg.length()); i++){
        m_console->render(&msg.m_msg[i], i, j + m_height, msg.m_colour);
      }
    }
  }
}

void Game::drawMap()
{
  int x;
  int y = 0;
  int offsetI;
  SDL_Color colour = {0xef, 0xd8, 0xa1};
  bool occupied;

  for (int i = 0; i < m_dungeon->Getm_width() * m_dungeon->Getm_height(); i++){
    x = i % m_dungeon->Getm_width();

    if (!(x >= m_camera->getX() && x < m_camera->getX() + m_camera->getWidth() && y >= m_camera->getY() && y < m_camera->getY() + m_camera->getHeight())){
      if (x == m_dungeon->Getm_width() - 1){
        y++;
      }
      continue;
    }

    occupied = false;
    if (m_dungeon->m_fovMap[i] == 1){
      for(GameObject* actor : m_actors){
        if (actor->position->x + actor->position->y*m_dungeon->Getm_width() == i){
          occupied = true;
        }
      }
      if(!occupied){
        offsetI = m_camera->calculateOffset(x, y);
        m_console->render(&m_dungeon->m_level[i], offsetI % m_camera->getWidth(), offsetI / m_camera->getWidth(), colour);
      }
    } else if (m_dungeon->m_fovMap[i] == 0){
      if (m_dungeon->m_exploredMap[i] == 1){
        for(GameObject* actor : m_actors){
          if (actor->position->x + actor->position->y*m_dungeon->Getm_width() == i){
            occupied = true;
          }
        }
        offsetI = m_camera->calculateOffset(x, y);
        m_console->render(&m_dungeon->m_level[i], offsetI % m_camera->getWidth(), offsetI / m_camera->getWidth(), colour);
      }
    }
    if (x == m_dungeon->Getm_width() - 1){
      y++;
    }
  }
}

void Game::drawActors()
{
  int mapArrayIndex;
  int offsetI;
  if (!m_actors.empty()){
    for (int i = 0; i < static_cast<int>(m_actors.size()); i++){
      mapArrayIndex = m_actors[i]->position->x + m_actors[i]->position->y*m_dungeon->Getm_width();
      if (m_dungeon->m_fovMap[mapArrayIndex] == 1){
        offsetI = m_camera->calculateOffset(m_actors[i]->position->x, m_actors[i]->position->y);
        m_console->render(&m_actors[i]->renderable->chr, offsetI % m_camera->getWidth(), offsetI / m_camera->getWidth(), m_actors[i]->renderable->colour);
      }
    }
  }
}

bool Game::checkMove(int dx, int dy, int uid)
{
  if (m_actors.at(uid)->position->x + dx>= 0 && m_actors.at(uid)->position->x + dx < m_dungeon->Getm_width() && m_actors.at(uid)->position->y + dy >= 0 && m_actors.at(uid)->position->y + dy < m_dungeon->Getm_height()){
    if (m_dungeon->m_level[(m_actors.at(uid)->position->x + dx) + m_dungeon->Getm_width() * (m_actors.at(uid)->position->y + dy)] != '.'){
      return false;
    } else{
      for (int i = 0; i < static_cast<int>(m_actors.size()); i++){
        if (i == uid){ continue; }

        if (m_actors.at(uid)->position->x + dx == m_actors.at(i)->position->x && m_actors.at(uid)->position->y + dy == m_actors.at(i)->position->y){
          SDL_Color colour = {0x3f, 0x3a, 0x0c};
          m_messageLog->addMessage("You kicked the mob!", colour);
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


void Game::run()
{
  SDL_Event e;
  KeyPressSurfaces keyPress;
  m_isPlaying = true;
  fpsInterval = 1.0;

  m_dungeon->createMap(60, 6, 2, 5);
  m_dungeon->createPlayer(&m_actors);
  m_dungeon->createEntities(&m_actors);
  m_dungeon->shadowCast(m_actors.at(0)->position->x, m_actors.at(0)->position->y, 10);
  m_camera->updatePosition(m_actors.at(0)->position->x, m_actors.at(0)->position->y);

  Uint32 currentTime;
  Uint32 lastTime = 0;
  Uint32 dt = 0;

  m_state = PLAYER;

  while(m_isPlaying){
    currentTime = SDL_GetTicks();

    if (m_dungeon->recomputeFOV){
      m_dungeon->doRecomputeFOV(m_actors.at(0)->position->x, m_actors.at(0)->position->y, 10);
    }

    m_console->flush();
    drawMap();
    drawActors();
    drawLog();
    m_console->update();

    keyPress = m_input->getEvent(&e);
    if (keyPress == ESCAPE){
        m_isPlaying = false;
    } else if (keyPress == ARROW_LEFT){
      movePlayer(-1, 0, 0);
      m_state = AI;
    } else if (keyPress == ARROW_RIGHT){
      movePlayer(1, 0, 0);
      m_state = AI;
    } else if (keyPress == ARROW_UP){
      movePlayer(0, -1, 0);
      m_state = AI;
    } else if (keyPress == ARROW_DOWN){
      movePlayer(0, 1, 0);
      m_state = AI;
    } else if (keyPress == F1){
      m_console->setFullscreen();
    }

    if (m_state == AI){
      processEntities();
    }

    m_camera->updatePosition(m_actors.at(0)->position->x, m_actors.at(0)->position->y);

    dt = (currentTime - lastTime);
    lastTime = currentTime;

    m_messageLog->ageMessages(dt);
  }
  m_console->closeSDL();
}
