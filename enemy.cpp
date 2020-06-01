#include "enemy.h"

Enemy::Enemy()
{
    dx = 5;
    dy = 5;
    look = UP;
}

void Enemy::setStartPosition(int tileno)
{
    pos = tileno;

    int row = tileno / LWIDTH;
    int col = tileno % LWIDTH;

    x = col * TILESIZE + TILESIZE / 2 - ENEMYW / 2;
    y = row * TILESIZE + TILESIZE / 2 - ENEMYH / 2;
    sprite.setPosition(x, y);
}

void Enemy::load(sf::Texture *enemy_texture)
{
    texture = enemy_texture;
    sprite.setTexture(*texture);

    sprite.setTextureRect(sf::IntRect(0, 0, ENEMYW, ENEMYH));
}

/* int Enemy::search(float player_x, float player_y, int pl_height, int pl_width, int time)
{
    float distance = 200;
    float pos_x; float pos_y;
    // Без понятия что по движению, буду считать
    // что середина координаты спрайта находится по середине коридора
    // возможно потребуется возможность определять координату стены либо её отдаленность?
    // но проще двигать их ровно по центру коридоров

    float corridor = 500;

    //  without time yet, для задержки(и постоять до разворота и для 2 секунд на убежать нужен таймер)

    // Up
    pos_x = x + sprite.getGlobalBounds().width / 2;   // середина спрайта -> середина коридора
    pos_y = y + sprite.getGlobalBounds().height / 2;  // задняя линия видимости врага
    if ((look == 0) && (player_y < y)) {
        if ((y - (player_y + pl_height)) < distance) {
            if (((x - corridor / 2) <= player_x) && ((player_x + pl_width) <= (x + corridor / 2))) {
                return 1;
            }
        }
    }

    // Right
    pos_x = x + sprite.getGlobalBounds().width / 2;   // задняя линия видимости врага
    pos_y = y + sprite.getGlobalBounds().height / 2;  // середина спрайта -> середина коридора
    if ((look == 1) && (player_x > x)) {
        if ((player_x - x) < distance) {
            if (((y - corridor / 2) <= player_y) && ((player_y + pl_height) <= (y + corridor / 2))) {
                return 1;
            }
        }
    }

    // Down
    pos_x = x + sprite.getGlobalBounds().width / 2;   // середина спрайта -> середина коридора
    pos_y = y + sprite.getGlobalBounds().height / 2;  // задняя линия видимости врага
    if ((look == 2) && (player_y > y)) {
        if ((player_y - y) < distance) {
            if (((x - corridor / 2) <= player_x) && ((player_x + pl_width) <= (x + corridor / 2))) {
                return 1;
            }
        }
    }

    // Left
    pos_x = x + sprite.getGlobalBounds().width / 2;   // задняя линия видимости врага
    pos_y = y + sprite.getGlobalBounds().height / 2;  // середина спрайта -> середина коридора
    if ((look == 3) && (player_x < x)) {
        if (((x - (player_x + pl_width)) < distance)) {
            if (((y - corridor / 2) <= player_y) && ((player_y + pl_height) <= (y + corridor / 2))) {
                return 1;
            }
        }
    }

    return 0;
} */
