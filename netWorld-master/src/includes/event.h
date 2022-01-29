/**
 * @file event.h
 *
 * @brief Header file of the event module
 *
 * This module allows the user to create events and eventManager.
 *
 * An event is a struct containing a pointer to a data and a function to call with this pointer
 *
 * An eventManager is a queue containing only events. It can launch all the events contained when needed
 *
 * This file can be used by ANY NetWorld game
 */

#ifndef EVENT_H
#define EVENT_H

#include "utils.h"

/**
 * Structure declaration of an event
 */
typedef struct {
  void * data; /**< Pointer to the first data */
  void * (*event) (void * data); /**< Function to launch */
} event;

/**
 * Structure declaration of an event manager
 */
typedef struct {
  queue * eventQueue; /**< An event queue */
} eventManager;

/**
 * Create a event manager
 * @return A pointer to the event manager
 */
eventManager * eventManagerCreate(void);

/**
 * Destroy a event manager
 * @param eventM A pointer to the event manager
 */
void eventManagerDestroy(eventManager * eventM);

/**
 * Add a event into the eventManager
 * @param eventM The event manager
 * @param data A pointer to the data
 * @param event A pointer to the function of the event using this data
 */
void eventManagerAdd(eventManager * eventM,
                     void * data,
                     void * (*event) (void * data));

/**
 * Launch all events contained in a eventManager
 * @param eventM A pointer to the eventManager
 */
void eventManagerLaunch(eventManager * eventM);

#endif
