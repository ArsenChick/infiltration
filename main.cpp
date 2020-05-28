#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"

// Объект, который, собственно, является главным окном приложения
sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Works!");
//  Create object
sf::Image image;
sf::Texture hero_texture;
sf::Sprite hero_sprite;
float speed = 0.1;
float CurrentFrame = 0;

void keyboard(float time);

int main()
{
    // Объект, который, собственно, является главным окном приложения
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Works!");
    window.setFramerateLimit(60);   // кол-во кадров в секунду

    // Loading hero
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

    // Главный цикл приложения: выполняется, пока открыто окно
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        // Обрабатываем события в цикле
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Пользователь нажал на «крестик» и хочет закрыть окно?
            if (event.type == sf::Event::Closed)
                // тогда закрываем его
                window.close();
        }

        // Установка цвета фона - белый
        window.clear(sf::Color::Black);

        keyboard(time);

        // Отрисовка спрайтов героя и врага
        window.draw(hero_sprite);
        window.draw(soldier.getSprite());

        // для проверки видно или нет std::cout << soldier.search(hero_sprite.getPosition().x,hero_sprite.getPosition().y,hero_sprite.getGlobalBounds().width,hero_sprite.getGlobalBounds().height,1);
        // Обратите внимание на параметры, Никита мне нужны будут позиция героя и доступ к параметрам спрайта (у меня такое для тебя есть)

        // Отрисовка окна
        window.display();
    }

    return 0;
}

void keyboard(float time)
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
