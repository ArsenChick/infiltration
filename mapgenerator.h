#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#define ROUTEUP 8
#define ROUTELEFT 4
#define ROUTEDOWN 2
#define ROUTERIGHT 1

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

    void addUpRoute(std::vector<int> &tiles, int pos);
    void addDownRoute(std::vector<int> &tiles, int pos);
    void addRightRoute(std::vector<int> &tiles, int pos);
    void addLeftRoute(std::vector<int> &tiles, int pos);

    std::mt19937 gen;
};

#endif // MAPGENERATOR_H
