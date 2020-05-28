#include "hero.h"

Hero::Hero()
{
    Hero::set_startconditions(0, 0);
}

int Hero::set_startconditions(int start_x, int start_y)
{
    /* updating x if available */
    if (start_x > -1 && start_x < 200)
        x = start_x;
    else
        return -1;

    /* updating y if available */
    if (start_y > -1 && start_y < 200)
        x = start_y;
    else
        return -1;

    return 0;
}

sf::Sprite Hero::load(sf::Texture hero_texture)
{
    sf::Sprite sprite;

    sprite.setTexture(hero_texture);
    sprite.setPosition(15, 15);

    return sprite;
}

float Hero::get_x()
{
    return x;
}

float Hero::get_y()
{
    return y;
}

int Hero::get_dx()
{
    return dx;
}

int Hero::get_dy()
{
    return dy;
}
