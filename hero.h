#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include "defines.h"

class Hero
{
private:
    sf::Sprite sprite;
    sf::Texture *texture;
    sf::FloatRect hitbox;
    sf::View view;

    float x; // x coordinate on the map
    float y; // y coordinate on the map
    float speed = 0.1;

    unsigned int pos = 0;

    void animate(float time, float& CurrentFrame);

public:
    Hero();

    void load(sf::Texture* hero_texture);
    void setStartPosition(unsigned int tileno);
    void move(std::vector<int>& level, float time, float& CurrentFrame);

    float getX() {return x;}
    float getY() {return y;}

    sf::Sprite& getSprite() {return sprite;}
    sf::View& getView() {return view;}
    sf::FloatRect& getRect() {return hitbox;}

    sf::RectangleShape testbox;
};


#endif // HERO_H
