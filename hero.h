#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>

class Hero
{
private:
    float x; // x coordinate on the map
    float y; // y coordinate on the map
    int dx; // horizontal speed
    int dy; // vertical speed
public:
    Hero(); // constructor
    sf::Sprite load(sf::Texture hero_texture); // loading custom texture for an enemy
    float get_x(); // getting x coordinate
    float get_y(); // getting y coordinate
    int get_dx(); // getting horizontal speed
    int get_dy(); // getting vertical speed
    int set_startconditions(int start_x, int start_y); // setting start x and y
};


#endif // HERO_H
