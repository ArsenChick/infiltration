#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>

class Enemy
{

private:
    sf::Sprite en_sprite;
    sf::Texture *en_texture;
    float en_x;
    float en_y;
    int en_dx;              // скорость по х
    int en_dy;              // скорость по у
    int en_look = 3;        // направление взгляда 0 - верх, 1 - право, 2 - вниз, 3 лево
    // переменная time понадобится для 2 секундной задержки
    // переменная статуса для убийства -> удаления

public:
    Enemy (int look);     // create enemy

    void load(sf::Texture *enemy_texture);  // load sprite

    int search(float player_x, float player_y, int pl_height, int pl_width, int time);   // check hero

    void coordinate(int x, int y);  // set coordinates

    // void move перемещение

    float getX() {return en_x;}
    float getY() {return en_y;}
    sf::Sprite getSprite() {return en_sprite;}
};


#endif // ENEMY_H
