#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>
#include "defines.h"

class Toolsbar
{
private:
    // font for demonstration
    sf::Font font;
    // sfml clock for timer
    sf::Clock time;
    // text area for timer
    sf::Text text;
    // text area for alive enemies
    sf::Text enemy_number;
public:
    // constructor
    Toolsbar(sf::Font fonts);
    // draw timer and count alive enemies, also return time of play
    int draw (sf::RenderWindow &window, unsigned int count_alive);
};

#endif // BAR_H
