/**
 * @file edge.h
 *
 * @brief Header file of the edge structure
 *
 * This structure is used to decalre structures and function relative to a edge
 * A edge links two nodes.
 * A edge can have a weight (A cost of travel). By default, it will be the distance between the 2 points, but it can be changed.
 * A edge can be biderctional, or not.
 *
 * This header file can be used by any NetWorld game
 *
 */

#ifndef EDGE_H
#define EDGE_H

#include "node.h"

/**
 * The structure used to describe a edge
 */
typedef struct {
  node * nodeA; /**< A pointer to the first node */
  node * nodeB; /**< A pointer to the second node */
  double weight; /**< The weight of this edge */
  char direction; /**< A positive number if you can go only from A to B, a negative number if you can go only from B to A, 0 if you can do both */
} edge;

/**
 * Give all nodes linked to another node in a edgeList
 * @param observedNode The node observed
 * @param edges The edges array
 * @param edgeSize The side of edges array
 * @return An array of pointer to all edges linked. YOU HAVE TO FREE THIS AFTER USE
 */
node ** edgeGetAllLinked(node * observedNode, edge ** edges,int edgeSize);

/**
 * Return the edge that linkds two nodes
 * @param edges An array of edge
 * @param edgeSize The size of edges
 * @param nodeA A pointer to first node
 * @param nodeB A pointer to second node
 * @return The pointer of the edge that links these two nodes if it exists, NULL otherwise
 */
edge * getEdgeOfNodes(edge ** edges, int edgeSize,
                      node * nodeA, node * nodeB);

#endif
