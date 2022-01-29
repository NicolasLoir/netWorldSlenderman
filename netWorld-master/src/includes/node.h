/**
 * @file node.h
 *
 * @brief Header file of the node module
 *
 * A node is a point in a 2 dimension array.
 * It can have a size, a weight if needed
 *
 * This module can be used for ANY NetWorld game
 */

#ifndef NODE_H
#define NODE_H

/**
 * Structure representing a node
 */
typedef struct {
  double x; /**< X position */
  double y; /**< Y position */
  double size; /**< Size/Weight of the node */
} node;

/**
 * Compare if the node's position are equals.
 * @param a The first node
 * @param b The node to compare.
 * @return 1 if node are equals, 0 if nodes are different.
 */
int nodeAreEquals(node * a, node * b);

/**
 * Return the distance between two nodes
 * @param a The first node
 * @param b The second node
 * @return The distance between these two nodes
 */
double nodeGetDistance(node * a, node * b);

/**
 * Return the manhattan distance between two nodes
 * @param a The first node
 * @param b The second node
 * @return The distance between these two nodes
 */
double nodeGetManhattanDistance(node * a, node * b);

/**
 * Reconstruct the path between two nodes based on an array of node, an array
 * describing the predecessor of each node
 * @param nodes An array containg the pointers to all nodes concerned here
 * @param start A pointer to the starting node
 * @param finish A pointer to the finishing node
 * @param predecessors An array containing the predecessor of each node
 * predessors[i] correspond to the predecessor of nodes[i]
 * @return The path starting from start to finish in the reverse order!
 *         NULL if there isn't a path between start and finish
 */
node ** reconstructPath(node ** nodes, node * start, node * finish, node ** predecessors);

#endif
