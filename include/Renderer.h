#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "Console.h"
#include "GameObject.h"
#include "Message.h"
#include "MessageLog.h"
#include "Camera.h"
#include "DungeonGenerator.h"

class Renderer
{
public:
  Renderer(Console* console);
  ~Renderer();
  void drawActors(Camera* camera, DungeonGenerator* dungeon, std::vector<GameObject*> *actors);
  void drawMap(Camera* camera, DungeonGenerator* dungeon, std::vector<GameObject*> *actors);
  void drawLog(MessageLog* messageLog, int height);
  void drawUI();
  void drawMenuOutline();
  void drawGameScreen(Camera* camera, DungeonGenerator* dungeon, std::vector<GameObject*> *actors, MessageLog* messageLog);
  void drawStartMenu(int i);

private:
  Console* m_console;
  SDL_Color m_defaultColour;
  SDL_Color m_inViewColour;
};

#endif
