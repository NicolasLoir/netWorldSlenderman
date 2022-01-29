#include "../includes/networld.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

void test1(void)
{
  //First test : creation by hand

  //World Init
  netWorld * world = netWorldNew(3, 2);

  //Tests
  assert(world->nodeSize == 3);
  assert(world->edgeSize == 2);
  
  //Nodes inits
  netWorldInitNodePosition(world, 1, 2);
  netWorldInitNodePosition(world, 3, 4);
  netWorldInitNodePosition(world, 5, 6);
  assert(world->nodes[0]->x == 1);
  assert(world->nodes[0]->y == 2);
  assert(world->nodes[1]->x == 3);
  assert(world->nodes[1]->y == 4);
  assert(world->nodes[2]->x == 5);
  assert(world->nodes[2]->y == 6);

  //Edges inits
  netWorldInitEdge(world, 0, world->nodes[0], world->nodes[1]);
  netWorldInitEdge(world, 1, world->nodes[2], world->nodes[1]);
  assert(world->edges[0]->nodeA == world->nodes[0]);
  assert(world->edges[0]->nodeB == world->nodes[1]);
  assert(world->edges[1]->nodeA == world->nodes[2]);
  assert(world->edges[1]->nodeB == world->nodes[1]);

  //Print
  netWorldPrint(world);

  //Get all linked
  node ** searchList = netWorldGetAllLinked(world, world->nodes[1]);
  assert(searchList[0] == world->nodes[0]);
  assert(searchList[1] == world->nodes[2]);
  assert(searchList[2] == NULL);

  free(searchList);

  netWorldDelete(world);
}

void test2(void)
{
  //Second test : generation of a rectangular and regular graph

  netWorld * regularWorld = generateRectangularNetWorld(5, 3, 2.5);

  //Check first and last object
  assert(regularWorld->nodes[0]->x == 0);
  assert(regularWorld->nodes[0]->y == 0);
  assert(regularWorld->nodes[regularWorld->nodeSize - 1]->x == 4 * 2.5);
  assert(regularWorld->nodes[regularWorld->nodeSize - 1]->y == 2 * 2.5);

  netWorldPrint(regularWorld);

  //Check a corner of the graph
  node ** searchList = netWorldGetAllLinked(regularWorld, regularWorld->nodes[0]);
  assert(searchList[0]->x == 0);
  assert(searchList[0]->y == 2.5);
  assert(searchList[1]->x == 2.5);
  assert(searchList[1]->y == 0);
  free(searchList);

  //Check in the middle of the graph (coordinate (2.5 * 2, 2.5))
  searchList = netWorldGetAllLinked(regularWorld, regularWorld->nodes[7]);
  // Top node
  assert(searchList[0]->x == 2.5 * 2);
  assert(searchList[0]->y == 0);
  // Bottom node
  assert(searchList[1]->x == 2.5 * 2);
  assert(searchList[1]->y == 2.5 * 2);
  // Left node
  assert(searchList[2]->x == 2.5 * 1);
  assert(searchList[2]->y == 2.5);
  // Right node
  assert(searchList[3]->x == 2.5 * 3);
  assert(searchList[3]->y == 2.5);
  // End of list
  assert(searchList[4] == NULL);
  free(searchList);

  netWorldDelete(regularWorld);
}

void test3(void)
{
  // Test 3 : Test d'algorithme de plus court chemin se basant sur
  // https://www.maths-cours.fr/methode/algorithme-de-dijkstra-etape-par-etape/
  netWorld * world = netWorldNew(6, 10);

  // Nodes are numbured by their alphabetical order in the example
  // 0 = E ; 1 = L ; 2 = M ; 3 = N ; 4 = S ; 5 = T
  netWorldInitNodePosition(world, 0, 0);
  netWorldInitNodePosition(world, 1, 1);
  netWorldInitNodePosition(world, 2, 2);
  netWorldInitNodePosition(world, 3, 3);
  netWorldInitNodePosition(world, 4, 4);
  netWorldInitNodePosition(world, 5, 5);

  // Edges that contains E (And a forward letter)
  netWorldInitEdgeComplete(world, 0,
                           world->nodes[0], world->nodes[1],
                           8, 0);
  netWorldInitEdgeComplete(world, 1,
                           world->nodes[0], world->nodes[2],
                           10, 0);
  netWorldInitEdgeComplete(world, 2,
                           world->nodes[0], world->nodes[4],
                           10, 0);
  netWorldInitEdgeComplete(world, 3,
                           world->nodes[0], world->nodes[5],
                           4, 0);
  // Edges that contains L (And a forward letter)
  netWorldInitEdgeComplete(world, 4,
                           world->nodes[1], world->nodes[2],
                           7, 0);
  netWorldInitEdgeComplete(world, 5,
                           world->nodes[1], world->nodes[3],
                           2, 0);
  netWorldInitEdgeComplete(world, 6,
                           world->nodes[1], world->nodes[4],
                           5, 0);

  // Edges that contains M (And a forward letter)
  netWorldInitEdgeComplete(world, 7,
                           world->nodes[2], world->nodes[3],
                           4, 0);

  // Edges that contains N (And a forward letter)
  netWorldInitEdgeComplete(world, 8,
                           world->nodes[3], world->nodes[4],
                           8, 0);

  // Edges that contains S (And a forward letter)
  netWorldInitEdgeComplete(world, 9,
                           world->nodes[4], world->nodes[5],
                           10, 0);

  // Get the shortest path from M to S
  node ** res = getShortestPath(world, world->nodes[2], world->nodes[4]);

  // The shortest path is M - N - L - S.

  assert(res != NULL);
  assert(res[0] == world->nodes[2]);
  assert(res[1] == world->nodes[3]);
  assert(res[2] == world->nodes[1]);
  assert(res[3] == world->nodes[4]);

  free(res);
  netWorldDelete(world);
}

void test4(void)
{
  // Test 4 : Implementation of directions in a edge
  /* The networld is a square when you can only go on a clockwise direction
   * But you can use diagonals in a bidirectional way
   * 
   *    A  -->  B
   *   /|\ \_/  | 
   *    |  / \ \|/
   *    D  <--  C --> E
   *            |
   *           \|/
   *            F
   */
  netWorld * world = netWorldNew(6, 8);
  
  netWorldInitNodePosition(world, 0, 0);
  netWorldInitNodePosition(world, 0, 1);
  netWorldInitNodePosition(world, 1, 1);
  netWorldInitNodePosition(world, 1, 0);
  netWorldInitNodePosition(world, 1, 2);
  netWorldInitNodePosition(world, 2, 1);

  netWorldInitEdgeComplete(world, 0,
                           world->nodes[0], world->nodes[1],
                           1, 1);
  netWorldInitEdgeComplete(world, 1,
                           world->nodes[1], world->nodes[2],
                           1, 2);
  netWorldInitEdgeComplete(world, 2,
                           world->nodes[3], world->nodes[2],
                           1, -2);
  netWorldInitEdgeComplete(world, 3,
                           world->nodes[0], world->nodes[3],
                           1, -1);
  netWorldInitEdgeComplete(world, 4,
                           world->nodes[0], world->nodes[2],
                           1, 0);
  netWorldInitEdgeComplete(world, 5,
                           world->nodes[1], world->nodes[3],
                           1, 0);
  netWorldInitEdgeComplete(world, 6,
                           world->nodes[2], world->nodes[4],
                           1, 1);
  netWorldInitEdgeComplete(world, 7,
                           world->nodes[5], world->nodes[2],
                           1, -1);

  // First test : All accesible from A
  node ** res = netWorldGetAllLinked(world, world->nodes[0]);
  assert(res[0] == world->nodes[1]);
  assert(res[1] == world->nodes[2]);
  assert(res[2] == NULL);

  free(res);
  
  // Second test : All accesible from C
  res = netWorldGetAllLinked(world, world->nodes[2]);
  assert(res[0] == world->nodes[3]);
  assert(res[1] == world->nodes[0]);
  assert(res[2] == world->nodes[4]);
  assert(res[3] == world->nodes[5]);
  assert(res[4] == NULL);

  free(res);
  netWorldDelete(world);
}

int main(void) {
  test1();
  test2();
  test3();
  test4();
}
