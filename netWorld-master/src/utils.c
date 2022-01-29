#include "includes/utils.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define __DEFAULT_SIZE__ 2

queue * queueCreate(int (*comparator) (void * dataA, void * dataB))
{
  queue * res = malloc(sizeof(queue));
  res->array = malloc(__DEFAULT_SIZE__ * sizeof(void *));
  res->numberOfElements = 0;
  res->maxSize = __DEFAULT_SIZE__;
  res->comparator = comparator;
  return res;
}

void queueAdd(queue * queue, void * elem)
{
  if(queue->numberOfElements == queue->maxSize) {
    queue->maxSize *= 2;
    queue->array = realloc(queue->array, sizeof(void *) * queue->maxSize);
  }

  int goalIdx;
  if(queue->comparator == NULL)
  {
    goalIdx = queue->numberOfElements;
  } else {
    goalIdx = 0;
    while(goalIdx < queue->numberOfElements
          && queue->comparator(queue->array[goalIdx], elem) < 0)
      goalIdx += 1;
    memmove(queue->array + goalIdx + 1,
            queue->array + goalIdx,
            sizeof(void *) * (queue->numberOfElements - goalIdx));
  }
  queue->array[goalIdx] = elem;
  queue->numberOfElements += 1;
}

void * queueRemoveLast(queue * queue)
{
  if(queue->numberOfElements == 0)
    return NULL;
  void * res = queue->array[0];
  queue->numberOfElements -= 1;
  memmove(queue->array,
          queue->array + 1,
          queue->numberOfElements * sizeof(void *));
  return res;
}

void queueDestroy(queue * queue)
{
  free(queue->array);
  free(queue);
}

void * queueConvertToArray(queue * queue)
{
  void * res = queue->array;
  free(queue);
  return res;
}

int queueContains(queue * queue, void * data)
{
  return getIndex(queue->array, data) < queue->numberOfElements;
}

int getIndex(void * tabOfPointer, void * value)
{
  void ** tab = (void **) tabOfPointer;
  int i = 0;
  while(tab[i] != NULL
        && tab[i] != value) i += 1;
  return i;
}

void reverseArrayOfPointer(void * arrayOfPointer, void * endOfArray)
{
  void ** array = (void **) arrayOfPointer;
  if(array != NULL) {
    int maxIdx = 0;
    while(array[maxIdx] != endOfArray) maxIdx += 1;
    for(int i = 0; i <= (maxIdx / 2); i += 1) {
      void * tmp = array[i];
      array[i] = array[maxIdx - i];
      array[maxIdx - i] = tmp;
    }
  }
}

int getIndexOfMinimal(double * array, void * pArray, int arraySize)
{
  void ** pointerArray = (void **) pArray;
  int i = 0;
  while(pointerArray[i] == NULL
        && i < arraySize)
    i += 1;
  int res = i;
  i += 1;
  while(i < arraySize) {
    if(pointerArray[i] != NULL && array[res] > array[i]) {
      res = i;
    }
    i += 1;
  }
  return res;
}
