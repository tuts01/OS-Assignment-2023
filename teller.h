/**
 * @file            teller.h
 * @author          Tristan S. Tutungis
 * @date_created    1/05/2023
 * @last_modified   3/05/2023 20:50
 * @description     Header file for a function representing a teller.
*/

#ifndef TELLER_H
#define TELLER_H

/**
 * @function    teller
 * @returns     NULL (void*)
 * @purpose     Function which simulates a bank teller - serves customers as
 *              they enter a queue
*/
void* teller(void* queue_ptr);

#endif
