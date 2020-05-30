#include "hero.h"

Hero::Hero()
{
    speed = 0.2;
}

int Hero::setCoordintaes(int start_x, int start_y)
{
    /* updating x if available */
    if (start_x > -1 && start_x < 200)
        x = start_x;
    else
        return -1;

    /* updating y if available */
    if (start_y > -1 && start_y < 200)
        x = start_y;
    else
        return -1;

    return 0;
}

void Hero::load(sf::Texture *hero_texture)
{
    texture = hero_texture;
    sprite.setTexture(*texture);

    sprite.setPosition(x, y);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 96));
}

void Hero::move(float time, float& CurrentFrame)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64, 96, 64, 96));
        sprite.move(-speed*time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64, 192, 64, 96));
        sprite.move(speed*time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64, 288, 64, 96));
        sprite.move(0, -speed*time);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*64, 0, 64, 96));
        sprite.move(0, speed*time);
    }
}
