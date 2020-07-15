#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <map>
#include <string>
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
  void drawActors(Camera* camera, DungeonGenerator* dungeon, std::map<int, GameObject*> *actors);
  void drawMap(Camera* camera, DungeonGenerator* dungeon, std::map<int, GameObject*> *actors);
  void drawLog(MessageLog* messageLog, int height);
  void drawUI();
  void drawMenuOutline();
  void drawGameScreen(Camera* camera, DungeonGenerator* dungeon, std::map<int, GameObject*> *actors, MessageLog* messageLog);
  void drawStartMenu(int i);
	void drawInventory(std::map<int, GameObject*> *actors, int i);
	void drawEquippedItem(std::string slot, std::string item, int y, int index);
	void drawEquippedItem(std::string slot, int y, int index);
	void drawCharacterScene(std::map<int, GameObject*> *actors, int index);

private:
  Console* m_console;
  SDL_Color m_defaultColour;
  SDL_Color m_inViewColour;
};

#endif
