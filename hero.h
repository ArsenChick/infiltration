#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "defines.h"

/*!
 * \ingroup GameChars
 * \brief A class for %Hero entity.
 */

class Hero
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

    //! Used for detecting collisions with Enemies.
    sf::FloatRect dmg_area;
    //! %Hero's field of view
    /*! Contains the part of the Map the player sees */
    sf::View view;

    //! X coordinate on the map.
    float x;
    //! Y coordinate on the map.
    float y;

    //! Current frame used for animation.
    float CurrentFrame = 0;

    //! Hero's speed.
    float speed = DEFAULTSPEED;

    ///@{
    /*!
     * \brief Directions that are available for moving into.
     */
    bool up = true;
    bool down = true;
    bool right = true;
    bool left = true;
    ///@}

    //! Position in the tiles.
    unsigned int pos = 0;

    //! Direction of the Hero's look.
    /*! Used for adjusting the line of sight. */
    unsigned int look = UP;

    //! Performs default moving animation.
    /*! Function used primarily within move function.
     * \param time represents the game state in terms of animation.
     */
    void animate(float time);
    //! Updates the rectangle of the line of sight.
    void adjustLoS();

public:
    //! Constructor.
    Hero();

    //! Loads a texture.
    /*! \param hero_texture texture to load.
     */
    void load(sf::Texture* hero_texture);
    //! Spawns the %Hero in a tile.
    /*! \param tileno position to spawn the %Hero in.
     */
    void setStartPosition(unsigned int tileno);

    //! Checks the intersection between the %Hero and Enemy hitboxes.
    /*!
     * \param soldier a specific Enemy's hitbox.
     * \param time represents the game time state.
     */
    void checkForEnemies(std::vector<sf::FloatRect> &soldier, float time);
    //! Performs a movement action.
    /*!
     * \param level represents the model for the current level.
     * \param time represents the game state in terms of animation.
     */
    void move(std::vector<int>& level, float time);
    //! Changes the speed between crouch mode and default.
    void changeSpeed();

    //! Performs an elimination on the specific Enemy.
    /*!
     * \param enemyHitbox rectangle representing %Enemy's hitbox.
     * \return The success status.
     * 1 if there's a elimination,
     * 0 if there's no elimination.
     */
    int kill(sf::FloatRect enemyHitbox);

    //! Getter for %Hero's sprite.
    sf::Sprite& getSprite() {return sprite;}
    //! Getter for %Hero's line of sight.
    sf::View& getView() {return view;}

};

#endif // HERO_H
