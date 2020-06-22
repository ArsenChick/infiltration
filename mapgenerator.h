#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <vector>
#include <chrono>
#include <random>
#include "defines.h"

class MapGenerator
{
public:
    explicit MapGenerator();
    // generates the level
    void levelGenerate(std::vector<int> &level);

private:
    // constructs a tree-like level
    void constructTree(std::vector<int> &tiles, std::vector<bool> &paths, int pos);

    // construct a route in a specific direction
    int constructUp(std::vector<int> &tiles, std::vector<bool> &paths, int pos);
    int constructDown(std::vector<int> &tiles, std::vector<bool> &paths, int pos);
    int constructRight(std::vector<int> &tiles, std::vector<bool> &paths, int pos);
    int constructLeft(std::vector<int> &tiles, std::vector<bool> &paths, int pos);

    // adding extensive routes
    void addRoute(std::vector<int> &tiles, int pos, unsigned int direction);

    // randomizer
    std::mt19937 gen;
};

#endif // MAPGENERATOR_H
