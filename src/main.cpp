#include <fstream>
#include <sstream>
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Game.h"

using namespace std;

int main()
{
	std::ifstream file;
	std::stringstream ss;
	int mapWidth, mapHeight, screenWidth, screenHeight, tileSize;
	std::string title;
	std::string line;

	file.open("./resources/config.txt");
	if (file.is_open()){
		getline(file, line);
		ss << line;	
		ss >> mapWidth >> mapHeight >> screenWidth >> screenHeight >> tileSize >> title;
	}

  Game* game = new Game();
  if(game->init(mapWidth, mapHeight, screenWidth, screenHeight, tileSize, title.c_str())){
      game->run();
  }
  return 0;
}
