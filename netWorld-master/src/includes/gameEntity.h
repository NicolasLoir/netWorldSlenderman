/**
 * @file gameEntity.h
 *
 * @brief Header file of the entity part of the slender game
 *
 * This header file contains declaration and fonctions to create entity made for the slender game
 *
 * This header file shall NOT BE USED for another NetWorld game
 */

#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "entity.h"
#include "node.h"

/**
 * Create a player at a node given
 * @param position The position of the future player
 * @return A pointer to the entity representing the player
 */
entity * playerCreate(node * position);

/** Free the player from the memory */
#define playerDestroy(player) (free(player))


/**
 * Create a slender at a node given
 * @param position The position of the future slender
 * @return A pointer to the entity representing the slender
 */
entity * slenderCreate(node * position);

/** Free the slender from the memory */
#define slenderDestroy(slender) (free(slender))

/**
 * Add a book in a itemsMap at a positition given
 * @param items The itemsMap
 * @param idx The idx in the array where to place the item
 * @param position A pointer to the position of the book
 * @param numero The numero of the book
 */
void bookAdd(itemsMap * items, int idx, node * position, int numero);

/**
 * Destroy a book in a itemsMap
 * @param items The itemsMap
 * @param idx The index in the array of the book
 */
void bookDestroy(itemsMap * items, int idx);

/**
 * Add a wall into a itemsMap. A wall doesn't have to be destroyed
 * @param items The itemsmap
 * @param idx The index where to put the wall
 * @param position A pointer to the position where to put the wall
 */
void wallAdd(itemsMap * items, int idx, node * position);

#endif
