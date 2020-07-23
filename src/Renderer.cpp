
#include <iostream>
#include <string>
#include <map>
#include "Renderer.h"
#include "Slots.h"

Renderer::Renderer(Console* console)
{
  m_console = console;
  m_defaultColour = {0x39, 0x2a, 0x1c};
  m_inViewColour = {0xef, 0xd8, 0xa1};
}

Renderer::~Renderer()
{
  m_console = nullptr;
}

void Renderer::drawLog(MessageLog* messageLog, int height)
{
  std::vector<Message> messages = messageLog->getMessages();

  if (messages.size() > 0){
    for(int j = 0; j < static_cast<int>(messages.size()); j++){
      Message msg = messages.at(j);
      for(int i = 0; i < static_cast<int>(msg.m_msg.length()); i++){
        m_console->render(&msg.m_msg[i], i + 1, j + height+1, msg.m_colour);
      }
    }
  }
}

void Renderer::drawMap(Camera* camera, DungeonGenerator* dungeon, std::map<int, GameObject*> *actors)
{
  int x;
  int y = 0;
  int offsetI;
  //SDL_Color colour = {0xef, 0xd8, 0xa1};
  bool occupied;

  for (int i = 0; i < dungeon->Getm_width() * dungeon->Getm_height(); ++i){
    x = i % dungeon->Getm_width();

    if (!(x >= camera->getX() && x < camera->getX() + camera->getWidth() && y >= camera->getY() && y < camera->getY() + camera->getHeight())){
      if (x == dungeon->Getm_width() - 1){
        y++;
      }
      continue;
    }

    occupied = false;
    if (dungeon->m_fovMap[i] == 1){
			
			std::map<int, GameObject*>::iterator it;
      for(it = actors->begin(); it != actors->end(); ++it){
        if (it->second->position == nullptr){ continue; }

        if (it->second->position->x + it->second->position->y*dungeon->Getm_width() == i){
          occupied = true;
        }
      }
      if(!occupied){
        offsetI = camera->calculateOffset(x, y);
        m_console->render(&dungeon->m_level[i], offsetI % camera->getWidth(), offsetI / camera->getWidth(), m_inViewColour);
      }
    } else if (dungeon->m_fovMap[i] == 0){
      if (dungeon->m_exploredMap[i] == 1){

				std::map<int, GameObject*>::iterator it;
        for (it = actors->begin(); it != actors->end(); ++it){
          if (it->second->position == nullptr){ continue; }

          if (it->second->position->x + it->second->position->y*dungeon->Getm_width() == i){
            occupied = true;
          }
        }
        offsetI = camera->calculateOffset(x, y);
        m_console->render(&dungeon->m_level[i], offsetI % camera->getWidth(), offsetI / camera->getWidth(), m_defaultColour);
      }
    }
    if (x == dungeon->Getm_width() - 1){
      ++y;
    }
  }
}

void Renderer::drawActors(Camera* camera, DungeonGenerator* dungeon, std::map<int, GameObject*> *actors)
{
  int mapArrayIndex;
  int offsetI;
  if (!actors->empty()){

		std::map<int, GameObject*>::reverse_iterator it;
    for (it = actors->rbegin(); it != actors->rend(); ++it){
      if (it->second->position == nullptr){ continue; }

      mapArrayIndex = it->second->position->x + it->second->position->y*dungeon->Getm_width();
      if (dungeon->m_fovMap[mapArrayIndex] == 1){
        offsetI = camera->calculateOffset(it->second->position->x, it->second->position->y);
        m_console->render(&it->second->renderable->chr, offsetI % camera->getWidth(), offsetI / camera->getWidth(), it->second->renderable->colour);
      }
    }
  }
}

void Renderer::drawMenuOutline()
{
  SDL_Color colour = {0xef, 0xb7, 0x75};
  int xBuffer = m_console->getXBuffer();
  int yBuffer = m_console->getYBuffer();
  int height = m_console->Getm_height();
  int width = m_console->Getm_width();
  int verticalBar = 186;
  int topLeft = 201;
  int topRight = 187;
  int bottomLeft = 200;
  int bottomRight = 188;
  int horizontalBar = 205;
  int leftJoin = 185;
  int topJoin = 202;

  for (int i = 0; i < width + xBuffer; ++i){
    for (int j = 0; j < height + yBuffer; ++j){
      if (i == width && j == 0){
        m_console->render(topLeft, i, j, colour);
      } else if (i == width + xBuffer - 1 && j == 0){
        m_console->render(topRight, i, j, colour);
      } else if (i == width && j == height + yBuffer -1){
        m_console->render(topJoin, i, j, colour);
      } else if (i == width + xBuffer - 1 && j == height + yBuffer -1){
        m_console->render(bottomRight, i, j, colour);
      }else if (j == height && i == width){
        m_console->render(leftJoin, i, j, colour);
      } else if (i == width || i == width + xBuffer - 1){
        m_console->render(verticalBar, i, j, colour);
      } else if ((j == 0 || j == height + yBuffer - 1) && i > width){
        m_console->render(horizontalBar, i, j, colour);
      } else if (i == 0 && j == height){
        m_console->render(topLeft, i, j, colour);
      } else if (i == 0 && j == height + yBuffer - 1){
        m_console->render(bottomLeft, i, j, colour);
      } else if (i == 0 && j >= height){
        m_console->render(verticalBar, i, j, colour);
      } else if (j == height && i < width){
        m_console->render(horizontalBar, i, j, colour);
      } else if (j == height + yBuffer - 1 && i < width){
        m_console->render(horizontalBar, i, j, colour);
      }
    }
  }
}

void Renderer::drawUI()
{
  drawMenuOutline();
}

void Renderer::drawPlayerInfo(GameObject* player)
{
	int width = m_console->Getm_width();
	int buffer = m_console->getXBuffer()-2;
	char healthBarChar = '=';
	SDL_Color colour = {0x9b, 0x1a, 0x0a};
	int healthBarWidth = (player->fighter->health * buffer) / player->fighter->maxHealth;
	std::string health = "Health: " + std::to_string(player->fighter->health) + " / " + std::to_string(player->fighter->maxHealth);
	int yPosition = 2;
	
	for (int i = 0; i < static_cast<int>(health.length()); ++i){
		m_console->render(&health[i], width + 1 + i, yPosition, m_inViewColour);
	} 
	yPosition += 2;
	
	for (int i = 0; i < buffer; ++i){
		if (i <= healthBarWidth && healthBarWidth != 0){
			m_console->render(&healthBarChar, width + 1 + i, yPosition, colour);
		} else {
			m_console->render(&healthBarChar, width + 1 + i, yPosition, m_defaultColour);
		}
	} 
	yPosition += 2;
	
	colour = {0x3c, 0x9f, 0x9c};

	int expBarWidth = (player->player->exp * buffer) / (player->player->next);
	std::string exp = "Exp: " + std::to_string(player->player->exp) + " / " + std::to_string(player->player->next);

	for (int i = 0; i < static_cast<int>(exp.length()); ++i){
		m_console->render(&exp[i], width + 1 + i, yPosition, m_inViewColour);
	} 
	yPosition += 2;
	
	for (int i = 0; i < buffer; ++i){
		if (i <= expBarWidth && expBarWidth != 0){
			m_console->render(&healthBarChar, width + 1 + i, yPosition, colour);
		} else {
			m_console->render(&healthBarChar, width + 1 + i, yPosition, m_defaultColour);
		}
	} 
	yPosition += 2;
	
	std::string level = "Level: " + std::to_string(player->player->level);

	for (int i = 0; i < static_cast<int>(level.length()); ++i){
		m_console->render(&level[i], width + 1 + i, yPosition, m_inViewColour);
	}
	yPosition += 2;
}

void Renderer::drawStartMenu(int i)
{
  int width = m_console->Getm_width() + m_console->getXBuffer();
  int height = m_console->Getm_height() + m_console->getYBuffer();
  std::string name = "ROGUELIKE";
  std::string startText = "START GAME";
  std::string exitText = "EXIT GAME";

  m_console->flush();

  for (int j = 0; j < static_cast<int>(name.length()); ++j){
    m_console->render(&name[j], width/2 + j - 5, height/2-4, m_defaultColour);
  }

  for (int j = 0; j < static_cast<int>(startText.length()); ++j){
    if (i == 0){
      m_console->render(&startText[j], width/2 + j - 5, height/2, m_inViewColour);
    } else {
      m_console->render(&startText[j], width/2 + j - 5, height/2, m_defaultColour);
    }
  }

  for (int j = 0; j < static_cast<int>(exitText.length()); ++j){
    if (i == 1){
      m_console->render(&exitText[j], width/2 + j - 5, height/2+4, m_inViewColour);
    } else {
      m_console->render(&exitText[j], width/2 + j - 5, height/2+4, m_defaultColour);
    }
  }

  m_console->update();
}

void Renderer::drawInventory(std::map<int, GameObject*> *actors, int i)
{
	m_console->flush();

	std::string inventoryHeader = "Inventory";
	std::string selectedItem;

	for (int k = 0; k < static_cast<int>(inventoryHeader.length()); ++k){
		m_console->render(&inventoryHeader[k], 2 + k, 1, m_inViewColour);
	}

	if (actors->at(0)->inventory->inventory.size() > 0){
		for (int k = 0; k < static_cast<int>(actors->at(0)->inventory->inventory.size());++k){
			GameObject* item = actors->at(0)->inventory->inventory.at(k);
			if (k == i){
				selectedItem = ">" + item->m_name;
				for (int j = 0; j < static_cast<int>(selectedItem.length()); ++j){
					m_console->render(&selectedItem[j], 1 + j, 2*k + 3, m_inViewColour);
				}
			} else {
				for (int j = 0; j < static_cast<int>(item->m_name.length()); ++j){
					m_console->render(&item->m_name[j], 2 + j, 2*k + 3, m_defaultColour);
				}
			}
		}
	}

	m_console->update();
}

void Renderer::drawEquippedItem(std::string slot, std::string item, int y, int index)
{
	std::string equipmentSlot = slot + item;

	if (index == y){
		equipmentSlot = ">" + equipmentSlot;
	}	

	for (int j = 0; j < static_cast<int>(equipmentSlot.length()); ++j){
		if (index == y){
			m_console->render(&equipmentSlot[j], j + 2, 3 + 2 * y, m_inViewColour);
		} else {
			m_console->render(&equipmentSlot[j], j + 3, 3 + 2 * y, m_defaultColour);
		}	
	}
}

void Renderer::drawEquippedItem(std::string slot, int y, int index)
{
	std::string equipmentSlot = slot + "empty";
	
	if (index == y){
		equipmentSlot = ">" + equipmentSlot;
	}
	
	for (int j = 0; j < static_cast<int>(equipmentSlot.length()); ++j){
		if (index == y){
			m_console->render(&equipmentSlot[j], j + 2, 3 + 2 * y, m_inViewColour);
		} else {
			m_console->render(&equipmentSlot[j], j + 3, 3 + 2 * y, m_defaultColour);
		}
	}
} 

void Renderer::drawCharacterScene(std::map<int, GameObject*> *actors, int index)
{
	m_console->flush();

	std::string character = "Character Screen";
	std::string slot;

	for (int j = 0; j < static_cast<int>(character.length()); ++j){
		m_console->render(&character[j], j + 3, 1, m_inViewColour);
	}	

	for (std::map<EquipSlots, GameObject*>::iterator iter = actors->at(0)->body->slots.begin(); iter != actors->at(0)->body->slots.end(); ++iter){

		switch(iter->first){
			case HEAD: slot = "Head: "; break;
			case LEFTHAND: slot = "Left Hand: "; break;
			case RIGHTHAND: slot = "Right Hand: "; break;
			case BODY: slot = "Body: "; break;
			case NECK: slot = "Amulet: "; break;
			case BACK: slot = "Cloak: "; break;
		}

		if (iter->second != nullptr){
			drawEquippedItem(slot, iter->second->m_name, static_cast<int>(iter->first), index);
		} else {
			drawEquippedItem(slot, static_cast<int>(iter->first), index);
		}
	} 
	
	m_console->update();
}

void Renderer::drawTargetingScene(Camera* camera, DungeonGenerator* dungeon, std::map<int, GameObject*> *actors, MessageLog* messageLog, int radius, std::vector<int> *path)
{
	int offsetI, x, y;	
  m_console->flush();
  drawMap(camera, dungeon, actors);
  drawActors(camera, dungeon, actors);
  drawLog(messageLog, camera->getHeight());
  drawUI();
	drawPlayerInfo(actors->at(0));

	for (int i = 0; i < static_cast<int>(path->size()); ++i){
		x = path->at(i) % dungeon->Getm_width();
		y = path->at(i) / dungeon->Getm_width();
	
	  offsetI = camera->calculateOffset(x, y);

		if (checkInRange(x, y, actors->at(0)->position->x, actors->at(0)->position->y, radius)){
			SDL_Color colour = {0x39, 0x57, 0x1c};
 			m_console->fillBackgroundTile(offsetI % camera->getWidth(), offsetI / camera->getWidth(), colour);
  	} else {
			SDL_Color colour = {0x9b, 0x1a, 0x0a};
 			m_console->fillBackgroundTile(offsetI % camera->getWidth(), offsetI / camera->getWidth(), colour);
		}
	}

	m_console->update();
}

void Renderer::drawGameScreen(Camera* camera, DungeonGenerator* dungeon, std::map<int, GameObject*> *actors, MessageLog* messageLog)
{
  m_console->flush();
  drawMap(camera, dungeon, actors);
  drawActors(camera, dungeon, actors);
  drawLog(messageLog, camera->getHeight());
  drawUI();
	drawPlayerInfo(actors->at(0));
  m_console->update();
}
