#include <SFML/Graphics.hpp>
#include <vector>
#include "mapgenerator.h"
#include "map.h"

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(640, 640), "Tilemap");

    // define the level with an array of tile indices
    std::vector<int> level(100, 0);

    MapGenerator *mg = new MapGenerator;
    mg->levelGenerate(level);
    delete mg;

    // create the tilemap from the level definition
    Map map;
    if (!map.load("map.png", sf::Vector2u(64, 64), level, 10, 10))
        return -1;

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // draw the map
        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}
