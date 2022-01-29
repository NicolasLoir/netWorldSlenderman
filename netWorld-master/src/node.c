#include "includes/node.h"
#include "includes/utils.h"
#include <stdlib.h>
#include <math.h>

int nodeAreEquals(node * a, node * b)
{
    return a->x == b->x && a->y == b->y;
}

double nodeGetDistance(node * a, node * b)
{
  return sqrt(pow(a->x - b->x, 2)
              +
              pow(a->y - b->y, 2));
}

double nodeGetManhattanDistance(node * a, node * b)
{
  return fabs(a->x - b->x) + fabs(a->y - b->y);
}
node ** reconstructPath(node ** nodes, node * start, node * finish, node ** predecessors)
{
  queue * nodeQueue = queueCreate(NULL);
  queueAdd(nodeQueue, finish);
  int idx = getIndex(nodes, finish);
  while(predecessors[idx] != NULL
        && predecessors[idx] != start)
  {
    queueAdd(nodeQueue, predecessors[idx]);
    idx = getIndex(nodes, predecessors[idx]);
  }
  if(predecessors[idx] == NULL) {
    queueDestroy(nodeQueue);
    return NULL;
  } else {
    queueAdd(nodeQueue, predecessors[idx]);
    node ** res = (node **) queueConvertToArray(nodeQueue);
    return res;
  }
}
