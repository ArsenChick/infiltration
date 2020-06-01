#include "hero.h"

Hero::Hero()
{
    speed = 0.2;
    pos = 0;
}

void Hero::setStartPosition(int tileno)
{
    pos = tileno;

    int row = tileno / LWIDTH;
    int col = tileno % LWIDTH;

    x = col * TILESIZE + TILESIZE / 2 - HEROW / 2;
    y = row * TILESIZE + TILESIZE / 2 - HEROH / 2;
    sprite.setPosition(x, y);
}

void Hero::load(sf::Texture *hero_texture)
{
    texture = hero_texture;
    sprite.setTexture(*texture);

    sprite.setTextureRect(sf::IntRect(0, 0, HEROW, HEROH));
}

void Hero::move(std::vector<int>& level, float time, float& CurrentFrame)
{
    int row = pos / LWIDTH;
    int col = pos % LWIDTH;

    int left_bound = col * TILESIZE + WALLSIZE;
    int upper_bound = row * TILESIZE + WALLSIZE;
    int right_bound = (col+1) * TILESIZE - WALLSIZE - HEROW;
    int lower_bound = (row+1) * TILESIZE - WALLSIZE - HEROH;

    animate(time, CurrentFrame);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

        if ((level[pos] & ROUTELEFT) != 0) {
            if (y >= upper_bound && y < lower_bound)
                sprite.move(-speed*time, 0);
            else if (x - speed*time >= left_bound)
                sprite.move(-speed*time, 0);
        }
        else if (x - speed*time >= left_bound)
            sprite.move(-speed*time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

        if ((level[pos] & ROUTERIGHT) != 0) {
            if (y >= upper_bound && y < lower_bound)
                sprite.move(speed*time, 0);
            else if (x + speed*time < right_bound)
                sprite.move(speed*time, 0);
        }
        else if (x + speed*time < right_bound)
            sprite.move(speed*time, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

        if ((level[pos] & ROUTEUP) != 0) {
            if (x >= left_bound && x < right_bound)
                sprite.move(0, -speed*time);
            else if (y - speed*time >= upper_bound)
                sprite.move(0, -speed*time);
        }
        else if (y - speed*time >= upper_bound)
            sprite.move(0, -speed*time);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

        if ((level[pos] & ROUTEDOWN) != 0) {
            if (x >= left_bound && x < right_bound)
                sprite.move(0, speed*time);
            else if (y + speed*time < lower_bound)
                sprite.move(0, speed*time);
        }
        else if (y + speed*time < lower_bound)
            sprite.move(0, speed*time);
    }

    x = sprite.getPosition().x;
    y = sprite.getPosition().y;

    pos = int(x)/TILESIZE + int(y)/TILESIZE * LWIDTH;

}

void Hero::animate(float time, float &CurrentFrame)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*HEROW, HEROH, HEROW, HEROH));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*HEROW, 2*HEROH, HEROW, HEROH));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*HEROW, 3*HEROH, HEROW, HEROH));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*HEROW, 0, HEROW, HEROH));
    }
}
