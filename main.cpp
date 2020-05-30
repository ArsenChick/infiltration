#include <SFML/Graphics.hpp>
#include <vector>
#include "mapgenerator.h"
#include "enemy.h"
#include "hero.h"
#include "map.h"

void keyboard(float time, float& speed, float& CurrentFrame, sf::Sprite& hero_sprite);

int main()
{
    float CurrentFrame = 0;

    // Creating the window
    sf::RenderWindow window(sf::VideoMode(640, 640), "Tilemap");
    window.setFramerateLimit(60);

    // Loading hero
    sf::Texture hero_texture;
    if(!hero_texture.loadFromFile("image.png"))
        exit(EXIT_FAILURE);

    Hero hero;
    hero.setCoordintaes(50, 50);
    hero.load(&hero_texture);

    // Loading enemy
    sf::Texture enemy_texture;
    if(!enemy_texture.loadFromFile("enemy.png"))
        exit(EXIT_FAILURE);

    Enemy soldier;
    soldier.setCoordinates(200,200);
    soldier.load(&enemy_texture);

    // Timer
    sf::Clock clock;

    // Creating level
    std::vector<int> level(100, 0);

    MapGenerator *mg = new MapGenerator;
    mg->levelGenerate(level);
    delete mg;

    Map map;
    if (!map.load("map.png", sf::Vector2u(64, 64), level, 10, 10))
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
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // draw the map
        window.clear();

        hero.move(time, CurrentFrame);

        window.draw(map);

        // Отрисовка спрайтов героя и врага
        window.draw(hero.getSprite());
        window.draw(soldier.getSprite());


        window.display();
    }

    return 0;
}
