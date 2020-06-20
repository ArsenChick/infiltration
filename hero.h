#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "defines.h"

#include <iostream>

class Hero
{
private:
    sf::Sprite sprite;
    sf::Texture *texture;
    sf::FloatRect dmg_area;
    sf::View view;

    float x; // x coordinate on the map
    float y; // y coordinate on the map
    float speed = DEFAULTSPEED;

    bool up = true;
    bool down = true;
    bool right = true;
    bool left = true;

    unsigned int pos = 0;
    unsigned int look = UP;

    void animate(float time, float& CurrentFrame);
    void adjustLoS();

public:
    Hero();

    void load(sf::Texture* hero_texture);
    void setStartPosition(unsigned int tileno);

    void checkForEnemies(std::vector<sf::FloatRect> &soldier, float time);
    void move(std::vector<int>& level, float time, float& CurrentFrame);
    void changeSpeed();

    int kill(sf::FloatRect enemyHitbox);

    sf::Sprite& getSprite() {return sprite;}
    sf::View& getView() {return view;}

    sf::RectangleShape testbox;
};


#endif // HERO_H
