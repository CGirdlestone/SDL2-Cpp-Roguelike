#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "Pathfind.h"

using namespace std;

Node::Node(int x, int y, int g, int h, int f, Node* parent){
  _x = x;
  _y = y;
  _g = g;
  _h = h;
  _f = f;
  _parent = parent;
}

Node::~Node(){
  if (_parent != nullptr){
    _parent = nullptr;
  }
}

bool Node::equals(Node* n){
  return _x == n->_x && _y == n->_y;
}

bool Node::equals(int x, int y){
  return _x == x && _y == y;
}


int calculate_h(int x1, int y1, int xf, int yf)
{
  return (abs(x1-xf) + abs(y1-yf))*10;
}

void getNeighbours(vector<int> *neighbours, int width, int height, int x, int y){
  int i = x + y * width;

  if (i == 0){
    // top left
    // ignore W, NW N
    for (int m = 0; m < 2; m++){
      for (int n = 0; n < 2; n++){
        if (n == 0 && m == 0){
          continue;
        }
        if (x + m >= 0 && x + m < width && y + n >= 0 && y + n < height){
          neighbours->push_back(i + m + n * width);
        }
      }
    }
  } else if (i == width - 1){
    // top right
    // ignore E, NE, N
    for (int m = -1; m < 1; m++){
      for (int n = 0; n < 2; n++){
        if (n == 0 && m == 0){
          continue;
        }
        if (x + m >= 0 && x + m < width && y + n >= 0 && y + n < height){
          neighbours->push_back(i + m + n * width);
        }
      }
    }
  } else if (i == width * height - 1){
    // bottom right
    // ignore E, SE, S
    for (int m = -1; m < 1; m++){
      for (int n = -1; n < 1; n++){
        if (n == 0 && m == 0){
          continue;
        }
        if (x + m >= 0 && x + m < width && y + n >= 0 && y + n < height){
          neighbours->push_back(i + m + n * width);
        }
      }
    }
  } else if (i == width * (height - 1)){
    // bottom left
    // ignore W, SW, S
    for (int m = 0; m < 2; m++){
      for (int n = -1; n < 1; n++){
        if (n == 0 && m == 0){
          continue;
        }
        if (x + m >= 0 && x + m < width && y + n >= 0 && y + n < height){
          neighbours->push_back(i + m + n * width);
        }
      }
    }
  } else if (i % width == 0){
    // left boundary
    // ignore W
    for (int m = 0; m < 2; m++){
      for (int n = -1; n < 2; n++){
        if (n == 0 && m == 0){
          continue;
        }
        if (x + m >= 0 && x + m < width && y + n >= 0 && y + n < height){
          neighbours->push_back(i + m + n * width);
        }
      }
    }
  } else if (i > 0 && i < width){
    // top boundary
    // ignore N
    for (int m = -1; m < 2; m++){
      for (int n = 0; n < 2; n++){
        if (n == 0 && m == 0){
          continue;
        }
        if (x + m >= 0 && x + m < width && y + n >= 0 && y + n < height){
          neighbours->push_back(i + m + n * width);
        }
      }
    }
  } else if (i % width == width - 1){
    // right boundary
    // ignore E
    for (int m = -1; m < 1; m++){
      for (int n = -1; n < 2; n++){
        if (n == 0 && m == 0){
          continue;
        }
        if (x + m >= 0 && x + m < width && y + n >= 0 && y + n < height){
          neighbours->push_back(i + m + n * width);
        }
      }
    }
  } else if (i > width * (height - 1) && i < width * height){
    // bottom boundary
    // ignore S
    for (int m = -1; m < 2; m++){
      for (int n = -1; n < 1; n++){
        if (n == 0 && m == 0){
          continue;
        }
        if (x + m >= 0 && x + m < width && y + n >= 0 && y + n < height){
          neighbours->push_back(i + m + n * width);
        }
      }
    }
  } else {
    // all other points
    for (int m = -1; m < 2; m++){
      for (int n = -1; n < 2; n++){
        if (n == 0 && m == 0){
          continue;
        }
        if (x + m >= 0 && x + m < width && y + n >= 0 && y + n < height){
          neighbours->push_back(i + m + n * width);
        }
      }
    }
  }
}

bool compareNodes(Node* n, Node* m){
  return n->_f > m->_f;
}

void aStar(char* world, vector<int> *path, int width, int height, int x1, int y1, int xf, int yf)
{
  // TO DO
  int g, h;
  int i, x, y;
  bool addChild = true;
  const int SIDE_STEP = 10;
  const int DIAGONAL_STEP = 14;
  Node *currentNode = nullptr;
  Node *child = nullptr;

  vector<Node*> openList;
  vector<Node*> closedList;
  vector<int> neighbours;

  h = calculate_h(x1, y1, xf, yf);

  Node* start = new Node(x1, y1, 0, h, h, nullptr);

  openList.push_back(start);

  while (!openList.empty()){
    addChild = true;

    sort(openList.begin(), openList.end(), compareNodes);
    currentNode = openList.back();
    openList.pop_back();

    closedList.push_back(currentNode);
    if (currentNode->equals(xf, yf)){
      while(currentNode->_parent != nullptr){
        path->push_back(currentNode->_x + currentNode->_y * width);
        currentNode = currentNode->_parent;
      }
      break;
    }

    getNeighbours(&neighbours, width, height, currentNode->_x, currentNode->_y);

    while(neighbours.size() > 0){
      i = neighbours.back();
      neighbours.pop_back();

      if (world[i] != '.'){
        continue;
      }

      x = i % width;
      y = i / width;

      if ((currentNode->_x - x) * (currentNode->_y-y) == 0){
        // cardinal axes
        g = currentNode->_g + SIDE_STEP;
      } else if ((currentNode->_x - x) * (currentNode->_y-y) != 0){
        // diagonal axes
        g = currentNode->_g + DIAGONAL_STEP;
      }

      h = calculate_h(x, y, xf, yf);

      child = new Node(x, y, g, h, g+h, currentNode);

      for(int i = 0; i < closedList.size(); ++i){
        if (closedList.at(i)->equals(child)){
          for(int i = 0; i < openList.size(); ++i){
            if (openList.at(i)->equals(child) && child->_g > openList.at(i)->_g){
              addChild = false;
            }
          }
        }
      }

      if(addChild){
        openList.push_back(child);
      } else {
        delete child;
        child = nullptr;
      }
    }
  }

  while(!openList.empty()){
    currentNode = openList.back();
    delete currentNode;
    currentNode = nullptr;
    openList.pop_back();
  }

  while(!closedList.empty()){
    currentNode = closedList.back();
    delete currentNode;
    currentNode = nullptr;
    closedList.pop_back();
  }
}
