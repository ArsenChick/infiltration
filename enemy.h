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
    float speed;

    int pos;
    unsigned int look = LEFT;

    float time_w = -1;
    std::mt19937 gen;

public:
    Enemy();

    void load(sf::Texture *enemy_texture);
    void setStartPosition(int tileno);
    void move(std::vector<int>& level, float time);

    float getX() {return x;}
    float getY() {return y;}

    sf::Sprite getSprite() {return sprite;}
};


#endif // ENEMY_H
