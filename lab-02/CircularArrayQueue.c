// Implementation of the Queue ADT using a circular array

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

#define DEFAULT_SIZE 16 // DO NOT change this line

// DO NOT modify this struct
struct queue {
	Item *items;
	int size;
	int capacity;
	int frontIndex;
};

/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}

	q->items = malloc(DEFAULT_SIZE * sizeof(Item));
	if (q->items == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}

	q->size = 0;
	q->capacity = DEFAULT_SIZE;
	q->frontIndex = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	free(q->items);
	free(q);
}

/**
 * Increases the capacity of the array.
 */

static void increaseCirArrayCapacity(Queue q);

static void increaseCirArrayCapacity(Queue q) {
	q->items = realloc(q->items, 2 * q->capacity *sizeof(Item));

	//Need to fix the sort of the items after doubling the size of the array
	for (int i = 0; i < q->frontIndex; i++) {
		q->items[q->capacity + i] = q->items[i]; //moving the values before the frontIndex
	}
	
	//If items is empty then there is a failure. 
	if (q->items == NULL) {
		exit(EXIT_FAILURE);
	}
	q->capacity *= 2;
}


/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {
	// TODO
	// if queue is full, need to double its size using the function declared above.
	if (q->size ==  q->capacity) {
		increaseCirArrayCapacity(q); 
	}
	// Now need to assign it to the back of the list
	int backList = (q->size + q->frontIndex) % q->capacity;
	q->items[backList] = it;
	q->size++;
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	// TODO

	// assign the item to be removed by oldIt.
	Item it = q->items[(q->frontIndex)];
	//new front index, thus we remove the item from the "list" even though it is still in the array.
	q->frontIndex = (q->frontIndex + 1) % q->capacity; 
	q->size--;

	return it;
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueueFront(Queue q) {
	assert(q->size > 0);

	return q->items[q->frontIndex];
}

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q) {
	return q->size;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q) {
	return q->size == 0;
}

/**
 * Prints the queue to the given file with items space-separated
 */
void QueueDump(Queue q, FILE *fp) {
	for (int i = q->frontIndex, j = 0; j < q->size; i = (i + 1) % q->capacity, j++) {
		fprintf(fp, "%d ", q->items[i]);
	}
	fprintf(fp, "\n");
}

/**
 * Prints out information for debugging
 */
void QueueDebugPrint(Queue q) {
	QueueEnqueue(q, 2);
	QueueEnqueue(q, 5);
	printf("%d, %d", q->items[0], q->items[0]);
}

