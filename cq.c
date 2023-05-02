/**
 * @file            cq.c
 * @author          Tristan S. Tutungis
 * @date_created    29/03/2023
 * @last_modified   25/04/2023 20:43
 * @description     
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include "cust.h"
#include "queue.h"
#include "fileio.h"
#include "teller.h"
#include "misc.h"

long q_size,   //Queue Size
     a_time,   //Arrival Time
     d_time,   //Deposit Time
     w_time,   //Withdrawal Time
     i_time;   //Information Time

int running_tellers = 0; //Number of running teller threads
_Bool done; //Boolean to indicate whether all customers have been read

pthread_mutex_t num_mutex;
pthread_mutex_t queue_mutex;
pthread_mutex_t file_mutex;
pthread_mutex_t sig_mutex;
pthread_cond_t teller_cond;

int main(int argc, char** argv)
{
    pthread_t cust_thread;
    pthread_t teller_thread[4];

    num_mutex = PTHREAD_MUTEX_INITIALIZER;
    queue_mutex = PTHREAD_MUTEX_INITIALIZER;
    file_mutex = PTHREAD_MUTEX_INITIALIZER;
    sig_mutex = PTHREAD_MUTEX_INITIALIZER;
    teller_cond = PTHREAD_COND_INITIALIZER;

    if(argc == 1)
    {
        fputs("Usage:\ncq <queue size> <time to arrive> <deposit time> <withdrawal time> <information time>\n", stderr);
        return EXIT_FAILURE;
    }
    else if(argc != 6)
    {
        fputs("Error: Invalid Number of Arguments\nUsage:\ncq <queue size> <time to arrive> <deposit time> <withdrawal time> <information time>\n", stderr);
        return EXIT_FAILURE;
    }

    q_size = strtol(argv[1], NULL, 10);
    if(q_size <= 0) return printerr("Invalid Queue Size");

    a_time = strtol(argv[2], NULL, 10);
    if(a_time <= 0) return printerr("Invalid Arrival Time");

    d_time = strtol(argv[3], NULL, 10);
    if(d_time <= 0) return printerr("Invalid Deposit Time");

    w_time = strtol(argv[4], NULL, 10);
    if(w_time <= 0) return printerr("Invalid Withdrawal Time");

    i_time = strtol(argv[5], NULL, 10);
    if(d_time <= 0) return printerr("Invalid Information Time");

    queue_t* c_queue = create_queue(q_size);

    pthread_create(&cust_thread, NULL, customer, c_queue);

    for(int i = 0; i < 4; i++) pthread_create(&teller_thread[i], NULL, teller, NULL);

    destroy_queue(c_queue);

    return EXIT_SUCCESS;
}