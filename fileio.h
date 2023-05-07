/**
 * @file            fileio.c
 * @author          Tristan S. Tutungis
 * @date_created    29/03/2023
 * @last_modified   04/05/2023 15:12
 * @description     Contains functions for reading from and writing to files
*/

#ifndef FILEIO_H
#define FILEIO_H

#include "cust.h"

#define MAXLINELEN 8 //Max length of line
#define INFILENAME "c_file" //Input file name
#define OUTFILENAME "r_log" //Output file name
//Divider for log file
#define DIVIDER "-----------------------------------------------------------------------"

/**
 * @function    open
 * @returns     f (FILE*)
 * @purpose     Wrapper for fopen() - open a file stream and check for errors
*/
FILE* open(char* name, char* mode);

/**
 * @function    readCustFile
 * @returns     customer (cust_t*)
 * @purpose     Read a customer from the passed file stream - sets eof to true
 *              if the end of the file is reached
*/
cust_t* readCustFile(FILE* file);

#endif
