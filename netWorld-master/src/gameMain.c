#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "includes/node.h"
#include "includes/networld.h"
#include "includes/entity.h"
#include "includes/game.h"
#include "includes/audio.h"
#include "includes/menu.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

int main()
{
  
  srand(time(NULL)); // une seule fois
  // Initialization
  //--------------------------------------------------------------------------------------
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SlenderGame");
  PlayAudioMainMusic();

  SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
  
  int repeatGame = 1;
  menus * theMenus = create_menus(30, 30,
                                  3, 10);

  do
  {
    // Main game loop
    game * gameData = NULL;

    while (!WindowShouldClose() && theMenus->array_menu[0]->start_the_game == 0)    // Detect window close button or ESC key
    {
      BeginDrawing();
        updateMenus(theMenus, &repeatGame);
        
      EndDrawing();
      
    }

    if (theMenus->array_menu[0]->start_the_game == 1)
      gameData = gameNew(theMenus->netWorldHeight, theMenus->netWorldWidth,
                         SCREEN_WIDTH, SCREEN_HEIGHT,
                         theMenus->aura, theMenus->wallPeercentage);
    
    while (!WindowShouldClose()
           && theMenus->array_menu[0]->start_the_game == 1
           && theMenus->array_menu[2]->start_the_game != -1
           && !gameIsDone(gameData)
           && repeatGame == 1)
    {
      BeginDrawing();

      updateMenus(theMenus, &repeatGame);
      if (theMenus->array_menu[2]->start_the_game == 1){
        gameUpdate(gameData);
        UpdateAudio();
      }
      
      EndDrawing();
      
    }

    if(gameData != NULL)
      gameDestroy(gameData);
    
    resetMenus(theMenus);
  } while (repeatGame == 1);

  //--------------------------------------------------------------------------------------
  FreeAudioMainMusic();
  CloseWindow();        // Close window and OpenGL context
  destroyMenus(theMenus); 
  //--------------------------------------------------------------------------------------
    
    
  return 0;
}



