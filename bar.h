#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>
#include "defines.h"

class Toolsbar
{
private:
    sf::Font font;
    sf::Clock time;
    sf::Text text;
    sf::Text enemy_number;
public:
    Toolsbar(sf::Font fonts);
    int draw (sf::RenderWindow &window, unsigned int count_alive);
};

#endif // BAR_H
