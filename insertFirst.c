#include "apc.h"

/* 
 * Insert Node at First on List
 * Inputs: Double linked list pointers
 * Output: list with nodes
 * Return Value: FAILURE / SUCCESS, based on node insertion
 */
int insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new_ = malloc(sizeof(Dlist));
    if(new_ == NULL)    return FAILURE;
    
    new_->data = data;
    new_->next = *head;
    new_->prev = NULL;
    
    if(*head == NULL)
    {
        *head = new_;
        *tail = new_;
        return SUCCESS;
    }
    
    (*head)->prev = new_;
    *head = new_;
    return SUCCESS;
}