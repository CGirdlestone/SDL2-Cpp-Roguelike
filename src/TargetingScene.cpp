
#include <map>
#include <iostream>
#include "StartScene.h"
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "KeyPressSurfaces.h"
#include "Pathfind.h"
#include "EventManager.h"
#include "Events.h"
#include "EventTypes.h"
#include "SceneTypes.h"
#include "TargetingScene.h"
#include "Pathfind.h"

TargetingScene::TargetingScene(EventManager *eventManager, Renderer *renderer, std::map<int, GameObject*> *entities, Camera *camera, DungeonGenerator *dungeon, MessageLog* messageLog):
m_eventManager(eventManager), m_renderer(renderer), m_entities(entities), m_camera(camera), m_dungeon(dungeon), m_messageLog(messageLog)
{

}

TargetingScene::~TargetingScene()
{

}

enum KeyPressSurfaces TargetingScene::getEvent(SDL_Event *e)
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
		  
				case SDLK_RETURN:
				return USE;
      }
  	}
  }
  return NONE;
}

void TargetingScene::handleInput(KeyPressSurfaces keyPress)
{
	int targetUID;
  
	if (keyPress == ESCAPE){
    m_eventManager->pushEvent(PopScene(1));
  }else if (keyPress == NORTH){
		m_y -= 1;
	} else if (keyPress == SOUTH){
		m_y += 1;
	} else if (keyPress == WEST){
		m_x -= 1;
	} else if (keyPress == EAST){
		m_x += 1;
	} else if (keyPress == SOUTHEAST){
		m_y += 1;
		m_x += 1;
	} else if (keyPress == SOUTHWEST){
		m_y += 1;
		m_x -= 1;
	} else if (keyPress == NORTHWEST){
		m_y -= 1;
		m_x -= 1;
	} else if (keyPress == NORTHEAST){
		m_y -= 1;
		m_x +=1 ;
	} else if (keyPress == USE){
		targetUID = getTargetUID();
		if (targetUID != -1){
			if (m_entities->at(targetUID)->fighter != nullptr){
				if (m_entities->at(targetUID)->fighter->isAlive){
					m_eventManager->pushEvent(UseItemEvent(m_user_uid, m_item_uid, targetUID));
					m_eventManager->pushEvent(PopScene(1));
				}
			}
		}
	}
}

int TargetingScene::getTargetUID()
{
	int radius;
	if (m_entities->at(m_item_uid)->useable->funcToDo == DIRECTDAMAGE){
		radius = m_entities->at(m_item_uid)->damage->radius;
	} else if (m_entities->at(m_item_uid)->useable->funcToDo == AOE){
		radius = m_entities->at(m_item_uid)->areaDamage->radius;
	} else if (m_entities->at(m_item_uid)->useable->funcToDo == STATUS){
		radius = m_entities->at(m_item_uid)->status->radius;
	}
	
	std::map<int, GameObject*>::iterator it;
	for (it = m_entities->begin(); it != m_entities->end(); ++it){
		if (it->second->position == nullptr){ continue; }

		if (it->second->position->x == m_x && it->second->position->y == m_y && it->second->m_uid != m_user_uid){
			if (checkInRange(m_x, m_y, m_entities->at(m_user_uid)->position->x, m_entities->at(m_user_uid)->position->y, radius)){
				return it->second->m_uid;
			}
		}
	}
	return -1;
}

void TargetingScene::render()
{
	int radius;
	int splashRadius = 0;

	if (m_entities->at(m_item_uid)->useable->funcToDo == DIRECTDAMAGE){
		radius = m_entities->at(m_item_uid)->damage->radius;
	} else if (m_entities->at(m_item_uid)->useable->funcToDo == AOE){
		radius = m_entities->at(m_item_uid)->areaDamage->radius;
		splashRadius = m_entities->at(m_item_uid)->areaDamage->splashRadius;
	} else if (m_entities->at(m_item_uid)->useable->funcToDo == STATUS){
		radius = m_entities->at(m_item_uid)->status->radius;
		splashRadius = m_entities->at(m_item_uid)->areaDamage->splashRadius;
	}
	m_renderer->drawTargetingScene(m_camera, m_dungeon, m_entities, m_messageLog, radius, &bresenhamLine, splashRadius, m_x, m_y);
}

void TargetingScene::update(Uint32 dt)
{

}

void TargetingScene::onTick()
{
	bresenhamLine.clear();
	getBresenhamLine(&bresenhamLine, m_dungeon->Getm_width(), m_x, m_y, m_entities->at(0)->position->x, m_entities->at(0)->position->y);	
}
