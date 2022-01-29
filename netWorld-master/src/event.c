#include "includes/event.h"
#include <stdio.h>
#include <stdlib.h>

eventManager * eventManagerCreate(void)
{
  eventManager * res = malloc(sizeof(eventManager));
  res->eventQueue = queueCreate(NULL);
  return res;
}

void eventManagerDestroy(eventManager * eventM)
{
  for(int i = 0; i < eventM->eventQueue->numberOfElements; i += 1)
  {
    free(eventM->eventQueue->array[i]);
  }
  queueDestroy(eventM->eventQueue);
  free(eventM);
}

void eventManagerAdd(eventManager * eventM,
                     void * data,
                     void * (*eventFunction) (void * data))
{
  event * eventToAdd = malloc(sizeof(event));
  eventToAdd->data = data;
  eventToAdd->event = eventFunction;
  queueAdd(eventM->eventQueue, eventToAdd);
}

void eventManagerLaunch(eventManager * eventM)
{
  for(int i = 0; i < eventM->eventQueue->numberOfElements; i += 1)
  {
    event * eventToLaunch = (event *) eventM->eventQueue->array[i];
    eventToLaunch->event(eventToLaunch->data);
  }
}
