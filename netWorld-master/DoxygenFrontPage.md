# NetWorld

## Introduction

NetWorld is a game engine made in C and with the raylib library. The main point of a game made with his engine is the NetWorld.

A NetWorld is a graph-based representation of a world. It contains node, and edges that link these nodes.

This game engine contains header file that allows use to (non-exhausive list) :

* Create and manage a NetWorld
* Add entities that belongs in this NetWorld
* Create and manage entity-following IA throughout multi-threaded process
* Play music and audio sound
* Create a event manager that can launch differents functions when needed

## How to use this documentation?

This documentation contains the source code of the game engine and the source code of a demonstration game "Slenderman".

We advise you to read the documentation of the header files. Theses files can be found in Files/Files List/src/includes. Documentation of the source files shall be used especialy if you want to see the static functions declarations.

All these headers files are especially made for the slenderman game and shall not be used for another NetWorld game

* game.h
* gameEntity.h
* menu.h

All the others headers file could be used for any NetWorld game and are the mains points of the NetWorld engine :

* aStar.h
* audio.h
* edge.h
* entity.h
* event.h
* ia.h
* networld.h
* node.h
* utils.h

There is a lot of files, but each file is made for one purpose.

You can also read the documentation based on the data structures used, functions, macros... To do so, use the search bar and the two box "Data Structures" and "Files" on the top of this website.
