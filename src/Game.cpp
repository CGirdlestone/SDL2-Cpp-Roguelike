#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <time.h>

#include "DungeonGenerator.h"
#include "Console.h"
#include "InputHandler.h"
#include "KeyPressSurfaces.h"
#include "Components.h"
#include "GameObject.h"
#include "Message.h"
#include "MessageLog.h"
#include "Game.h"


Game::Game()
{
    //ctor
    m_console = nullptr;
    m_dungeon = nullptr;
    m_input = nullptr;
    m_playerPos = nullptr;
    m_playerRender = nullptr;
}

Game::~Game()
{
    //dtor
    delete m_console;
    m_console = nullptr;

    delete m_dungeon;
    m_dungeon = nullptr;

    delete m_input;
    m_input = nullptr;

    delete m_messageLog;
    m_messageLog = nullptr;

    delete m_playerPos;
    m_playerPos = nullptr;

    delete m_playerRender;
    m_playerRender = nullptr;

    for (int i = 0; i < m_actors.size(); i++){
      delete m_actors[i];
    }
}

bool Game::init(int width, int height, int tileSize, char* title, int fps)
{
    m_dungeon = new DungeonGenerator(width, height);
    m_console = new Console(width, height, title, "./resources/Cheepicus_8x8x2.png", tileSize);
    m_input = new InputHandler();
    m_messageLog = new MessageLog(width, 10);
    m_width = width;
    m_height = height;
    m_tileSize = tileSize;
    m_fps = fps;

    if (m_dungeon == nullptr || m_console == nullptr || m_input == nullptr){
        return false;
    } else {
        return true;
    }
}

void Game::drawLog()
{
    std::vector<Message> messages = m_messageLog->getMessages();

    if (messages.size() > 0){
        for(int j = 0; j < messages.size(); j++){
            Message msg = messages.at(j);
            std::cout << "Age of message: " << msg.m_lifetime << std::endl;
            for(int i = 0; i < msg.m_msg.length(); i++){
                m_console->render(&msg.m_msg[i], i, j + m_height, msg.m_colour);
            }
        }
    }
}

void Game::drawMap()
{
    int x;
    int y = 0;
    char *wall = new char[1]{'#'};
    char *space = new char[1]{' '};

    for (int i = 0; i < m_dungeon->Getm_width() * m_dungeon->Getm_height(); i++){
        x = i % m_dungeon->Getm_width();

        if (i % m_dungeon->Getm_width() == m_dungeon->Getm_width() - 1){
            if (m_dungeon->m_level[i] == '#'){
                m_console->render(wall, x, y);
            } else {
              m_console->render(space, x, y);
            }
            y++;
        } else {
            if (m_dungeon->m_level[i] == '#'){
                m_console->render(wall, x, y);
            } else {
              m_console->render(space, x, y);
            }
        }
    }

    delete[] wall;
    wall = nullptr;

    delete[] space;
    space = nullptr;
}

void Game::drawActors()
{
  if (!m_actors.empty()){
    for (int i = 0; i < m_actors.size(); i++){
      m_console->render(&m_actors[i]->renderable->chr, m_actors[i]->position->x, m_actors[i]->position->y, m_actors[i]->renderable->colour);
    }
  }
}

void Game::createPlayer()
{
    int i;
    int x;
    int y;
    bool playerPlaced = false;

    std::srand(time(0));

    SDL_Color colour = {0xef, 0xac, 0x28};
    char c = '@';

    Renderable *r = new Renderable(c, colour);

    while(!playerPlaced){
        i = std::rand()%(m_dungeon->Getm_width() * m_dungeon->Getm_height());
        if (m_dungeon->m_level[i] == '#'){
          continue;
        }
        x = i % m_dungeon->Getm_width();
        y = i / m_dungeon->Getm_width();
        playerPlaced = true;
    }

    Position *p = new Position(x, y);

    GameObject *player = new GameObject();
    player->position = p;
    player->renderable = r;
    m_actors.push_back(player);
}

bool Game::checkMove(int dx, int dy)
{
    if (m_actors.at(0)->position->x + dx>= 0 && m_actors.at(0)->position->x + dx < m_width && m_actors.at(0)->position->y + dy >= 0 && m_actors.at(0)->position->y + dy < m_height){
        if (m_dungeon->m_level[(m_actors.at(0)->position->x + dx) + m_dungeon->Getm_width() * (m_actors.at(0)->position->y + dy)] == '#'){
          return false;
        } else {
          return true;
        }
    } else {
      return false;
    }
}

void Game::movePlayer(int dx, int dy)
{
    if (checkMove(dx, dy)){
      m_actors.at(0)->position->x += dx;
      m_actors.at(0)->position->y += dy;

      m_messageLog->addMessage("Moved!");
    }
}

void Game::run()
{
    SDL_Event e;
    KeyPressSurfaces keyPress;
    m_isPlaying = true;

    m_dungeon->createMap(60, 6, 2, 5);
    createPlayer();

    Uint32 currentTime;
    Uint32 lastTime = 0;
    Uint32 dt = 0;

    while(m_isPlaying){
        currentTime = SDL_GetTicks();

        m_console->flush();
        drawMap();
        //m_console->render(&m_playerRender->chr, m_playerPos->x, m_playerPos->y, m_playerRender->colour);
        drawActors();
        drawLog();
        m_console->update();

        keyPress = m_input->getEvent(&e);
        if (keyPress == ESCAPE){
            m_isPlaying = false;
        } else if (keyPress == ARROW_LEFT){
          movePlayer(-1, 0);
        } else if (keyPress == ARROW_RIGHT){
          movePlayer(1, 0);
        } else if (keyPress == ARROW_UP){
          movePlayer(0, -1);
        } else if (keyPress == ARROW_DOWN){
          movePlayer(0, 1);
        } else if (keyPress == F1){
          m_console->setFullscreen();
        }

        dt = (currentTime - lastTime);
        lastTime = currentTime;

        m_messageLog->ageMessages(dt);
    }
    m_console->closeSDL();
}
