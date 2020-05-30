#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

class Enemy
{

private:
    sf::Sprite sprite;
    sf::Texture *texture;

    float x;
    float y;

    int dx;
    int dy;

    unsigned int look = LEFT;        // направление взгляда 0 - верх, 1 - право, 2 - вниз, 3 лево
    // переменная time понадобится для 2 секундной задержки
    // переменная статуса для убийства -> удаления

public:
    Enemy();

    void load(sf::Texture *enemy_texture);
    void setCoordinates(int x, int y);

    // int search(float player_x, float player_y, int pl_height, int pl_width, int time);

    float getX() {return x;}
    float getY() {return y;}

    int getDX() {return dx;}
    int getDY() {return dy;}

    sf::Sprite getSprite() {return sprite;}
};


#endif // ENEMY_H
