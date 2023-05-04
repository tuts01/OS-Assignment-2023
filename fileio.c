/**
 * @file            fileio.c
 * @author          Tristan S. Tutungis
 * @date_created    29/03/2023
 * @last_modified   04/05/2023 15:53
 * @description     Contains functions for reading from and writing to files
*/
//TODO: Move some things to this file, maybe...
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "fileio.h"

/**
 * @function    open
 * @returns     f (FILE*)
 * @purpose     Wrapper for fopen() - open a file stream and check for errors
*/
FILE* open(char* name, char* mode)
{
    FILE* f = fopen(name, mode); //Open the file stream

    //Check for any errors
    if(f == NULL) perror("Error opening file");
    else if(ferror(f))
    {
        perror("Error opening file");
        f = NULL;
    }

    return f; //Return the open file stream
}

/**
 * @function    readCustFile
 * @returns     customer (cust_t*)
 * @purpose     Read a customer from the passed file stream - sets eof to true
 *              if the end of the file is reached
*/
//TODO: Remove eof - does not need to be passed in as it is a global variable
cust_t* readCustFile(FILE* file, _Bool* eof)
{
    cust_t* customer = NULL;
    char* curLine = (char*)calloc(MAXLINELEN + 1, sizeof(char));
    const char s[2] = " ";
    char* token;
    long custNo; 

    //Only read if the file opened successfully
    if(file != NULL)
    {
        /* If fgets() returns NULL, no bits were read, signifying the end of
           the file */
        if(fgets(curLine, MAXLINELEN, file) == NULL)
        {
            *eof = true;
            return NULL;
        }

        //Allocate memory for a customer
        customer = (cust_t*)malloc(sizeof(cust_t));

        //Tokenise the string and convert the first token to a long (customer ID)
        token = strtok(curLine);
        custNo = strtol(token, NULL, 10);

        /* Get the next token and assign an enum value based on it - NULL is
           immediately returned if an invalid entry is provided */
        token = strtok(curLine);
        switch(*token)
        {
            case 'W':
                customer->service = W;
                break;

            case 'D':
                customer->service = D;
                break;

            case 'I':
                customer->service = I;
                break;

            default:
                free(customer);
                customer = NULL;
                /* TODO: fix calling method (NULL being returned DOES NOT
                    necessarily mean that the end of file has been reached) */
        }
    }    

    free(curLine); //Free the memory allocated for the line
    return customer;
}