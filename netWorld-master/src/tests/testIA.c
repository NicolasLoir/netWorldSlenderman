#include "../includes/ia.h"
#include <assert.h>
#include "../includes/networld.h"
#include "../includes/entity.h"
#include <pthread.h>
#include <unistd.h>

void test(void)
{
  // Initialisation of vars
  // The world is just a straight road
  netWorld * world = generateRectangularNetWorld(1, 10, 1);

  entity iaEntity;
  iaEntity.type = PLAYER;
  iaEntity.name = "Slenderman";
  iaEntity.fixed = 0;
  iaEntity.position = world->nodes[0];

  entity goal;
  goal.type = PLAYER;
  goal.name = "Stolas";
  goal.fixed = 0;
  goal.position = world->nodes[9];

  // Start the IA and wait for it to calculate a path

  entity item_entity;
  item_entity.type = WORLD_ITEM;
  item_entity.name = "Porte";
  item_entity.property.world.isCrossable = 1;
  item_entity.fixed = 1;
  item_entity.position = world->nodes[3];

  itemsMap items = {&item_entity, 1};
  
  followingIA * ia = startFollowingIA(&iaEntity, world, &goal, &items);

  sleep(4);

  pthread_mutex_lock(&(ia->pathLocked));
  assert(ia->path[0] == iaEntity.position);
  int i = 0;
  while(ia->path[i] != iaEntity.position) i += 1;
  assert(i < world->nodeSize);
  pthread_mutex_unlock(&(ia->pathLocked));

  // Close the door, wait for the update and check if it has been updated
  item_entity.property.world.isCrossable = 0;
  sleep(4);
  
  pthread_mutex_lock(&(ia->pathLocked));
  assert(ia->path == NULL);
  pthread_mutex_unlock(&(ia->pathLocked));
  
  // var destroy
  freeAndStopFollowingIA(ia);
  netWorldDelete(world);
}

int main(void)
{
  test();
}
