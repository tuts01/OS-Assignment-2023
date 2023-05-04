/**
 * @file            misc.h
 * @author          Tristan S. Tutungis
 * @date_created    01/05/2023
 * @last_modified   04/05/2023 16:01
 * @description     Header file for misc.c
*/

#ifndef MISC_H
#define MISC_H

//Usage string
#define USAGE "Usage:\ncq <queue size> <time to arrive> <deposit time> <withdrawal time> <information time>\n"

/**
 * @function    get_time
 * @returns     str (char*)
 * @purpose     Returns the current time as a string in the format HH:MM:SS
*/
char* get_time(void);

/**
 * @function    printerr
 * @returns     EXIT_FAILURE (int)
 * @purpose     Print an error string and return EXIT_FAILURE
*/
int printerr(char* errstr);

#endif
