#ifndef ENEMY_H
#define ENEMY_H

/*!
 * \defgroup GameChars Game characters
 * \brief Main game character entities.
 *
 * This group contains links to classes
 * which describe character entities in
 * the game: Enemy and Hero.
 *
 * \note Need to show my mentor how
 * Doxygen behaves strangely when dealing
 * with member grouping in modules.
 */

/*! \file */

#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include "defines.h"

/*!
 * \ingroup GameChars
 * \brief A class for %Enemy entity.
 */

class Enemy
{

private:
    ///@{
    /*!
     * \brief Graphical resourses.
     *
     * Needs to be stored throughout the program.
     */
    sf::Sprite sprite;
    sf::Texture *texture;
    ///@}

    //! Damage area rectangle.
    sf::FloatRect dmg_area;
    //! %Enemy's line of sight rectangle
    sf::RectangleShape lineOfSight;

    //! X coordinate on the map.
    float x;
    //! Y coordinate on the map.
    float y;

    //! %Enemy's speed.
    float speed = 0.2;

    //! Current frame used for animation.
    float CurrentFrame = 0;

    //! Position in the tiles.
    unsigned int pos = 0;
    //! Direction of the %Enemy's look.
    /*! Used for adjusting the line of sight. */
    unsigned int look = UP;

    //! SFML clock for calculations.
    /*! Used as a base for the %Enemy's simple AI. */
    sf::Clock clock;
    //! Time spent still.
    /*! Acts as a death timer for the Hero. */
    float time_wait = -1;

    //! Randomizer.
    /*! Used for changing the directions. */
    std::mt19937 gen;

    //! Performs default moving animation.
    /*! Function used primarily within move function.
     * \param time represents the game state in terms of animation.
     */
    void animate(float time);
    //! Updates the rectangle of the line of sight.
    /*! \param level represents the model for the current level.
     */
    void adjustLoS(std::vector<int>& level);

public:
    //! %Enemy's status
    /*! ALIVE or DEAD */
    unsigned int status = ALIVE;

    //! Loads a texture.
    /*! \param enemy_texture texture to load.
     */
    void load(sf::Texture *enemy_texture);
    //! Spawns the %Enemy in a tile.
    /*! \param tileno position to spawn the %Enemy in.
     */
    void setStartPosition(unsigned int tileno);

    //! Performs a movement action.
    /*!
     * \param level represents the model for the current level.
     * \param time represents the game state in terms of animation.
     */
    void move(std::vector<int>& level, float time);
    //! Checks if the Enemy has catched a Hero.
    /*!
     * \param heroRect rectangle representing Hero's hitbox.
     * \return The status of the hunt.
     * 0 if the Enemy does not have the %Hero in the line of sight,
     * 1 if does, 2 if the %Hero stood long enough in the %Enemy's line of sight.
     */
    int hunt(sf::FloatRect heroRect);

    //! Getter for %Enemy's sprite.
    sf::Sprite& getSprite() {return sprite;}
    //! Getter for %Enemy's line of sight.
    sf::RectangleShape getLoS() {return lineOfSight;}
};

#endif // ENEMY_H
