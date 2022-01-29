/**
 * @file ia.h
 *
 * @brief Header file of the IA module
 *
 * The IA module consist of one IA : The following IA
 * The following IA caculate constantly the path between himself and
 * an entity.
 *
 * Important things about the followingIA :
 *
 * To ensure that a followingIA forks correctly,
 * You have to follow some rules to read the path var
 *
 * 1) Import <pthread.h>
 *
 * 2) Lock the path var (pthread_mutex_lock(&(ia->pathLocked))
 *
 * 3) Read the path as you want. As long as the var is locked, it won't be
 *    updated by the IA
 *
 * 4) Unlock it (pthread_mutex_unlock(&(ia->pathLocked))) to ensure that
 *    the IA can update it with the newest path
 * 
 * Indeed, an IA equals to a thread running next to the main thread
 * As long as you lock his path, he won't be updated
 * As long as you let it live, it may be calculating new path
 *
 * This module can be used for ANY NetWorld game
 */

#ifndef IA_H
#define IA_H

#include "entity.h"
#include "networld.h"
#include <pthread.h>

/**
 * The structure of an following IA
 */
typedef struct
{
  entity * entity; /**< A pointer to the entity that the IA plays with */
  netWorld * world; /**< A pointer to the netWorld */
  itemsMap * worldItems; /**< A pointer to the netWorld Items */
  entity * goal; /**< A pointer to the entity the IA has to follow */
  node ** path; /**< The latest path calculated */
  node * latestGoal; /**< The goal of the latest path calculated */
  pthread_mutex_t pathLocked; /**< A pthread mutex */
  pthread_t thread; /**< The pthread */
} followingIA;

/**
 * Create a following IA
 * This structure got an array of nodes that represents the path that the IA
 * has to follow to go between his position and the goal. His content will be
 * updated on a regular basis
 * @param iaEntity A pointer to the entity that will be controlled by the IA
 * @param world A pointer to the netWorld where our entites lives
 * @param goal A pointer to the entity that our IA will follow
 * @param items A pointer to the itemsMap
 * @return A pointer to the following IA
 */
followingIA * startFollowingIA(entity * iaEntity, netWorld * world, entity * goal, itemsMap * items);

/**
 * Stop the following IA and free its memory
 * @param followingIA A pointer to the following IA
 */
void freeAndStopFollowingIA(followingIA * followingIA);

/**
 * Generate a netWorld adapted for the IA
 * @param networld The original netWorld
 * @param items An array of item
 * @return An networld adapted for the IA
 */
netWorld duplicateNetWorldForIA(netWorld * networld, itemsMap * items);

#endif
