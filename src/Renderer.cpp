
#include <iostream>
#include <string>
#include <map>
#include "Renderer.h"
#include "Slots.h"

Renderer::Renderer(Console* console)
{
  m_console = console;
  m_defaultColour = {0x3a, 0x4b, 0x6d};
  m_inViewColour = {0xb4, 0xc3, 0xa8}; // 0xde, 0xed, 0xd6
	m_borderColour = {0x99, 0xb4, 0xdd};
	m_highlightColour = {0xd3, 0xea, 0xd8};
	m_backgroundColour = {0x0d, 0x0e, 0x1e};
	m_textColour = {0x94, 0xa5, 0xaa};
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
        m_console->render(&dungeon->m_level[i], offsetI % camera->getWidth()+camera->getXBuffer(), offsetI / camera->getWidth()+camera->getYBuffer(), m_inViewColour);
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
        m_console->render(&dungeon->m_level[i], offsetI % camera->getWidth()+camera->getXBuffer(), offsetI / camera->getWidth()+camera->getYBuffer(), m_defaultColour);
      }
    }
    if (x == dungeon->Getm_width() - 1){
      ++y;
    }
  }
}

void Renderer::drawMiniMap(DungeonGenerator* dungeon, std::map<int, GameObject*> *actors)
{
	int mapOriginX = (m_console->Getm_width() + 2) * m_console->getTileSize();
	int mapOriginY = (m_console->Getm_height() - 2) * m_console->getTileSize();

	SDL_Color player = {0x00, 0x00, 0x00};
	SDL_Color enemy = {0xd0, 0x46, 0x48};
	SDL_Color item = {0x34, 0x65, 0x24};
	SDL_Color other = {0x22, 0x20, 0x34};

	SDL_Color lightWall = {0x75, 0x71, 0x61};
	SDL_Color darkWall = {0x4e, 0x4a, 0x4e};

	for (int i = 0; i < dungeon->Getm_width() * dungeon->Getm_height(); ++i){
		if (dungeon->m_level[i] == ' '){ continue; }	
		if (dungeon->m_exploredMap[i] == 0){ continue; }
		
		if (dungeon->m_fovMap[i] == 0){
			if (dungeon->m_level[i] == '#'){
				m_console->fillBackgroundTile(i%dungeon->Getm_width(), i/dungeon->Getm_width(), darkWall, 255, 2, mapOriginX, mapOriginY);
			} else {
				m_console->fillBackgroundTile(i%dungeon->Getm_width(), i/dungeon->Getm_width(), m_defaultColour, 255, 2, mapOriginX, mapOriginY);
			}
		} else if (dungeon->m_fovMap[i] == 1){
			if (dungeon->m_level[i] == '#'){
				m_console->fillBackgroundTile(i%dungeon->Getm_width(), i/dungeon->Getm_width(), lightWall, 255, 2, mapOriginX, mapOriginY);
			} else {
				m_console->fillBackgroundTile(i%dungeon->Getm_width(), i/dungeon->Getm_width(), m_inViewColour, 255, 2, mapOriginX, mapOriginY);
			}
		}
	}
	
	std::map<int, GameObject*>::iterator it;
	for (it = actors->begin(); it != actors->end(); ++it){
		if (it->second->position == nullptr){ continue; }

		if (dungeon->m_fovMap[it->second->position->x + it->second->position->y * dungeon->Getm_width()] == 0){ continue; }		

		if (it->first == 0){
			m_console->fillBackgroundTile(it->second->position->x, it->second->position->y, player, 255, 2, mapOriginX, mapOriginY);
		} else if (it->second->item != nullptr){
			m_console->fillBackgroundTile(it->second->position->x, it->second->position->y, item, 255, 2, mapOriginX, mapOriginY);
		} else if (it->second->ai != nullptr){
			m_console->fillBackgroundTile(it->second->position->x, it->second->position->y, enemy, 255, 2, mapOriginX, mapOriginY);
		} else {
			m_console->fillBackgroundTile(it->second->position->x, it->second->position->y, other, 255, 2, mapOriginX, mapOriginY);
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
        m_console->render(&it->second->renderable->chr, offsetI % camera->getWidth()+camera->getXBuffer(), offsetI / camera->getWidth()+camera->getYBuffer(), it->second->renderable->colour);
      }
    }
  }
}

void Renderer::drawMenuOutline()
{
	int tileSize = m_console->getTileSize();
	int windowHeight = m_console->Getm_height() + m_console->getYBuffer();
  int xBuffer = m_console->getXBuffer();
  int yBuffer = m_console->getYBuffer();
  int height = m_console->Getm_height();
  int width = m_console->Getm_width();
	int block = 13*16 + 11;

	int miniMapBarTopPos = (windowHeight * tileSize - 160)/tileSize - 2;

  for (int i = 0; i < width + xBuffer; ++i){
    for (int j = 0; j < height + yBuffer; ++j){
      if (i == width && j == 0){
        m_console->render(block, i, j, m_borderColour);
      } else if (i == width + xBuffer - 1 && j == 0){
        m_console->render(block, i, j, m_borderColour);
      } else if (i == width && j == height + yBuffer -1){
        m_console->render(block, i, j, m_borderColour);
      } else if (i == width + xBuffer - 1 && j == height + yBuffer -1){
        m_console->render(block, i, j, m_borderColour);
			} else if (j == miniMapBarTopPos && i == width){
				m_console->render(block, i, j, m_borderColour);
      } else if ((j == height && i == width)){
        m_console->render(block, i, j, m_borderColour);
			} else if (j == miniMapBarTopPos && i == width + xBuffer - 1){
        m_console->render(block, i, j, m_borderColour);
      } else if (i == width || i == width + xBuffer - 1){
        m_console->render(block, i, j, m_borderColour);
			} else if (j == miniMapBarTopPos && (i > width && i < width + xBuffer) ){
				m_console->render(block, i, j, m_borderColour);
      } else if ((j == 0 || j == height + yBuffer - 1) && i > width){
        m_console->render(block, i, j, m_borderColour);
      } else if (i == 0 && j == height){
        m_console->render(block, i, j, m_borderColour);
      } else if (i == 0 && j == height + yBuffer - 1){
        m_console->render(block, i, j, m_borderColour);
      } else if (i == 0 && j >= height){
        m_console->render(block, i, j, m_borderColour);
      } else if (j == height && i < width){
        m_console->render(block, i, j, m_borderColour);
      } else if (j == height + yBuffer - 1 && i < width){
        m_console->render(block, i, j, m_borderColour);
      }
    }
  }
}

void Renderer::drawUI()
{
  drawMenuOutline();
}

void Renderer::drawPlayerInfo(GameObject* player, DungeonGenerator* dungeon)
{
	int width = m_console->Getm_width();
	int buffer = m_console->getXBuffer()-2;
	int healthBarChar = 13 * 16 + 11; // solid block
	SDL_Color colour = {0xd0, 0x46, 0x48};
	int healthBarWidth = (player->fighter->health * buffer) / player->fighter->maxHealth;
	std::string health = "Health: " + std::to_string(player->fighter->health) + " / " + std::to_string(player->fighter->maxHealth);
	int yPosition = 2;
	
	for (int i = 0; i < static_cast<int>(health.length()); ++i){
		m_console->render(&health[i], width + 1 + i, yPosition, m_textColour);
	} 
	yPosition += 2;
	
	for (int i = 0; i < buffer; ++i){
		if (i <= healthBarWidth && healthBarWidth != 0){
			m_console->render(healthBarChar, width + 1 + i, yPosition, colour);
		} else {
			m_console->render(healthBarChar, width + 1 + i, yPosition, m_defaultColour);
		}
	} 
	yPosition += 2;
	
	colour = {0x59, 0x7d, 0xce};

	int expBarWidth = (player->player->exp * buffer) / (player->player->next);
	std::string exp = "Exp: " + std::to_string(player->player->exp) + " / " + std::to_string(player->player->next);

	for (int i = 0; i < static_cast<int>(exp.length()); ++i){
		m_console->render(&exp[i], width + 1 + i, yPosition, m_textColour);
	} 
	yPosition += 2;
	
	for (int i = 0; i < buffer; ++i){
		if (i <= expBarWidth && expBarWidth != 0){
			m_console->render(healthBarChar, width + 1 + i, yPosition, colour);
		} else {
			m_console->render(healthBarChar, width + 1 + i, yPosition, m_defaultColour);
		}
	} 
	yPosition += 2;
	
	std::string level = "Level: " + std::to_string(player->player->level);

	for (int i = 0; i < static_cast<int>(level.length()); ++i){
		m_console->render(&level[i], width + 1 + i, yPosition, m_textColour);
	}
	yPosition += 2;

	std::string depth = "Depth: " + std::to_string(dungeon->m_uid);

	for (int i = 0; i < static_cast<int>(depth.length()); ++i){
		m_console->render(&depth[i], width + 1 + i, yPosition, m_textColour);
	}
	yPosition += 2;

	
}

void Renderer::drawStartMenu(int i, int options)
{
  int width = m_console->Getm_width() + m_console->getXBuffer();
  int height = m_console->Getm_height() + m_console->getYBuffer();
  std::string name = "ROGUELIKE";
  std::string startText = "START GAME";
  std::string exitText = "EXIT GAME";
	std::string continueText = "CONTINUE";

	int yPosition = height/2 - 4;

	if ((options == 2 && i == 0) || (options == 3 && i == 1)){
		startText = ">" + startText;
	} else if ((options == 2 && i == 1) || (options == 3 && i == 2)){
		exitText = ">" + exitText;
	} else {
		continueText = ">" + continueText;
	}

  m_console->flush();

  for (int j = 0; j < static_cast<int>(name.length()); ++j){
    m_console->render(&name[j], width/2 + j - 5, yPosition, m_textColour);
  }
	
	yPosition += 2;

	if (options == 3){
		
  	for (int j = 0; j < static_cast<int>(continueText.length()); ++j){
    	if (i == 0){
      	m_console->render(&continueText[j], width/2 - 1 + j - 5, yPosition, m_highlightColour);
    	} else {
      	m_console->render(&continueText[j], width/2 + j - 5, yPosition, m_textColour);
    	}
  	}
		yPosition += 2;
	}
	

  for (int j = 0; j < static_cast<int>(startText.length()); ++j){
    if ((options == 3 && i == 1) || (options == 2 && i == 0)){
      m_console->render(&startText[j], width/2 - 1 + j - 5, yPosition, m_highlightColour);
    } else {
      m_console->render(&startText[j], width/2 + j - 5, yPosition, m_textColour);
    }
  }
	yPosition += 2;

  for (int j = 0; j < static_cast<int>(exitText.length()); ++j){
    if ((options == 3 && i == 2) || (options == 2 && i == 1)){
      m_console->render(&exitText[j], width/2 - 1 + j - 5, yPosition, m_highlightColour);
    } else {
      m_console->render(&exitText[j], width/2 + j - 5, yPosition, m_textColour);
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
		m_console->render(&inventoryHeader[k], 2 + k, 1, m_textColour);
	}

	if (actors->at(0)->inventory->inventory.size() > 0){
		for (int k = 0; k < static_cast<int>(actors->at(0)->inventory->inventory.size());++k){
			GameObject* item = actors->at(0)->inventory->inventory.at(k);
			if (k == i){
				selectedItem = ">" + item->m_name;
				for (int j = 0; j < static_cast<int>(selectedItem.length()); ++j){
					m_console->render(&selectedItem[j], 1 + j, 2*k + 3, m_highlightColour);
				}
			} else {
				for (int j = 0; j < static_cast<int>(item->m_name.length()); ++j){
					m_console->render(&item->m_name[j], 2 + j, 2*k + 3, m_textColour);
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
			m_console->render(&equipmentSlot[j], j + 2, 3 + 2 * y, m_highlightColour);
		} else {
			m_console->render(&equipmentSlot[j], j + 3, 3 + 2 * y, m_textColour);
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
			m_console->render(&equipmentSlot[j], j + 2, 3 + 2 * y, m_highlightColour);
		} else {
			m_console->render(&equipmentSlot[j], j + 3, 3 + 2 * y, m_textColour);
		}
	}
} 

void Renderer::drawCharacterScene(std::map<int, GameObject*> *actors, int index)
{
	m_console->flush();

	std::string character = "Character Screen";
	std::string slot;

	for (int j = 0; j < static_cast<int>(character.length()); ++j){
		m_console->render(&character[j], j + 3, 1, m_textColour);
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

void Renderer::drawPauseMenu(int index, Camera* camera, DungeonGenerator* dungeon, std::map<int, GameObject*> *actors, MessageLog* messageLog)
{
	m_console->flush();

	drawGameMapBorder(camera->getXBuffer(), camera->getYBuffer(), camera->getWidth(), camera->getHeight());	
  drawMap(camera, dungeon, actors);
  drawActors(camera, dungeon, actors);
  drawLog(messageLog, camera->getHeight()+camera->getYBuffer());
  drawUI();
	drawPlayerInfo(actors->at(0), dungeon);
	drawMiniMap(dungeon, actors);

  int width = m_console->Getm_width();
  int height = m_console->Getm_height();
  std::string startText = "CONTINUE";
  std::string exitText = "EXIT GAME";

	int xOrigin = width/2 - 5;
	int yOrigin = height/2 - 2;
	int boxWidth = startText.size() < exitText.size() ? static_cast<int>(exitText.size())+4 : static_cast<int>(startText.size())+4;
	int boxHeight = 7;

	int block = 13*16 + 11;
	
	for (int h = 0; h < boxHeight; ++h){
		for (int j = 0; j < boxWidth; ++j){
			m_console->fillBackgroundTile(xOrigin+j, yOrigin+h, m_backgroundColour, 255, m_console->getTileSize(), 0, 0);
		}
	}

	for (int h = 0; h < boxHeight; ++h){
		for (int j = 0; j < boxWidth; ++j){
			if (j == 0 && h == 0){
				m_console->render(block, xOrigin+j, yOrigin+h, m_borderColour);
			} else if (j == 0 && h == boxHeight - 1){
				m_console->render(block, xOrigin+j, yOrigin+h, m_borderColour);
			} else if (j == boxWidth - 1 && h == 0){
				m_console->render(block, xOrigin+j, yOrigin+h, m_borderColour);
			} else if (j == boxWidth - 1 && h == boxHeight - 1){
				m_console->render(block, xOrigin+j, yOrigin+h, m_borderColour);
			} else if (j == 0 || j == boxWidth -1){
				m_console->render(block, xOrigin+j, yOrigin+h, m_borderColour);
			}	else if (h == 0 || h == boxHeight - 1){
				m_console->render(block, xOrigin+j, yOrigin+h, m_borderColour);
			}

			if (h == 2){
				if (j > static_cast<int>(startText.size())){ continue; }
				if (j == 0){ continue; }

    		if (index == 0){
      		m_console->render(&startText[j-1], xOrigin+j+1, yOrigin+h, m_highlightColour);
   			} else {
      		m_console->render(&startText[j-1], xOrigin+j+1, yOrigin+h, m_textColour);
				}
			} else if (h == 4){
				if (j > static_cast<int>(exitText.size())){ continue; }
				if (j == 0){ continue; }
				if (index == 1){
      		m_console->render(&exitText[j-1], xOrigin+j+1, yOrigin+h, m_highlightColour);
    		} else {
      		m_console->render(&exitText[j-1], xOrigin+j+1, yOrigin+h, m_textColour);
				}
			}
		}
	}

	m_console->update();
}

void Renderer::drawTargetingScene(Camera* camera, DungeonGenerator* dungeon, std::map<int, GameObject*> *actors, MessageLog* messageLog, int radius, std::vector<int> *path, int splashRadius, int _x, int _y)
{
	int offsetI, x, y;
	
  m_console->flush();
	drawGameMapBorder(camera->getXBuffer(), camera->getYBuffer(), camera->getWidth(), camera->getHeight());
  drawMap(camera, dungeon, actors);
  drawActors(camera, dungeon, actors);
  drawLog(messageLog, camera->getHeight()+camera->getYBuffer());
  drawUI();
	drawPlayerInfo(actors->at(0), dungeon);
	drawMiniMap(dungeon, actors);

	for (int i = 0; i < static_cast<int>(path->size()); ++i){
		x = path->at(i) % dungeon->Getm_width();
		y = path->at(i) / dungeon->Getm_width();
	
	  offsetI = camera->calculateOffset(x, y);

		if (checkInRange(x, y, actors->at(0)->position->x, actors->at(0)->position->y, radius)){
			SDL_Color colour = {0x6d, 0xaa, 0x2c};
 			m_console->fillBackgroundTile(offsetI % camera->getWidth()+camera->getXBuffer(), offsetI / camera->getWidth()+camera->getYBuffer(), colour);
  	} else {
			SDL_Color colour = {0xd0, 0x46, 0x48};
 			m_console->fillBackgroundTile(offsetI % camera->getWidth()+camera->getXBuffer(), offsetI / camera->getWidth()+camera->getYBuffer(), colour);
		}
	}

	if (splashRadius > 0){
		for (int i = -splashRadius; i <= splashRadius; ++i){
			for (int j = -splashRadius; j <= splashRadius; ++j){
				
				offsetI = camera->calculateOffset(_x-i, _y-j);
							
				if (checkInRange(_x, _y, actors->at(0)->position->x, actors->at(0)->position->y, radius)){
					SDL_Color colour = {0x6d, 0xaa, 0x2b};
 					m_console->fillBackgroundTile(offsetI % camera->getWidth()+camera->getXBuffer(), offsetI / camera->getWidth()+camera->getYBuffer(), colour);
  			} else {
					SDL_Color colour = {0xd0, 0x46, 0x48};
 					m_console->fillBackgroundTile(offsetI % camera->getWidth()+camera->getXBuffer(), offsetI / camera->getWidth()+camera->getYBuffer(), colour);
				}
			}
		} 
	}

	m_console->update();
}

void Renderer::drawParticles(Camera* camera, DungeonGenerator* dungeon, std::vector<Particle> &particles)
{
	SDL_Color colour;
	int offsetI;
	for (auto p : particles){
		colour = {p.red, p.green, p.blue};
		offsetI = camera->calculateOffset(p.x, p.y);
		if (p.steps % 2 == 0){
			m_console->fillBackgroundTile(0, 0, colour, 255, p.size, (offsetI % camera->getWidth() +camera->getXBuffer()) * m_console->getTileSize(), (offsetI / camera->getWidth() + camera->getYBuffer()) * m_console->getTileSize());
		} 
	}
}

void Renderer::drawGameMapBorder(int xBuffer, int yBuffer, int width, int height)
{
	int block = 13*16 + 11;

	for (int i = 0; i < width + 2 * xBuffer; ++i){
		for (int j = 0; j < height + 2 * yBuffer; ++j){
			if (i == 0 && j == 0){
				m_console->render(block, i, j, m_borderColour);
			} else if (i == width + xBuffer && j == 0){
				m_console->render(block, i, j, m_borderColour);
			} else if (i == 0 && j == height + yBuffer){
				m_console->render(block, i, j, m_borderColour);
			} else if (i == width + xBuffer && j == height + yBuffer){
				m_console->render(block, i, j, m_borderColour);
			} else if (i == 0){
				m_console->render(block, i, j, m_borderColour);
			} else if (j == 0){
				m_console->render(block, i, j, m_borderColour);
			}
		}
	}
}

void Renderer::drawGameScreen(Camera* camera, DungeonGenerator* dungeon, std::map<int, GameObject*> *actors, MessageLog* messageLog, std::vector<Particle> &particles)
{
  m_console->flush();
	drawGameMapBorder(camera->getXBuffer(), camera->getYBuffer(), camera->getWidth(), camera->getHeight());
  drawMap(camera, dungeon, actors);
  drawActors(camera, dungeon, actors);
  drawLog(messageLog, camera->getHeight()+camera->getYBuffer());
  drawUI();
	drawPlayerInfo(actors->at(0), dungeon);
	drawMiniMap(dungeon, actors);
	drawParticles(camera, dungeon, particles);
  m_console->update();
}

void Renderer::drawGameOver(int i, std::vector<std::string> &deathMessages, int totalLines)
{
	std::string restart = "Play again";
	std::string exitGame = "Exit game";
	
  int width = m_console->Getm_width() + m_console->getXBuffer();
  int height = m_console->Getm_height() + m_console->getYBuffer();

	int xPosition = width/2 - 15;

	int yPosition = height/2 - 16;

	if (i == 0){
		restart = ">" + restart;
	} else if (i == 1){
		exitGame = ">" + exitGame;
	}

  m_console->flush();

	for (std::string line : deathMessages){
  	for (int j = 0; j < static_cast<int>(line.length()); ++j){
    	m_console->render(&line[j], xPosition + j, yPosition, m_textColour);
  	}
		yPosition += 2;
	}

	for (int i = 0; i < static_cast<int>(totalLines - deathMessages.size()); ++i){
		yPosition += 2;
	}

	yPosition += 1;
	
  for (int j = 0; j < static_cast<int>(restart.length()); ++j){
    if (i == 0){
      m_console->render(&restart[j], xPosition - 1 + j + 10, yPosition, m_highlightColour);
    } else {
      m_console->render(&restart[j], xPosition + j + 10, yPosition, m_textColour);
    }
  }
	yPosition += 2;
	
  for (int j = 0; j < static_cast<int>(exitGame.length()); ++j){
		if (i == 1){
      m_console->render(&exitGame[j], xPosition - 1 + j + 10, yPosition, m_highlightColour);
    } else {
      m_console->render(&exitGame[j], xPosition + j + 10, yPosition, m_textColour);
    }
  }
	yPosition += 2;

  m_console->update();
}
