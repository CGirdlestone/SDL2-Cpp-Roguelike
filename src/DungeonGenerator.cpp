#include <cstdlib>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>

#include "DungeonGenerator.h"

DungeonGenerator::DungeonGenerator(int width, int height)
{
    //ctor
    m_width = width;
    m_height = height;
    recomputeFOV = false;
}

DungeonGenerator::~DungeonGenerator()
{
    //dtor
    delete[] m_level;
    m_level = nullptr;

    delete[] m_fovMap;
    m_fovMap = nullptr;

    delete[] m_exploredMap;
    m_exploredMap = nullptr;
}

void DungeonGenerator::initialiseMap(int threshold){
    int chance;

    std::srand(time(0));

    m_level = new char[m_width * m_height];
    m_fovMap = new int[m_width * m_height];
    m_exploredMap = new int[m_width * m_height];

    for (int i = 0; i < m_width * m_height; i++){
        chance = std::rand()%100 + 1;
        if(chance >= threshold){
            m_level[i] = '.';
        } else {
            m_level[i] = '#';
        }
        m_fovMap[i] = 0;
        m_exploredMap[i] = 0;
    }
}

int DungeonGenerator::getNeigbourWallCount(int i){
    int wallCount = 0;

    if (i == 0){
        // top left
        // ignore W, NW N
        for (int m = 0; m < 2; m++){
            for (int n = 0; n < 2; n++){
                if (n == 0 && m == 0){
                    continue;
                }
                if (m_level[i + m + n * m_width] == '#'){
                    wallCount++;
                }
            }
        }
    } else if (i == m_width - 1){
        // top right
        // ignore E, NE, N
        for (int m = -1; m < 1; m++){
            for (int n = 0; n < 2; n++){
                if (n == 0 && m == 0){
                    continue;
                }
                if (m_level[i + m + n * m_width] == '#'){
                    wallCount++;
                }
            }
        }
    } else if (i == m_width * m_height - 1){
        // bottom right
        // ignore E, SE, S
        for (int m = -1; m < 1; m++){
            for (int n = -1; n < 1; n++){
                if (n == 0 && m == 0){
                    continue;
                }
                if (m_level[i + m + n * m_width] == '#'){
                    wallCount++;
                }
            }
        }
    } else if (i == m_width * (m_height - 1)){
        // bottom left
        // ignore W, SW, S
        for (int m = 0; m < 2; m++){
            for (int n = -1; n < 1; n++){
                if (n == 0 && m == 0){
                    continue;
                }
                if (m_level[i + m + n * m_width] == '#'){
                    wallCount++;
                }
            }
        }
    } else if (i % m_width == 0){
        // left boundary
        // ignore W
        for (int m = 0; m < 2; m++){
            for (int n = -1; n < 2; n++){
                if (n == 0 && m == 0){
                    continue;
                }
                if (m_level[i + m + n * m_width] == '#'){
                    wallCount++;
                }
            }
        }
    } else if (i > 0 && i < m_width){
        // top boundary
        // ignore N
        for (int m = -1; m < 2; m++){
            for (int n = 0; n < 2; n++){
                if (n == 0 && m == 0){
                    continue;
                }
                if (m_level[i + m + n * m_width] == '#'){
                    wallCount++;
                }
            }
        }
    } else if (i % m_width == m_width - 1){
        // right boundary
        // ignore E
        for (int m = -1; m < 1; m++){
            for (int n = -1; n < 2; n++){
                if (n == 0 && m == 0){
                    continue;
                }
                if (m_level[i + m + n * m_width] == '#'){
                    wallCount++;
                }
            }
        }
    } else if (i > m_width * (m_height - 1) && i < m_width * m_height){
        // bottom boundary
        // ignore S
        for (int m = -1; m < 2; m++){
            for (int n = -1; n < 1; n++){
                if (n == 0 && m == 0){
                    continue;
                }
                if (m_level[i + m + n * m_width] == '#'){
                    wallCount++;
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
                if (m_level[i + m + n * m_width] == '#'){
                    wallCount++;
                }
            }
        }
    }

    return wallCount;
}

void DungeonGenerator::simulationStep(int underPop, int overPop){
    int wallCount;
    char *new_level = new char[m_width * m_height];

    for (int i=0; i < m_width*m_height; i++){
        wallCount = 0;
        wallCount = getNeigbourWallCount(i);
        if (wallCount <= underPop || wallCount > overPop){
            new_level[i] = '#';
        } else {
            new_level[i] = '.';
        }
    }
    delete[] m_level;
    m_level = new_level;
}

void DungeonGenerator::getNeighbours(std::vector<int>* neighbours, int i){
    if (i == 0){
        // top left
        // ignore W, NW N
        for (int m = 0; m < 2; m++){
            for (int n = 0; n < 2; n++){
                if (n * m != 0){
                    continue;
                }
                if (std::find(neighbours->begin(), neighbours->end(), i + m + n * m_width) == neighbours->end()){
                    neighbours->push_back(i + m + n * m_width);
                }
            }
        }
    } else if (i == m_width - 1){
        // top right
        // ignore E, NE, N
        for (int m = -1; m < 1; m++){
            for (int n = 0; n < 2; n++){
                if (n * m != 0){
                    continue;
                }
                if (std::find(neighbours->begin(), neighbours->end(), i + m + n * m_width) == neighbours->end()){
                    neighbours->push_back(i + m + n * m_width);
                }
            }
        }
    } else if (i == m_width * m_height - 1){
        // bottom right
        // ignore E, SE, S
        for (int m = -1; m < 1; m++){
            for (int n = -1; n < 1; n++){
                if (n * m != 0){
                    continue;
                }
                if (std::find(neighbours->begin(), neighbours->end(), i + m + n * m_width) == neighbours->end()){
                    neighbours->push_back(i + m + n * m_width);
                }
            }
        }
    } else if (i == m_width * (m_height - 1)){
        // bottom left
        // ignore W, SW, S
        for (int m = 0; m < 2; m++){
            for (int n = -1; n < 1; n++){
                if (n * m != 0){
                    continue;
                }
                if (std::find(neighbours->begin(), neighbours->end(), i + m + n * m_width) == neighbours->end()){
                    neighbours->push_back(i + m + n * m_width);
                }
            }
        }
    } else if (i % m_width == 0){
        // left boundary
        // ignore W
        for (int m = 0; m < 2; m++){
            for (int n = -1; n < 2; n++){
                if (n * m != 0){
                    continue;
                }
                if (std::find(neighbours->begin(), neighbours->end(), i + m + n * m_width) == neighbours->end()){
                    neighbours->push_back(i + m + n * m_width);
                }
            }
        }
    } else if (i > 0 && i < m_width){
        // top boundary
        // ignore N
        for (int m = -1; m < 2; m++){
            for (int n = 0; n < 2; n++){
                if (n * m != 0){
                    continue;
                }
                if (std::find(neighbours->begin(), neighbours->end(), i + m + n * m_width) == neighbours->end()){
                    neighbours->push_back(i + m + n * m_width);
                }
            }
        }
    } else if (i % m_width == m_width - 1){
        // right boundary
        // ignore E
        for (int m = -1; m < 1; m++){
            for (int n = -1; n < 2; n++){
                if (n * m != 0){
                    continue;
                }
                if (std::find(neighbours->begin(), neighbours->end(), i + m + n * m_width) == neighbours->end()){
                    neighbours->push_back(i + m + n * m_width);
                }
            }
        }
    } else if (i > m_width * (m_height - 1) && i < m_width * m_height){
        // bottom boundary
        // ignore S
        for (int m = -1; m < 2; m++){
            for (int n = -1; n < 1; n++){
                if (n * m != 0){
                    continue;
                }
                if (std::find(neighbours->begin(), neighbours->end(), i + m + n * m_width) == neighbours->end()){
                    neighbours->push_back(i + m + n * m_width);
                }
            }
        }
    } else {
        // all other points
        for (int m = -1; m < 2; m++){
            for (int n = -1; n < 2; n++){
                if (n * m != 0){
                    continue;
                }
                if (std::find(neighbours->begin(), neighbours->end(), i + m + n * m_width) == neighbours->end()){
                    neighbours->push_back(i + m + n * m_width);
                }
            }
        }
    }
}

void DungeonGenerator::floodFill(){
    std::vector<int> *neighbours = new std::vector<int>;
    int start_letter_code = 97;
    int letter_code = 97; // a
    char letter = static_cast<int>(letter_code);
    int j;

    for (int i = 0; i < m_width * m_height; i++){
        if (m_level[i] == '#'){
            continue;
        } else if (m_level[i] == '.'){
            getNeighbours(neighbours, i);
            while (neighbours->size() > 0){

                j = neighbours->back();
                neighbours->pop_back();

                if (m_level[j] == '.'){
                    m_level[j] = letter;
                    getNeighbours(neighbours, j);
                }
            }
        letter_code++;
        letter = static_cast<int>(letter_code);
        }
    }

    int letter_count;
    char most_frequent;

    for (int i = start_letter_code; i < letter_code; i++){
        letter = static_cast<int>(i);
        letter_count = std::count(m_level, m_level + (m_width * m_height), letter);
        if (i == start_letter_code){
            most_frequent = letter;
        } else {
            if (std::count(m_level, m_level + (m_width * m_height), most_frequent) < letter_count){
                most_frequent = letter;
            }
        }
    }

    for (int i = 0; i < m_width * m_height; i++){
        if (m_level[i] == most_frequent){
            m_level[i] = '.';
        } else {
            m_level[i] = '#';
        }
    }

    delete neighbours;
}

void DungeonGenerator::removeLoneWalls(int j){
    int wallCount;

    for (int i = 0; i < m_width * m_height; i++){
        if (i == 0 || i == m_width - 1 || i == m_width * m_height - 1 || i == m_width * m_height - m_width){
          continue;
        }
        wallCount = getNeigbourWallCount(i);
        if (wallCount <= j){
            m_level[i] = '.';
        }
    }

}

void DungeonGenerator::fillBorder(){
    for (int i = 0; i < m_width * m_height; i++){
        if (i % m_width  == 0 || i % m_width == m_width - 1 || i < m_width || i > m_width * m_height - m_width){
          m_level[i] = '#';
        }
    }
}

void DungeonGenerator::createMap(int threshold, int steps, int underPop, int overPop){
    initialiseMap(threshold);
    for (int i = 0; i < steps; i++){
        simulationStep(underPop, overPop);
    }

    floodFill();

    for (int j = 0; j < 3; j++){
        removeLoneWalls(j);
    }

    removeLoneWalls(3);
    removeLoneWalls(0);
    removeLoneWalls(2);

    fillBorder();
}

float DungeonGenerator::getGradient(float x1, float y1, float x2, float y2)
{
    return (y1 - y2) / (x1 - x2);
}

int DungeonGenerator::transformX(int x, int y, int octant)
{
  if (octant == 2){
    return x;
  } else if (octant == 3){
    return -y;
  } else if (octant == 4){
    return -y;
  } else if (octant == 5){
    return -x;
  } else if (octant == 6){
    return -x;
  } else if (octant == 7){
    return y;
  } else if (octant == 8){
    return y;
  } else {
    return x;
  }
}

int DungeonGenerator::transformY(int x, int y, int octant)
{
  if (octant == 2){
    return -y;
  } else if (octant == 3){
    return x;
  } else if (octant == 4){
    return -x;
  } else if (octant == 5){
    return -y;
  } else if (octant == 6){
    return y;
  } else if (octant == 7){
    return -x;
  } else if (octant == 8){
    return x;
  } else {
    return y;
  }
}

bool DungeonGenerator::checkInMap(int x, int y)
{
  if(x >= 0 && x < m_width && y >= 0 && y < m_height){
    return true;
  } else {
    return false;
  }
}

void DungeonGenerator::castOctant(int x, int y, int radius, float bottomSlope, float topSlope, int step, int octant)
{
  int l, k; // offsets in the octant
  int a, b; // transformed offsets for octants 2 - 8
  int mapArrayIndex;
  float gradient, newBottomSlope;

  for(int i = 0; i < radius - step; i++){
    l = i + step;
    for (int j = 0; j < l + 1; j++){
      if (i==0 && j == 0){
        m_fovMap[y*m_width+x] = 1;
        m_exploredMap[y*m_width+x] = 1;
        continue;
      }

      k = j;

      a = transformX(l, k, octant);
      b = transformY(l, k, octant);

      mapArrayIndex = m_width*(y+b) + (x+a);

      if((y+b)*m_width+x+a < 0 && (y+b)*m_width+x+a >= m_width * m_height){
        continue;
      }

      gradient = getGradient(static_cast<float>(x+l), static_cast<float>(y+k), static_cast<float>(x), static_cast<float>(y));

      if (gradient < bottomSlope){
        continue;
      }

      if (gradient >= bottomSlope && gradient <= topSlope){
        if (m_level[(y+b)*m_width+x+a] == '#'){
          newBottomSlope = getGradient(static_cast<float>(x+l-0.5), static_cast<float>(y+k+0.5), static_cast<float>(x), static_cast<float>(y));
          castOctant(x, y, radius, newBottomSlope, topSlope, step, octant);

          topSlope = getGradient(static_cast<float>(x+l+0.5), static_cast<float>(y+k-0.5), static_cast<float>(x), static_cast<float>(y));
        }
        m_fovMap[(y+b)*m_width+x+a] = 1;
        m_exploredMap[(y+b)*m_width+x+a] = 1;
      }
    }
  }
}

void DungeonGenerator::shadowCast(int x, int y, int radius)
{
  for(int i = 1; i < 9; i++){
    castOctant(x, y, radius, 0, 1, 0, i);
  }
}


void DungeonGenerator::doRecomputeFOV(int x, int y, int radius)
{
  recomputeFOV = false;
  for (int i = 0; i < m_width * m_height; i++){
    m_fovMap[i] = 0;
  }

  shadowCast(x, y, radius);
}
