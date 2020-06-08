#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include "defines.h"

class Hero
{
private:
    sf::Sprite sprite;
    sf::Texture *texture;

    float x; // x coordinate on the map
    float y; // y coordinate on the map

    float speed;

    int pos;

    void animate(float time, float& CurrentFrame);

public:
    Hero();

    void load(sf::Texture* hero_texture);
    void setStartPosition(int tileno);
    void move(std::vector<int>& level, float time, float& CurrentFrame);

    float getX() {return x;}
    float getY() {return y;}

    sf::Sprite getSprite() {return sprite;}
};


#endif // HERO_H
