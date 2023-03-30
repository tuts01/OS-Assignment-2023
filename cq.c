/**
 * @file            cq.c
 * @author          Tristan S. Tutungis
 * @date_created    29/03/2023
 * @last_modified   29/03/2023
 * @description     
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if(argc == 1){
        puts("Usage:\ncq <queue size> <time to arrive> <deposit time> <withdrawal time> <information time>");
        return EXIT_FAILURE;
    }
    else if(argc != 6){
        puts("Error: Invalid Number of Arguments\nUsage:\ncq <queue size> <time to arrive> <deposit time> <withdrawal time> <information time>");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}