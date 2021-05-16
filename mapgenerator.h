#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <vector>
#include <chrono>
#include <random>
#include "defines.h"

//! A class for level generator.
/*! Generates the main level of the game.
 * Each level is randomly generated.
 */
class MapGenerator
{
public:
    //! Default constructor.
    explicit MapGenerator();
    //! Generates the level.
    /*! \param level represents the model of a level.
     * Initially empty, it is populated with landscape
     * as a result of this function.
     */
    void levelGenerate(std::vector<int> &level);

private:
    //! Constructs a tree-like structured maze.
    /*!
    * \param tiles represents the model of a level.
    * \param paths represents the paths available on each tile.
    * \param pos current position of a builder.
    */
    void constructTree(std::vector<int> &tiles, std::vector<bool> &paths, int pos);

    ///@{
    /*!
     * \brief Constructs a route in a specific direction.
     * \param tiles represents the model of a level.
     * \param paths represents the paths available on each tile.
     * \param pos current position of a builder.
     * \return Returns the new position of a builder
     * if the route has been constructed.
     * Otherwise returns -1.
     */
    int constructUp(std::vector<int> &tiles, std::vector<bool> &paths, int pos);
    int constructDown(std::vector<int> &tiles, std::vector<bool> &paths, int pos);
    int constructRight(std::vector<int> &tiles, std::vector<bool> &paths, int pos);
    int constructLeft(std::vector<int> &tiles, std::vector<bool> &paths, int pos);
    ///@}

    //! Adds extensive routes.
    /*!
     * \param tiles represents the model of a level.
     * \param pos current position of a builder.
     * \param direction direction to place a road to.
     */
    void addRoute(std::vector<int> &tiles, int pos, unsigned int direction);

    //! Randomizer.
    std::mt19937 gen;
};

#endif // MAPGENERATOR_H
