#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include "defines.h"
#include "hero.h"

class Enemy
{

private:
    sf::Sprite sprite;
    sf::Texture *texture;
    sf::FloatRect dmg_area;

    float x;
    float y;
    float speed = 0.15;

    unsigned int pos = 0;
    unsigned int look = UP;

    sf::Clock clock;
    float time_wait = -1;

    std::mt19937 gen;

    void adjustLoS(std::vector<int>& level);

public:
    Enemy();

    void load(sf::Texture *enemy_texture);
    void setStartPosition(unsigned int tileno);
    void move(std::vector<int>& level, float time);

    int hunt(Hero &hero);

    sf::RectangleShape testbox;

    float getX() {return x;}
    float getY() {return y;}

    sf::Sprite& getSprite() {return sprite;}
};


#endif // ENEMY_H
