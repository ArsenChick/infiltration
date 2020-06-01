#include <SFML/Graphics.hpp>
#include <vector>

#include "mapgenerator.h"
#include "enemy.h"
#include "hero.h"
#include "map.h"

int main()
{
    float CurrentFrame = 0;

    // Creating the window
    sf::RenderWindow window(sf::VideoMode(128*LWIDTH, 128*LHEIGHT), "Tilemap");
    window.setFramerateLimit(60);

    // Loading hero
    sf::Texture hero_texture;
    if (!hero_texture.loadFromFile("image.png"))
        exit(EXIT_FAILURE);

    Hero hero;
    hero.setCoordintaes(35, 35);
    hero.load(&hero_texture);

    // Loading enemy
    sf::Texture enemy_texture;
    if (!enemy_texture.loadFromFile("enemy.png"))
        exit(EXIT_FAILURE);

    Enemy soldier[5];
    for (int i = 0; i < 5; i++) {
        soldier[i].setCoordinates(50 * i, 200);
        soldier[i].load(&enemy_texture);
    }

    // Timer
    sf::Clock clock;

    // Creating level
    std::vector<int> level(LHEIGHT*LWIDTH, 0);

    MapGenerator *mg = new MapGenerator;
    mg->levelGenerate(level);
    delete mg;

    Map map;
    if (!map.load("map.png", sf::Vector2u(128, 128), level, LWIDTH, LHEIGHT))
        return -1;

    // Running the main loop
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // draw the map
        window.clear();

        hero.move(level, time, CurrentFrame);

        window.draw(map);

        // Отрисовка спрайтов героя и врага
        window.draw(hero.getSprite());
        for (int i = 0; i < 5; i++)
            window.draw(soldier[i].getSprite());


        window.display();
    }

    return 0;
}
