#include "apc.h"

/* 
 * Insert Zeros on list
 * Inputs: Double linked list pointers and number of zeros need to be inserted(count)
 * Output: list inserted with 0's
 * Return Value: -----
 */
void insert_zeros(Dlist **head, Dlist **tail, int count_0s)
{
    while(count_0s != 0)
    {
        insert_first(head, tail, 0);
        count_0s--;
    }
}

/* 
 * Mutiply the two numbers
 * Inputs: 5 - double Linked List
 * Output: Multiplication Result from two numbers
 * Return Value: SUCCESS / FAILURE, on multiplication operation
 */
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	Dlist *headr = NULL, *tailr = NULL;
    Dlist *bckhead = NULL, *bcktail = NULL;

    int num1 = 0, num2 = 0, carry =  0, mul = 0, data = 0, count = 0, flag = 0;

    Dlist *temp1 = *tail1;  Dlist *temp2 = *tail2;
    
    while(temp2 != NULL)
    {
        num1 = temp2->data;
        flag = 1;
        while(temp1 != NULL)
        {
            if(temp1 != NULL)   num2 = temp1->data;
            
            mul = (num1 * num2) + carry;

            data = mul % 10;

            carry = mul / 10;
            
            if(!count)  insert_first(headR, tailR, data);//R1
            else
            {
                if(flag == 1)
                {
                    insert_zeros(&headr, &tailr, count); //insert zeros
                    flag = 0;
                }
                insert_first(&headr, &tailr, data);//R2
            }
            temp1 = temp1->prev;
        }
        if(headr != NULL)
        {
            addition(headR, tailR, &headr, &tailr, &bckhead, &bcktail);
            //delete lists
            delete_list(headR, tailR);
            delete_list(&headr, &tailr);
            //update R1
            *headR = bckhead;
            *tailR = bcktail;
            //update backuplists
            bckhead = NULL;
            bcktail = NULL;
        }
        
        count++;
        temp2 = temp2->prev;
        temp1 = *tail1;
    }
    return SUCCESS;
}
