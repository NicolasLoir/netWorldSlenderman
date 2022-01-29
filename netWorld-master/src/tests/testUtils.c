#include "../includes/utils.h"
#include <assert.h>
#include <stddef.h>

static int compareInts(void * dataA, void * dataB)
{
  int intA = *((int *) dataA);
  int intB = *((int *) dataB);
  if(intA < intB)
  {
    return -1;
  } else if(intA > intB)
  {
    return 1;
  } else {
    return 0;
  }
}

void testQueuePriority(void)
{
  queue * testQueue = queueCreate(&compareInts);
  int ints[] = {7, 15, 3, 2};
  queueAdd(testQueue, ints + 0);
  queueAdd(testQueue, ints + 1);
  queueAdd(testQueue, ints + 2);

  void * ejected;
  ejected = queueRemoveLast(testQueue);
  assert(ejected == ints + 2);
  ejected = queueRemoveLast(testQueue);
  assert(ejected == ints + 0);

  queueAdd(testQueue, ints + 3);
  ejected = queueRemoveLast(testQueue);
  assert(ejected == ints + 3);
  ejected = queueRemoveLast(testQueue);
  assert(ejected == ints + 1);
  ejected = queueRemoveLast(testQueue);
  assert(ejected == NULL);

  queueDestroy(testQueue);
}

void testQueueSimple(void)
{
  queue * testQueue = queueCreate(NULL);
  int ints[] = {7, 15, 3, 2};
  queueAdd(testQueue, ints + 0);
  queueAdd(testQueue, ints + 1);
  queueAdd(testQueue, ints + 2);

  void * ejected;
  ejected = queueRemoveLast(testQueue);
  assert(ejected == ints + 0);
  ejected = queueRemoveLast(testQueue);
  assert(ejected == ints + 1);

  queueAdd(testQueue, ints + 3);
  ejected = queueRemoveLast(testQueue);
  assert(ejected == ints + 2);
  ejected = queueRemoveLast(testQueue);
  assert(ejected == ints + 3);
  ejected = queueRemoveLast(testQueue);
  assert(ejected == NULL);

  queueDestroy(testQueue);
}

int main(void)
{
  testQueuePriority();
  testQueueSimple();
}
