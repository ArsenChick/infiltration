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
    sf::FloatRect dmg_area;

    float x;
    float y;
    float speed = 0.2;

    float CurrentFrame = 0;

    unsigned int pos = 0;
    unsigned int look = UP;

    sf::Clock clock;
    float time_wait = -1;

    std::mt19937 gen;

    void animate(float time);
    void adjustLoS(std::vector<int>& level);

public:
    unsigned int status = ALIVE;

    void load(sf::Texture *enemy_texture);
    void setStartPosition(unsigned int tileno);

    void move(std::vector<int>& level, float time);
    int hunt(sf::FloatRect heroRect);

    sf::RectangleShape testbox;

    sf::Sprite& getSprite() {return sprite;}
};


#endif // ENEMY_H
