
#include <vector>
#include <map>

#include "GameStateManager.h"
#include "EventManager.h"
#include "Events.h"
#include "EventTypes.h"
#include "StartScene.h"
#include "GameScene.h"
#include "InventoryScene.h"
#include "CharacterScene.h"
#include "GameOverScene.h"
#include "SceneTypes.h"

GameStateManager::GameStateManager(EventManager* eventManager, std::map<int, GameObject*> *entities):
m_eventManager(eventManager), m_entities(entities)
{
  m_eventManager->registerSystem(POPSCENE, this);
  m_eventManager->registerSystem(PUSHSCENE, this);
  m_eventManager->registerSystem(QUIT, this);
	m_eventManager->registerSystem(PASSUSERINFO, this);
	m_eventManager->registerSystem(DEAD, this);
	m_eventManager->registerSystem(PLAYERTURNOVER, this);
	m_eventManager->registerSystem(LOADGAME, this);
	m_eventManager->registerSystem(RESTART, this);

  m_startScene = nullptr;
  m_gameScene = nullptr;
	m_inventoryScene = nullptr;
	m_characterScene = nullptr;
	m_targetingScene = nullptr;
	m_pauseScene = nullptr;
	m_gameOverScene = nullptr;

  playing = true;
}

GameStateManager::~GameStateManager()
{
  m_eventManager = nullptr;
  m_entities = nullptr;
	m_startScene = nullptr;
	m_gameScene = nullptr;
	m_inventoryScene = nullptr;
	m_characterScene = nullptr;
	m_targetingScene = nullptr;
	m_pauseScene = nullptr;
	m_gameOverScene = nullptr;
};

void GameStateManager::notify(PushScene event)
{
  if (event.m_scene == STARTMENU){
    m_sceneStack.push_back(m_startScene);
  } else if (event.m_scene == GAMESCENE){
    m_sceneStack.push_back(m_gameScene);
		m_gameScene->newGame();
  } else if (event.m_scene == INVENTORY){
		m_sceneStack.push_back(m_inventoryScene);
		m_inventoryScene->resetIndex();
	} else if (event.m_scene == CHARACTER){
		m_sceneStack.push_back(m_characterScene);
		m_characterScene->resetIndex();
	} else if (event.m_scene == TARGETING){
		if (static_cast<int>(m_sceneStack.size()) == 1){
			m_sceneStack.push_back(m_gameScene);
		}
		m_sceneStack.push_back(m_targetingScene);
		m_targetingScene->resetIndex();
	} else if (event.m_scene == PAUSEMENU){
		m_sceneStack.push_back(m_pauseScene);
		m_targetingScene->resetIndex();
	} 
}

void GameStateManager::notify(PopScene event)
{
  for (int i = 0; i < event.m_numPops; ++i){
    m_sceneStack.pop_back();
  }
}

void GameStateManager::notify(QuitEvent event)
{
  playing = false;
}

void GameStateManager::notify(DeadEvent event)
{
	if (event.m_uid == 0){
		m_sceneStack.push_back(m_gameOverScene);
		m_gameOverScene->deleteSave();
	}
}

void GameStateManager::notify(PassUserInfoEvent event)
{
	m_targetingScene->m_user_uid = event.m_user_uid;
	m_targetingScene->m_item_uid = event.m_item_uid;
}

void GameStateManager::notify(PlayerTurnOverEvent event)
{
	m_gameScene->finishPlayerTurn();
}

void GameStateManager::notify(LoadEvent event)
{
	m_sceneStack.push_back(m_gameScene);
	m_gameScene->loadGame();
}
void GameStateManager::notify(RestartEvent event)
{
	while (m_sceneStack.size() > 1){
		m_sceneStack.pop_back();
	}
	m_startScene->reset();
	m_gameScene->startOver();
}

void GameStateManager::processInput(SDL_Event *e)
{
  KeyPressSurfaces keyPress;
  keyPress = m_sceneStack.back()->getEvent(e);
  m_sceneStack.back()->handleInput(keyPress);
}

void GameStateManager::update(Uint32 dt)
{
  m_sceneStack.back()->update(dt);
}

void GameStateManager::onTick()
{
}

void GameStateManager::render()
{
  m_sceneStack.back()->render();
}
