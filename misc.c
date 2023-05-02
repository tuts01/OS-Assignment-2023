//
// Created by Tristan on 1/5/2023.
//

#include <stdio.h>
#include <stdlib.h>

char* get_time(void)
{
    time_t time = time(NULL);
    struct tm* start_time = localtime(&time);
    char* str = (char*)calloc(9, sizeof(char));
    sprintf(str, "%d:%d:%d", curtime->tm_hour, curtime->tm_min, curtime->tm_sec);
    return str;
}

int printerr(char* errstr)
{
    fprintf(stderr, "Error: %s\nUsage:\ncq <queue size> <time to arrive> <deposit time> <withdrawal time> <information time>\n", errstr);
    return EXIT_FAILURE;
}