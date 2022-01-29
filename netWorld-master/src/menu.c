#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "includes/menu.h"
#include "includes/game.h"



void draw_box(box aBox, int framesCounter)
{
    float roundness = 0.2f;
    int segments = 0;
    int lineThick = 3;
    //int fontSize = height/2;

    //rectangle intereur
    DrawRectangleRounded(aBox.rec, roundness, segments, aBox.main_color);
    if (aBox.is_box_field)  DrawText(aBox.text, aBox.rec.x + 5, aBox.rec.y + 5, aBox.font_size, WHITE); //le texte se dessine bien dans la case du coup 
    else DrawText(aBox.text, aBox.rec.x + aBox.padding_left, aBox.rec.y + aBox.font_size/2, aBox.font_size, WHITE);
    //bordure
    if (!aBox.is_selected)
        DrawRectangleRoundedLines(aBox.rec, roundness, segments, lineThick, aBox.border_color);
    else if ((framesCounter/30)%2)
        DrawRectangleRoundedLines(aBox.rec, roundness, segments, lineThick, RED);
}

menu * create_menu_principal(int width, int height)
{    
    int padding = height/4;
    int sFont = height/2; //size font

    box box_start;
    Rectangle rec_start = { (GetScreenWidth() - width)/2, (GetScreenHeight() - height)/2 - 2*height, width, height };
    box_start.rec = rec_start;
    box_start.text = "Start";
    box_start.is_selected = 1; //par defaut
    box_start.font_size = sFont;
    box_start.main_color = Fade(MAROON, 0.2);
    box_start.border_color = BROWN;
    box_start.padding_left = box_start.rec.width/4;
    box_start.is_box_field = 0;

    box box_help;
    Rectangle rec_help = { (GetScreenWidth() - width)/2, (GetScreenHeight() - height)/2 - height + padding, width, height };
    box_help.rec = rec_help;
    box_help.text = "Help";
    box_help.is_selected = 0;
    box_help.font_size = sFont;
    box_help.main_color = Fade(MAROON, 0.2);
    box_help.border_color = BROWN;
    box_help.padding_left = box_help.rec.width/4;
    box_help.is_box_field = 0;

    box box_parameter;
    Rectangle rec_parameter = { (GetScreenWidth() - width)/2, (GetScreenHeight() - height)/2 + 2* padding, width, height };
    box_parameter.rec = rec_parameter;
    box_parameter.text = "Parameter";
    box_parameter.is_selected = 0;
    box_parameter.font_size = sFont;
    box_parameter.main_color = Fade(MAROON, 0.2);
    box_parameter.border_color = BROWN;
    box_parameter.padding_left = box_parameter.rec.width/12;
    box_parameter.is_box_field = 0;


    box box_leave;
    Rectangle rec_leave = { (GetScreenWidth() - width)/2, (GetScreenHeight() - height)/2 + height + 3 * padding, width, height };
    box_leave.rec = rec_leave;
    box_leave.text = "Leave";
    box_leave.is_selected = 0;
    box_leave.font_size = sFont;
    box_leave.main_color = Fade(MAROON, 0.2);
    box_leave.border_color = BROWN;
    box_leave.padding_left = box_leave.rec.width/4;
    box_leave.is_box_field = 0;


    menu * aMenu = malloc(sizeof(menu));
    aMenu->size_menu = 4;
    box * buttons = malloc(aMenu->size_menu * sizeof(box));
    buttons[0] = box_start;
    buttons[1] = box_help;
    buttons[2] = box_parameter;
    buttons[3] = box_leave;
    aMenu->array_box = buttons;
    aMenu->selected_box = 0;
    aMenu->start_the_game = 0;

    return aMenu;
}

menu * create_menu_help(int width, int height)
{
    int padding = height/4;
    int sFont = height/2; //size font

    box box_exit;
    Rectangle rec_exit= { (GetScreenWidth() - width)/2, (GetScreenHeight() - height)/2 + height + 2 * padding, width, height };
    box_exit.rec = rec_exit;
    box_exit.text = "Exit";
    box_exit.is_selected = 1;
    box_exit.font_size = sFont;
    box_exit.main_color = Fade(MAROON, 0.2);
    box_exit.border_color = BROWN;
    box_exit.padding_left = box_exit.rec.width/4;
    box_exit.is_box_field = 0;

    menu * aMenu = malloc(sizeof(menu));
    aMenu->size_menu = 1;
    box * buttons = malloc(aMenu->size_menu * sizeof(box));
    buttons[0] = box_exit;
    aMenu->array_box = buttons;
    aMenu->selected_box = 0;
    aMenu->start_the_game = 0;

    return aMenu;
}

menu * create_menu_pause(int width, int height)
{
    int padding = height/4;
    int sFont = height/2; //size font

    box box_start;
    Rectangle rec_start = { (GetScreenWidth() - width)/2, (GetScreenHeight() - height)/2 - height, width, height };
    box_start.rec = rec_start;
    box_start.text = "Resume";
    box_start.is_selected = 1; //par defaut
    box_start.font_size = sFont;
    box_start.main_color = Fade(MAROON, 0.2);
    box_start.border_color = BROWN;
    box_start.padding_left = box_start.rec.width/4;
    box_start.is_box_field = 0;

    box box_help;
    Rectangle rec_help = { (GetScreenWidth() - width)/2, (GetScreenHeight() - height)/2 + padding, width, height };
    box_help.rec = rec_help;
    box_help.text = "Help";
    box_help.is_selected = 0;
    box_help.font_size = sFont;
    box_help.main_color = Fade(MAROON, 0.2);
    box_help.border_color = BROWN;
    box_help.padding_left = box_help.rec.width/4;
    box_help.is_box_field = 0;

    box box_leave;
    Rectangle rec_leave = { (GetScreenWidth() - width)/2, (GetScreenHeight() - height)/2 + height + 2 * padding, width, height };
    box_leave.rec = rec_leave;
    box_leave.text = "Exit";
    box_leave.is_selected = 0;
    box_leave.font_size = sFont;
    box_leave.main_color = Fade(MAROON, 0.2);
    box_leave.border_color = BROWN;
    box_leave.padding_left = box_leave.rec.width/4;
    box_leave.is_box_field = 0;

    menu * aMenu = malloc(sizeof(menu));
    aMenu->size_menu = 3;
    box * buttons = malloc(aMenu->size_menu * sizeof(box));
    buttons[0] = box_start;
    buttons[1] = box_help;
    buttons[2] = box_leave;
    aMenu->array_box = buttons;
    aMenu->selected_box = 0;
    aMenu->start_the_game = 1;

    return aMenu;
}

menu * create_menu_parameter(int width, int height, int auraRange, int wallPeercentage)
{
    //char largeurTXT[3] = "30"; //valeur par défaut
    box largeur;
    Rectangle rec_largeur = {20, 50, 70, 60};//posX ;posY;largeur;hauteur
    largeur.rec = rec_largeur;
    largeur.text = malloc(sizeof(char) * 3);
    snprintf(largeur.text, 3, "%i", width);
    largeur.is_selected = 1; //par defaut
    largeur.font_size = 30;
    largeur.letterCount = strlen(largeur.text);
    largeur.value = TextToInteger(largeur.text);
    largeur.is_box_field = 1;
    largeur.main_color = Fade(MAROON, 0.2);
    largeur.border_color = BROWN;
    
    //char hauteurTXT[3] = "30"; //valeur par défaut
    box hauteur;
    Rectangle rec_hauteur = {20, 170, 70, 60};
    hauteur.rec = rec_hauteur;
    hauteur.text = malloc(sizeof(char) * 3);
    snprintf(hauteur.text, 3, "%i", height);
    hauteur.is_selected = 0;
    hauteur.font_size = 30;
    hauteur.letterCount = strlen(hauteur.text);
    hauteur.value = TextToInteger(hauteur.text);
    hauteur.is_box_field = 1;
    hauteur.main_color = Fade(MAROON, 0.2);
    hauteur.border_color = BROWN;

    //char auraTXT[3] = "3"; //valeur par défaut
    box aura;
    Rectangle rec_aura = {20, 290, 70, 60};
    aura.rec = rec_aura;
    aura.text = malloc(sizeof(char) * 3);
    snprintf(aura.text, 3, "%i", auraRange);
    aura.is_selected = 0;
    aura.font_size = 30;
    aura.letterCount = strlen(aura.text);
    aura.value = TextToInteger(aura.text);
    aura.is_box_field = 1;
    aura.main_color = Fade(MAROON, 0.2);
    aura.border_color = BROWN;

    //char murTXT[4] = "15"; //valeur par défaut
    box mur;
    Rectangle rec_mur = {20, 410, 70, 60};
    mur.rec = rec_mur;
    mur.text = malloc(sizeof(char) * 3);
    snprintf(mur.text, 3, "%i", wallPeercentage);
    mur.is_selected = 0;
    mur.font_size = 30;
    mur.letterCount = strlen(mur.text);
    mur.value = TextToInteger(mur.text);
    mur.is_box_field = 1;
    mur.main_color = Fade(MAROON, 0.2);
    mur.border_color = BROWN;

    box box_exit;
    Rectangle rec_exit= { GetScreenWidth() - 115, GetScreenHeight()-90, 100, 50 };
    box_exit.rec = rec_exit;
    box_exit.text = "Exit";
    box_exit.is_selected = 0;
    box_exit.font_size = 30;
    box_exit.main_color = Fade(MAROON, 0.2);
    box_exit.border_color = BROWN;
    box_exit.padding_left = box_exit.rec.width/4;
    box_exit.is_box_field = 0;

    
    menu * aMenu = malloc(sizeof(menu));
    
    aMenu->size_menu = 5;
    box * buttons = malloc(aMenu->size_menu * sizeof(box));
    buttons[0] = largeur;
    buttons[1] = hauteur;
    buttons[2] = aura;
    buttons[3] = mur;
    buttons[4] = box_exit;
    aMenu->array_box = buttons;
    aMenu->selected_box = 0;
    
    
    

    return aMenu;
}



void draw_menu_all_box(menu * aMenu, int framesCounter)
{
    for (int i = 0; i < aMenu->size_menu; i++)
    {
        draw_box(aMenu->array_box[i], framesCounter);
    }
}

void draw_menu_principal(menu * aMenu, int framesCounter)
{
    draw_menu_all_box(aMenu, framesCounter);
}

void draw_menu_help(menu * aMenu, int framesCounter)
{
    ClearBackground(Fade(BLACK, 0.5));
    int height = GetScreenHeight()/6;
    int sFont = height/4;
    DrawText("Hello friend, can you help me to collect", 1.5*sFont+10, 10+ 3*sFont, sFont, WHITE);
    DrawText(" the things I have lost?", 5*sFont+10, 10 + 5*sFont, sFont, WHITE);
    DrawText("Use keyboard arrow to move around", 3*sFont, 10 + 8*sFont, sFont, WHITE);
    DrawText("Be careful, I saw a shadow lurking around.", 1.5*sFont, 10 + 10*sFont, sFont, WHITE);
    DrawText("Press 'P' to pause the game. Good luck.", 2*sFont, 10 + 12*sFont, sFont, WHITE);

    draw_menu_all_box(aMenu, framesCounter);   
}

void draw_menu_pause(menu * aMenu, int framesCounter)
{
    ClearBackground(Fade(GRAY, 0.2));
    int height = GetScreenHeight()/12;
    DrawText("Game paused", 3*height, 10 + height, height, WHITE);
    draw_menu_all_box(aMenu, framesCounter);
}


void update_menu_selection(menu * aMenu)
{
    if (IsKeyPressed(KEY_DOWN))
    {
        aMenu->array_box[aMenu->selected_box].is_selected = 0;
        aMenu->selected_box += 1;
        //si on appuie que sur bas
        if (aMenu->selected_box == aMenu->size_menu)
            aMenu->selected_box = 0;
        aMenu->array_box[aMenu->selected_box].is_selected = 1;
    }
    else if (IsKeyPressed(KEY_UP))
    {
        aMenu->array_box[aMenu->selected_box].is_selected = 0;
        aMenu->selected_box -= 1;
        if (aMenu->selected_box == -1)
            aMenu->selected_box = aMenu->size_menu - 1;
        aMenu->array_box[aMenu->selected_box].is_selected = 1;
    }
}

void update_menu_principal(menu * aMenu, int * selected_menu, int * repeatGame)
{
    update_menu_selection(aMenu);
    if (IsKeyPressed(KEY_ENTER))
    {
        switch (aMenu->selected_box)
        {
        case 0:
            aMenu->start_the_game = 1;
            break;
        case 1:
            *selected_menu = 1;//menu help
            break;
        case 2:
            *selected_menu = 3;//menu parameter
            break;
        case 3:
            aMenu->start_the_game = -1;
            *repeatGame = 0;
            break;
        
        default:
            break;
        }
    }
}

void update_menu_pause(menu * aMenu, int * selected_menu)
{
    update_menu_selection(aMenu);
    if (IsKeyPressed(KEY_ENTER))
    {
        switch (aMenu->selected_box)
        {
        case 0:
            aMenu->start_the_game = 1; //resume the game
            break;
        case 1:
            *selected_menu = 1; //display help panel
            break;
        case 2:
            aMenu->start_the_game = -1; //go to main menu, exit the game
            break;
        
        default:
            break;
        }
    }
}

menus * create_menus(int netWorldWidth, int netWorldHeight,
                     int aura, int wallPeercentage)
{
    menus * theMenus = malloc(sizeof(menus));

    int width = GetScreenWidth()/2;
    int height = GetScreenHeight()/6;
    menu * menuPrincipal = create_menu_principal(width, height);
    menu * menuHelp = create_menu_help(width, height);
    menu * menuPause = create_menu_pause(width, height);
    menu * menuParameter = create_menu_parameter(netWorldWidth, netWorldHeight,
                                                 aura, wallPeercentage);
    
    theMenus->nb_menu = 4;
    menu ** array_menu = malloc(theMenus->nb_menu  * sizeof(menu));
    array_menu[0] = menuPrincipal;
    array_menu[1] = menuHelp;
    array_menu[2] = menuPause;
    array_menu[3] = menuParameter;

    theMenus->array_menu = array_menu;
    theMenus->framesCounter = 0;
    theMenus->selected_menu = 0;

    theMenus->netWorldHeight = netWorldHeight;
    theMenus->netWorldWidth = netWorldWidth;
    theMenus->aura = aura;
    theMenus->wallPeercentage = wallPeercentage;

    return theMenus;
}

void updateMenus(menus * theMenus, int * repeatGame)
{
    if (theMenus->array_menu[0]->start_the_game == 0) //main menu
    {
        ClearBackground(Fade(BLACK, 0.5));
        if (theMenus->selected_menu == 0)//main menu
        {
            draw_menu_principal(theMenus->array_menu[0], theMenus->framesCounter);
            update_menu_principal(theMenus->array_menu[0], &theMenus->selected_menu, repeatGame);
        }
        else if (theMenus->selected_menu == 1)//menu help
        {
            draw_menu_help(theMenus->array_menu[1], theMenus->framesCounter);
            if (IsKeyPressed(KEY_ENTER)) theMenus->selected_menu  = 0;
        }
        else if (theMenus->selected_menu == 3)//menu parameter
        {
            draw_menu_parameter(theMenus->array_menu[3], theMenus->framesCounter);
            update_menu_parameter(theMenus, theMenus->array_menu[3], &theMenus->selected_menu);
        }
    }
    else if (theMenus->array_menu[0]->start_the_game == 1 && theMenus->array_menu[2]->start_the_game != -1) //pause menu
    {
        if (IsKeyPressed(KEY_P))
        {
            theMenus->array_menu[2]->start_the_game = 0; //menu pause
        }
        else if(theMenus->array_menu[2]->start_the_game == 0)
        {
            if (theMenus->selected_menu == 0)//on retourne au menu principal
            {
                draw_menu_pause(theMenus->array_menu[2], theMenus->framesCounter);
                update_menu_pause(theMenus->array_menu[2], &theMenus->selected_menu);
            }
            else if (theMenus->selected_menu == 1)//on lance le menu help
            {
                draw_menu_help(theMenus->array_menu[1], theMenus->framesCounter);
                if (IsKeyPressed(KEY_ENTER))
                    theMenus->selected_menu = 0;
            }
        }
    }
    theMenus->framesCounter++;
}

void draw_menu_parameter(menu * aMenu, int framesCounter)
{
    int fontSize = 18;
    ClearBackground(Fade(BLACK, 0.5));
    DrawText("Largeur du plateau (min 4, max 60) : ", 20, 10, fontSize, WHITE);
    draw_box(aMenu->array_box[0], framesCounter);
    DrawText("Hauteur du plateau (min 4, max 60) : ", 20, 130, fontSize, WHITE);
    draw_box(aMenu->array_box[1], framesCounter);
    DrawText("Taille de l'aura (min 1, max (min(Hauteur,Largeur)-1)/2)  : ", 20, 250, fontSize, WHITE);
    draw_box(aMenu->array_box[2], framesCounter);
    DrawText("Pourcentage de murs (min 0, max 30) :", 20, 370, fontSize, WHITE);
    draw_box(aMenu->array_box[3], framesCounter);
    draw_box(aMenu->array_box[4], framesCounter);

    if(checkArg(aMenu->array_box[0].value, aMenu->array_box[1].value,
                aMenu->array_box[2].value, aMenu->array_box[3].value) != 0)
    {
        DrawText("Paramètres incorrects!", 20, 570, fontSize * 2, RED);
    }

}

void modify_field_box(box * aBox)
{
    int key = GetKeyPressed();

    //Seulement entre 48 et 57 pour récupérer uniquement des chiffres cf table ASCII
    if ((key >= 48) && (key <= 57) && (aBox->letterCount < 2))
    {
        
        aBox->text[aBox->letterCount] = (char)key;
        aBox->text[aBox->letterCount + 1] = '\0';
        
        aBox->letterCount++;
        aBox->value = TextToInteger(aBox->text);
        
    }
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        aBox->letterCount--;
        if (aBox->letterCount < 0) aBox->letterCount = 0;
        aBox->text[aBox->letterCount] = '\0';
        aBox->value = TextToInteger(aBox->text);
    }
}



void update_menu_parameter(menus * menus, menu * aMenu, int * selected_menu)
{
    update_menu_selection(aMenu);
    int boxSelected = aMenu->selected_box;
    
    menus->netWorldWidth = aMenu->array_box[0].value;
    menus->netWorldHeight = aMenu->array_box[1].value;
    menus->aura = aMenu->array_box[2].value;
    menus->wallPeercentage = aMenu->array_box[3].value;

    if (boxSelected < 4)//parameter
        modify_field_box(&(aMenu->array_box[aMenu->selected_box]));
    else if (IsKeyPressed(KEY_ENTER)
             && checkArg(menus->netWorldWidth, menus->netWorldHeight,
                         menus->aura, menus->wallPeercentage) == 0)
        *selected_menu = 0;
}



void destroyMenus(menus * theMenus)
{
  free(theMenus->array_menu[0]->array_box);
  free(theMenus->array_menu[0]);
  free(theMenus->array_menu[1]->array_box);
  free(theMenus->array_menu[1]);
  free(theMenus->array_menu[2]->array_box);
  free(theMenus->array_menu[2]);
  free(theMenus->array_menu[3]->array_box[0].text);
  free(theMenus->array_menu[3]->array_box[1].text);
  free(theMenus->array_menu[3]->array_box[2].text);
  free(theMenus->array_menu[3]->array_box[3].text);
  free(theMenus->array_menu[3]->array_box);
  free(theMenus->array_menu[3]);
  free(theMenus->array_menu);
  free(theMenus);
}

void resetMenus(menus * theMenus)
{
    theMenus->array_menu[0]->start_the_game = 0;
    theMenus->array_menu[2]->start_the_game = 1;
}