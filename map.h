#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

class Map : public sf::Drawable, public sf::Transformable
{
public:
    // load map texture and form level based on configs
    bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> &tiles,
              unsigned int width, unsigned int height);

private:
    // draw map
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    // storing texture and quads
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

#endif // MAP_H
