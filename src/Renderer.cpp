

#include "Renderer.h"

Renderer::Renderer(Console* console)
{
  m_console = console;
  m_defaultColour = {0x18, 0x79, 0x87};
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
        m_console->render(&msg.m_msg[i], i, j + height, msg.m_colour);
      }
    }
  }
}

void Renderer::drawMap(Camera* camera, DungeonGenerator* dungeon, std::vector<GameObject*> *actors)
{
  int x;
  int y = 0;
  int offsetI;
  //SDL_Color colour = {0xef, 0xd8, 0xa1};
  bool occupied;

  for (int i = 0; i < dungeon->Getm_width() * dungeon->Getm_height(); i++){
    x = i % dungeon->Getm_width();

    if (!(x >= camera->getX() && x < camera->getX() + camera->getWidth() && y >= camera->getY() && y < camera->getY() + camera->getHeight())){
      if (x == dungeon->Getm_width() - 1){
        y++;
      }
      continue;
    }

    occupied = false;
    if (dungeon->m_fovMap[i] == 1){
      for(int i = 0; i < static_cast<int>(actors->size()); i++){
        if (actors->at(i)->position->x + actors->at(i)->position->y*dungeon->Getm_width() == i){
          occupied = true;
        }
      }
      if(!occupied){
        offsetI = camera->calculateOffset(x, y);
        m_console->render(&dungeon->m_level[i], offsetI % camera->getWidth(), offsetI / camera->getWidth(), m_inViewColour);
      }
    } else if (dungeon->m_fovMap[i] == 0){
      if (dungeon->m_exploredMap[i] == 1){
        for(int i = 0; i < static_cast<int>(actors->size()); i++){
          if (actors->at(i)->position->x + actors->at(i)->position->y*dungeon->Getm_width() == i){
            occupied = true;
          }
        }
        offsetI = camera->calculateOffset(x, y);
        m_console->render(&dungeon->m_level[i], offsetI % camera->getWidth(), offsetI / camera->getWidth(), m_defaultColour);
      }
    }
    if (x == dungeon->Getm_width() - 1){
      y++;
    }
  }
}

void Renderer::drawActors(Camera* camera, DungeonGenerator* dungeon, std::vector<GameObject*> *actors)
{
  int mapArrayIndex;
  int offsetI;
  if (!actors->empty()){
    for (int i = 0; i < static_cast<int>(actors->size()); i++){
      mapArrayIndex = actors->at(i)->position->x + actors->at(i)->position->y*dungeon->Getm_width();
      if (dungeon->m_fovMap[mapArrayIndex] == 1){
        offsetI = camera->calculateOffset(actors->at(i)->position->x, actors->at(i)->position->y);
        m_console->render(&actors->at(i)->renderable->chr, offsetI % camera->getWidth(), offsetI / camera->getWidth(), actors->at(i)->renderable->colour);
      }
    }
  }
}
