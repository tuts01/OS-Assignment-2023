/**
 * @file            cust.c
 * @author          Tristan S. Tutungis
 * @date_created    18/04/2023
 * @last_modified   
 * @description     Contains a function that periodically reads an entry from
 *                  file and adds it to a FIFO queue
*/

#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include "cust.h"
#include "queue.h"
#include "fileio.h"

extern long a_time;
extern pthread_mutex_t queue_mutex;
extern pthread_mutex_t file_mutex;

void* customer(void *queue_ptr)
{
    FILE* c_file = open(INFILENAME, "r");
    FILE* r_log = open(OUTFILENAME, "a");
    bool done = false;
    queue_t* queue = (queue_t*)queue_ptr;
    cust_t* cust;
    char service;
    
    while (!done)
    {
        cust = readCustFile(c_file, &done);
        
        if(cust = NULL) done = true;
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

            struct tm* curtime = localtime(time(NULL));

            pthread_mutex_lock(&queue_mutex);

            fprintf(r_log, "%s\n%d: %c\nArrival Time: %d:%d:%d\n%s", DIVIDER,
                    cust->custNo, service, curtime->tm_hour, curtime->tm_min,
                    curtime->tm_sec, DIVIDER);
            add(queue, cust);

            pthread_mutex_unlock(&queue_mutex);
            sleep(a_time);
        }
    }
}