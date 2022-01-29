#include "includes/networld.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "includes/utils.h"

netWorld * netWorldNew(int nodeSize, int edgeSize)
{
  netWorld * p = malloc( sizeof(netWorld) );
  p->nodeSize = nodeSize;
  p->nodes = calloc(p->nodeSize, sizeof(node *));
  p->edgeSize = edgeSize;
  p->edges = calloc(p->edgeSize, sizeof(edge *)); 
  return p;
}


void netWorldDelete(netWorld * self)
{
  for(int i = 0; i < self->nodeSize; i += 1) {
    free(self->nodes[i]);
  }
  free(self->nodes);
  for(int i = 0; i < self->edgeSize; i += 1) {
    free(self->edges[i]);
  }
  free(self->edges);
  free(self);
}

// Node initialization
void netWorldInitNodePosition(netWorld * self,
                              double x, double y)
{
  createNodeAt(self, x, y);
}

// Edge initialization
void netWorldInitEdge(netWorld * self, int iEdge,
                      node * nodeA, node * nodeB)
{
  netWorldInitEdgeComplete(self, iEdge,
                           nodeA, nodeB,
                           sqrt(pow(nodeA->x - nodeB->x, 2)
                                +
                                pow(nodeA->y - nodeB->y, 2)),
                           0);
}

void netWorldInitEdgeComplete(netWorld * self, int iEdge,
                              node * nodeA, node * nodeB,
                              double weight, char direction)
{
  if(self->edges[iEdge] == NULL) {
    self->edges[iEdge] = malloc(sizeof(edge));
  }
  self->edges[iEdge]->nodeA = nodeA;
  self->edges[iEdge]->nodeB = nodeB;
  self->edges[iEdge]->weight = weight;
  self->edges[iEdge]->direction = direction;
}

// To String of a Node
static void netWorldPrintNode(node node)
{
  printf("[%lf, %lf]\n", node.x, node.y);
}

// To String
void netWorldPrint(netWorld * self)
{
  puts("List of nodes\n");
  for(int i = 0 ; i < self->nodeSize ; i++ )
    netWorldPrintNode(*(self->nodes[i]));

  puts("List of edges\n");
  for(int i = 0 ; i < self->edgeSize ; i++){
    printf("Edge N°%i\n", i);
    netWorldPrintNode(*(self->edges[i]->nodeA));
    netWorldPrintNode(*(self->edges[i]->nodeB));
  }
}

node ** netWorldGetAllLinked(netWorld * self, node * node)
{
  return edgeGetAllLinked(node, self->edges, self->edgeSize);
}

netWorld * generateRectangularNetWorld(int nbNodeH, int nbNodeV, double spaceBetween)
{
  int horizontalEdgeNumber = (nbNodeH - 1) * nbNodeV;
  int verticalEdgeNumber = (nbNodeV - 1) * nbNodeH;
  netWorld * res = netWorldNew(nbNodeH * nbNodeV, horizontalEdgeNumber + verticalEdgeNumber);

  // Create all points
  for(int i = 0; i < nbNodeH; i += 1)
  {
    for(int j = 0; j < nbNodeV; j += 1)
    {
      netWorldInitNodePosition(res, spaceBetween * i, spaceBetween * j);
    }
  }

  // Create all vertical edges
  for(int x = 0; x < nbNodeH; x += 1)
  {
    for(int y = 0; y < nbNodeV - 1; y += 1)
    {
      netWorldInitEdgeComplete(res, x * (nbNodeV - 1) + y,
                               res->nodes[(nbNodeV * x) + y],
                               res->nodes[(nbNodeV * x) + y + 1],
                               spaceBetween, 0);
    }
  }

  // Create all horizontal edges
  for(int y = 0; y < nbNodeV; y += 1)
  {
    for(int x = 0; x < nbNodeH - 1; x += 1)
    {
      netWorldInitEdgeComplete(res, verticalEdgeNumber + y * (nbNodeH - 1) + x,
                               res->nodes[(nbNodeV * x) + y],
                               res->nodes[(nbNodeV * (x + 1)) + y],
                               spaceBetween, 0);
    }
  }

  return res;
}

edge * netWorldGetEdgeOfNodes(netWorld * self,
                              node * nodeA, node * nodeB) {
  return getEdgeOfNodes(self->edges, self->edgeSize,
                        nodeA, nodeB);
}

/**
 * Search for the QUICKIEST path between two nodes
 * The path is inverted : The finish will be at the begining of the array, the start at the end
 * @param self The NetWorld where are the nodes start and finish
 * @param start The sarting node of the path
 * @param finish The finishing node of the path
 * @return The quickiest path between the 2 nodes, but inverted
 */
static node ** getShortestPathInverted(netWorld * self, node * start, node * finish)
{
  // Application de l'algorithme de dijkstra

  // First step : variable initialization
  node * nodesCheck[self->nodeSize];
  for(int i = 0; i < self->nodeSize; i += 1)
  {
    nodesCheck[i] = self->nodes[i];
  }

  double distances[self->nodeSize];
  for(int i = 0; i < self->nodeSize; i += 1)
  {
    if(nodesCheck[i] != start) {
      distances[i] = FLT_MAX;
    } else {
      distances[i] = 0;
    }
  }

  node * predecessors[self->nodeSize];
  for(int i = 0; i < self->nodeSize; i += 1)
  {
    predecessors[i] = NULL;
  }
  int nbChecked = 0;

  // Main loop : As long as the list is not empty, aka while we haven't check everything
  while(nbChecked < self->nodeSize) {
    // Get the index of the node in nodeToCheck with distance[] being the minimal
    int indexOfChecked = getIndexOfMinimal(distances, nodesCheck, self->nodeSize);
    node * checkedNode = nodesCheck[indexOfChecked];

    // Get all surronding of this node
    node ** surronding = netWorldGetAllLinked(self, checkedNode);
    node ** surrondingCopy = surronding;

    // For each of his surronding
    while(*surronding != NULL) {
          
      // If he's in nodeCopy and distance is shortest, add it
      int indexOfSurronding = getIndex(self->nodes, *surronding);
      edge * edgeChecked = netWorldGetEdgeOfNodes(self, *surronding, checkedNode);
      if(nodesCheck[indexOfSurronding] != NULL
         && distances[indexOfSurronding] > (distances[indexOfChecked] + edgeChecked->weight)) {
         distances[indexOfSurronding] = distances[indexOfChecked] + edgeChecked->weight;
          predecessors[indexOfSurronding] = checkedNode;
      }
      surronding += 1;
    }
    // Clear everything and remove checked
    netWorldFreeAllLinked(surrondingCopy);
    nodesCheck[indexOfChecked] = NULL;
    nbChecked += 1;
  }
  
  node ** res = reconstructPath(self->nodes, start, finish, predecessors);
  return res;
}

node ** getShortestPath(netWorld * self, node * start, node * finish) {
  node ** path = getShortestPathInverted(self, start, finish);
  reverseArrayOfPointer(path, start);
  return path;
}

node * getNodeAt(netWorld * netWorld, double x, double y)
{
  int i;
  node toCheck = {x, y, 0};
  
  for (i = 0; i < netWorld->nodeSize && netWorld->nodes[i] != NULL; ++i)
  {
    if(nodeAreEquals(netWorld->nodes[i], &toCheck))
      return netWorld->nodes[i];
  }
  return NULL;
}

node * createNodeAt(netWorld * netWorld, double x, double y)
{
    int i, found;
    node * newNode = NULL;
    node toCheck = {x, y, 0};

    found = 0;
    for (i = 0; i < netWorld->nodeSize && found == 0 && netWorld->nodes[i] != NULL; ++i)
    {
        if(nodeAreEquals(netWorld->nodes[i], &toCheck))
            found = 1;
    }
    
    // si on l'a trouvé
    if(!found) {
      if(netWorld->nodes[i] == NULL) {
        netWorld->nodes[i] = malloc(sizeof(node));
      }
      *(netWorld->nodes[i]) = toCheck;
      newNode = netWorld->nodes[i];
    }

    return newNode;
}

node * netWorldGetRandomNode(netWorld * netWorld) {
  return netWorld->nodes[rand() % netWorld->nodeSize];
}

void fillWithRandomNode(netWorld * netWorld, node ** nodeArray,
                        int arraySize)
{
  for(int i = 0; i < arraySize; i += 1)
  {
    int j;
    do {
      j = 0;
      nodeArray[i] = netWorldGetRandomNode(netWorld);
      while(j < i
            && nodeArray[i] != nodeArray[j])
      {
        j += 1;
      }
    } while(j != i);
  }
}

netWorld netWorldDuplicate(netWorld * networld)
{
  netWorld res;
  res.nodeSize = networld->nodeSize;
  res.nodes = malloc(res.nodeSize * sizeof(node *));
  memcpy(res.nodes, networld->nodes, res.nodeSize * sizeof(node *));
  res.edgeSize = networld->edgeSize;
  res.edges = malloc(res.edgeSize * sizeof(node *));
  memcpy(res.edges, networld->edges, res.edgeSize * sizeof(node *));

  return res;
}

void netWorldFreeDuplicated(netWorld duplicatedNetWorld)
{
  free(duplicatedNetWorld.nodes);
  free(duplicatedNetWorld.edges);
}
