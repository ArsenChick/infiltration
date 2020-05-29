#include <SFML/Graphics.hpp>
#include <vector>
#include "mapgenerator.h"
#include "enemy.h"
#include "map.h"

void keyboard(float time, float& speed, float& CurrentFrame, sf::Sprite& hero_sprite);

int main()
{
    sf::Image image;
    sf::Texture hero_texture;
    sf::Sprite hero_sprite;
    float speed = 0.1;
    float CurrentFrame = 0;

    // create the window
    sf::RenderWindow window(sf::VideoMode(640, 640), "Tilemap");
    window.setFramerateLimit(60);

    image.loadFromFile("C:\\QtTasks\\Project\\image.png");
    hero_texture.loadFromImage(image);
    hero_sprite.setTexture(hero_texture);
    hero_sprite.setPosition(50, 50);
    hero_sprite.setTextureRect(sf::IntRect(0, 0, 64, 96));

    // Loading enemy
    sf::Texture enemy_texture;
    image.loadFromFile("C:\\QtTasks\\Project\\enemy.png");
    enemy_texture.loadFromImage(image);
    Enemy soldier(0);
    soldier.coordinate(200,200);
    soldier.load(&enemy_texture);

    // Timer
    sf::Clock clock;

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

        keyboard(time, speed, CurrentFrame, hero_sprite);

        // Отрисовка спрайтов героя и врага
        window.draw(hero_sprite);
        window.draw(soldier.getSprite());

        window.draw(map);
        window.display();
    }

    return 0;
}

void keyboard(float time, float& speed, float& CurrentFrame, sf::Sprite& hero_sprite)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        hero_sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64, 96, 64, 96));
        hero_sprite.move(-speed*time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        hero_sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64, 192, 64, 96));
        hero_sprite.move(speed*time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        hero_sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64, 288, 64, 96));
        hero_sprite.move(0, -speed*time);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        hero_sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64, 0, 64, 96));
        hero_sprite.move(0, speed*time);
    }
}

