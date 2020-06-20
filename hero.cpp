#include "hero.h"

Hero::Hero()
{
    view.reset(sf::FloatRect(0, 0, MAPSCALE*640, MAPSCALE*480));
}

void Hero::changeSpeed()
{
    if (fabs(speed - DEFAULTSPEED) <= EPS)
        speed = CROUCHSPEED;
    else
        speed = DEFAULTSPEED;
}

void Hero::setStartPosition(unsigned int tileno)
{
    pos = tileno;
    int row = tileno / LWIDTH;
    int col = tileno % LWIDTH;

    // calculating x and y coordinates
    x = col * TILESIZE + float(TILESIZE) / 2 - float(HEROW) / 2;
    y = row * TILESIZE + float(TILESIZE) / 2 - float(HEROH) / 2;
    // setting up the sprite position
    sprite.setPosition(x, y);

    // damage area of your hero
    dmg_area = sf::FloatRect(x, y, HEROW, HEROH);

    testbox.setPosition(x, y);
    testbox.setSize(sf::Vector2f(HEROW, HEROH));
    testbox.setFillColor(sf::Color(0, 0, 255, 100));

    // camera's center == hero's center
    view.setCenter(x + (float)HEROW/2, y + (float)HEROH/2);
}

void Hero::load(sf::Texture *hero_texture)
{
    // loading texture
    texture = hero_texture;
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(0, 0, HEROW, HEROH));
}

void Hero::checkForEnemies(std::vector<sf::FloatRect> &enemyRect, float time)
{
    // getting hero's hitbox from his sprite
    sf::FloatRect hitboxHero = sprite.getGlobalBounds();
    // offset for enemy extended hitbox
    float offset = speed*time;

    // checking collision for every enemy
    for (unsigned int i = 0; i < enemyRect.size(); i++) {
        // making extended enemy hitbox
        sf::FloatRect enemyExtendedRect(enemyRect[i].left - offset, enemyRect[i].top - offset,
                                        enemyRect[i].width + offset*2, enemyRect[i].height + offset*2);
        // using a sfml function "intercests" to check the collision
        if (enemyExtendedRect.intersects(hitboxHero)) {

            // getting enemy's coordinates from his non-extended hitbox
            float enemy_x = enemyRect[i].left;
            float enemy_y = enemyRect[i].top;

            // checking available for moving ways
            if (x - enemy_x - ENEMYW < offset && x - enemy_x - ENEMYW > 0)
                left = false;
            if (enemy_x - x - HEROW < offset && enemy_x - x - HEROW > 0)
                right = false;
            if (enemy_y - y - HEROH < offset && enemy_y - y - HEROH > 0)
                down = false;
            if (y - enemy_y - ENEMYH < offset && y - enemy_y - ENEMYH > 0)
                up = false;
        }
    }

}

void Hero::move(std::vector<int>& level, float time, float& CurrentFrame)
{
    int row = pos / LWIDTH;
    int col = pos % LWIDTH;

    int left_bound = col * TILESIZE + WALLSIZE;
    int upper_bound = row * TILESIZE + WALLSIZE;
    int right_bound = (col+1) * TILESIZE - WALLSIZE - HEROW;
    int lower_bound = (row+1) * TILESIZE - WALLSIZE - HEROH;

    // calling animate to make hero look properly
    animate(time, CurrentFrame);

    // moving the hero according to a pressed button
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && left) {

        if ((level[pos] & ROUTELEFT) != 0) {
            if (y >= upper_bound && y <= lower_bound) {
                sprite.move(-speed*time, 0);
                dmg_area.left -= speed*time;
            }
            else if (x - speed*time >= left_bound) {
                sprite.move(-speed*time, 0);
                dmg_area.left -= speed*time;
            }
        }
        else if (x - speed*time >= left_bound) {
            sprite.move(-speed*time, 0);
            dmg_area.left -= speed*time;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && right) {

        if ((level[pos] & ROUTERIGHT) != 0) {
            if (y >= upper_bound && y <= lower_bound) {
                sprite.move(speed*time, 0);
                dmg_area.left += speed*time;
            }
            else if (x + speed*time <= right_bound) {
                sprite.move(speed*time, 0);
                dmg_area.left += speed*time;
            }
        }
        else if (x + speed*time <= right_bound) {
            sprite.move(speed*time, 0);
            dmg_area.left += speed*time;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && up) {

        if ((level[pos] & ROUTEUP) != 0) {
            if (x >= left_bound && x <= right_bound) {
                sprite.move(0, -speed*time);
                dmg_area.top -= speed*time;
            }
            else if (y - speed*time >= upper_bound) {
                sprite.move(0, -speed*time);
                dmg_area.top -= speed*time;
            }
        }
        else if (y - speed*time >= upper_bound) {
            sprite.move(0, -speed*time);
            dmg_area.top -= speed*time;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && down) {

        if ((level[pos] & ROUTEDOWN) != 0) {
            if (x >= left_bound && x <= right_bound) {
                sprite.move(0, speed*time);
                dmg_area.top += speed*time;
            }
            else if (y + speed*time <= lower_bound) {
                sprite.move(0, speed*time);
                dmg_area.top += speed*time;
            }
        }

        else if (y + speed*time <= lower_bound) {
            sprite.move(0, speed*time);
            dmg_area.top += speed*time;
        }
    }

    // updating x and y
    x = sprite.getPosition().x;
    y = sprite.getPosition().y;

    // updating line of sight
    adjustLoS();

    // making ways available
    up = true;
    down = true;
    left = true;
    right = true;

    // updating pos in the tiles
    pos = int(x)/TILESIZE + int(y)/TILESIZE * LWIDTH;

    // updating camera's center
    view.setCenter(x + HEROW/2, y + HEROH/2);
}

void Hero::animate(float time, float &CurrentFrame)
{
    // animating hero depending on a pressed button
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        CurrentFrame += 0.005*time;
        look = LEFT;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*HEROW, HEROH, HEROW, HEROH));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        CurrentFrame += 0.005*time;
        look = RIGHT;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*HEROW, 2*HEROH, HEROW, HEROH));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        CurrentFrame += 0.005*time;
        look = UP;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*HEROW, 3*HEROH, HEROW, HEROH));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        CurrentFrame += 0.005*time;
        look = DOWN;
        if (CurrentFrame > 4) CurrentFrame -= 4;
        sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*HEROW, 0, HEROW, HEROH));
    }
}

void Hero::adjustLoS()
{
    // adjusting the line of sight depending on a hero's look
    switch(look) {
    case LEFT: {
        dmg_area.top = y - LOSOFFSET;
        dmg_area.left = x - HEROW - LOSOFFSET;
        dmg_area.width = 2*HEROW;
        dmg_area.height = HEROH + 2*LOSOFFSET;
        break;
    }
    case RIGHT: {
        dmg_area.top = y - LOSOFFSET;
        dmg_area.left = x - LOSOFFSET;
        dmg_area.width = 2*HEROW + 2*LOSOFFSET;
        dmg_area.height = HEROH + 2*LOSOFFSET;
        break;
    }
    case UP: {
        dmg_area.top = y - HEROW - 2*LOSOFFSET;
        dmg_area.left = x - 2*LOSOFFSET;
        dmg_area.width = HEROW + 4*LOSOFFSET;
        dmg_area.height = 2*HEROH;
        break;
    }
    case DOWN: {
        dmg_area.top = y - 2*LOSOFFSET;
        dmg_area.left = x - 2*LOSOFFSET;
        dmg_area.height = 2*HEROH;
        dmg_area.width = HEROW + 4*LOSOFFSET;
        break;
    }
    }
    testbox.setPosition(dmg_area.left, dmg_area.top);
    testbox.setSize(sf::Vector2f(dmg_area.width, dmg_area.height));
}

int Hero::kill(sf::FloatRect enemyHitbox)
{
    /* we can kill only if hero's line of sight intersects enemy's hitbox
    *  and also the button for eliminating (Tab originally) is pressed
    */
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) &&
        enemyHitbox.intersects(dmg_area))
            return 1;
        else
            return 0;

}
