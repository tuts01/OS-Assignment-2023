/**
 * @file            cust.c
 * @author          Tristan S. Tutungis
 * @date_created    18/04/2023
 * @last_modified   
 * @description     Contains a function that periodically reads an entry from
 *                  file and adds it to a FIFO queue
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include "cust.h"
#include "queue.h"
#include "fileio.h"
#include "misc.h"

extern long a_time;
extern bool done;
extern pthread_mutex_t queue_mutex;
extern pthread_mutex_t file_mutex;
extern pthread_mutex_t sig_mutex;
extern pthread_cond_t teller_cond;

void* customer(void *queue_ptr)
{
    FILE* c_file = open(INFILENAME, "r");
    FILE* r_log = open(OUTFILENAME, "a");
    done = false;
    queue_t* queue = (queue_t*)queue_ptr;
    cust_t* cust;
    char service;
    
    while (!done)
    {
        cust = readCustFile(c_file, &done);
        
        if(cust == NULL) done = true;
        else
        {
            switch(cust->service)
            {
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

            cust->arrivalTime = get_time()

            pthread_mutex_lock(&file_mutex);
            fprintf(r_log, "%s\n%ld: %c\nArrival Time: %s\n%s\n", DIVIDER,
                    cust->custNo, service, cust->arrivalTime, DIVIDER);
            fflush(r_log);
            pthread_mutex_unlock(&file_mutex);

            pthread_mutex_lock(&queue_mutex);
            add(queue, cust);
            pthread_mutex_unlock(&queue_mutex);

            pthread_mutex_lock(&sig_mutex);
            pthread_cond_signal(&teller_cond);
            pthread_mutex_unlock(&sig_mutex);

            sleep(a_time);
        }
    }
}