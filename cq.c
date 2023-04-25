/**
 * @file            cq.c
 * @author          Tristan S. Tutungis
 * @date_created    29/03/2023
 * @last_modified   25/04/2023 20:43
 * @description     
*/

#include <stdio.h>
#include <stdlib.h>
#include "cust.h"

long q_size,   //Queue Size
     a_time,   //Arrival Time
     d_time,   //Deposit Time
     w_time,   //Withdrawal Time
     i_time;   //Information Time

int main(int argc, char** argv)
{
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
    if(q_size <= 0)
    {
        fputs("Error: Invalid Queue Size\nUsage:\ncq <queue size> <time to arrive> <deposit time> <withdrawal time> <information time>\n", stderr);
        return EXIT_FAILURE;
    }

    a_time = strtol(argv[2], NULL, 10);
    if(a_time <= 0)
    {
        fputs("Error: Invalid Arrival Time\nUsage:\ncq <queue size> <time to arrive> <deposit time> <withdrawal time> <information time>\n", stderr);
        return EXIT_FAILURE;
    }

    d_time = strtol(argv[3], NULL, 10);
    if(d_time <= 0)
    {
        free(q_size);
        free(a_time);
        free(d_time);
        fputs("Error: Invalid Deposit Time\nUsage:\ncq <queue size> <time to arrive> <deposit time> <withdrawal time> <information time>\n", stderr);
        return EXIT_FAILURE;
    }

    w_time = strtol(argv[4], NULL, 10);
    if(w_time <= 0)
    {
        free(q_size);
        free(a_time);
        free(d_time);
        free(w_time);
        fputs("Error: Invalid Withdrawal Time\nUsage:\ncq <queue size> <time to arrive> <deposit time> <withdrawal time> <information time>\n", stderr);
        return EXIT_FAILURE;
    }

    i_time = strtol(argv[5], NULL, 10);
    if(d_time <= 0)
    {
        free(q_size);
        free(a_time);
        free(d_time);
        free(w_time);
        free(i_time);
        fputs("Error: Invalid Information Time\nUsage:\ncq <queue size> <time to arrive> <deposit time> <withdrawal time> <information time>\n", stderr);
        return EXIT_FAILURE;
    }

    cust_t* c_queue = (cust_t*)malloc(q_size * sizeof(cust_t));

    return EXIT_SUCCESS;
}