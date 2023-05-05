/**
 * @file            teller.h
 * @author          Tristan S. Tutungis
 * @date_created    1/05/2023
 * @last_modified   3/05/2023 23:42
 * @description     Contains a function representing a teller
*/

/* Include Statements */
#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "teller.h"
#include "queue.h"
#include "misc.h"
#include "cust.h"
#include "fileio.h"

/* Externally declared global variables - see cq.c */
extern pthread_mutex_t num_mutex;
extern pthread_mutex_t queue_mutex;
extern pthread_mutex_t file_mutex;
extern pthread_mutex_t sig_mutex;
extern pthread_cond_t teller_cond;

extern int running_tellers;
extern _Bool done;

extern long a_time;
extern long d_time;
extern long w_time;
extern long i_time;

/**
 * @function    teller
 * @returns     NULL (void*)
 * @purpose     Function which simulates a bank teller - serves customers as
 *              they enter a queue
*/
void* teller(void* queue_ptr)
{
    //Queue is passed in from calling thread
    queue_t* queue = (queue_t*)queue_ptr;
    //Open "r_log" for writing (appending)
    FILE* r_log = open(OUTFILENAME, "a");
    char* start_time = get_time(); //Get the starting time

    /* Increment the number of running tellers and assign a teller number to
       the running thread. Running threads number is used to determine if a
       thread is the final teller to be terminated, and teller number is used
       as part of output to file */
    pthread_mutex_lock(&num_mutex);
    running_tellers++;
    unsigned int teller_num = running_tellers;
    pthread_mutex_unlock(&num_mutex);

    /* Keep looping until all customers are read from file (i.e. when done is
       set to true) and the queue has been emptied */
    while(!done || queue->num != 0)
    {
        /* TODO: combine sig_mutex and queue_mutex into one to prevent a potential race condition */
        /* If there are no customers in the queue, the thread is to block until
           it is signalled that a customer has arrived in the queue */
        pthread_mutex_lock(&sig_mutex);
        if(queue->num == 0) pthread_cond_wait(&teller_cond, &sig_mutex);
        pthread_mutex_lock(&sig_mutex);

        //Get the customer from the queue
        pthread_mutex_lock(&queue_mutex);
        cust_t* cust = remove_queue(queue);
        pthread_mutex_unlock(&queue_mutex);

        //Write an entry to the log file outlining that the customer has arrived
        pthread_mutex_lock(&file_mutex);
        char* response_time = get_time();
        fprintf(r_log, "Teller: %d\nCustomer: %ld\nArrival Time: %s\nResponse Time: %s\n",
                teller_num, cust->custNo, cust->arrivalTime, response_time);
        fflush(r_log);
        free(response_time);
        pthread_mutex_unlock(&file_mutex);

        //Simulate the service of the customer that has arrived
        switch(cust->service)
        {
            case W:
                sleep(w_time);
                break;

            case D:
                sleep(d_time);
                break;

            case I:
                sleep(i_time);
                break;
        }

        /* Write another entry to the log file now that the simulated operation
           has completed */
        pthread_mutex_lock(&file_mutex);
        char* completion_time = get_time();
        fprintf(r_log, "Teller: %d\nCustomer: %ld\nArrival Time: %s\nCompletion Time: %s\n",
                teller_num, cust->custNo, cust->arrivalTime, completion_time);
        fflush(r_log);
        free(completion_time);
        pthread_mutex_unlock(&file_mutex);
    }
    //TODO: Finish writing this function
    return NULL;
}
