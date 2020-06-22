#include "mapgenerator.h"
#include <algorithm>

MapGenerator::MapGenerator() {
    // initalizing the randomizer
    auto now = std::chrono::high_resolution_clock::now();
    gen.seed(now.time_since_epoch().count());
}

void MapGenerator::levelGenerate(std::vector<int> &level)
{
    // making a tree-like level
    std::vector<bool> paths(LHEIGHT*LWIDTH, false);
    paths[0] = true;
    constructTree(level, paths, 0);

    // adding extra routes
    float leftV; int addVertices;
    leftV = (LHEIGHT - 1) * (LWIDTH - 1);
    addVertices = gen() % int(leftV * 0.3 + 1);
    addVertices += int(leftV * 0.4);

    // there's a random chance of placing route in a direction
    for(int i = 0; i < LHEIGHT*LWIDTH; i++) {
        if (gen() % 8 > 5) {
            addRoute(level, i, ROUTEUP);
            addVertices--;
            continue;
        }
        if (gen() % 8 > 5) {
            addRoute(level, i, ROUTELEFT);
            addVertices--;
            continue;
        }
        if (gen() % 8 > 2) {
            addRoute(level, i, ROUTERIGHT);
            addVertices--;
            continue;
        }
        if (gen() % 8 > 2) {
            addRoute(level, i, ROUTEDOWN);
            addVertices--;
            continue;
        }
        if (addVertices == 0)
           break;
    }
}

void MapGenerator::constructTree(std::vector<int> &tiles, std::vector<bool> &paths, int pos)
{
    // creating a vector of... functions!
    std::vector<int (MapGenerator::*)(std::vector<int> &tiles, std::vector<bool> &paths, int pos)> routes;

    routes.push_back(&MapGenerator::constructUp);
    routes.push_back(&MapGenerator::constructDown);
    routes.push_back(&MapGenerator::constructRight);
    routes.push_back(&MapGenerator::constructLeft);

    // shuffling it
    std::shuffle(routes.begin(), routes.end(), gen);

    // and that's how we add routes in a random sequence
    int newpos;
    for(int i = 0; i < 4; i++) {
        if(-1 != (newpos = (this->*(routes[i]))(tiles, paths, pos))) {
            constructTree(tiles, paths, newpos);
        }
    }
}

// add a route leading up
int MapGenerator::constructUp(std::vector<int> &tiles, std::vector<bool> &paths, int pos) {
    int row = pos / LWIDTH;
    int newpos = pos - LWIDTH;

    if((row - 1 >= 0) && (paths[newpos] != true)) {
        tiles[pos] += ROUTEUP;
        tiles[newpos] += ROUTEDOWN;
        paths[newpos] = true;
        return newpos;
    }

    return -1;
}

// add a route leading down
int MapGenerator::constructDown(std::vector<int> &tiles, std::vector<bool> &paths, int pos) {
    int row = pos / LWIDTH;
    int newpos = pos + LWIDTH;

    if((row + 1 < LHEIGHT) && (paths[newpos] != true)) {
        tiles[pos] += ROUTEDOWN;
        tiles[newpos] += ROUTEUP;
        paths[newpos] = true;
        return newpos;
    }

    return -1;
}

// add a route leading right
int MapGenerator::constructRight(std::vector<int> &tiles, std::vector<bool> &paths, int pos) {
    int col = pos % LWIDTH;
    int newpos = pos + 1;

    if((col + 1 < LWIDTH) && (paths[newpos] != true)) {
        tiles[pos] += ROUTERIGHT;
        tiles[newpos] += ROUTELEFT;
        paths[newpos] = true;
        return newpos;
    }

    return -1;
}

// add a route leading left
int MapGenerator::constructLeft(std::vector<int> &tiles, std::vector<bool> &paths, int pos) {
    int col = pos % LWIDTH;
    int newpos = pos - 1;

    if((col - 1 >= 0) && (paths[newpos] != true)) {
        tiles[pos] += ROUTELEFT;
        tiles[newpos] += ROUTERIGHT;
        paths[newpos] = true;
        return newpos;
    }

    return -1;
}

// add an extra route to the grid
void MapGenerator::addRoute(std::vector<int> &tiles, int pos, unsigned int direction) {
    int row = pos / LWIDTH;
    int col = pos % LWIDTH;
    int newpos;

    switch(direction) {
    case ROUTEUP: {
        newpos = pos - LWIDTH;
        if((row - 1 >= 0) && ((tiles[pos] & ROUTEUP) == 0)) {
            tiles[pos] += ROUTEUP;
            tiles[newpos] += ROUTEDOWN;
        }
        break;
    }
    case ROUTEDOWN: {
        newpos = pos + LWIDTH;
        if((row + 1 < LHEIGHT) && ((tiles[pos] & ROUTEDOWN) == 0)) {
            tiles[pos] += ROUTEDOWN;
            tiles[newpos] += ROUTEUP;
        }
        break;
    }
    case ROUTERIGHT: {
        newpos = pos + 1;
        if((col + 1 < LWIDTH) && ((tiles[pos] & ROUTERIGHT) == 0)) {
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
