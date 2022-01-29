/**
 * @file game.h
 *
 * @brief Header file of a slenderman game
 *
 * This header file contains all data necessary for a Slenderman game
 *
 * This file is UNIQUE for the demo and shall not be used for a NetWorld game
 */

#ifndef GAME_H
#define GAME_H

#include "networld.h"
#include "entity.h"
#include "ia.h"
#include "raylib.h"
#include "event.h"

int checkArg(int width, int height,
             int auraRange, int wallPeercentage);

/**
 * Structure containing the graphical data of the game
 */
typedef struct {
  Rectangle * netWorldRectangles; /**< Array of rectangles to draw */
  Rectangle borders[4]; /**< Borders of the map  */

  Texture2D playerTextures[5]; /**< Textures of the player */
  Texture2D slenderTextures[5]; /**< Textures of the slender */
  Texture2D wallTextures[7]; /**< Texture of the walls (tree and rock) */
  Texture2D pagesTextures[7]; /**< Textures of the pages */

  int frameCounter; /**< A counter for the frames */
  int frameSpeed; /**< The number of frame for which a sprite should be displayed in a animation */
  
  Camera2D camera; /**< The camera */
  Texture2D background; /**< The background */
} graphicalData;

/**
 * Structure containing all data necessary for the slenderman game
 */
typedef struct {
  netWorld * netWorld; /**< A pointer to the netWorld */
  int width; /**< The width of the netWorld */
  int height; /**< The height of the netWorld */
  entity * player; /**< A pointer to the player */
  entity * slender; /**< A pointer to the slenderman */
  itemsMap * worldEntities; /**< The array of world entities */
  followingIA * slenderIA; /**< A pointer to the slenderman IA */

  int pageWasRead[7]; /**< An array determining whose book has beek read */
  int slenderAuraRange; /**< The size of effect of the slender */
  int lightRange; /**< The range of the light */

  Rectangle playerSpriteRectangle; /**< The position where the player is currently drawed */
  Rectangle slenderSpriteRectangle; /**< The position where the slender is currently drawed */

  eventManager * everyTwoSecondEvents; /**< Event manager for each two seconds */
  eventManager * everyMoveEvents; /**< Event manager for every moves */

  graphicalData * uiData; /**< A pointer to the graphical data of the game */
} game;

/**
 * Create a game
 * For the moment, the board will be simple, without any other entity
 * than the books, the player and slenderman
 * The position of the player and the slenderman shall be randomized
 * @param xSize The size of the netWorld in the xAxis in number of case
 * @param ySize The size of the netWorld in the yAxis in number of case
 * @param screenX The size of the screen in the xAxis in pixel
 * @param screenY The size of the screen in the yAxis in pixel
 * @param slenderAura The slender's aura ray
 * @param wallPeercentage The peercentage of wall in the map
 * @return A pointer to the game created
 */
game * gameNew(int xSize, int ySize,
               int screenX, int screenY,
               int slenderAura, int wallPeercentage);

/**
 * Destroy a game
 * @param game A pointer to the game
 */
void gameDestroy(game * game);

/**
 * Reactualise and display all content of a game
 * @param game A pointer to the game
 */
void gameUpdate(game * game);

/**
 * Init graphical data of a game
 * @param game A pointer to the game
 * @param screenX The size of the screen in the X axis
 * @param screenY The size of the screen in the Y axis
 */
void initGraphicalData(game * game, int screenX, int screenY);

/**
 * Free all graphical data
 * @param game A pointer to the game
 */
void freeGraphicalData(game * game);


/**
 * Number returned by gameIsDone if the slender has won
 */
#define SLENDER_WON 1

/**
 * Number returned by gameIsDone if the player has won
 */
#define PLAYER_WON 2

/**
 * Check if a game is finished or not
 * @param gameP A pointer to the game
 * @return 0 if the game is not done, SLENDER_WON or PLAYER_WON otherwise
 */
int gameIsDone(game * gameP);

/**
 * Check if a game is viable or not
 * @param gameP A pointer to the game
 * @return 0 if the game is viable, anything else otherwise
 */
int gameIsViable(game * gameP);


/** Get the book of a number given from the game */
#define bookGetByNumber(game, number) (((game)->worldEntities->arrayWorldItem) + (number) - 1)

#endif
