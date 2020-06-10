#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include "defines.h"

class Enemy
{

private:
    sf::Sprite sprite;
    sf::Texture *texture;
    sf::Clock clock_e;

    float x;
    float y;

    int dx;
    int dy;
    float speed;

    int pos;
    unsigned int look = LEFT;        // направление взгляда 0 - верх, 1 - право, 2 - вниз, 3 лево
    float time_w = -1;           // переменная time понадобится для 2 секундной задержки
    std::mt19937 gen;

public:
    Enemy();

    void load(sf::Texture *enemy_texture);
    void setStartPosition(int tileno);
    void move(std::vector<int>& level, float time);

    // int search(float player_x, float player_y, int pl_height, int pl_width, int time);

    float getX() {return x;}
    float getY() {return y;}

    int getDX() {return dx;}
    int getDY() {return dy;}

    sf::Sprite getSprite() {return sprite;}
};


#endif // ENEMY_H
