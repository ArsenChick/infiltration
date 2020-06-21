#include "enemy.h"
#include <algorithm>

Enemy::Enemy()
{

}

void Enemy::setStartPosition(unsigned int tileno)
{
    pos = tileno;
    int row = tileno / LWIDTH;
    int col = tileno % LWIDTH;

    x = col * TILESIZE + (float)TILESIZE / 2 - (float)ENEMYW / 2;
    y = row * TILESIZE + (float)TILESIZE / 2 - (float)ENEMYH / 2;
    sprite.setPosition(x, y);

    dmg_area = sf::FloatRect(x, y, ENEMYW, ENEMYH);

    testbox.setPosition(x, y);
    testbox.setSize(sf::Vector2f(ENEMYW, ENEMYH));
    testbox.setFillColor(sf::Color(255, 0, 0, 100));

    gen.seed(rand() % (int)x + y);
    clock.restart();
}

void Enemy::load(sf::Texture *enemy_texture)
{
    texture = enemy_texture;
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(0, 0, ENEMYW, ENEMYH));
}

void Enemy::move(std::vector<int>& level, float time)
{
    if (time_wait != -1) {
        if (clock.getElapsedTime().asSeconds() - time_wait >= 0.2) {
            clock.restart();
            time_wait = -1;
            look = gen() % 4;
            adjustLoS(level);
        }
        return;
    }

    float last_x = x;
    float last_y = y;

    int row = pos / LWIDTH;
    int col = pos % LWIDTH;

    float left_bound = col * TILESIZE + WALLSIZE + 10;
    float upper_bound = row * TILESIZE + WALLSIZE + 10;
    float right_bound = (col+1) * TILESIZE - WALLSIZE - ENEMYW - 10;
    float lower_bound = (row+1) * TILESIZE - WALLSIZE - ENEMYH - 10;

    switch (look) {
    case LEFT: {
        if ((level[pos] & ROUTELEFT) != 0) {
            if (y >= upper_bound && y <= lower_bound) {
                sprite.move(-speed*time, 0);
                dmg_area.left -= speed*time;
            }
        }
        else if (x - speed*time >= left_bound) {
            sprite.move(-speed*time, 0);
            dmg_area.left -= speed*time;
        }
        break;
    }
    case RIGHT: {
        if ((level[pos] & ROUTERIGHT) != 0) {
            if (y >= upper_bound && y <= lower_bound) {
                sprite.move(speed*time, 0);
                dmg_area.left += speed*time;
            }
        }
        else if (x + speed*time <= right_bound) {
            sprite.move(speed*time, 0);
            dmg_area.left += speed*time;
        }
        break;
    }
    case UP: {
        if ((level[pos] & ROUTEUP) != 0) {
            if (x >= left_bound && x <= right_bound) {
                sprite.move(0, -speed*time);
                dmg_area.top -= speed*time;
            }
        }
        else if (y - speed*time >= upper_bound) {
            sprite.move(0, -speed*time);
            dmg_area.top -= speed*time;
        }
        break;
    }
    case DOWN: {
        if ((level[pos] & ROUTEDOWN) != 0) {
            if (x >= left_bound && x <= right_bound) {
                sprite.move(0, speed*time);
                dmg_area.top += speed*time;
            }
        }
        else if (y + speed*time <= lower_bound) {
            sprite.move(0, speed*time);
            dmg_area.top += speed*time;
        }
        break;
    }
    }

    x = sprite.getPosition().x;
    y = sprite.getPosition().y;

    adjustLoS(level);

    testbox.setPosition(dmg_area.left-LOSOFFSET, dmg_area.top-LOSOFFSET);

    pos = int(x)/TILESIZE + int(y)/TILESIZE * LWIDTH;

    if ((x >= left_bound && x <= right_bound) &&
        (y >= upper_bound && y <= lower_bound)) {
        int chance = gen() % 1000;
        if (chance > 980)
            time_wait = clock.getElapsedTime().asSeconds();
    }

    if ((last_x == x) && (last_y == y)) {
        time_wait = clock.getElapsedTime().asSeconds();
    }
}

int Enemy::hunt(sf::FloatRect heroRect)
{
    if (dmg_area.intersects(heroRect)) {
        if (time_wait != -1) {
            if (clock.getElapsedTime().asSeconds() - time_wait >= 1) {
                return 2;
            }
        }
        else {
            time_wait = clock.getElapsedTime().asSeconds();
        }
        return 1;
    }
    return 0;
}

void Enemy::adjustLoS(std::vector<int>& level)
{
    switch(look) {
    case LEFT: {
        if ((level[pos] & ROUTELEFT) != 0) {
            dmg_area.left = x - 2*ENEMYW;
            dmg_area.width = 3*ENEMYW;
        } else {
            dmg_area.left = x - ENEMYW;
            dmg_area.width = 2*ENEMYW;
        }
        dmg_area.top = y;
        dmg_area.height = ENEMYH;
        break;
    }
    case RIGHT: {
        if ((level[pos] & ROUTERIGHT) != 0)
            dmg_area.width = 3*ENEMYW;
        else
            dmg_area.width = 2*ENEMYW;
        dmg_area.left = x;
        dmg_area.top = y;
        dmg_area.height = ENEMYH;
        break;
    }
    case UP: {
        if ((level[pos] & ROUTEUP) != 0) {
            dmg_area.top = y - 2*ENEMYH;
            dmg_area.height = 3*ENEMYH;
        } else {
            dmg_area.top = y - ENEMYH;
            dmg_area.height = 2*ENEMYH;
        }
        dmg_area.left = x;
        dmg_area.width = ENEMYW;
        break;
    }
    case DOWN: {
        if ((level[pos] & ROUTEDOWN) != 0)
            dmg_area.height = 3*ENEMYH;
        else
            dmg_area.height = 2*ENEMYH;
        dmg_area.left = x;
        dmg_area.top = y;
        dmg_area.width = ENEMYW;
        break;
    }
    }
    testbox.setPosition(dmg_area.left-LOSOFFSET, dmg_area.top-LOSOFFSET);
    testbox.setSize(sf::Vector2f(dmg_area.width+2*LOSOFFSET, dmg_area.height+2*LOSOFFSET));
}
