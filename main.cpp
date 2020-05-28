#include <iostream>
#include <SFML/Graphics.hpp>
#include "hero.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML");

    Hero hero;
    sf::Image hero_image;
    sf::Texture hero_texture;
    sf::Sprite hero_sprite;

    char *filename = (char*) malloc(sizeof(char) * 1024);
    snprintf(filename, 1024, "%s/external/images/hero.png", PRO_FILE_PWD);

    hero_image.loadFromFile(filename);
    hero_texture.loadFromImage(hero_image);
    hero_sprite = hero.load(hero_texture);

    free(filename);

    while (window.isOpen())
    {
        // Обрабатываем очередь событий в цикле
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Пользователь нажал на «крестик» и хочет закрыть окно?
            if (event.type == sf::Event::Closed)
                // Тогда закрываем его
                window.close();
        }
        // Отрисовка окна
        window.display();
        window.draw(hero_sprite);
    }

    return 0;
}
