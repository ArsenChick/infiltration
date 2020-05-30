#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>

class Hero
{
private:
    sf::Sprite sprite;
    sf::Texture *texture;

    float x; // x coordinate on the map
    float y; // y coordinate on the map

    float speed;

public:
    Hero();

    void load(sf::Texture* hero_texture);
    int setCoordintaes(int start_x, int start_y);
    void move(float time, float& CurrentFrame);

    float getX() {return x;}
    float getY() {return y;}

    sf::Sprite getSprite() {return sprite;}
};


#endif // HERO_H
