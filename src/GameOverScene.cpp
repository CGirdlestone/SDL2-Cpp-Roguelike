#include <stdio.h>
#include <fstream>
#include "GameOverScene.h"
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "KeyPressSurfaces.h"
#include "EventManager.h"
#include "Events.h"
#include "EventTypes.h"
#include "SceneTypes.h"


GameOverScene::GameOverScene(EventManager *eventManager, Renderer *renderer):
m_eventManager(eventManager), m_renderer(renderer)
{
	m_i = 0;
	loadDeathMessage();
	timer = 75;
	ticks = 0;
	numChars = 1;
	numLines = 0;
	m_deathMessages.push_back(std::string(1, m_completeDeathMessages.at(0)[0]));
	
}

GameOverScene::~GameOverScene()
{

}

void GameOverScene::loadDeathMessage()
{
	std::ifstream file;
	std::string line;	

	file.open("./resources/death_message.txt");

	while (!file.eof()){
		std::getline(file, line);
		if( file.eof()) { break; }
		m_completeDeathMessages.push_back(line);
	}
}

bool GameOverScene::deleteSave()
{
	if(remove("save.txt") == 0){
		return true;
	} else {
		return false;
	}
}

enum KeyPressSurfaces GameOverScene::getEvent(SDL_Event *e)
{
  while(SDL_PollEvent(e)){
    if (e->type == SDL_QUIT){
      return ESCAPE;
    } else if (e->type == SDL_KEYDOWN){
      switch(e->key.keysym.sym){
        case SDLK_UP:
        return MENUUP;

        case SDLK_DOWN:
        return MENUDOWN;

        case SDLK_RETURN:
        return PRESS;
      }
    }
  }
  return NONE;
}

void GameOverScene::handleInput(KeyPressSurfaces keyPress)
{
  if (keyPress == ESCAPE){
  
	} else if (keyPress == MENUUP){
    m_i = m_i - 1 < 0 ? 1 : m_i - 1;
  } else if (keyPress == MENUDOWN){
    m_i = m_i + 1 > 1 ? 0 : m_i + 1;
  } else if (keyPress == PRESS){
		if (m_i == 0){
			m_eventManager->pushEvent(RestartEvent());
		} else if (m_i == 1){
			m_eventManager->pushEvent(QuitEvent());
		}
  }
}


void GameOverScene::render()
{
  m_renderer->drawGameOver(m_i, m_deathMessages, static_cast<int>(m_completeDeathMessages.size()));
}

void GameOverScene::update(Uint32 dt)
{
	int lines = static_cast<int>(m_completeDeathMessages.size());
	int shownLines = static_cast<int>(m_deathMessages.size());
	int finalLineLength = static_cast<int>(m_completeDeathMessages.back().size());

	ticks += dt;

	if (ticks > timer){
		if (shownLines >= lines && static_cast<int>(m_deathMessages.back().size()) == finalLineLength){
			// do nothing
		} else {
			if (static_cast<int>(m_completeDeathMessages.at(numLines).size()) == numChars + 1){
				m_deathMessages.at(numLines) += std::string(1, m_completeDeathMessages.at(numLines)[numChars]);
				numChars = 0;
				numLines += 1;
				ticks = - timer;
			} else {
				if (numChars == 0){
					m_deathMessages.push_back(std::string(1, m_completeDeathMessages.at(numLines)[numChars]));
				} else {
					m_deathMessages.at(numLines) += std::string(1, m_completeDeathMessages.at(numLines)[numChars]);
				}
				numChars += 1;
			}
		}
		ticks = 0;
	}
}

void GameOverScene::onTick()
{

}
