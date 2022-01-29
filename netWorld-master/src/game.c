#include "includes/audio.h"
#include "includes/game.h"
#include "includes/gameEntity.h"
#include "includes/utils.h"
#include "includes/aStar.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <float.h>

#define SIZE_NODE 130
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

int checkArg(int width, int height,
                    int auraRange, int wallPeercentage)
{
  if(width < 4 || width > 60)
    return 1;
  if(height < 4 || height > 60)
    return 2;
  if(auraRange <= 0
     || auraRange > 3
     || auraRange * 2 + 1 > MIN(width, height))
    return 3;
  if(wallPeercentage <= 0 || wallPeercentage > 30)
    return 4;

  return 0;
}

/* EVENTS FUNCTIONS */

static void * checkForBookReceived(void * data)
{
  game * gameData = (game *) data;
  for(int i = 1; i <= 7; i += 1)
  {
    if(!gameData->pageWasRead[i - 1]
       && bookGetByNumber(gameData, i)->position == gameData->player->position)
    {
      gameData->pageWasRead[i - 1] = 1;
    }
  }
  return NULL;
}

static void * moveSlenderman(void * data)
{
  game * gameData = (game *) data;
  node * oldPosition = gameData->slender->position;
  pthread_mutex_lock(&(gameData->slenderIA->pathLocked));
  if(gameData->slenderIA->path != NULL
     && gameData->slender->position != gameData->slenderIA->latestGoal)
  {
    int i = 0;
    while(gameData->slenderIA->path[i] != gameData->slender->position
          && gameData->slenderIA->path[i] != gameData->slenderIA->latestGoal) i += 1;
    // In case the slender lost track of where he was, put it at the begining of the calculated path
    if(gameData->slenderIA->path[i] == gameData->slenderIA->latestGoal)
      gameData->slender->position = gameData->slenderIA->path[0];
    else
      gameData->slender->position = gameData->slenderIA->path[i + 1];
  }
  pthread_mutex_unlock(&(gameData->slenderIA->pathLocked));

  // Update of the position of the slender sprite
  if(oldPosition != gameData->slender->position)
  {
    if(oldPosition->x < gameData->slender->position->x)
    {
      gameData->slenderSpriteRectangle.x += SIZE_NODE;
      entityInitGraphics(gameData->slender, &(gameData->uiData->slenderTextures[1]), 3);
    } else if (oldPosition->x > gameData->slender->position->x) {
      gameData->slenderSpriteRectangle.x -= SIZE_NODE;
      entityInitGraphics(gameData->slender, &(gameData->uiData->slenderTextures[0]), 3);
    } else if (oldPosition->y < gameData->slender->position->y) {
      gameData->slenderSpriteRectangle.y += SIZE_NODE;
      entityInitGraphics(gameData->slender, &(gameData->uiData->slenderTextures[2]), 3);
    } else if (oldPosition->y > gameData->slender->position->y) {
      gameData->slenderSpriteRectangle.y -= SIZE_NODE;
      entityInitGraphics(gameData->slender, &(gameData->uiData->slenderTextures[3]), 3);
    }
  }
  
  return NULL;
}

/* GAME FUNCTIONS */

void initGraphicalData(game * game, int screenX, int screenY)
{
  graphicalData * data = malloc(sizeof(graphicalData));
  
  // netWorldRectangles initialisation
  data->netWorldRectangles = calloc(game->netWorld->nodeSize, sizeof(Rectangle));
  for(int i = 0; i < game->netWorld->nodeSize; i += 1)
  {
    Rectangle boxNode = {game->netWorld->nodes[i]->x * SIZE_NODE,
                         game->netWorld->nodes[i]->y * SIZE_NODE,
                         SIZE_NODE, SIZE_NODE};
    data->netWorldRectangles[i] = boxNode;
  }

  // borders initialisation
  data->borders[0] = (Rectangle) {-SIZE_NODE,
                                  -SIZE_NODE,
                                  SIZE_NODE,
                                  (game->height + 2) * SIZE_NODE};
  data->borders[1] = (Rectangle) {0,
                                  -SIZE_NODE,
                                  game->width * SIZE_NODE,
                                  SIZE_NODE};
  data->borders[2] = (Rectangle) {0,
                                  game->height * SIZE_NODE,
                                  game->width * SIZE_NODE,
                                  SIZE_NODE};
  data->borders[3] = (Rectangle) {game->width * SIZE_NODE,
                                  -SIZE_NODE,
                                  SIZE_NODE,
                                  (game->height + 2) * SIZE_NODE};

  // Player textures intialisation
  data->playerTextures[0] = LoadTexture("resources/LinkRight.png");
  data->playerTextures[1] = LoadTexture("resources/LinkLeft.png");
  data->playerTextures[2] = LoadTexture("resources/LinkBack.png");
  data->playerTextures[3] = LoadTexture("resources/LinkFace.png");
  data->playerTextures[4] = LoadTexture("resources/LinkPause.png");

  entityInitGraphics(game->player, data->playerTextures + 4, 10);

  // Slender textures initialisation
  data->slenderTextures[0] = LoadTexture("resources/SlenderLeft.png");
  data->slenderTextures[1] = LoadTexture("resources/SlenderRight.png");
  data->slenderTextures[2] = LoadTexture("resources/SlenderFace.png");
  data->slenderTextures[3] = LoadTexture("resources/SlenderBack.png");
  data->slenderTextures[4] = LoadTexture("resources/SlenderFace.png");

  entityInitGraphics(game->slender, &(data->slenderTextures[4]), 3);

  // Wall textures initialisation
  data->wallTextures[0] = LoadTexture("resources/Tree.png");
  data->wallTextures[1] = LoadTexture("resources/Tree2.png");
  data->wallTextures[2] = LoadTexture("resources/Tree3.png");
  data->wallTextures[3] = LoadTexture("resources/Tree4.png");
  data->wallTextures[4] = LoadTexture("resources/Tree5.png");
  data->wallTextures[5] = LoadTexture("resources/Rock.png");
  data->wallTextures[6] = LoadTexture("resources/Jar.png");
  for(int i = 7; i < game->worldEntities->sizeWorldItem; i += 1)
  {
    entityInitGraphics(game->worldEntities->arrayWorldItem + i,
                       &(data->wallTextures[rand() % 7]), 1);
  }

  // Book textures initialisation
  data->pagesTextures[0] = LoadTexture("resources/Book01.png");
  data->pagesTextures[1] = LoadTexture("resources/Book02.png");
  data->pagesTextures[2] = LoadTexture("resources/Book03.png");
  data->pagesTextures[3] = LoadTexture("resources/Book04.png");
  data->pagesTextures[4] = LoadTexture("resources/Book05.png");
  data->pagesTextures[5] = LoadTexture("resources/Book06.png");
  data->pagesTextures[6] = LoadTexture("resources/Book07.png");
  for(int i = 0; i < 7; i += 1)
  {
    entityInitGraphics(game->worldEntities->arrayWorldItem + i,
                       &(data->pagesTextures[i]), 1);
  }

  // Frames vars init
  data->frameCounter = 0;
  data->frameSpeed = 8;
  
  // Camera init
  data->camera = (Camera2D) {0};
  data->camera.offset = (Vector2){screenX / 2, screenY / 2};
  data->camera.zoom = 0.5;

  // Background init
  data->background = LoadTexture("resources/FieldP.png");
  
  game->uiData = data;
}

void freeGraphicalData(game * game)
{
  free(game->uiData->netWorldRectangles);
  // Unload player and slender
  for(int i = 0; i < 5; i += 1)
  {
    UnloadTexture(game->uiData->playerTextures[i]);
    UnloadTexture(game->uiData->slenderTextures[i]);
  }
  // Unload wall and pages
  for(int i = 0; i < 5; i += 1)
  {
    UnloadTexture(game->uiData->wallTextures[i]);
    UnloadTexture(game->uiData->pagesTextures[i]);
  }

  UnloadTexture(game->uiData->background);
  free(game->uiData);
}

game * gameNew(int xSize, int ySize,
               int screenX, int screenY,
               int slenderAura, int wallPeercentage)
{ 
  game * newGame = malloc(sizeof(game));
  
  // NetWorld creation
  newGame->netWorld = generateRectangularNetWorld(xSize, ySize, 1);
  newGame->width = xSize;
  newGame->height = ySize;

  // Creation of walls and books
  int numberOfWall = (xSize * ySize * wallPeercentage) / 100;
  node * randomPosition[numberOfWall + 9];
  fillWithRandomNode(newGame->netWorld, randomPosition,
                     numberOfWall + 9);
  newGame->worldEntities = itemsMapsNew(numberOfWall + 7);
  for(int i = 0; i < 7; i += 1)
  {
    bookAdd(newGame->worldEntities,
            i,
            randomPosition[i],
            i + 1);
  }
  
  memset(newGame->pageWasRead, 0, 7 * sizeof(int));
  
  for(int i = 0; i < numberOfWall; i += 1)
  {
    wallAdd(newGame->worldEntities,
            i + 7,
            randomPosition[i + 7]);
  }

  // Placement of the slenderman and the player
  newGame->player = playerCreate(randomPosition[numberOfWall + 7]);
  newGame->slender = slenderCreate(randomPosition[numberOfWall + 8]);

  // Configuration of the aura and the light range
  newGame->slenderAuraRange = slenderAura;
  newGame->lightRange = slenderAura + 2;
  
  // Checks if the game is viable and if not, return another game after freeing
  if(!gameIsViable(newGame))
  {
    for(int i = 0; i < 7; i += 1)
    {
      bookDestroy(newGame->worldEntities, i);
    }
    itemsMapsDelete(newGame->worldEntities);
    slenderDestroy(newGame->slender);
    playerDestroy(newGame->player);
    netWorldDelete(newGame->netWorld);
    free(newGame);
    return gameNew(xSize, ySize, screenX, screenY, slenderAura, wallPeercentage);
  }

  // IA creation
  newGame->slenderIA = startFollowingIA(newGame->slender, newGame->netWorld,
                                        newGame->player, newGame->worldEntities);

  // Events inits
  newGame->everyTwoSecondEvents = eventManagerCreate();
  eventManagerAdd(newGame->everyTwoSecondEvents, newGame, &moveSlenderman);

  newGame->everyMoveEvents = eventManagerCreate();
  eventManagerAdd(newGame->everyMoveEvents, newGame, &checkForBookReceived);

  // Player and slender drawed position
  newGame->playerSpriteRectangle = (Rectangle) {newGame->player->position->x * SIZE_NODE, newGame->player->position->y * SIZE_NODE, SIZE_NODE, SIZE_NODE};
  newGame->slenderSpriteRectangle = (Rectangle) {newGame->slender->position->x * SIZE_NODE, newGame->slender->position->y * SIZE_NODE, SIZE_NODE, SIZE_NODE};

  // Graphical init
  initGraphicalData(newGame, screenX, screenY);
  
  return newGame;
}

void gameDestroy(game * game)
{
  freeAndStopFollowingIA(game->slenderIA);
  for(int i = 0; i < 7; i += 1)
  {
    bookDestroy(game->worldEntities, i);
  }
  itemsMapsDelete(game->worldEntities);
  slenderDestroy(game->slender);
  playerDestroy(game->player);
  netWorldDelete(game->netWorld);
  freeGraphicalData(game);
  eventManagerDestroy(game->everyTwoSecondEvents);
  eventManagerDestroy(game->everyMoveEvents);
  free(game);
}

static void gameCheckMove(game * game)
{
  /*
   * The new sprite position is calculated based on the inputs of the keys
   * The sprite frame is also updated based on the direction
   */
  Rectangle newPosition = game->playerSpriteRectangle;
  int updated = 0;
  if (IsKeyDown(KEY_RIGHT))
  {
    newPosition.x += 2;
    if(!updated)
    {
      entityInitGraphics(game->player, &(game->uiData->playerTextures[0]), 10);
      updated = 1;
    }
  }
  if (IsKeyDown(KEY_LEFT))
  {
    newPosition.x -= 2;
    if(!updated)
    {
      entityInitGraphics(game->player, &(game->uiData->playerTextures[1]), 10);
      updated = 1;
    }
  }
  if (IsKeyDown(KEY_UP))
  {
    newPosition.y -= 2;
    if(!updated)
    {
      entityInitGraphics(game->player, &(game->uiData->playerTextures[2]), 10);
      updated = 1;
    }
  }
  if (IsKeyDown(KEY_DOWN))
  {
    newPosition.y += 2;
    if(!updated)
    {
      entityInitGraphics(game->player, &(game->uiData->playerTextures[3]), 10);
      updated = 1;
    }
  }
  if (newPosition.x == game->playerSpriteRectangle.x
      && newPosition.y == game->playerSpriteRectangle.y)
  {
    entityInitGraphics(game->player, &(game->uiData->playerTextures[4]), 10);
    return;
  }

  // Checks if you are out of bounds
  if(newPosition.x < 0
     || newPosition.x + SIZE_NODE > SIZE_NODE * game->width
     || newPosition.y < 0
     || newPosition.y + SIZE_NODE > SIZE_NODE * game->height)
    return;
  
  // Check of the collisions with the walls
  Rectangle newCollision = newPosition;
  newCollision.x += (SIZE_NODE) / 4;
  newCollision.y += (SIZE_NODE) / 4;
  newCollision.width -= (SIZE_NODE) / 2;
  newCollision.height -= (SIZE_NODE) / 2;
  int i = 7;
  while(i < game->worldEntities->sizeWorldItem
        && !CheckCollisionRecs(newCollision, game->uiData->netWorldRectangles[getIndex(game->netWorld->nodes,
                                                                                       game->worldEntities->arrayWorldItem[i].position)]))
    i += 1;
  if(i == game->worldEntities->sizeWorldItem)
  {
    /*
     * If they weren't any collisions, update the drawed position
     * and check if we need to update the position in the NetWorld
     */
    game->playerSpriteRectangle = newPosition;
    node * newNodePosition = getNodeAt(game->netWorld, (int) ((newPosition.x + (SIZE_NODE / 2)) / SIZE_NODE), (int) ((newPosition.y + (SIZE_NODE / 2)) / SIZE_NODE));
    if(newNodePosition != NULL
       && newNodePosition != game->player->position)
    {
      game->player->position = newNodePosition;
      eventManagerLaunch(game->everyMoveEvents);
      PlaySoundRandomStep();
    }
  }
}

static void gameDraw(game * game)
{
  // Camera update
  Camera2D * cam = &(game->uiData->camera);
  cam->target = (Vector2) {game->playerSpriteRectangle.x + (SIZE_NODE) / 2,
                           game->playerSpriteRectangle.y + (SIZE_NODE) / 2};
  cam->zoom += ((float)GetMouseWheelMove()*0.05f);
  if (cam->zoom > 3.0f) cam->zoom = 3.0f;
  else if (cam->zoom < 0.2f) cam->zoom = 0.2f;
  BeginMode2D(*cam);

  // Background drawing
  ClearBackground(RAYWHITE);
  Vector2 tiling = {1, 1},
          offset = {0, 0};
  Rectangle quad = {-5000, -5000, 30000, 30000};
  DrawTextureQuad(game->uiData->background, tiling, offset,
                  quad, WHITE);

  int shouldChangeFrame = game->uiData->frameCounter % (60/game->uiData->frameSpeed) == 0;
  
  // Border drawing
  for(int i = 0; i < 4; i++)
  {
    DrawRectangleRec(game->uiData->borders[i], BLACK);
  }

  // Book drawing
  for(int i = 0; i < 7; i++)
  {
    int bookIndex =  getIndex(game->netWorld->nodes,
                              bookGetByNumber(game, i + 1)->position);
    if(!game->pageWasRead[i])
      entityDrawInRec(bookGetByNumber(game, i + 1),
                      game->uiData->netWorldRectangles[bookIndex],
                      shouldChangeFrame);
  }

  // Wall drawing
  for(int i = 7; i < game->worldEntities->sizeWorldItem; i++)
  {
    int wallIndex =  getIndex(game->netWorld->nodes,
                              game->worldEntities->arrayWorldItem[i].position);
    entityDrawInRec(game->worldEntities->arrayWorldItem + i,
                    game->uiData->netWorldRectangles[wallIndex],
                    shouldChangeFrame);
  }

  // Player drawing
  int playerIndex = getIndex(game->netWorld->nodes, game->player->position);
  DrawRectangleRec(game->uiData->netWorldRectangles[playerIndex], ORANGE);
  entityDrawInRec(game->player, game->playerSpriteRectangle, shouldChangeFrame);

  // Slender drawing (aura included)
  for(int i = 0; i < game->netWorld->nodeSize; i += 1)
  {
    int distance = nodeGetManhattanDistance(game->netWorld->nodes[i],
                                            game->slender->position);
    if(distance <= game->slenderAuraRange)
    {
      DrawRectangleRec(game->uiData->netWorldRectangles[i],
                       RED_ALPHA(122 - (((distance - 1) * 122) / game->slenderAuraRange)));
    }
  }
  entityDrawInRec(game->slender, game->slenderSpriteRectangle, shouldChangeFrame);

  // Lightning effects
  Vector2 positionVector = {game->playerSpriteRectangle.x + (SIZE_NODE / 2), 
                            game->playerSpriteRectangle.y + (SIZE_NODE / 2)};
  DrawCircleGradient(positionVector.x,
                     positionVector.y,
                     game->lightRange * SIZE_NODE,
                     BLANK,
                     BLACK);
  DrawRing(positionVector,
           game->lightRange * SIZE_NODE - 10,
           FLT_MAX,
           0,
           360,
           100,
           BLACK);
}

void gameUpdate(game * game)
{
  gameCheckMove(game);
  game->uiData->frameCounter += 1;
  if(game->uiData->frameCounter % 120 == 0)
    eventManagerLaunch(game->everyTwoSecondEvents);
  gameDraw(game);
}

int gameIsDone(game * gameP)
{
  int i = 0;
  while(i < 7
        && gameP->pageWasRead[i])
    i += 1;

  // Has the player got all books
  if(i == 7)
    return PLAYER_WON;

  // Is the player in the range of the slender
  if(nodeGetManhattanDistance(gameP->player->position,
                              gameP->slender->position) <= gameP->slenderAuraRange)
    return SLENDER_WON;
  else
    return 0;
}

int gameIsViable(game * gameP)
{
  // Is the game allready done for the player
  if(nodeGetManhattanDistance(gameP->player->position,
                              gameP->slender->position) <= gameP->slenderAuraRange)
    return 0;
  
  // Can the player get every pages in the netWorld
  netWorld netWorldWithoutItems = duplicateNetWorldForIA(gameP->netWorld, gameP->worldEntities);
  node ** path;
  int i = 1;
  while(i <= 7
        && (path = getEstimatedShortestPath(&netWorldWithoutItems,
                                            gameP->player->position,
                                            bookGetByNumber(gameP, i)->position)) != NULL)
  {
    i += 1;
    free(path);
  }
  if(i <= 7)
  {
    free(path);
    netWorldFreeDuplicated(netWorldWithoutItems);
    return 0;

    // Can the slender follow the player in the map
  } else if ((path = getEstimatedShortestPath(&netWorldWithoutItems,
                                              gameP->player->position,
                                              gameP->slender->position)) == NULL) {
    return 0;
  } else {
    free(path);
    netWorldFreeDuplicated(netWorldWithoutItems);
    return 1;
  }
}
