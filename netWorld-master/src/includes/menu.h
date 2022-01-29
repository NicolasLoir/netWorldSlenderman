
/**
 * @file menu.h
 *
 * @brief Header file of the menu module
 *
 * The menu module consist of create all menu needed for the game
 *
 * This module shall not used by another NetWorld game
 */

#ifndef menu_H
#define menu_H
#include "raylib.h"

/**
 * The structure of box.
 */
typedef struct Str_box box;
struct Str_box
{
    Rectangle rec; /**< The geometric shape of the box */
    char * text; /**< Array of char, text of the box */
    int is_selected; /**< to know if the outline color will blink */
    int font_size; /**< Font size of the text */
    Color main_color; /**< Color of inside the box */
    Color border_color; /**< Outline color */
    int padding_left; /**< Padding between the left part of the box and the text */
    int is_box_field;
    int letterCount;    //compte le nombre ce caractères déjà dans le champ -> pour nous tout est inférieur à 100 donc max 2 caractères + 1 pour le '\0' 
    int value;          //même chose que dans char * text mais en entier (on aura que des valeurs entières)
    
};

/**
 * Structure representing a menu
 */
typedef struct Str_menu menu;
struct Str_menu
{
    box * array_box; /**< Array of pointers to the box of the menu */
    int size_menu; /**< Number of box in the menu */
    int selected_box; /**< To know wich action to perform*/
    int start_the_game; /**< Usefull inside the main loop*/
};


/**
 * Structure representing the whole menu
 */
typedef struct Str_menus menus;
struct Str_menus
{
    
    menu ** array_menu; /**< Array of pointers to the menu of the struct */
    int nb_menu; /**< Number of menu in the struct */
    int selected_menu; /**< the menu selected. 0 for the main menu, 1 for the help menu and 2 for the pause menu. */
    int framesCounter;/**< An int to make the selected box blink */
    int netWorldWidth; /**<  The netWorld width */
    int netWorldHeight; /**<  The netWorld height */
    int aura; /**< The aura range of the slenderman */
    int wallPeercentage; /**< The peercentage of wall in the netWorld */
};

/**
 * Draw a box
 * @param aBox The box
 * @param framesCounter An int to make the selected box blink
 */
void draw_box(box aBox, int framesCounter);

/**
 * Retrun the main menu
 * @param width A reduction ratio according to the size of the window
 * @param height A reduction ratio according to the size of the window
 * @return the main menu
 */
menu * create_menu_principal(int width, int height);

/**
 * Retrun the help menu
 * @param width A reduction ratio according to the size of the window
 * @param height A reduction ratio according to the size of the window
 * @return the help menu
 */
menu * create_menu_help(int width, int height);

/**
 * Retrun the pause menu
 * @param width A reduction ratio according to the size of the window
 * @param height A reduction ratio according to the size of the window
 * @return the pause menu
 */
menu * create_menu_pause(int width, int height);

/**
 * Return the parameter menu
 * @param width the width of the netWorld
 * @param height the height of the netWorld
 * @param aura the aura range
 * @param wallPeercentage the peercentage of wall in the map
 * @return the parameter menu
 */
menu * create_menu_parameter(int width, int height, int aura, int wallPeercentage);



/**
 * draw all box of a menu
 * @param aMenu the menu selected
 * @param framesCounter An int to make the selected box blink
 */
void draw_menu_all_box(menu * aMenu, int framesCounter);

/**
 * draw the principal menu
 * @param aMenu the menu selected
 * @param framesCounter An int to make the selected box blink
 */
void draw_menu_principal(menu * aMenu, int framesCounter);

/**
 * draw the help menu
 * @param aMenu the menu selected
 * @param framesCounter An int to make the selected box blink
 */
void draw_menu_help(menu * aMenu, int framesCounter);

/**
 * draw the pause menu
 * @param aMenu the menu selected
 * @param framesCounter An int to make the selected box blink
 */
void draw_menu_pause(menu * aMenu, int framesCounter);

/**
 * draw the parameter menu
 * @param aMenu the menu selected
 * @param framesCounter An int to make the selected box blink
 */
void draw_menu_parameter(menu * aMenu, int framesCounter);

/**
 * Update the hoover of the box of the menu. When we use the arrow, the selected box changes.
 * @param aMenu the menu selected
 */
void update_menu_selection(menu * aMenu);

/**
 * Update the principal menu.
 * @param aMenu the menu selected
 * @param selected_menu the menu selected. 0 for the main menu, 1 for the help menu and 2 for the pause menu.
 * @param repeatGame An int to lunch the game one more time, inside the main loop
 */
void update_menu_principal(menu * aMenu, int * selected_menu, int * repeatGame);

/**
 * Update the pause menu.
 * @param aMenu the menu selected
 * @param selected_menu the menu selected. 0 for the main menu, 1 for the help menu and 2 for the pause menu.
 */
void update_menu_pause(menu * aMenu, int * selected_menu);

/**
 * Update the parameter menu. Need to implement more
 * @param menus the menus
 * @param aMenu the menu selected
 * @param selected_menu the menu selected. 0 for the main menu, 1 for the help menu and 2 for the pause menu.
 */
void update_menu_parameter(menus * menus, menu * aMenu, int * selected_menu);

/**
 * Return All the menus for the game
 * @param width the width of the netWorld
 * @param height the height of the netWorld
 * @param aura the aura range
 * @param wallPeercentage the peercentage of wall in the map
 * @return the whole menu
 */
menus * create_menus(int width, int height,
                     int aura, int wallPeercentage);

/**
 * Update the whole menu of the game
 * @param theMenus the whole menu
 * @param repeatGame An int to lunch the game one more time, inside the main loop
 */
void updateMenus(menus * theMenus, int * repeatGame);

/**
 * Free the whole menu
 * @param theMenus the whole menu
 */
void destroyMenus(menus * theMenus);

/**
 * Reset all menus as if they were just created
 * @param theMenus The menus
 */
void resetMenus(menus * theMenus);

#endif