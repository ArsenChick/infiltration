#include "enemy.h"

Enemy::Enemy (int look)
{
    en_dx = 5;         // скорость по х
    en_dy = 5;         // скороссть по у
    en_look = look;
}

void Enemy::coordinate(int x, int y)
{
    en_x = x;
    en_y = y;
}

void Enemy::load(sf::Texture *enemy_texture)
{
    // Loading
    en_texture = enemy_texture;
    en_sprite.setTexture(*en_texture);
    en_sprite.setPosition(en_x, en_y);
    en_sprite.setTextureRect(sf::IntRect(0, 0, 179, 187));
}

int Enemy::search(float player_x, float player_y, int pl_height, int pl_width, int time)
{
    float distance = 200;
    float x; float y;
    // Без понятия что по движению, буду считать
    // что середина координаты спрайта находится по середине коридора
    // возможно потребуется возможность определять координату стены либо её отдаленность?
    // но проще двигать их ровно по центру коридоров

    float corridor = 500;

    //  without time yet, для задержки(и постоять до разворота и для 2 секунд на убежать нужен таймер)

    // Up
    x = en_x + en_sprite.getGlobalBounds().width / 2;   // середина спрайта -> середина коридора
    y = en_y + en_sprite.getGlobalBounds().height / 2;  // задняя линия видимости врага
    if ((en_look == 0) && (player_y < y)) {
        if ((y - (player_y + pl_height)) < distance) {
            if (((x - corridor / 2) <= player_x) && ((player_x + pl_width) <= (x + corridor / 2))) {
                return 1;
            }
        }
    }

    // Right
    x = en_x + en_sprite.getGlobalBounds().width / 2;   // задняя линия видимости врага
    y = en_y + en_sprite.getGlobalBounds().height / 2;  // середина спрайта -> середина коридора
    if ((en_look == 1) && (player_x > x)) {
        if ((player_x - x) < distance) {
            if (((y - corridor / 2) <= player_y) && ((player_y + pl_height) <= (y + corridor / 2))) {
                return 1;
            }
        }
    }

    // Down
    x = en_x + en_sprite.getGlobalBounds().width / 2;   // середина спрайта -> середина коридора
    y = en_y + en_sprite.getGlobalBounds().height / 2;  // задняя линия видимости врага
    if ((en_look == 2) && (player_y > y)) {
        if ((player_y - y) < distance) {
            if (((x - corridor / 2) <= player_x) && ((player_x + pl_width) <= (x + corridor / 2))) {
                return 1;
            }
        }
    }

    // Left
    x = en_x + en_sprite.getGlobalBounds().width / 2;   // задняя линия видимости врага
    y = en_y + en_sprite.getGlobalBounds().height / 2;  // середина спрайта -> середина коридора
    if ((en_look == 3) && (player_x < x)) {
        if (((x - (player_x + pl_width)) < distance)) {
            if (((y - corridor / 2) <= player_y) && ((player_y + pl_height) <= (y + corridor / 2))) {
                return 1;
            }
        }
    }

    return 0;
}
