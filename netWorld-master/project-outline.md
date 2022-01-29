# NetWord - Outline of the project

This document lists the project components as in a backlog-product from the [*SCRUM*](https://fr.wikipedia.org/wiki/Scrum_(d%C3%A9veloppement)#Glossaire) terminology.

NetWorld aims to become a KISS (keep it stupid simple) Game-engine in which the game entities interact on a world seen as a network of key positions (nodes).

The development is organized over several functionalities listed here from the most mandatory to the less important:
Each Functionnality groups several components to develop as UserStories under the responsibility of one or two main developers.

## Networld-Based functionnalities

All these functionnalities can be used for any NetWorld game and are the main points of the NetWorld game engine.

### Fct.1 - NetWorld (networld.h | node.h | edge.h)
---
- @MainDevelopers: Hugo
- @SecondaryDevelopers: Nicolas
---

NetWorld represent the center piece of the game engine. It is the programme component that glue all the others. 
It is an environment for the game entities, viewed as a planar graph modelling all the possible movements. 

- A NetWorld is composed of nodes at specific position (x,y) with a weight.
- Nodes are connected to other with edges.
- Edges can have a direction and a weight.
- An algorithm provides paths in the NetWorld between two positions (Dijkstra). 
- We can generate a regular networld with a certain amount of nodes horizontaly and verticaly.


### Fct.2 - Entities (entity.h)

---
- @MainDevelopers: Pierre
- @SecondaryDevelopers: Nicolas
---

Entities are the game element capable of actions. This functionality mainly regroups the basic interactions of those entities between them and with the NetWorld.


- An entity is at a specific node. 
- Entities can be a player, an NPC or an itemWorld. An NPC is, for example, an IA. An itemWorld can be a wall or a door.
- Entities see the different possible movements (edges from the nodes) and can try one. The movement succeed only if there is not entity of type item world (like a wall or a closed door) inside of the node.
- Entities can act on the NetWorld (change the colour of a node for instance). (to do, to pick up an item, open door)
- Entities can have a sprite that can be drawed and that handles animation
- A item map can be created to stock multiplies entites in a array


### Fct.3 - IAs and A Star (ia.h | aStar.h)
---
- @MainDevelopers: Hugo
---

The goal here is to distribute the game process.

- IAs can be launched in the background
- IAs recalculate at a given rythme the path between itself and another entity based on A Star
- IAs are aware of their world and their limits (it cannot bypass a wall)

### Fct.4 - Audio (audio.h)
---
- @MainDevelopers: Pierre
---

The goal of this module is to manage sound effects.

- You can play random step sounds when needed
- You can play, pause and stop a main music

### Fct.5 - Events (event.h)
---
- @MainDevelopers: Hugo and Pierre
---

The goal of this module is to allow the user to create and manage events easily

- The user can create and stock events throught a eventManager
- The user can play all the events in a eventManager when needed

### Fct.6 - Utilities (utils.h)
---
- @MainDevelopers: Hugo
---

The goal of this module is to provide the user with easy-to-use functions and structures

- The user can use queues, array-like structure that don't need a predefined length
- Some useful functions based on arrays are defined in this header file


## Slender-Game functionnalities

All theses functionnalites are used and created especialy for the Slender-Game.

### Fct.7 - User Interface

Severals interface has been made :

#### The menus (menu.h)
---
- @MainDevelopers: Nicolas
---

- The player starts the game with a title screen
- From the title screen, the player can see a help page, change the settings of the game and launch the game
- The player can pause and stop the game at any moment with the P key

#### The settings interface (menu.h)
---
- @MainDevelopers: Guillaume
---

- The player can change several settings of the game
- These settings are saved and reused when the player goes back to this menu

#### The game interface (game.h)
---
- @MainDevelopers: Nicolas
- @SecondaryDevelopers: Hugo and Quentin
---

- Animations and textures (Quentin)
  - Definition of the graphial chart of the game
  - Recherche and creation of the vectors used by the animation
  - Development of the walking animation
  - Development of a following camera
  - Development of a zoom/unzoom
  - Development of a 4-directional deplacement : Up, Down, Left, Right
  - Pause in the animation added
  - Textures added

- Representation of the NetWorld (Nicolas and Hugo)
  - A netWorld can be reproduced graphically
  - The position of the sprite of the player is associated to a node in the netWorld
  - Collisions through border and wall are handled
  - The player, the walls, the slenderman and his aura are all represented

## Fct.8 - The game module (game.h | gameEntity.h)
---
- @MainDevelopers: Hugo
---

This module contains the declaration of a game and define several functions to manage the game through time

- Update the game based on the IA and the input of player
- Check if a game is done or not
- Generate a game that is not impossible for the player
- Create entities especialy made for the Slender-Game

## Fct.9 - Game-play
---
- @MainDevelopers: Guillaume
- @SecondaryDevelopers: Quentin
---

The Slender-Game has a game design defined and implemented in the game (see README.md)


## Others functionnality

These points are made for both the Game Engine and the Slenderman game.

## Fct.10 - Project Framing.
---
- @MainDevelopers: Guillaume
- @SecondaryDevelopers: Arthur
---

This functionality cover a framework for the team of developers.

- Developers can communicate with others (discord, ...)
- A developer can share a working directory (git, gitlab, ...)
- Hello World’s programmes can be completed and executed.
- Everyone can refer to documentation.
- A solution for Unit Test is operational.



## Fct.11 - Robust Development environment
---
- @MainDevelopers: Hugo
- @SecondaryDevelopers: Pierre 
---

- All developers can refer to an documentation and follows good practice and standards.
- Developers would use a proper C unit-test framework.