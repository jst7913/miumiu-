#ifndef GRIDWORLD_H
#define GRIDWORLD_H

#include <vector>
#include "Objects.h"

class GridWorld {
private:
    int seed;
    int id;
    int dimX;
    int dimY;
    int numMovingCars;
    int numMovingBikes;
    int numParkedCars;
    int numStopSigns;
    int numTrafficLights;
    int simulationTicks;
    int minConfidenceThreshold;

    std::vector<WorldObject*> objects;

    Position randomPos();   // helper

public:
    GridWorld();  // default constructor

    GridWorld(int seed, int dimX, int dimY,
              int numMovingCars, int numMovingBikes, int numParkedCars,
              int numStopSigns, int numTrafficLights,
              int simulationTicks, int minConfidenceThreshold);

    ~GridWorld();

    void generateWorld();
    void showWorld();
    void tickAll();
};

#endif // GRIDWORLD_H
