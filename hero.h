#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "defines.h"

class Hero
{
private:
    sf::Sprite sprite;
    sf::Texture *texture;
    sf::View view;

    float x; // x coordinate on the map
    float y; // y coordinate on the map
    float speed = DEFAULTSPEED;

    bool up = true;
    bool down = true;
    bool right = true;
    bool left = true;

    unsigned int pos = 0;

    void animate(float time, float& CurrentFrame);

public:
    Hero();

    void load(sf::Texture* hero_texture);
    void setStartPosition(unsigned int tileno);
    void move(std::vector<int>& level, float time, float& CurrentFrame);
    void changeSpeed();

    float getX() {return x;}
    float getY() {return y;}

    void checkForEnemies(std::vector<sf::FloatRect> &soldier);

    sf::Sprite& getSprite() {return sprite;}
    sf::View& getView() {return view;}

    sf::RectangleShape testbox;
};


#endif // HERO_H
