#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include "defines.h"

class Enemy
{

private:
    // graphical tools
    sf::Sprite sprite;
    sf::Texture *texture;
    // damage area rect
    sf::FloatRect dmg_area;
    // enemy's line of sight
    sf::RectangleShape lineOfSight;

    // x coordinate on the map
    float x;
    // y coordinate on the map
    float y;

    // enemy's speed
    float speed = 0.2;

    // current frame used for animation
    float CurrentFrame = 0;

    // position in the tiles
    unsigned int pos = 0;
    // enemy's look (used for line of sight)
    unsigned int look = UP;

    // sfml clock for calculations
    sf::Clock clock;
    // hero's death timer
    float time_wait = -1;

    // randomizer
    std::mt19937 gen;

    // default moving animation
    void animate(float time);
    // updating line of sight
    void adjustLoS(std::vector<int>& level);

public:
    // enemy's status - ALIVE or DEAD
    unsigned int status = ALIVE;

    // loading a texture
    void load(sf::Texture *enemy_texture);

    // choosing starting tile number
    void setStartPosition(unsigned int tileno);

    // the function moves the enemy
    void move(std::vector<int>& level, float time);

    // the function checks if the enemy has catched a hero
    int hunt(sf::FloatRect heroRect);

    // getting enemy's sprite and line of sight
    sf::Sprite& getSprite() {return sprite;}
    sf::RectangleShape getLoS() {return lineOfSight;}
};


#endif // ENEMY_H
