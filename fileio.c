/**
 * @file            fileio.c
 * @author          Tristan S. Tutungis
 * @date_created    29/03/2023
 * @last_modified   
 * @description     Contains functions for reading from and writing to files
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fileio.h"

FILE* open(char* name, char* mode)
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

cust_t* readCustFile(FILE* file)
{
    cust_t* customer = NULL;
    bool done = false;
    char* curLine = (char*)calloc(MAXLINELEN + 1, sizeof(char));
    const char s[2] = " ";
    char* token;
    long custNo; 

    if(file != NULL)
    {
        customer = (cust_t*)malloc(sizeof(cust_t));

        fgets(curLine, MAXLINELEN, file);

        token = strtok(curLine);
        custNo = strtol(token, NULL, 10);

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
                break;
        }
    }    

    free(curLine);
    return customer;
}