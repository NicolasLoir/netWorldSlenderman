/**
 * @file networld.h
 *
 * @brief Header file of the NetWorld component
 *
 * A Networld is a graph representation of a world, make of nodes and edges.
 * It can be used for a lot of thing
 *
 * This compononent an be used for ANY NetWorld game
 */

#ifndef NETWORLD_H
#define NETWORLD_H

#include "node.h"
#include "edge.h"

/**
 * Structure representing the netWorld
 */
typedef struct {
  int nodeSize; /**< Number of nodes in the NetWorld */
  node ** nodes; /**< Array of pointers to the nodes of the NetWorld */
  int edgeSize; /**< Number of edges in the NetWorld */
  edge ** edges; /**< Array of pointers to the edges of the NetWorld */
} netWorld;

/**
 * Create a new netWorld
 * @param nodeSize The number of node that will be preallocated
 * @param edgeSize The number of edge that will be preallocated
 */
netWorld * netWorldNew(int nodeSize, int edgeSize);

/**
 * Delete a netWorld
 * @param self A pointer to the netWorld
 */
void netWorldDelete(netWorld * self);

/**
 * Initialize a netWorld node at specific position
 * @param self A pointer to the netWorld
 * @param x The position of the node in the x axis
 * @param y The position of the node in the y axis
 */
void netWorldInitNodePosition(netWorld * self, double x, double y);

/**
 * Initialize a netWorld edge with specified nodes
 * @param self A pointer to the netWorld
 * @param iEdge The number of the edge
 * @param nodeA The first node
 * @param nodeB The second node
 */
void netWorldInitEdge(netWorld * self, int iEdge, node * nodeA, node * nodeB);

/**
 * Initialize a netWorld edge with specified nodes
 * @param self A pointer to the netWorld
 * @param iEdge The number of the edge
 * @param nodeA The first node
 * @param nodeB The second node
 * @param weight The weight of the edge
 * @param direction A positive number if you can go only from A to B, a negative number if you can go only from B to A, 0 otherwise
 */
void netWorldInitEdgeComplete(netWorld * self, int iEdge, node * nodeA, node * nodeB, double weight, char direction);

/**
 * Print data about the netWorld
 * @param self A pointer to the netWorld
 */
void netWorldPrint(netWorld * self);

/**
 * Give all node linked to another node in a netWorld
 * The returned value shall be freed later with, for example, netWorldFreeAllLinked
 * @param self A pointer to the netWorld
 * @param node The node observed
 * @return An array of pointer of netWorld that ends with the value NULL
 */
node ** netWorldGetAllLinked(netWorld * self, node * node);

/**
 * Free the result given by netWorldGetAllLinked
 * @param linked The result of netWorldGetAllLinked
 */
#define netWorldFreeAllLinked(linked) free(linked);

/**
 * Generate a rectangular netWorld with a specific number of node horonzontally and vertically
 * @param nbNodeX The number of node horizontally (>=0)
 * @param nbNodeY The number of node vertically (>=0)
 * @param spaceBetween The space between each node
 * @return A pointer to the generated netWorld
 */
netWorld * generateRectangularNetWorld(int nbNodeX, int nbNodeY, double spaceBetween);

/**
 * Return the shortest path between two nodes
 * @param self A pointer to the netWorld
 * @param start A pointer to the start of the node
 * @param finish A pointer to the end of the node
 * @return A array of node pointer, with start at the begining
 * and finish at the end. Return NULL if there isn't a path between two points 
 */
node ** getShortestPath(netWorld * self, node * start, node * finish);

/**
 * Return the edge that linkds two nodes
 * @param self The networld
 * @param nodeA A pointer to first node
 * @param nodeB A pointer to second node
 * @return The pointer of the edge that links these two nodes if it exists, NULL otherwise
 */
edge * netWorldGetEdgeOfNodes(netWorld * self,
                              node * nodeA, node * nodeB);

/**
 * Create a node in a netWorld while checking if the node already exist.
 * @param netWorld The networld with nodes and edges.
 * @param x The x coordinate of the new node.
 * @param y The y coordinate of the new node.
 * @return NULL if a node already exist at this position or a node's pointer with the new created node.
 */
node * createNodeAt(netWorld * netWorld, double x, double y);


node * getNodeAt(netWorld * netWorld, double x, double y);

/**
 * Return a random node of a netWorld
 * @param netWorld A pointer to the netWorld
 * @return A pointer to a random node of the netWorld
 */
node * netWorldGetRandomNode(netWorld * netWorld);

/**
 * Fill an array with random position in the netWorld
 * There won't be 2 identical position in this array
 * @param netWorld A pointer to the netWorld
 * @param nodeArray An array of node pointer
 * @param arraySize The size of the array
 */
void fillWithRandomNode(netWorld * netWorld, node ** nodeArray,
                        int arraySize);

/**
 * Duplicate a NetWorld
 * A DUPLICATED NETWORLD HAS TO BE DELETED WITH netWorldFreeDuplicate
 * @param netWorld A pointer to the netWorld
 * @return The duplicatedNetWorld
 */
netWorld netWorldDuplicate(netWorld * netWorld);

/**
 * Free a duplicated NetWorld from the memory
 * @param duplicatedNetworld The duplicated netWorld
 */
void netWorldFreeDuplicated(netWorld duplicatedNetworld);

#endif //NETWORLD_H
