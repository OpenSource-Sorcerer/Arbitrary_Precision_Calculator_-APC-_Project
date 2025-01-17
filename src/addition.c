#include "apc.h"

/* 
 * Add the two numbers
 * Inputs: 3 - double Linked List pointers
 * Output: Addition Result from two numbers
 * Return Value: SUCCESS / FAILURE, on addition operation
 */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	int carry = 0, num1 = 0, num2 = 0, sum = 0, data = 0, sign = 0;

    /*Conditions add
        num1 (+)    num2 (+)
        num1 (-)    num2 (-) //change first digit polarity in both numbers and add sign atlast
      Conditions sub
        num1 (+)    num2 (-)
        num1 (-)    num2 (+)
    */
   //check first digit on both numbers
   if(((*head1)->data < 0) && ((*head2)->data < 0)) // num1 (-)    num2 (-)
   {
        sign++;
        (*head1)->data *= -1;
        (*head2)->data *= -1;
   }
   else if(((*head1)->data > 0) && ((*head2)->data < 0)) //num1 (+)    num2 (-)
   {
        //subtract
        (*head2)->data *= -1;
        if(subtraction(head1, tail1, head2, tail2, headR, tailR) == FAILURE)		return FAILURE;
        return SUCCESS;
   }
   else if(((*head1)->data < 0) && ((*head2)->data > 0)) //num1 (-)    num2 (+)
   {
        //subtract
        (*head1)->data *= -1;
        if(subtraction(head1, tail1, head2, tail2, headR, tailR) == FAILURE)		return FAILURE;
        return SUCCESS;
   }
   Dlist *temp1 = *tail1; Dlist *temp2 = *tail2;

   while(temp1 != NULL || temp2 != NULL)
   {
        if(temp1 != NULL)  
        {
            num1 = temp1->data;
            temp1 = temp1->prev;
        } 
        else num1 = 0;
        
        if(temp2 != NULL)   
        {
            num2 = temp2->data;
            temp2 = temp2->prev;
        }
        else num2 = 0;

        sum = num1 + num2 + carry;

        data = sum % 10;

        carry = sum / 10;

        if(insert_first(headR, tailR, data) == FAILURE)            return FAILURE;
   }

   if(carry)    if(insert_first(headR, tailR, carry) == FAILURE)   return FAILURE;  

   if(sign)
   {
        if(carry)   data = carry;

        data *= -1;
        if(delete_first(headR, tailR) == FAILURE)         return FAILURE;
        if(insert_first(headR, tailR, data) == FAILURE)   return FAILURE;
   } 
   return SUCCESS;
}