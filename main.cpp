#include <SFML/Graphics.hpp>
#include <vector>

#include "mapgenerator.h"
#include "enemy.h"
#include "hero.h"
#include "map.h"
#include "bar.h"

void spawnCharacters(Hero &hero, Enemy* soldier);

int main()
{
    float CurrentFrame = 0;

    // Creating the window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Tilemap", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // Loading hero
    sf::Texture hero_texture;
    if (!hero_texture.loadFromFile("image.png"))
        exit(EXIT_FAILURE);

    Hero hero;
    hero.load(&hero_texture);

    // Loading enemy
    sf::Texture enemy_texture;
    if (!enemy_texture.loadFromFile("enemy.png"))
        exit(EXIT_FAILURE);

    Enemy soldier[ENEMYN];
    for (int i = 0; i < ENEMYN; i++)
        soldier[i].load(&enemy_texture);

    // Creating level
    std::vector<int> level(LHEIGHT*LWIDTH, 0);

    MapGenerator *mg = new MapGenerator;
    mg->levelGenerate(level);
    delete mg;

    spawnCharacters(hero, soldier);

    Map map;
    if (!map.load("map.png", sf::Vector2u(160, 160), level, LWIDTH, LHEIGHT))
        return -1;

    // Load font
    sf::Font font;
    if (!font.loadFromFile("19413.ttf"))
    {
        exit(EXIT_FAILURE);
    }

    // Toolsbar and Timer for moving
    Toolsbar toolsbar(font);
    int count_alive;
    int timeOfGame = 0;
    int endOfGame = -1;
    sf::Clock clock;

    // Running the main loop
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        // getting enemy's hitboxes for later calculations
        std::vector<sf::FloatRect> enemyHitbox;
        for (int i = 0; i < ENEMYN; i++) {
            sf::FloatRect currentRect = soldier[i].getSprite().getGlobalBounds();
            if (soldier[i].status == DEAD) {
                currentRect.left = 0;
                currentRect.top = 0;
                currentRect.width = 0;
                currentRect.height = 0;
            }
            enemyHitbox.push_back(currentRect);
        }


        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // key - LCtrl - crouch mode
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::LControl))
                hero.changeSpeed();
            // key - ESC - leaving the game
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // setting game camera
        window.setView(hero.getView());
      
        // draw the map
        window.clear(sf::Color(50, 50, 38));

        // checking collisions and moving the hero
        hero.checkForEnemies(enemyHitbox, time);
        hero.move(level, time, CurrentFrame);

        // enemy routine
        for (int i = 0; i < ENEMYN; i++) {
            if (soldier[i].status == ALIVE) {
                int res = soldier[i].hunt(hero.getSprite().getGlobalBounds());
                /* if the hero is not in an enemy's line of sight
                 * then move the enemy, else - don't move
                 */
                if (res == 0) {
                    soldier[i].move(level, time);
                    if (hero.kill(enemyHitbox[i]))
                        soldier[i].status = DEAD;
                }
                if (res == 2)
                    endOfGame = 0;
            }
        }

        // drawing objects
        window.draw(map);
        //window.draw(hero.testbox);
        window.draw(hero.getSprite());

        // drawing enemies depending on their status
        count_alive = 0;
        for (int i = 0; i < ENEMYN; i++) {
            if (soldier[i].status == ALIVE) {
                count_alive ++;
                window.draw(soldier[i].testbox);
                window.draw(soldier[i].getSprite());
            }
        }

        // drawing HUD
        timeOfGame = toolsbar.draw(window, count_alive);

        // displaying collected objects
        window.display();

        // Time's up
        if (timeOfGame == 0) {
            endOfGame = 2;
            window.close();
        }


        // Situation of lose
        if (endOfGame == 0) {
            window.close();
        }

        // Situation of win
        if (count_alive == 0) {
            endOfGame = 1;
            window.close();
        }
    }

    if (endOfGame != -1) {

        // Creating object for text and getting font
        sf::Text text;

        // Creating window for end of game
        sf::RenderWindow windowOfEnd(sf::VideoMode(400, 200), "", sf::Style::Titlebar | sf::Style::Close);
        windowOfEnd.setFramerateLimit(60);
        windowOfEnd.requestFocus();
        while (windowOfEnd.isOpen()) {

            sf::Event events;
            while (windowOfEnd.pollEvent(events))
            {
                // key - ESC - leaving the game
                if (events.type == sf::Event::Closed)
                    windowOfEnd.close();
            }

            windowOfEnd.clear(sf::Color::White);

            // Establish parameters
            if (endOfGame == 0)
                text.setString("YOU LOST");
            if (endOfGame == 1)
                text.setString("YOU WON");
            if (endOfGame == 2)
                text.setString("TIME'S UP");

            text.setFont(font);
            text.setStyle(sf::Text::Bold);
            text.setFillColor(sf::Color::Black);
            text.setCharacterSize(40);
            text.setPosition(windowOfEnd.getView().getCenter().x - text.getGlobalBounds().width/2,
                             windowOfEnd.getView().getCenter().y - text.getGlobalBounds().height/2);
            windowOfEnd.draw(text);
            windowOfEnd.display();
        }
    }

    return 0;
}

void spawnCharacters(Hero &hero, Enemy* soldier)
{
    std::mt19937 gen;
    auto now = std::chrono::high_resolution_clock::now();
    gen.seed(now.time_since_epoch().count());

    int hero_pos = gen() % (LHEIGHT*LWIDTH);
    hero.setStartPosition(hero_pos);

    int row = hero_pos / LWIDTH;
    int col = hero_pos % LWIDTH;

    for (int i = 0; i < ENEMYN; i++) {
        int enemy_col, enemy_row;

        while(true) {
            enemy_col = gen() % LWIDTH;
            enemy_row = gen() % LHEIGHT;
            if ((enemy_col < col - 1 || enemy_col > col + 1) &&
                (enemy_row < row - 1 || enemy_row > row + 1))
                break;
        }

        unsigned int enemy_pos = enemy_row * LWIDTH + enemy_col;
        soldier[i].setStartPosition(enemy_pos);
    }
}
