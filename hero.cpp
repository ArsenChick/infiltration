#include "hero.h"

Hero::Hero()
{
    view.reset(sf::FloatRect(0, 0, MAPSCALE*640, MAPSCALE*480));
}

void Hero::setStartPosition(unsigned int tileno)
{
    pos = tileno;
    int row = tileno / LWIDTH;
    int col = tileno % LWIDTH;

    x = col * TILESIZE + float(TILESIZE) / 2 - float(HEROW) / 2;
    y = row * TILESIZE + float(TILESIZE) / 2 - float(HEROH) / 2;
    sprite.setPosition(x, y);

    hitbox = sf::FloatRect(x, y, HEROW, HEROH);

    testbox.setPosition(x, y);
    testbox.setSize(sf::Vector2f(HEROW, HEROH));
    testbox.setFillColor(sf::Color(0, 0, 255, 100));

    view.setCenter(x + (float)HEROW/2, y + (float)HEROH/2);
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
            if (y >= upper_bound && y <= lower_bound) {
                sprite.move(-speed*time, 0);
                hitbox.left -= speed*time;
            }
            else if (x - speed*time >= left_bound) {
                sprite.move(-speed*time, 0);
                hitbox.left -= speed*time;
            }
        }
        else if (x - speed*time >= left_bound) {
            sprite.move(-speed*time, 0);
            hitbox.left -= speed*time;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

        if ((level[pos] & ROUTERIGHT) != 0) {
            if (y >= upper_bound && y <= lower_bound) {
                sprite.move(speed*time, 0);
                hitbox.left += speed*time;
            }
            else if (x + speed*time <= right_bound) {
                sprite.move(speed*time, 0);
                hitbox.left += speed*time;
            }
        }
        else if (x + speed*time <= right_bound) {
            sprite.move(speed*time, 0);
            hitbox.left += speed*time;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

        if ((level[pos] & ROUTEUP) != 0) {
            if (x >= left_bound && x <= right_bound) {
                sprite.move(0, -speed*time);
                hitbox.top -= speed*time;
            }
            else if (y - speed*time >= upper_bound) {
                sprite.move(0, -speed*time);
                hitbox.top -= speed*time;
            }
        }
        else if (y - speed*time >= upper_bound) {
            sprite.move(0, -speed*time);
            hitbox.top -= speed*time;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

        if ((level[pos] & ROUTEDOWN) != 0) {
            if (x >= left_bound && x <= right_bound) {
                sprite.move(0, speed*time);
                hitbox.top += speed*time;
            }
            else if (y + speed*time <= lower_bound) {
                sprite.move(0, speed*time);
                hitbox.top += speed*time;
            }
        }
        else if (y + speed*time <= lower_bound) {
            sprite.move(0, speed*time);
            hitbox.top += speed*time;
        }
    }

    x = sprite.getPosition().x;
    y = sprite.getPosition().y;

    testbox.setPosition(hitbox.left, hitbox.top);

    pos = int(x)/TILESIZE + int(y)/TILESIZE * LWIDTH;
    view.setCenter(x + HEROW/2, y + HEROH/2);
}

void Hero::animate(float time, float &CurrentFrame)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*HEROW, HEROH, HEROW, HEROH));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*HEROW, 2*HEROH, HEROW, HEROH));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*HEROW, 3*HEROH, HEROW, HEROH));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        CurrentFrame += 0.005*time;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*HEROW, 0, HEROW, HEROH));
    }
}
