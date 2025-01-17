#include "apc.h"

/* 
 * Create Double Linked List
 * Inputs: Double linked list pointers
 * Output: list with nodes
 * Return Value: FAILURE / SUCCESS, based on list creation
 */
int create_list(Dlist **head, Dlist **tail, int num)
{
    //get a digit
    int temp = num,sign = 0, data = 0;

    if(num < 0)//negative nums
    {
        temp *= -1; 
        sign++;
    }
    
    while(temp != 0)
    {
        data = temp % 10;
        
        if(insert_first(head, tail, data) == FAILURE)   return FAILURE;

        temp /= 10; 
    }
    
    if(sign) 
    {
        data *= -1;
        if(delete_first(head, tail) == FAILURE)         return FAILURE;
        if(insert_first(head, tail, data) == FAILURE)   return FAILURE;
    }
    return SUCCESS;
}