#include "includes/ia.h"
#include <stdlib.h>
#include <pthread.h>
#include "includes/networld.h"
#include <unistd.h>
#include <string.h>
#include "includes/utils.h"
#include "includes/aStar.h"

static void * mainFollowingIA(void * data)
{
  /*
   * The algorith of this bot goes as following : 
   * 1) Desactivate cancelling and caculate a new path
   * 2) Lock actual path, free its memory, update the path, unlock the path
   *    and enable cancelling
   * 3) Wait 5 seconds and redo the algorithm
   */
  followingIA * ia= (followingIA *) data;
  while(1 == 1) {
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    netWorld duplicateNetWorld = duplicateNetWorldForIA(ia->world, ia->worldItems);
    node * newLatestGoal = ia->goal->position;
    node ** newPath = getEstimatedShortestPath(&duplicateNetWorld,
                                               ia->entity->position,
                                               newLatestGoal);
    netWorldFreeDuplicated(duplicateNetWorld);
    pthread_mutex_lock(&(ia->pathLocked));
    free(ia->path);
    ia->path = newPath;
    ia->latestGoal = newLatestGoal;
    pthread_mutex_unlock(&(ia->pathLocked));
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    sleep(1);
  }
  return NULL;
}

followingIA * startFollowingIA(entity * iaEntity, netWorld * world, entity * goal, itemsMap * items)
{
  // CREATION OF A FOLLOWING IA
  followingIA * ia = malloc(sizeof(followingIA));
  ia->entity = iaEntity;
  ia->world = world;
  ia->worldItems = items;
  ia->goal = goal;
  ia->path = NULL;
  pthread_mutex_t fastmutex = PTHREAD_MUTEX_INITIALIZER;
  ia->pathLocked = fastmutex;
  if(pthread_create(&(ia->thread), NULL, &mainFollowingIA, ia) != 0) {
    free(ia);
    return NULL;
  }
  return ia;
}

void freeAndStopFollowingIA(followingIA * followingIA)
{
  pthread_cancel(followingIA->thread);
  pthread_join(followingIA->thread, NULL);
  pthread_mutex_destroy(&(followingIA->pathLocked));
  free(followingIA->path);
  free(followingIA);
}

netWorld duplicateNetWorldForIA(netWorld * networld, itemsMap * items)
{
  // Create another netWorld from the based networld and copy the arrays to modify
  // them without impact on the original netWorld
  netWorld res = netWorldDuplicate(networld);
  
  // For each items
  for(int i = 0; i < items->sizeWorldItem; i += 1) {
    entity * entity = items->arrayWorldItem + i;
    // If it's not crossable
    if(entity->type == WORLD_ITEM
       && !entity->property.world.isCrossable) {
      node * nodeToRemove = entity->position;
      
      // Search all neighborhoods
      node ** allLinked = edgeGetAllLinked(nodeToRemove, res.edges, res.edgeSize);
      for(int j = 0; allLinked[j] != NULL; j += 1) {
        // Search the edge that link our node and his neighborhood,
        // Remove it and pass to the next node
        edge * edgeToRemove = getEdgeOfNodes(res.edges, res.edgeSize, nodeToRemove, allLinked[j]);
        int indexOfEdge = getIndex(res.edges, edgeToRemove);
        res.edgeSize -= 1;
        res.edges[indexOfEdge] = res.edges[res.edgeSize];
      }
      netWorldFreeAllLinked(allLinked);

      // Remove our node from the duplicate networld table
      int indexOfNode = getIndex(res.nodes, nodeToRemove);
      res.nodeSize -= 1;
      res.nodes[indexOfNode] = res.nodes[res.nodeSize];
    }
  }

  return res;
}
