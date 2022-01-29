/**
 * @file utils.h
 *
 * @brief Headef file of the utils module
 *
 * The utils module is a header with various declaration useful for a lot of things
 *
 * This module can be used by any NetWorld game
 */

#ifndef UTILS_H
#define UTILS_H

/**
 * Structure representing a queue
 */
typedef struct {
  void ** array; /**< Array of pointer to things */
  int numberOfElements; /**< Number of element actually in the queue */
  int maxSize; /**< The maximal size of the queue before realloc */
  int (*comparator) (void * dataA, void * dataB); /**< Compoarator function */
} queue;

/**
 * Create a empty queue
 * A QUEUE CONTAINS ONLY POINTERS
 * @param comparator A function comparing two elements of the array. It return a negative number if dataA < dataB, a positive number if dataA > dataB, 0 if they are equals. Give NULL if you want a simple queue
 * @return A empty queue 
 */
queue * queueCreate(int (*comparator) (void * dataA, void * dataB));

/**
 * Add an element in the queue
 * @param queue A pointer to the queue
 * @param elem The element to add
 */
void queueAdd(queue * queue, void * elem);

/**
 * Remove the last element of the queue and return it
 * @param queue A pointer to the queue
 * @return The last element of the queue, NULL if the queue is empty
 */
void * queueRemoveLast(queue * queue);

/**
 * Destroy the queue from the memory
 * @param queue A pointer to the queue
 */
void queueDestroy(queue * queue);

/**
 * Destroy the queue from the memory, but return an array containing all the elements of the queue.
 * This array shall be destroyed by the user when it won't be needed anymore
 * @param queue A pointer to the queue
 * @return An array containg all the elements of the queue
 */
void * queueConvertToArray(queue * queue);

/**
 * Destroy a previousely converted array from the memory
 * @param array A pointer to the array
 */
#define destroyArray(array) free(array)

/**
 * Check if the data is present in the queue
 * @param queue A pointer to the queue
 * @param data A pointer to the data
 * @return If the data is in the queue
 */
int queueContains(queue * queue, void * data);

/**
 * Get the index of a pointer in a array of pointer
 * @param tab The array of pointer
 * @param value The value searched
 * @return The index of the value in the array
 */
int getIndex(void * tab, void * value);

/**
 * Reverse an array of pointer up to a certain value
 * @param arrayOfPointer The array of pointer
 * @param endOfArray The furthest value of the array
 */
void reverseArrayOfPointer(void * arrayOfPointer, void * endOfArray);

/**
 * This function search the index i of the lowest numble in array for whose the
 * value pArray[i] is not NULL
 * @param array An array of double values
 * @param pArray An array of pointers
 * @param arraySize The size of both arrays
 * @return the index i of the lowest numble in array for whose the value pArray[i] is not NULL
 */
int getIndexOfMinimal(double * array, void * pArray, int arraySize);

/**
 * Return the color red with the alpha value given as a parameter
 * @param a The transpareny value (0-255)
 */
#define RED_ALPHA(a) (Color){ 230, 41, 55, (a)}

#endif
