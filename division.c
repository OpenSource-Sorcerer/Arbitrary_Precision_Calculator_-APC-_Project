#include "apc.h"

/* 
 * Get list length
 * Inputs: Double linked list pointers
 * Output: length of the list
 * Return Value: size / count
 */
int get_list_length(Dlist **head, Dlist **tail)
{
    Dlist *temp = *head;
    int count = 0;
    while(temp != NULL)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

/* 
 * Divide the two numbers
 * Inputs: 3 - double Linked List pointers
 * Output: Division Result from two numbers
 * Return Value: SUCCESS / FAILURE, on division operation
 */
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int len1 = 0, len2 = 0, count = 0, flag = 0;
    while(1)
    {
        //find the length of list
        len1 = get_list_length(head1, tail1);
        //printf("len1 %d\n",len1);

        len2 = get_list_length(head2, tail2);
        //printf("len2 %d\n",len2);

        if (*head1 == NULL || *tail1 == NULL) break;

        //compare both lengths
        if(len1 > len2)
        {
            subtraction(head1, tail1, head2, tail2, headR, tailR);
            if(delete_list(head1, tail1) == FAILURE)    return FAILURE;
            *head1 = *headR;
            *tail1 = *tailR;
            *headR = NULL;
            *tailR = NULL;
            //remove zeros at first
            if(remove_zeros_atFirst(head1, tail1) == FAILURE)		return FAILURE;
            count++;
        }
        else if(len1 == len2)
        {
            for(int i = 0; i < len1; i++)
            {
                Dlist *temp1 = *head1, *temp2 = *head2;
                
                if(temp1->data > temp2->data)
                {
                    flag++;
                    break;
                }

                else if(temp1->data < temp2->data)
                {
                    flag = 0;
                    break;
                }

                else
                {
                    flag++;
                    temp1 = temp1->next;
                    temp2 = temp2->next;
                } 
            }
            if(flag)
            {
                subtraction(head1, tail1, head2, tail2, headR, tailR);
                if(delete_list(head1, tail1) == FAILURE)    return FAILURE;
                *head1 = *headR;
                *tail1 = *tailR;
                *headR = NULL;
                *tailR = NULL;
                count++;
                //remove zeros at first
                if(remove_zeros_atFirst(head1, tail1) == FAILURE)		return FAILURE;
            }
            else    break;
        }
        else    break;
    }
    
    if(*headR != NULL)    if(delete_list(headR, tailR) == FAILURE)    return FAILURE;
        
    if(count)
    {
        if(create_list(headR, tailR, count) == FAILURE)
	    {
		    printf("\n\033[1mINFO:	Error in Creating List on Division\033[0m\n");
		    return FAILURE;
	    }
    }
    //count = 0    
    else    if(insert_first(headR, tailR, 0) == FAILURE)   return FAILURE;
    return SUCCESS;
}
