#include "mapgenerator.h"
#include <algorithm>
#include <chrono>

MapGenerator::MapGenerator() {
    auto now = std::chrono::high_resolution_clock::now();
    gen.seed(now.time_since_epoch().count());
}

void MapGenerator::levelGenerate(std::vector<int> &level)
{
    std::vector<bool> paths(100, false);
    paths[0] = true;
    constructTree(level, paths, 0);

    int addVertex;
    addVertex = (gen() % 11) + 40;
    for(int i = 0; i < 100; i++) {
        if (gen() % 8 > 2) {
            addRoute(level, i, ROUTERIGHT);
            addVertex--;
        }
        if (gen() % 8 > 2) {
            addRoute(level, i, ROUTEDOWN);
            addVertex--;
        }
        if (addVertex == 0)
           break;
    }
}

void MapGenerator::constructTree(std::vector<int> &tiles, std::vector<bool> &paths, int pos)
{
    std::vector<int (MapGenerator::*)(std::vector<int> &tiles, std::vector<bool> &paths, int pos)> routes;

    routes.push_back(&MapGenerator::constructUp);
    routes.push_back(&MapGenerator::constructDown);
    routes.push_back(&MapGenerator::constructRight);
    routes.push_back(&MapGenerator::constructLeft);

    std::shuffle(routes.begin(), routes.end(), gen);

    int newpos;
    for(int i = 0; i < 4; i++) {
        if(-1 != (newpos = (this->*(routes[i]))(tiles, paths, pos))) {
            constructTree(tiles, paths, newpos);
        }
    }
}

int MapGenerator::constructUp(std::vector<int> &tiles, std::vector<bool> &paths, int pos) {
    int row = pos / 10;
    int newpos = pos - 10;

    if((row - 1 >= 0) && (paths[newpos] != true)) {
        tiles[pos] += ROUTEUP;
        tiles[newpos] += ROUTEDOWN;
        paths[newpos] = true;
        return newpos;
    }

    return -1;
}

int MapGenerator::constructDown(std::vector<int> &tiles, std::vector<bool> &paths, int pos) {
    int row = pos / 10;
    int newpos = pos + 10;

    if((row + 1 < 10) && (paths[newpos] != true)) {
        tiles[pos] += ROUTEDOWN;
        tiles[newpos] += ROUTEUP;
        paths[newpos] = true;
        return newpos;
    }

    return -1;
}

int MapGenerator::constructRight(std::vector<int> &tiles, std::vector<bool> &paths, int pos) {
    int col = pos % 10;
    int newpos = pos + 1;

    if((col + 1 < 10) && (paths[newpos] != true)) {
        tiles[pos] += ROUTERIGHT;
        tiles[newpos] += ROUTELEFT;
        paths[newpos] = true;
        return newpos;
    }

    return -1;
}

int MapGenerator::constructLeft(std::vector<int> &tiles, std::vector<bool> &paths, int pos) {
    int col = pos % 10;
    int newpos = pos - 1;

    if((col - 1 >= 0) && (paths[newpos] != true)) {
        tiles[pos] += ROUTELEFT;
        tiles[newpos] += ROUTERIGHT;
        paths[newpos] = true;
        return newpos;
    }

    return -1;
}

void MapGenerator::addRoute(std::vector<int> &tiles, int pos, unsigned int direction) {
    int row = pos / 10;
    int col = pos % 10;
    int newpos;

    switch(direction) {
    case ROUTEUP: {
        newpos = pos - 10;
        if((row - 1 >= 0) && ((tiles[pos] & ROUTEUP) == 0)) {
            tiles[pos] += ROUTEUP;
            tiles[newpos] += ROUTEDOWN;
        }
        break;
    }
    case ROUTEDOWN: {
        newpos = pos + 10;
        if((row + 1 < 10) && ((tiles[pos] & ROUTEDOWN) == 0)) {
            tiles[pos] += ROUTEDOWN;
            tiles[newpos] += ROUTEUP;
        }
        break;
    }
    case ROUTERIGHT: {
        newpos = pos + 1;
        if((col + 1 < 10) && ((tiles[pos] & ROUTERIGHT) == 0)) {
            tiles[pos] += ROUTERIGHT;
            tiles[newpos] += ROUTELEFT;
        }
        break;
    }
    case ROUTELEFT:{
        newpos = pos - 1;
        if((col - 1 >= 0) && ((tiles[pos] & ROUTELEFT) == 0)) {
            tiles[pos] += ROUTELEFT;
            tiles[newpos] += ROUTERIGHT;
        }
        break;
    }
    }
}
