#ifndef MACROS_H
#define MACROS_H

/*!
 * \defgroup GameConsts Game constants
 * \brief Contsnts defined in defines.h.
 *
 * This group contains descriptions of
 * various constants in the game. Most are
 * documented so it's easy to figure out their purpose.
 */

/*! \addtogroup GameConsts
 * @{
 */

/*!
 * \name Consts for level generator.
 */
//!@{
#define ROUTEUP 8 //!< Upward direction.
#define ROUTELEFT 4 //!< Left-side direction.
#define ROUTEDOWN 2 //!< Downward direction.
#define ROUTERIGHT 1 //!< Right-side direction.

//!@}

/*!
 * \name Level metrics.
 */
//!@{
#define LHEIGHT 20 //!< Level height in tiles.
#define LWIDTH 20 //!< Level width in tiles.
#define TILESIZE 160 //!< Tile size in pixels.
#define WALLSIZE 32 //!< Wall length in pixels.

//!@}

/*!
 * \name View direction enum (sort of)
 */
//!@{
#define UP 0 //!< Upward direction.
#define RIGHT 1 //!< Right-side direction.
#define DOWN 2 //!< Downward direction.
#define LEFT 3 //!< Left-side direction.

//!@}

/*!
 * \name Characters' metrics.
 */
//!@{
#define HEROH 48 //!< Hero height in pixels.
#define HEROW 32 //!< Hero width in pixels.
#define ENEMYH 48 //!< Enemy height in pixels.
#define ENEMYW 55 //!< Enemy width in pixels.

//!@}

/*!
 * \name Speed constants.
 */
//!@{
#define CROUCHSPEED 0.25 //!< Sprint speed.
#define DEFAULTSPEED 0.18 //!< Default speed.
#define EPS 0.01 //!< Epsilon.

//!@}

//! Offset for line of sight hitboxes.
#define LOSOFFSET 5

/*!
 * \name Enemy status.
 */
//!@{
#define ALIVE 1 //!< Alive.
#define DEAD 0 //!< Dead.

//!@}

/*!
 * \name Game settings.
 */
//!@{
#define ENEMYN 25 //!< Number of enemies.
#define TIMEFORPLAY 180 //!< Time to play in seconds.
#define MAPSCALE 1 //!< Field of view scale.

//!@}

/*! @} */

#endif // MACROS_H
