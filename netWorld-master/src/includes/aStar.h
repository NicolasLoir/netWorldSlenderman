/**
 * @file aStar.h
 *
 * @brief Header file of the A Star module
 * 
 * This file contains declarations for the A Star implementation in the NetWorld
 * A Star is an angorith that estimate the shortest path between 2 nodes.
 * It is way quickier that some others path finding algorith, but the result given won't be always THE best option
 *
 * This header can be used for any Networld Game
 */

#ifndef ASTAR_H
#define ASTAR_H

#include "networld.h"

/**
 * Structure used by the A Star algorithm, but hidden for the user
 */
typedef struct {
  node * node; /**< A pointer to a node */
  double cost; /**< The cost (real distance) to get to that point */
  double heuristic; /**< The estimated cost to go from that point to the end */
} starNode;

/**
 * This function estimate the shortest path between two points with A*
 * It is quicker than getting THE shortest path,
 * But the result given won't be always the quickiest path
 * YOU HAVE TO FREE THE RES
 * @param self A pointer to the netWorld
 * @param start The starting node
 * @param finish The goal
 * @return A array of node pointer, with start at the begining
 * and finish at the end. Return NULL if there isn't a path between two points
 */
node ** getEstimatedShortestPath(netWorld * self, node * start, node * finish);

#endif
