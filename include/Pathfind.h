#ifndef PATHFIND_H
#define PATHFIND_H

#include <vector>

struct Node
{
  int _x;
  int _y;
  int _g;
  int _h;
  int _f;
  Node *_parent;

  Node(int x, int y, int g, int h, int f, Node* parent);
  ~Node();
  bool equals(Node* n);
  bool equals(int x, int y);
};

int calculate_h(int x1, int y1, int xf, int yf);
void getNeighbours(std::vector<int> *neighbours, int width, int height, int x, int y);
bool compareNodes(Node* n, Node* m);
void aStar(char* world, std::vector<int> *path, int width, int height, int x1, int y1, int xf, int yf);
void getBresenhamLine(std::vector<int> *path, int width, int x1, int y1, int xf, int yf);
float getGradient(int x1, int y1, int xf, int yf);
#endif
