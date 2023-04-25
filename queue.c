/**
 * @file            queue.h
 * @author          Tristan S. Tutungis
 * @date_created    24/04/2023
 * @last_modified   25/04/2023 20:17
 * @description     Contains a struct that represents a queue of customers,
 *                  allowing it to be passed to a pthread function. It also
 *                  contains functions required to manipulate the queue.
*/

#include <stdlib.h>
#include "queue.h"
#include "cust.h"

/**
 * @function    create_queue
 * @returns     queue (queue_t*) - pointer to the queue itself
 * @purpose     Creates a queue in the form of an array and returns it to the
 *              calling function.
*/
queue_t* create_queue(int size)
{
     //Allocate memory for the queue itself
    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));

    //Initialise variables of the queue
    queue->queue_size = size;
    queue->num = 0;

    //Allocate memory for the array itself - size is fixed
    queue->cust_queue = (cust_t*)malloc(size * sizeof(cust_t));

    return queue;
}

/**
 * @function    destroy_queue
 * @purpose     Deallocates and destroys the queue.
*/
void destroy_queue(queue_t* queue)
{
    //Deallocate memory for each element left in the queue, if any.
    for(int i = 0; i < queue->num; i++) free(queue->cust_queue[i]);

    free(queue->cust_queue); //Deallocate the queue array
    free(queue); //Deallocate the queue structure
}

/**
 * @function    add
 * @purpose     Adds an element to the queue
*/
void add(queue_t* queue, cust_t* customer)
{
    //Check that we haven't exceeded the maximum size of the queue
    if(queue->num < queue->queue_size)
    {
        queue->cust_queue[queue->num] = customer; //Add the customer to the queue
        queue->num++; //Increment the count
    }
}

/**
 * @function    remove
 * @returns     customer (cust_t*) - pointer to the customer removed
 * @purpose     Creates a queue in the form of an array and returns it to the
 *              calling function.
*/
cust_t* remove(queue_t* queue)
{
    cust_t* customer = queue->cust_queue[0]; //Get customer from queue

    //Move each element in the array down by an index of 1
    for(int i = 1; i < queue->num; i++)
    {
        queue->cust_queue[i-1] = queue->cust_queue[i];
    }

    queue->num--; //Decrement the count

    //Set the final element to NULL - it has been moved down already so it is no longer needed
    queue->cust_queue[queue->num] = NULL;

    return customer;
}