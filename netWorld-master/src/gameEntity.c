#include "includes/gameEntity.h"
#include <stdlib.h>
#include <stdio.h>

entity * playerCreate(node * position)
{
  entity * res = malloc(sizeof(entity));
  res->type = PLAYER;
  res->name = "Joueur";
  res->property.player.health = 100;
  res->fixed = 0;
  res->position = position;
  res->spriteTexture = NULL;
  return res;
}

entity * slenderCreate(node * position)
{
  entity * res = malloc(sizeof(entity));
  res->type = NPC;
  res->name = "Slender";
  res->fixed = 0;
  res->position = position;
  res->spriteTexture = NULL;
  return res;
}

void bookAdd(itemsMap * itemsMap, int i, node * position, int numero)
{
  itemsMap->arrayWorldItem[i].type = WORLD_ITEM;
  itemsMap->arrayWorldItem[i].name = malloc(sizeof(char) * 22);
  snprintf(itemsMap->arrayWorldItem[i].name, 22, "Livre N°%1i", numero);
  itemsMap->arrayWorldItem[i].property.world.state = 1;
  itemsMap->arrayWorldItem[i].property.world.isCrossable = 1;
  itemsMap->arrayWorldItem[i].fixed = 1;
  itemsMap->arrayWorldItem[i].position = position;
  itemsMap->arrayWorldItem[i].spriteTexture = NULL;
}

void bookDestroy(itemsMap * itemsMap, int i)
{
  free(itemsMap->arrayWorldItem[i].name);
}

void wallAdd(itemsMap * itemsMap, int i, node * position)
{
  itemsMap->arrayWorldItem[i].type = WORLD_ITEM;
  itemsMap->arrayWorldItem[i].name = "Mur";
  itemsMap->arrayWorldItem[i].property.world.state = 1;
  itemsMap->arrayWorldItem[i].property.world.isCrossable = 0;
  itemsMap->arrayWorldItem[i].fixed = 1;
  itemsMap->arrayWorldItem[i].position = position;
  itemsMap->arrayWorldItem[i].spriteTexture = NULL;
}
