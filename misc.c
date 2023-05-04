/**
 * @file            misc.c
 * @author          Tristan S. Tutungis
 * @date_created    01/05/2023
 * @last_modified   04/05/2023 16:01
 * @description     Contains miscellaneous functions that don't fit anywhere else
*/

/* Include Statements */
#include <stdio.h>
#include <stdlib.h>
#include "misc.h"

/**
 * @function    get_time
 * @returns     str (char*)
 * @purpose     Returns the current time as a string in the format HH:MM:SS
*/
char* get_time(void)
{
    //Get the "current time" (seconds since the Epoch) and convert it to a string in the format "HH:MM:SS"
    time_t time = time(NULL);
    struct tm* start_time = localtime(&time);
    char* str = (char*)calloc(9, sizeof(char));
    sprintf(str, "%d:%d:%d", curtime->tm_hour, curtime->tm_min, curtime->tm_sec);
    return str;
}

/**
 * @function    printerr
 * @returns     EXIT_FAILURE (int)
 * @purpose     Print an error string and return EXIT_FAILURE
*/
int printerr(char* errstr)
{
    fprintf(stderr, "Error: %s\n%s", errstr, USAGE);//Print error message
    return EXIT_FAILURE;
}