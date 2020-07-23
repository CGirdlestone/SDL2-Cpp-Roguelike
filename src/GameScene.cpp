#include <iostream>
#include <map>
#include "StartScene.h"
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "KeyPressSurfaces.h"
#include "Pathfind.h"
#include "EventManager.h"
#include "Events.h"
#include "EventTypes.h"
#include "SceneTypes.h"
#include "GameScene.h"


GameScene::GameScene(EventManager *eventManager, Renderer *renderer, std::map<int, GameObject*> *entities, Camera* camera, DungeonGenerator* dungeon, MessageLog* messageLog):
m_eventManager(eventManager), m_renderer(renderer), m_entities(entities), m_camera(camera), m_dungeon(dungeon), m_messageLog(messageLog)
{
  m_playerTurn = true;
}

GameScene::~GameScene()
{

}

void GameScene::newGame()
{
	m_dungeon->createMap(60, 6, 2, 5);
	m_dungeon->createPlayer(m_entities);
	m_dungeon->createEntities(m_entities);
	m_dungeon->createItems(m_entities);
	m_dungeon->placeStairs(m_entities);
	m_dungeon->shadowCast(m_entities->at(0)->position->x, m_entities->at(0)->position->y, 10);
	m_camera->updatePosition(m_entities->at(0)->position->x, m_entities->at(0)->position->y);
}

void GameScene::nextLevel()
{
	m_dungeon->createMap(60, 6, 2, 5);
	m_dungeon->createEntities(m_entities);
	m_dungeon->createItems(m_entities);
	m_dungeon->placeStairs(m_entities);
	m_dungeon->shadowCast(m_entities->at(0)->position->x, m_entities->at(0)->position->y, 10);
	m_camera->updatePosition(m_entities->at(0)->position->x, m_entities->at(0)->position->y);
}

void GameScene::processEntities()
{
  int j;
  int x, y;

	std::map<int, GameObject*>::iterator it;
  for (it = m_entities->begin(); it != m_entities->end(); ++it){
    if (it->second->ai != nullptr && it->second->fighter != nullptr){
      if (it->second->fighter->isAlive){
        if (m_dungeon->m_fovMap[it->second->position->x + it->second->position->y * m_dungeon->Getm_width()] == 1){
          it->second->ai->path.clear();
          aStar(m_dungeon->m_level, &it->second->ai->path, m_dungeon->Getm_width(), m_dungeon->Getm_height(), it->second->position->x, it->second->position->y, m_entities->at(0)->position->x, m_entities->at(0)->position->y);

          j = it->second->ai->path.back();
          it->second->ai->path.pop_back();

          x = j % m_dungeon->Getm_width();
          y = j / m_dungeon->Getm_width();

          MoveEvent moveEvent = MoveEvent(x - it->second->position->x, y - it->second->position->y, it->first);
          m_eventManager->pushEvent(moveEvent);

        } else {
          if (it->second->ai->path.size() > 0){
            j = it->second->ai->path.back();
            it->second->ai->path.pop_back();

            x = j % m_dungeon->Getm_width();
            y = j / m_dungeon->Getm_width();

            MoveEvent moveEvent = MoveEvent(x - it->second->position->x, y - it->second->position->y, it->first);
            m_eventManager->pushEvent(moveEvent);
          }
        }
      }
    }
  }
  m_playerTurn = true;
}

bool GameScene::checkDescend()
{
	std::map<int, GameObject*>::iterator iter;

	for (iter = m_entities->begin(); iter != m_entities->end(); ++iter){
		if (iter->second->stairs != nullptr){
			if (iter->second->position->x == m_entities->at(0)->position->x && iter->second->position->y == m_entities->at(0)->position->y){
				return true;
			}
		} 
	}
	return false;
}

enum KeyPressSurfaces GameScene::getEvent(SDL_Event *e)
{
  while(SDL_PollEvent(e)){
      if (e->type == SDL_QUIT){
          return ESCAPE;
      } else if (e->type == SDL_KEYDOWN){
          switch(e->key.keysym.sym){
              case SDLK_UP:
              return NORTH;

              case SDLK_DOWN:
              return SOUTH;

              case SDLK_LEFT:
              return WEST;

              case SDLK_RIGHT:
              return EAST;

              case SDLK_KP_1:
              return SOUTHWEST;

              case SDLK_KP_2:
              return SOUTH;

              case SDLK_KP_3:
              return SOUTHEAST;

              case SDLK_KP_4:
              return WEST;

              case SDLK_KP_5:
              return WAIT;

              case SDLK_KP_6:
              return EAST;

              case SDLK_KP_7:
              return NORTHWEST;

              case SDLK_KP_8:
              return NORTH;

              case SDLK_KP_9:
              return NORTHEAST;

              case SDLK_ESCAPE:
              return ESCAPE;

              case SDLK_F1:
              return F1;

              case SDLK_g:
              return GRAB;

							case SDLK_i:
							return BAG;

							case SDLK_c:
							return SHOWCHARSCREEN;

							case SDLK_RETURN:
							return USE;
          }
      }
  }
  return NONE;
}

void GameScene::handleInput(KeyPressSurfaces keyPress)
{
  if (keyPress == ESCAPE){
      m_eventManager->pushEvent(QuitEvent());
  } else if (keyPress == WEST){
    MoveEvent moveEvent = MoveEvent(-1, 0, 0);
    m_eventManager->pushEvent(moveEvent);
    m_playerTurn = false;
  } else if (keyPress == EAST){
    MoveEvent moveEvent = MoveEvent(1, 0, 0);
    m_eventManager->pushEvent(moveEvent);
    m_playerTurn = false;
  } else if (keyPress == NORTH){
    MoveEvent moveEvent = MoveEvent(0, -1, 0);
    m_eventManager->pushEvent(moveEvent);
    m_playerTurn = false;
  } else if (keyPress == SOUTH){
    MoveEvent moveEvent = MoveEvent(0, 1, 0);
    m_eventManager->pushEvent(moveEvent);
    m_playerTurn = false;
  } else if (keyPress == NORTHWEST){
    MoveEvent moveEvent = MoveEvent(-1, -1, 0);
    m_eventManager->pushEvent(moveEvent);
    m_playerTurn = false;
  } else if (keyPress == NORTHEAST){
    MoveEvent moveEvent = MoveEvent(1, -1, 0);
    m_eventManager->pushEvent(moveEvent);
    m_playerTurn = false;
  } else if (keyPress == SOUTHWEST){
    MoveEvent moveEvent = MoveEvent(-1, 1, 0);
    m_eventManager->pushEvent(moveEvent);
    m_playerTurn = false;
  } else if (keyPress == SOUTHEAST){
    MoveEvent moveEvent = MoveEvent(1, 1, 0);
    m_eventManager->pushEvent(moveEvent);
    m_playerTurn = false;
  } else if (keyPress == WAIT){
    m_playerTurn = false;
  } else if (keyPress == GRAB){
    TakeEvent takeEvent = TakeEvent(0, m_entities->at(0)->position->x, m_entities->at(0)->position->y);
    m_eventManager->pushEvent(takeEvent);
    m_playerTurn = false;
  } else if (keyPress == BAG){
		m_eventManager->pushEvent(PushScene(INVENTORY));
	} else if (keyPress == SHOWCHARSCREEN){
		m_eventManager->pushEvent(PushScene(CHARACTER));
	} else if (keyPress == USE){
		if(checkDescend()){
			nextLevel();
		}
	}

  if (!m_playerTurn){
    processEntities();
  }
}


void GameScene::render()
{
  m_renderer->drawGameScreen(m_camera, m_dungeon, m_entities, m_messageLog);
}

void GameScene::update(Uint32 dt)
{

  m_messageLog->ageMessages(dt);
}

void GameScene::onTick()
{
  if (m_dungeon->recomputeFOV){
    m_dungeon->doRecomputeFOV(m_entities->at(0)->position->x, m_entities->at(0)->position->y, 10);
  }

  m_camera->updatePosition(m_entities->at(0)->position->x, m_entities->at(0)->position->y);
}
