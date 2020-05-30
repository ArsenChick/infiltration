#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#define ROUTEUP 8
#define ROUTELEFT 4
#define ROUTEDOWN 2
#define ROUTERIGHT 1

#define LHEIGHT 10
#define LWIDTH 10

#include <vector>
#include <random>

class MapGenerator
{
public:
    explicit MapGenerator();

    void levelGenerate(std::vector<int> &level);

private:
    void constructTree(std::vector<int> &tiles, std::vector<bool> &paths, int pos);

    int constructUp(std::vector<int> &tiles, std::vector<bool> &paths, int pos);
    int constructDown(std::vector<int> &tiles, std::vector<bool> &paths, int pos);
    int constructRight(std::vector<int> &tiles, std::vector<bool> &paths, int pos);
    int constructLeft(std::vector<int> &tiles, std::vector<bool> &paths, int pos);

    void addRoute(std::vector<int> &tiles, int pos, unsigned int direction);

    std::mt19937 gen;
};

#endif // MAPGENERATOR_H
