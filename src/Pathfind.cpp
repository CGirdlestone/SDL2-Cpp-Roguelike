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

	for (int m = -1; m < 2; ++m){
		for (int n = -1; n < 2; ++n){
			if (n == 0 && m == 0){ continue; }

      if (x + m >= 0 && x + m < width && y + n >= 0 && y + n < height){
        neighbours->push_back(i + m + n * width);
      }
		}
	}
}

bool compareNodes(Node* n, Node* m){
  return n->_f > m->_f;
}

void aStar(char* world, vector<int> *path, int width, int height, int x1, int y1, int xf, int yf)
{
  int g, h;
  int i, x, y;
  bool addChild;
	bool inClosedList;
  const int SIDE_STEP = 10;
  const int DIAGONAL_STEP = 14;
  Node *currentNode = nullptr;
  Node *child = nullptr;

  vector<Node*> openList;
  vector<Node*> closedList;
  vector<int> neighbours;

	std::string tmp;

  h = calculate_h(x1, y1, xf, yf);

  Node* start = new Node(x1, y1, 0, h, h, nullptr);

  openList.push_back(start);

  while (!openList.empty()){

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
    	addChild = false;
			inClosedList = false;
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
			
      for(int i = 0; i < static_cast<int>(closedList.size()); ++i){
				if (closedList.at(i)->equals(child)){
					inClosedList = true;
					if (child->_g < closedList.at(i)->_g){
						addChild = true;
						break;
					}
				}
			}

			if (addChild || !inClosedList){
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

float getGradient(int x1, int y1, int xf, int yf)
{
	return static_cast<float>(yf - y1) / static_cast<float>(xf - x1);
}

void getBresenhamLine(std::vector<int> *path, int width, int x1, int y1, int xf, int yf)
{
	float error = 0;
	int x = x1;
	int y = y1;
	float m;

	path->push_back(x1 + y1*width);

	if (x1 == xf){
		if (yf >= y1){
			for (int i = 0; i < yf - y1; ++i){
				path->push_back(x1 + (y1 + i)*width);
			}
		} else if (yf < y1){
			for (int i = 0; i < y1 - yf; ++i){
				path->push_back(x1 + (y1 - i)*width);
			}
		}
	}	else {
		m = getGradient(x1, y1, xf, yf);


		if (m >= -1 && m <= 1){

			if (xf >= x1){
				for (int i = 0; i < xf - x1; ++i){
					error += std::abs(m);
					if (error > 0.5){
						if (yf >= y1){
							y += 1;
						} else {
							y -= 1;
						}
						error -= 1.0;
					}
					path->push_back((x1+i) + y * width);
				}
			} else if (x1 > xf){
				for (int i = 0; i < x1 - xf; ++i){
					error += std::abs(m);
					if (error > 0.5){
						if (yf >= y1){
							y += 1;
						} else {
							y -= 1;
						}
						error -= 1.0;
					}
					path->push_back((x1-i) + y * width);
				}
			}
		} else {
			m = 1.0 / m;

			if (yf >= y1){
				for (int i = 0; i < yf - y1; ++i){
					error += std::abs(m);
					if (error > 0.5){
						if (xf >= x1){
							x += 1;
						} else {
							x -= 1;
						}
						error -= 1.0;
					}
					path->push_back(x + (y1+i) * width);
				}
			} else if (y1 > yf) {
				for (int i = 0; i < y1 - yf; ++i){
					error += std::abs(m);
					if (error > 0.5){
						if (x1 >= xf){
							x -= 1;
						} else {
							x += 1;
						}
						error -= 1.0;
					}
					path->push_back(x + (y1-i) * width);
				}
			}
		}
	}
	path->push_back(xf + yf * width);
}
