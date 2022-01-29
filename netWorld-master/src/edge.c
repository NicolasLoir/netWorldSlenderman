#include "includes/edge.h"
#include "includes/utils.h"
#include <stdlib.h>
#include <stddef.h>

#define __DEFAULT_SIZE__ 2
node ** edgeGetAllLinked(node * observedNode, edge ** edges,
                         int edgeSize)
{
  queue * nodeQueue = queueCreate(NULL);
  for(int i = 0; i < edgeSize; i ++) {
    node * toAdd;
    // Search the linked node
    if(edges[i]->nodeA == observedNode
       && edges[i]->direction >= 0) {
      toAdd = edges[i]->nodeB;
    } else if(edges[i]->nodeB == observedNode
              && edges[i]->direction <= 0) {
      toAdd = edges[i]->nodeA;
    } else {
      toAdd = NULL;
    }

    if(toAdd != NULL) {
      queueAdd(nodeQueue, toAdd);
    }
  }
  
  queueAdd(nodeQueue, NULL);

  node ** res = (node **) queueConvertToArray(nodeQueue);
  return res;

  /*
  // Result array initialization
  node ** res = malloc(__DEFAULT_SIZE__ * sizeof(node *));

  // Counters
  int resMaxSize = __DEFAULT_SIZE__ - 1;
  res[resMaxSize] = NULL;
  int resSize = 0;

  for(int i = 0; i < edgeSize; i ++) {
    node * toAdd;
    // Search the linked node
    if(edges[i]->nodeA == observedNode
       && edges[i]->direction >= 0) {
      toAdd = edges[i]->nodeB;
    } else if(edges[i]->nodeB == observedNode
              && edges[i]->direction <= 0) {
      toAdd = edges[i]->nodeA;
    } else {
      toAdd = NULL;
    }

    if(toAdd != NULL) {
      // Reallocation of the array if needed
      if(resSize == resMaxSize) {
        res = realloc(res, sizeof(node *) * (resMaxSize + 1) * 2);
        resMaxSize = resMaxSize * 2 + 1;
        res[resMaxSize] = NULL;
      }

      res[resSize] = toAdd;
      resSize += 1;
    }
  }

  res[resSize] = NULL;
  return res;
  */
}

edge * getEdgeOfNodes(edge ** edges, int edgeSize,
                      node * nodeA, node * nodeB)
{
  for(int i = 0; i < edgeSize; i += 1){
    if((nodeA == edges[i]->nodeA || nodeA == edges[i]->nodeB)
       &&
       (nodeB == edges[i]->nodeA || nodeB == edges[i]->nodeB)) {
      return edges[i];
    }
  }
  return NULL;
}
