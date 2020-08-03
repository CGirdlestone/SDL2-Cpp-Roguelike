#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include <vector>
#include <map>
#include "GameObject.h"
#include "EntityFactory.h"

class DungeonGenerator
{
  public:
    DungeonGenerator(int width, int height, EntityFactory* factory);
    virtual ~DungeonGenerator();

    int Getm_width() { return m_width; }
    void Setm_width(unsigned int val) { m_width = val; }
    int Getm_height() { return m_height; }
    void Setm_height(unsigned int val) { m_height = val; }

    void initialiseMap(int threshold);
    int getNeigbourWallCount(int i);
    void simulationStep(int underPop, int overPop);
    void getNeighbours(std::vector<int>*, int i);
    int floodFill();
    void removeLoneWalls(int j);
    void fillBorder();
    void hollowSolidChunks();
    void createMap(int threshold, int steps, int underPop, int overPop);
    float getGradient(float x1, float y1, float x2, float y2);
    int transformX(int x, int y, int octant);
    int transformY(int x, int y, int octant);
    void castOctant(int x, int y, int radius, float bottomSlope, float topSlope, int step, int octant);
    void shadowCast(int x, int y, int radius);
    bool checkInMap(int x, int y);
    void doRecomputeFOV(int x, int y, int radius);
		int getFreePosition();
    void createPlayer(std::map<int, GameObject*> *actors);
    void createMobs(std::map<int, GameObject*> *actors);
    void createItems(std::map<int, GameObject*> *actors);
		void createEntity(std::map<int, GameObject*> *actors, EntityType type);
		void placeStairs(std::map<int, GameObject*> *actors);
		void descendDungeon(std::map<int, GameObject*> *actors);
		void repositionPlayer(GameObject* player);
		std::vector<GameObject*> getObjectsAtTile(int i);
		void removeObjectFromTile(GameObject* entity, int i);
		void moveObjectToTile(GameObject* entity, int i);
		void clearGrid();
		void populateGrid(std::map<int, GameObject*> *actors);
		void reset(){ m_uid = 0; m_factory->resetUID(); }
		
    char *m_level;
    int *m_fovMap;
    int *m_exploredMap;
    bool recomputeFOV;
		int m_uid;
  protected:

  private:
		std::map<int, std::vector<GameObject*>> m_grid;
    int m_width;
    int m_height;
		EntityFactory* m_factory;
};

#endif // DUNGEONGENERATOR_H
