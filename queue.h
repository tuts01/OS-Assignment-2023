/**
 * @file            queue.h
 * @author          Tristan S. Tutungis
 * @date_created    22/04/2023
 * @last_modified   02/05/2023 10:44
 * @description     Contains a struct that represents a queue of customers,
 *                  allowing it to be passed to a pthread function. It also
 *                  contains functions required to manipulate the queue.
*/

#ifndef QUEUE_H
#define QUEUE_H

#include "cust.h"

/**
 * @struct      queue_t
 * @purpose     Structure representing a FIFO queue - contains the size of the
 *              queue, the number of elements in the queue, and the array
 *              representing the queue itself.
*/
typedef struct
{
    int queue_size; //Queue size
    int num; //Number of elements in the queue
    cust_t** cust_queue; //Queue
} queue_t;

/**
 * @function    create_queue
 * @returns     queue (queue_t*) - pointer to the queue itself
 * @purpose     Creates a queue in the form of an array and returns it to the
 *              calling function.
*/
queue_t* create_queue(int size);

/**
 * @function    destroy_queue
 * @purpose     Deallocates and destroys the queue.
*/
void destroy_queue(queue_t* queue);

/**
 * @function    add_queue
 * @purpose     Adds an element to the queue
*/
void add_queue(queue_t* queue, cust_t* customer);

/**
 * @function    remove_queue
 * @returns     customer (cust_t*) - pointer to the customer removed
 * @purpose     Creates a queue in the form of an array and returns it to the
 *              calling function.
*/
cust_t* remove_queue(queue_t* queue);

#endif