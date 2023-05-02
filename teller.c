/**
 * @file            teller.h
 * @author          Tristan S. Tutungis
 * @date_created    1/05/2023
 * @last_modified
 * @description     Contains a function representing a teller
*/

#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include "teller.h"
#include "queue.h"
#include "misc.h"

extern pthread_mutex_t queue_mutex;
extern pthread_mutex_t file_mutex;
extern pthread_mutex_t sig_mutex;
extern pthread_cond_t teller_cond;

void* teller(void* queue_ptr)
{
    queue_t* queue = (queue_t*)queue_ptr;
    FILE* r_log = open(OUTFILENAME, "a");
    char* start_time = get_time();

    while(!done)
    {
        pthread_mutex_lock(&sig_mutex);
        pthread_cond_wait(&teller_cond);
        pthread_mutex_lock(&sig_mutex);

        pthread_mutex_lock(&queue_mutex);
        cust *cust = remove_queue(queue);
        pthread_mutex_unlock(&queue_mutex);

        pthread_mutex_lock(&file_mutex);
        fprintf(r_log, "Teller: %d\nCustomer: %d\nArrival Time: %s\nCompletion Time: %s\n");

    }
    return NULL;
}
