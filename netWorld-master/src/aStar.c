#include "includes/aStar.h"
#include "includes/utils.h"
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>

/**
 * Compare two starNode given as void * based on their cost and heuristic
 * @param dataA The first starNode as a pointer
 * @param dataB The second starNode as a pointer
 * @return -1 If the first starNode got a cost + heuristic inferior than the
 * second starNode cost + heuristic, 0 if the 2 sum are equals, 1 otherwise
 */
static int compareStarNodes(void * dataA, void * dataB)
{
  starNode * nodeA = (starNode *) dataA;
  starNode * nodeB = (starNode *) dataB;
  if(nodeA->heuristic + nodeA->cost < nodeB->heuristic + nodeB->cost)
  {
    return -1;
  } else if (nodeA->heuristic + nodeA->cost > nodeB->heuristic + nodeB->cost) {
    return 1;
  } else {
    return 0;
  }
}

/**
 * Check if a starNode need to be added in the open queue
 * A starNode doesn't has to be added only if a starNode in the open or closed queue
 * has the same position with a cost + heuristic sum lower than the concerned starNode
 * @param closedQueue A pointer to a queue containing the closed starNodes
 * @param openQueue A pointer to a queue containing the opened starNode
 * @param starNodeNeighbordhood A pointer to the starNode to check
 * @return 1 if it need to be added, 0 otherwise
 */
static int needToBeAddedToOpenQueue(queue * closedQueue, queue * openQueue,
                                    starNode * starNodeNeighbordhood)
{
  double f = starNodeNeighbordhood->cost + starNodeNeighbordhood->heuristic;
  int i = 0;
  starNode * queueNode = (starNode *) openQueue->array[i];
  while(i < openQueue->numberOfElements
        &&
        !(queueNode->node == starNodeNeighbordhood->node
          && queueNode->cost + queueNode->heuristic < f))
  {
    i += 1;
    if(i < openQueue->numberOfElements)
      queueNode = (starNode *) openQueue->array[i];
  }
  if(i == openQueue->numberOfElements)
  {
    i = 0;
    queueNode = (starNode *) closedQueue->array[i];
    while(i < closedQueue->numberOfElements
          &&
          !(queueNode->node == starNodeNeighbordhood->node
            && queueNode->cost + queueNode->heuristic < f))
    {
      i += 1;
      if(i < closedQueue->numberOfElements)
        queueNode = (starNode *) closedQueue->array[i];
    }
    if(i == closedQueue->numberOfElements)
    {
      return 1;
    }
  }
  return 0;
}

/**
 * Return the estimated (not perfect) quickiest path between two nodes based on A*
 * and manhattan heuristic distance
 * @param netWorld A pointer to the netWorld containing the nodes
 * @param start A pointer to the starting node
 * @param finish A pointer to the finishing node
 * @return A array of pointer INVERTED describing the path between start and finish
 *         NULL if a path between these two nodes doesn't exist
 */
static node ** getEstimatedShortestPathInverted(netWorld * netWorld, node * start, node * finish)
{
  // BASED ON http://coecsl.ece.illinois.edu/ge423/lecturenotes/AstarHandOut.pdf
  // AND https://www.geeksforgeeks.org/a-search-algorithm/
  // INITIALISATION
  queue * closedQueue = queueCreate(NULL);
  queue * openQueue = queueCreate(&compareStarNodes);
  starNode * starNodeStart = malloc(sizeof(starNode));
  starNodeStart->node = start;
  starNodeStart->cost = 0;
  starNodeStart->heuristic = nodeGetManhattanDistance(start, finish);
  node ** predecessors = calloc(netWorld->nodeSize, sizeof(node *));
  node ** res = NULL;
  
  queueAdd(openQueue, starNodeStart);
  while(res == NULL
        && openQueue->numberOfElements > 0)
  {
    starNode * checkedStarNode = (starNode *) queueRemoveLast(openQueue);
    node ** neighbordhood = netWorldGetAllLinked(netWorld, checkedStarNode->node);
    node ** oldNeighbordHood = neighbordhood;
    while(*neighbordhood != NULL)
    {
      if(*neighbordhood == finish)
      {
        int nodeIndex = getIndex(netWorld->nodes, *neighbordhood);
        predecessors[nodeIndex] = checkedStarNode->node;
        res = reconstructPath(netWorld->nodes, start, finish, predecessors);
        break;
        // STOP THE SEARCH
      } else {
        starNode * starNodeNeighbordhood = malloc(sizeof(starNode));
        starNodeNeighbordhood->node = *neighbordhood;
        edge * edgeConcerned = netWorldGetEdgeOfNodes(netWorld,
                                                      checkedStarNode->node,
                                                      *neighbordhood);
        starNodeNeighbordhood->cost = checkedStarNode->cost + edgeConcerned->weight;
        starNodeNeighbordhood->heuristic = nodeGetManhattanDistance(*neighbordhood, finish);
        if(needToBeAddedToOpenQueue(closedQueue, openQueue,
                                    starNodeNeighbordhood))
        {
          queueAdd(openQueue, starNodeNeighbordhood);
          int nodeIndex = getIndex(netWorld->nodes, *neighbordhood);
          predecessors[nodeIndex] = checkedStarNode->node;
        } else {
          free(starNodeNeighbordhood);
        }
      }
      neighbordhood += 1;
    }
    netWorldFreeAllLinked(oldNeighbordHood);
    queueAdd(closedQueue, checkedStarNode);
  }

  for(int i = 0; i < openQueue->numberOfElements; i += 1)
    free(openQueue->array[i]);
  for(int i = 0; i < closedQueue->numberOfElements; i += 1)
    free(closedQueue->array[i]);

  free(predecessors);
  queueDestroy(openQueue);
  queueDestroy(closedQueue);
  return res;
}

node ** getEstimatedShortestPath(netWorld * netWorld, node * start, node * finish)
{
  node ** path = getEstimatedShortestPathInverted(netWorld, start, finish);
  reverseArrayOfPointer(path, start);
  return path;
}
