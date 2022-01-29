/**
 * @file entity.h
 *
 * @brief Header file of the entity module
 *
 * An entity is anything that belong in the networld. It could be an player, an object, anything.
 *
 * This header can be used by any NetWorld game
 */


#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>
#include "networld.h"
#include "raylib.h"

/**
 * Enum describing all the type of entity that could be encountered
 */
typedef enum {
  PLAYER, /**< The player */
  NPC, /**< Non Playable Character */
  WORLD_ITEM /**< A world item */
} ENTITY_TYPE;

/**
 * Structure containing variables mainly for the player
 */
typedef struct {
  double health; /**< The player health */
  double movementSpeed; /**< The player speed? */
} entityPlayer;

/**
 * Structure containing values for world items
 */
typedef struct
{
  int isCrossable; /**< a door can be cross for example, a wall can not: 1: yes; 0: no */
  int state; /**< a door can be open or close: 1: has been used; */
} worldItem;

typedef struct
{
  /* JSP QUOI METTRE*/
} npc;

/**
 * Union containing all the type of entity someone can be
 */
typedef union 
{
  entityPlayer player; /**< A player */
  npc NPC; /**< An Non Playable Character */
  worldItem world; /**< An world item */
} entityProperty;

/**
 * Structure describing an entity
 */
typedef struct
{
  // LOGICAL PART
  ENTITY_TYPE type; /**< The type of the entity */
  char * name; /**< The name of the entity */
  entityProperty property; /**< The property  */
  unsigned short fixed; /**< can move alone: 1 = fixed; 0 = can move */
  node * position; /**< The entity position */

  // GRAPHICAL PART
  Texture2D * spriteTexture; /**< The sprite texture */
  int numberOfFrame; /**< The number of frame in the spriteTexture */
  int currentFrame; /**< The current frame */
  Rectangle frameRec; /**< The frame rectangle */
} entity;

/**
 * Structure containing an array of entity
 */
typedef struct
{
  entity * arrayWorldItem; /**< Array of entity */
  int sizeWorldItem; /**< The size of the array */
} itemsMap;

/**
 * Return a int showing if the entity is crossable and open
 * @param entity The enity to test
 * @return A confirmation status (1 if it's OK, 0 if can't be crossed).
 */
int isCrossableAndOpen(entity * entity);

/**
 * Create a new item map
 * @param size The number of items of the map
 * @return A pointer to the itemsMap
 */
itemsMap * itemsMapsNew(int size);

/**
 * Delete a itemMap
 * @param itemsMap A pointer to the itemsMap
 */
void itemsMapsDelete(itemsMap * itemsMap);

/**
 * Move the entity from the current node to an another node.
 * @param entityPlayer The destination to move
 * @param toNode The destination node
 * @param netWorld the netWorld where are all entity 
 * @param arrayBlock the list of items inside the game
 * @return A confirmation status (1 if it's OK, 0 if there is an error).
 */
int moveEntityTo(entity * entityPlayer, node * toNode, netWorld * netWorld, itemsMap * arrayBlock);

/**
 * Init the graphical part of an entity
 * @param entity A pointer to the entity
 * @param texture A pointer to the texture
 * @param numberOfFrame The number of frame in the texture
 */
void entityInitGraphics(entity * entity, Texture2D * texture, int numberOfFrame);

/**
 * Draw an entity in a rectangle
 * @param entity A pointer to the entity
 * @param rectangle The rectangle where to draw the entity
 * @param changeFrameBefore Do the frame need to be updated before drawing
 */
void entityDrawInRec(entity * entity, Rectangle rectangle,
                     int changeFrameBefore);

#endif
