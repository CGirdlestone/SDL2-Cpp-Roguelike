
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

        case SDLK_KP_2:
        return SOUTH;

				case SDLK_KP_8:
				return NORTH;

        case SDLK_i:
        return ESCAPE;

				case SDLK_e:
				return WEAR;

				case SDLK_d:
				return DROPITEM;

				case SDLK_ESCAPE:
				return ESCAPE;
		  
				case SDLK_c:
				return SHOWCHARSCREEN;

				case SDLK_q:
				return USE;

				case SDLK_RETURN:
				return USE;
      }
  	}
  }
  return NONE;
}

void TargetingScene::handleInput(KeyPressSurfaces keyPress)
{

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
	} else if (keyPress == USE){
		//
		m_eventManager->pushEvent(PopScene(1));
	}
}

void TargetingScene::render()
{
	int radius;
	if (m_entities->at(m_item_uid)->useable->funcToDo == DIRECTDAMAGE){
		radius = m_entities->at(m_item_uid)->damage->radius;
	} else if (m_entities->at(m_item_uid)->useable->funcToDo == AOE){
		radius = m_entities->at(m_item_uid)->areaDamage->radius;
	} else if (m_entities->at(m_item_uid)->useable->funcToDo == STATUS){
		radius = m_entities->at(m_item_uid)->status->radius;
	}
	m_renderer->drawTargetingScene(m_camera, m_dungeon, m_entities, m_messageLog, m_x, m_y, radius);
}

void TargetingScene::update(Uint32 dt)
{

}

void TargetingScene::onTick()
{

}
