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
#include <stdlib.h>
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
extern pthread_mutex_t queue_mutex;
extern pthread_mutex_t file_mutex;
extern pthread_mutex_t sig_mutex;
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
        cust = readCustFile(c_file, &done);

        //If NULL is returned, EOF has been reached
        //TODO: Fix this if-else block as it may cause issues?
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

            //Add customer to the queue
            //TODO: See TODO entry in teller.
            pthread_mutex_lock(&queue_mutex);
            add_queue(queue, cust);
            pthread_mutex_unlock(&queue_mutex);

            //Signal to a teller that a customer is ready to be served
            //TODO: This could be improved.
            pthread_mutex_lock(&sig_mutex);
            pthread_cond_signal(&teller_cond);
            pthread_mutex_unlock(&sig_mutex);

            sleep(a_time);//Wait 'm' seconds before continuing
        }
    }

    return NULL; //Nothing to return
}