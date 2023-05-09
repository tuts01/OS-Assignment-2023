/**
 * @file            cust.c
 * @author          Tristan S. Tutungis
 * @date_created    18/04/2023
 * @last_modified   04/05/2023 10:55
 * @description     Contains a function that periodically reads an entry from
 *                  file and adds it to a FIFO queue
*/

/* Include Statements */
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "cust.h"
#include "queue.h"
#include "fileio.h"
#include "misc.h"

/* Externally declared global variables - see cq.c */
extern long a_time;
extern bool done;
extern int running_tellers;
extern pthread_mutex_t queue_mutex;
extern pthread_mutex_t file_mutex;
extern pthread_cond_t teller_cond;

/**
 * @function    customer
 * @returns     NULL (void*)
 * @purpose     Periodically read a list of customers from a file
*/
void* customer(void *queue_ptr)
{
    //Open input and output files for reading from and wrting to, respectively
    FILE* c_file = open(INFILENAME, "r");
    FILE* r_log = open(OUTFILENAME, "a");

    done = false;
    queue_t* queue = (queue_t*)queue_ptr;
    cust_t* cust;
    char service;

    /* Loop until EOF has been reached */
    while (!done)
    {
        //Retrieve a customer from the file
        cust = readCustFile(c_file);

        //If NULL is returned, EOF has been reached
        if(cust == NULL) done = true;
        else
        {
            //Translate the enum into a char value
            switch(cust->service) {
                case W:
                    service = 'W';
                    break;

                case D:
                    service = 'D';
                    break;

                case I:
                    service = 'I';
                    break;
            }

            //Record the arrival time
            cust->arrivalTime = get_time();

            //Write entry to file indicating that the customer has arrived
            pthread_mutex_lock(&file_mutex);
            fprintf(r_log, "%s\n%ld: %c\nArrival Time: %s\n%s\n", DIVIDER,
                    cust->custNo, service, cust->arrivalTime, DIVIDER);
            fflush(r_log);
            pthread_mutex_unlock(&file_mutex);

            //Wait if the queue is full (num == queue_size)
            while(queue->num == queue->queue_size);

            //Add customer to the queue and signal to a teller that a customer is ready to be served
            pthread_mutex_lock(&queue_mutex);
            add_queue(queue, cust);
            pthread_cond_signal(&teller_cond);
            pthread_mutex_unlock(&queue_mutex);

            sleep(a_time);//Wait 'm' seconds before continuing
        }
    }

    //Wake up any tellers that are still waiting
    while(running_tellers != 0) pthread_cond_broadcast(&teller_cond);

    //Close the file streams
    fclose(c_file);
    fclose(r_log);

    return NULL; //Nothing to return
}
