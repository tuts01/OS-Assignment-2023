/**
 * @file            fileio.c
 * @author          Tristan S. Tutungis
 * @date_created    29/03/2023
 * @last_modified   29/03/2023
 * @description     Contains functions for reading from and writing to files
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fileio.h"

static FILE* open(char* name, char* mode)
{
    FILE* file = fopen(name, mode); //Open the file stream
    
    if(file == NULL) perror("Error opening file"); //If file could not be read, NULL is returned - output error message
    else if(ferror(file)) //If error occurs, it will be found by ferror()
    {
        perror("Error opening file"); //If any error is found, output message to the user...
        file = NULL; //...and set file to NULL
    }

    return file; //Return the open file stream
}

cust_t* readCustFile()
{
    cust_t* customers = NULL;
    bool done = false;
    char* curLine = (char*)calloc(MAXLINELEN + 1, sizeof(char));

    

}