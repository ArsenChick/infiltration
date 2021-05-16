#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>
#include "defines.h"

//! A class for game UI.
class Toolsbar
{
private:
    //! Font used for writings.
    sf::Font font;
    //! SFML clock for the timer.
    sf::Clock time;
    //! Text area for displaying the timer.
    sf::Text text;
    //! Text area for displaying the number of alive enemies.
    sf::Text enemy_number;
public:
    //! Default constructor.
    /*! \param fonts the font to load.
     */
    Toolsbar(sf::Font fonts);
    //! Draws UI, also returning time left to play.
    /*!
     * \param window window area to draw UI onto.
     * \param count_alive number of alive enemies.
     * \return Time (in seconds) left on the timer.
     */
    int draw (sf::RenderWindow &window, unsigned int count_alive);
};

#endif // BAR_H
