#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include <vector>


class DungeonGenerator
{
    public:
        DungeonGenerator(int width, int height);
        virtual ~DungeonGenerator();

        int Getm_width() { return m_width; }
        void Setm_width(unsigned int val) { m_width = val; }
        int Getm_height() { return m_height; }
        void Setm_height(unsigned int val) { m_height = val; }

        void initialiseMap(int threshold);
        int getNeigbourWallCount(int i);
        void simulationStep(int underPop, int overPop);
        void getNeighbours(std::vector<int>*, int i);
        void floodFill();
        void removeLoneWalls(int j);
        void fillBorder();
        void createMap(int threshold, int steps, int underPop, int overPop);

        char *m_level;

    protected:

    private:
        int m_width;
        int m_height;
};

#endif // DUNGEONGENERATOR_H
