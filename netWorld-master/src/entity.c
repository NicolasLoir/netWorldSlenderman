#include "includes/entity.h"

#include <stdio.h>

int isCrossableAndOpen(entity * self)
{
    if (self->type == WORLD_ITEM)
    {
        worldItem a = self->property.world;
        if (a.isCrossable && a.state)
        {
            return 1;
        }
    }    
    return 0;
}

itemsMap * itemsMapsNew(int size)
{
    itemsMap * i = malloc( sizeof(itemsMap) );
    i->sizeWorldItem = size;
    i->arrayWorldItem = calloc(i->sizeWorldItem, sizeof(entity));
    return i;
}


int moveEntityTo(entity * entityPlayer, node * toNode, netWorld * netWorld, itemsMap * murs)
{
    int i, found, cptItemsMap = 0;
    node ** nodeAroundMe = netWorldGetAllLinked(netWorld, entityPlayer->position);
    
    // We return an error if there is no node around us.
    if(nodeAroundMe == NULL)
        return 0;
    
    i = 0, found = 0;
    while (found == 0 && nodeAroundMe[i] != NULL)
    {
        // If the node next to the current node.
        if(nodeAreEquals(toNode, nodeAroundMe[i]))
        {
            //search if there is an item on the node
            while (cptItemsMap < murs->sizeWorldItem && found == 0)
            {
                //if there is a item
                if (murs->arrayWorldItem[cptItemsMap].position != NULL)
                {
                    if (nodeAreEquals(toNode, murs->arrayWorldItem[cptItemsMap].position))
                    {
                        //only event and isCrossableAndOpen are crossable
                        if ( isCrossableAndOpen( &murs->arrayWorldItem[cptItemsMap] ) ) // || murs->array_world_item[cpt_items_map].type == EVENT
                        {
                            found = 1;
                        } 
                        else
                        //if there is a item and it's not crossable and open
                        {
                            free(nodeAroundMe);
                            return 0;
                        }
                        
                    }
                }
                
                cptItemsMap++;
            }
            //if there is not item on the node
            found = 1;
        }
        i++;
    }
    
    netWorldFreeAllLinked(nodeAroundMe);
    
    if(found)
        entityPlayer->position = toNode;

    return found;
}


void itemsMapsDelete(itemsMap * itemsMap)
{
  free(itemsMap->arrayWorldItem);
  free(itemsMap);
}

void entityInitGraphics(entity * entity, Texture2D * texture, int numberOfFrame)
{
  if(texture != entity->spriteTexture)
  {
    entity->spriteTexture = texture;
    entity->numberOfFrame = numberOfFrame;
    entity->currentFrame = 0;
    entity->frameRec = (Rectangle) {0, 0,
                                    (float) texture->width / numberOfFrame,
                                    (float) texture->height};
  }
}

void entityDrawInRec(entity * entity, Rectangle rectangle,
                     int changeFrameBefore)
{
  if(changeFrameBefore)
  {
    entity->currentFrame = (entity->currentFrame + 1) % entity->numberOfFrame;
    entity->frameRec.x = ((float)entity->currentFrame * (float)entity->spriteTexture->width)/entity->numberOfFrame;
  }

  Vector2 position = {rectangle.x, rectangle.y};
  
  DrawTextureRec(*(entity->spriteTexture), entity->frameRec, position, WHITE);
}
