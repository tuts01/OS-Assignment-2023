/**
 * @file            teller.h
 * @author          Tristan S. Tutungis
 * @date_created    1/05/2023
 * @last_modified
 * @description     Header file for a function representing a teller. Also
 *                  contains a structure representing data to be passed to
 *                  the thread function
*/

#ifndef TELLER_H
#define TELLER_H

typedef struct
{

} teller_t;

void* teller(void* data);

#endif
