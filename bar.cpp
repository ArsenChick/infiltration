#include "bar.h"
#include <sstream>

Toolsbar::Toolsbar(sf::Font fonts)
{
    font = fonts;
}

int Toolsbar::draw(sf::RenderWindow &window, unsigned int count_alive) {

    // Getting time
    int timeinsec = TIMEFORPLAY - static_cast<int>(time.getElapsedTime().asSeconds());

    // Transformation of time to minute&seconds
    int minute = 0;
    int sec = 0;
    if (timeinsec >= 60) {
        minute = timeinsec / 60;
        sec = timeinsec - minute * 60;
    } else sec = timeinsec;

    // Transformation to string
    std::ostringstream string;

    if (sec < 10) {
        string << minute << ":0" << sec;
    } else string << minute << ":" << sec;

    // Establish parameters
    text.setString("Time: " + string.str());
    text.setFont(font);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Black);
    text.setOutlineColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.setCharacterSize(20);
    text.setPosition(window.getView().getCenter().x - MAPSCALE*window.getSize().x/2,
                     window.getView().getCenter().y - MAPSCALE*window.getSize().y/2);

    // Cleaning string
    string.str("");

    // Establish parameters
    string << count_alive;
    enemy_number.setString("Alive enemy: " + string.str());
    enemy_number.setFont(font);
    enemy_number.setStyle(sf::Text::Bold);
    enemy_number.setFillColor(sf::Color::Black);
    enemy_number.setOutlineColor(sf::Color::White);
    enemy_number.setOutlineThickness(2);
    enemy_number.setCharacterSize(20);
    enemy_number.setPosition(window.getView().getCenter().x - MAPSCALE*window.getSize().x/2,
                     window.getView().getCenter().y + MAPSCALE*window.getSize().y/2 - enemy_number.getCharacterSize() - 5);

    // Draw
    window.draw(text);
    window.draw(enemy_number);

    return timeinsec;
}
