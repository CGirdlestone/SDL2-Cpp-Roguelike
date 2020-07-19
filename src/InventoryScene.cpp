
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
#include "InventoryScene.h"


InventoryScene::InventoryScene(EventManager *eventManager, Renderer *renderer, std::map<int, GameObject*> *entities):
m_eventManager(eventManager), m_renderer(renderer), m_entities(entities)
{
	m_index = 0;
}

InventoryScene::~InventoryScene()
{

}

enum KeyPressSurfaces InventoryScene::getEvent(SDL_Event *e)
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

void InventoryScene::handleInput(KeyPressSurfaces keyPress)
{
	int inventorySize = m_entities->at(0)->inventory->inventory.size();
	int x = m_entities->at(0)->position->x;
	int y = m_entities->at(0)->position->y;

  if (keyPress == ESCAPE){
    m_eventManager->pushEvent(PopScene(1));
  }else if (keyPress == NORTH){
		m_index = m_index - 1 < 0 ? inventorySize - 1 : m_index - 1;
	} else if (keyPress == SOUTH){
		m_index = m_index + 1 >= inventorySize ? 0 : m_index + 1;
	} else if (keyPress == WEAR){
		EquipEvent equipEvent = EquipEvent(0, m_entities->at(0)->inventory->inventory.at(m_index)->m_uid);
		m_eventManager->pushEvent(equipEvent);
	} else if (keyPress == DROPITEM){
		// TO DO
		DropEvent dropEvent = DropEvent(0, m_entities->at(0)->inventory->inventory.at(m_index)->m_uid, x, y);
		m_eventManager->pushEvent(DropEvent(dropEvent));
	} else if (keyPress == SHOWCHARSCREEN){
		m_eventManager->pushEvent(PopScene(1));
		m_eventManager->pushEvent(PushScene(CHARACTER));
	} else if (keyPress == USE){
		//
		m_eventManager->pushEvent(UseItemEvent(0, m_entities->at(0)->inventory->inventory.at(m_index)->m_uid));
	}
}

void InventoryScene::render()
{
	m_renderer->drawInventory(m_entities, m_index);  
}

void InventoryScene::update(Uint32 dt)
{

}

void InventoryScene::onTick()
{

}
