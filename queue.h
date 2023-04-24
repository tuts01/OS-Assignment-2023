/**
 * @file            queue.h
 * @author          Tristan S. Tutungis
 * @date_created    22/04/2023
 * @last_modified   22/04/2023 22:08
 * @description     Contains a struct that represents a queue of customers,
 *                  allowing it to be passed to a pthread function
*/

#ifndef QUEUE_H
#define QUEUE_H

#include "cust.h"

typedef struct
{
    int queue_size; //Queue size
    cust_t* cust_queue; //Queue
} queue_t;

#endif