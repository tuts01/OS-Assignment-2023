/**
 * @file            cq.c
 * @author          Tristan S. Tutungis
 * @date_created    29/03/2023
 * @last_modified   25/04/2023 20:43
 * @description     Program which simulates the producer-consumer problem in
 *                  the context of bank tellers and customers. It uses POSIX
 *                  threads for multithreading and mutual exclusion.
 *                  NOTE: This program is designed to run on Linux and may or
 *                  may not work on macOS due to differences in the
 *                  implementation of certain non-C-standard components.
*/

/* Include statements */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "cust.h"
#include "queue.h"
#include "teller.h"
#include "misc.h"

/* Global Variables */
long q_size;   //Queue Size
long a_time;   //Arrival Time
long d_time;   //Deposit Time
long w_time;   //Withdrawal Time
long i_time;   //Information Time

int running_tellers = 0; //Number of running teller threads
int served[4]; //Number of customers that each teller has served
_Bool done; //Boolean to indicate whether all customers have been read

pthread_mutex_t num_mutex = PTHREAD_MUTEX_INITIALIZER;      //Mutex for editing the number of running teller threads
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;    //Mutex for manipulating the queue
pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;     //Mutex for writing to "r_log" file
pthread_cond_t teller_cond = PTHREAD_COND_INITIALIZER;      //Conditional variable for a teller to block while there are no customers in the queue

/* Main function */
int main(int argc, char** argv)
{
    pthread_t cust_thread;      //Customer thread
    pthread_t teller_thread[4]; //Teller threads

    /* Ensure the correct number of arguments were passed to the program, and
       sanitise them - all must be positive integers */

    //No arguments given
    if(argc == 1) return printerr("No arguments given");

    //Incorrect number of arguments given
    if(argc != 6) return printerr("Invalid Number of Arguments");

    //Invalid queue size
    q_size = strtol(argv[1], NULL, 10);
    if(q_size <= 0) return printerr("Invalid Queue Size");

    //Invalid arrival time
    a_time = strtol(argv[2], NULL, 10);
    if(a_time <= 0) return printerr("Invalid Arrival Time");

    //Invalid deposit time
    d_time = strtol(argv[3], NULL, 10);
    if(d_time <= 0) return printerr("Invalid Deposit Time");

    //Invalid withdrawal time
    w_time = strtol(argv[4], NULL, 10);
    if(w_time <= 0) return printerr("Invalid Withdrawal Time");

    //Invalid information time
    i_time = strtol(argv[5], NULL, 10);
    if(d_time <= 0) return printerr("Invalid Information Time");

    //Initialise the queue
    queue_t* c_queue = create_queue(q_size);

    //Launch the customer() thread
    pthread_create(&cust_thread, NULL, customer, c_queue);

    //Launch all the teller() threads THEN join them
    for(int i = 0; i < 4; i++) pthread_create(&teller_thread[i], NULL, teller, c_queue);
    for(int i = 0; i < 4; i++) pthread_join(teller_thread[i], NULL);

    //Free up memory used for queue - no longer needed
    destroy_queue(c_queue);

    return EXIT_SUCCESS;
}