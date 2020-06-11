#include "enemy.h"
#include <algorithm>

Enemy::Enemy()
{
    dx = 5;
    dy = 5;
    speed = 0.1;
    look = UP;
}

void Enemy::setStartPosition(int tileno)
{
    pos = tileno;

    int row = tileno / LWIDTH;
    int col = tileno % LWIDTH;

    x = col * TILESIZE + (float)TILESIZE / 2 - (float)ENEMYW / 2;
    y = row * TILESIZE + (float)TILESIZE / 2 - (float)ENEMYH / 2;
    sprite.setPosition(x, y);
    gen.seed(rand() % (int)x + y);
}

void Enemy::load(sf::Texture *enemy_texture)
{
    texture = enemy_texture;
    sprite.setTexture(*texture);

    sprite.setTextureRect(sf::IntRect(0, 0, ENEMYW, ENEMYH));
}

void Enemy::move(std::vector<int>& level, float time)
{
    if (time_w != -1) {
        if (clock_e.getElapsedTime().asSeconds() - time_w >= 0.5) {
            clock_e.restart();
            time_w = -1;
            look = gen() % 5;
        }
        return;
    }

    float last_x = x;
    float last_y = y;

    int row = pos / LWIDTH;
    int col = pos % LWIDTH;

    float for_y = row * TILESIZE + WALLSIZE + (float)(TILESIZE - 2 * WALLSIZE - ENEMYH) / 2;
    float for_x = col * TILESIZE + WALLSIZE + (float)(TILESIZE - 2 * WALLSIZE - ENEMYW) / 2;

    float left_bound = col * TILESIZE + WALLSIZE;
    float upper_bound = row * TILESIZE + WALLSIZE;
    float right_bound = (col+1) * TILESIZE - WALLSIZE - ENEMYW;
    float lower_bound = (row+1) * TILESIZE - WALLSIZE - ENEMYH;

    if (look == LEFT) {
        if ((level[pos] & ROUTELEFT) != 0) {
            if (y >= upper_bound && y < lower_bound) {
                y = for_y;
                sprite.setPosition(x, y);
                sprite.move(-speed*time, 0);
            }
            //else if (x - speed*time >= for_x)
            //sprite.move(-speed*time, 0);
        }
        else if (x - speed*time >= for_x)
            sprite.move(-speed*time, 0);
    }
    if (look == RIGHT) {
        if ((level[pos] & ROUTERIGHT) != 0) {
            if (y >= upper_bound && y < lower_bound) {
                y = for_y;
                sprite.setPosition(x, y);
                sprite.move(speed*time, 0);
            }
            //else if (x + speed*time < for_x)
            //sprite.move(speed*time, 0);
        }
        else if (x + speed*time < for_x)
            sprite.move(speed*time, 0);
    }
    if (look == UP) {
        if ((level[pos] & ROUTEUP) != 0) {
            if (x >= left_bound && x < right_bound) {
                x = for_x;
                sprite.setPosition(x, y);
                sprite.move(0, -speed*time);
            }
            //else if (y - speed*time >= for_y)
            //sprite.move(0, -speed*time);
        }
        else if (y - speed*time >= for_y)
            sprite.move(0, -speed*time);
    }
    if (look == DOWN) {
        if ((level[pos] & ROUTEDOWN) != 0) {
            if (x >= left_bound && x < right_bound) {
                x = for_x;
                sprite.setPosition(x, y);
                sprite.move(0, speed*time);
            }
            //else if (y + speed*time < for_y)
            //sprite.move(0, speed*time);
        }
        else if (y + speed*time < for_y)
            sprite.move(0, speed*time);
    }

    x = sprite.getPosition().x;
    y = sprite.getPosition().y;

    pos = int(x)/TILESIZE + int(y)/TILESIZE * LWIDTH;

    if ((last_x == x) && (last_y == y)) {
        time_w = clock_e.getElapsedTime().asSeconds();
    }
}

