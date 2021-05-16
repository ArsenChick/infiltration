#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

//! A class for %Map entity.
class Map : public sf::Drawable, public sf::Transformable
{
public:
    //! Loads map texture and forms level based on configs.
    /*!
     * \param tileset a location of the file with tile textures.
     * \param tileSize represents in-game tile size.
     * \param tiles represents the model for the current level.
     * \param width witdh of a tile in the image texture.
     * \param height height of a tile in the image texture.
     * \return The status of an operation.
     * true if successfully loaded, false otherwise.
     */
    bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> &tiles,
              unsigned int width, unsigned int height);

private:
    //! Draws map
    /*! Function that needed to be added for SFML compability.
     * \param target parameters for SFML compability.
     * \param states parameters for SFML compability.
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    ///@{
    /*!
     * \brief Variables to store graphical resources.
     */
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    ///@}
};

#endif // MAP_H
