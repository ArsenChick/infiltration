#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "defines.h"

class Hero
{
private:
    // graphical tools
    sf::Sprite sprite;
    sf::Texture *texture;
    // dmg_area can be used for detecting collisions
    sf::FloatRect dmg_area;
    // view can be used for making a camera
    sf::View view;

    // x coordinate on the map
    float x;
    // y coordinate on the map
    float y;

    // current frame used for animation
    float CurrentFrame = 0;

    // hero's speed
    float speed = DEFAULTSPEED;

    // ways that are available for moving in
    bool up = true;
    bool down = true;
    bool right = true;
    bool left = true;

    // position in the tiles
    unsigned int pos = 0;

    // hero's look (used for line of sight)
    unsigned int look = UP;

    // default moving animation
    void animate(float time);
    // updating line of sight
    void adjustLoS();

public:
    Hero(); // constructor

    // loading a texture
    void load(sf::Texture* hero_texture);

    // choosing starting tile number
    void setStartPosition(unsigned int tileno);

    // the function updates available ways for hero's moving
    void checkForEnemies(std::vector<sf::FloatRect> &soldier, float time);

    // the function moves the hero
    void move(std::vector<int>& level, float time);

    // the function changes the speed between crouch mode and default
    void changeSpeed();

    /*  the function outputs 1 if there's a elimination
     * the function outputs 0 if there's no elimination
     */
    int kill(sf::FloatRect enemyHitbox);

    // getting hero's sprite
    sf::Sprite& getSprite() {return sprite;}

    // getting hero's view
    sf::View& getView() {return view;}

};


#endif // HERO_H
