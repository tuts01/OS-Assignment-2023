/**
 * @file            cust.h
 * @author          Tristan S. Tutungis
 * @date_created    29/03/2023
 * @last_modified   04/05/2023 10:55
 * @description     Contains a struct representing a customer (number and 
 *                  service type) as well as a function that periodically
 *                  adds a customer entry to the queue
*/

#ifndef CUST_H
#define CUST_H

/**
 * @enum    service_t
 * @purpose Enumeration of the three customer-teller interaction types - 
 *          Withdrawal (W), Deposit (D), and Information (I)
*/
typedef enum {W, D, I} service_t;

/**
 * @struct  cust_t
 * @purpose Structure containing a customer number, the service he/she
 *          requires, and their arrival time - represents a customer
 *          in the queue
*/
typedef struct
{
    long custNo; //Customer number
    service_t service; //Service required
    char* arrivalTime; //Arrival time
} cust_t;

/**
 * @function    customer
 * @returns     NULL (void*)
 * @purpose     Periodically read a list of customers from a file
*/
void* customer(void *queue);

#endif