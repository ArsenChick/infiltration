#include <SFML/Graphics.hpp>
#include <vector>

#include "mapgenerator.h"
#include "enemy.h"
#include "hero.h"
#include "map.h"

void spawnCharacters(Hero &hero, Enemy* soldier);

int main()
{
    float CurrentFrame = 0;

    // Creating the window
    sf::RenderWindow window(sf::VideoMode(TILESIZE*LWIDTH, TILESIZE*LHEIGHT), "Tilemap");
    window.setFramerateLimit(60);

    // Loading hero
    sf::Texture hero_texture;
    if (!hero_texture.loadFromFile("image.png"))
        exit(EXIT_FAILURE);

    Hero hero;
    hero.load(&hero_texture);

    // Loading enemy
    sf::Texture enemy_texture;
    if (!enemy_texture.loadFromFile("enemy.png"))
        exit(EXIT_FAILURE);

    Enemy soldier[5];
    for (int i = 0; i < 5; i++)
        soldier[i].load(&enemy_texture);

    // Timer
    sf::Clock clock;

    // Creating level
    std::vector<int> level(LHEIGHT*LWIDTH, 0);

    MapGenerator *mg = new MapGenerator;
    mg->levelGenerate(level);
    delete mg;

    spawnCharacters(hero, soldier);

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

        // Draw hero and enemies
        window.draw(hero.getSprite());
        for (int i = 0; i < 5; i++)
            window.draw(soldier[i].getSprite());


        window.display();
    }

    return 0;
}

void spawnCharacters(Hero &hero, Enemy* soldier)
{
    std::mt19937 gen;
    auto now = std::chrono::high_resolution_clock::now();
    gen.seed(now.time_since_epoch().count());

    int hero_pos = gen() % (LHEIGHT*LWIDTH);
    hero.setStartPosition(hero_pos);

    int row = hero_pos / LWIDTH;
    int col = hero_pos % LWIDTH;

    for (int i = 0; i < 5; i++) {
        int enemy_col, enemy_row;

        while(true) {
            enemy_col = gen() % LWIDTH;
            enemy_row = gen() % LHEIGHT;
            if ((enemy_col < col - 1 || enemy_col > col + 1) &&
                (enemy_row < row - 1 || enemy_row > row + 1))
                break;
        }

        int enemy_pos = enemy_row * LWIDTH + enemy_col;
        soldier[i].setStartPosition(enemy_pos);
    }
}
