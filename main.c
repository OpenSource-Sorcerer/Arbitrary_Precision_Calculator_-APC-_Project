#include "apc.h"

/* 
 * Prints line on screen
 * Inputs: ----
 * Output: Prints line on output screen
 * Return Value: ----
 */
void print_line()
{
    for(int i = 0; i < 100 ;i++)
        printf("\033[1;34;40m%s\033[0m","-");
}

/* 
 * Prints messages on screen
 * Inputs: ----
 * Output: Prints messages on output screen
 * Return Value: ----
 */
int print_error()
{
	//print invlaid args
	print_line();
    printf("\n\033[1mERROR : ./a.out : \033[1;37;41mINVALID ARGUMENTS\033[0m\n\033[0m\n");
	printf("\n\033[1mTo perform Addition please pass like         : \033[1;37;43m./a.out 50 + 10\033[0m\n\033[0m");//add
	printf("\n\033[1mTo perform Subtraction please pass like      : \033[1;37;43m./a.out 50 - 10\033[0m\n\033[0m");//sub
	printf("\n\033[1mTo perform Multiplication please pass like   : \033[1;37;43m./a.out 10 x 50\033[0m\n\033[0m");//mul
	printf("\n\033[1mTo perform DIVISION please pass like         : \033[1;37;43m./a.out 50 / 10\033[0m\n\033[0m");//div
	print_line();
    printf("\n");
	return 0;
}

/* 
 * Prints output list on screen
 * Inputs: output list head pointer
 * Output: Prints output list on screen
 * Return Value: ----
 */
void print_output(Dlist *headR)
{
	print_line();
	printf("\n\033[1;37;42m%s	\033[0m : 	","Output");
	print_list(headR);
	print_line();
	printf("\n");
}

/* 
 * Change the polarity of first digit on output list
 * Inputs: output list pointers
 * Output: Output List
 * Return Value: SUCCESS
 */
int change_head_data(Dlist ** headR, Dlist **tailR, int data_)
{
	data_ *= -1;
    if(delete_first(headR, tailR) == FAILURE)         return FAILURE;
    if(insert_first(headR, tailR, data_) == FAILURE)   return FAILURE;

	return SUCCESS;
}

/* 
 * Min function
 * Inputs: Command Line Arguments
 * Output: Prints the Output List
 * Return Value: 0
 */
int main(int argc, char *argv[])
{
	/* Declare the pointers */
      
	Dlist *head1=NULL, *tail1=NULL;
    Dlist *head2=NULL, *tail2=NULL; 
    Dlist *headR=NULL, *tailR=NULL;

	int num1 = 0, num2 = 0;
	if(validate_args(argc, argv, &num1, &num2) == FAILURE)		if(print_error() == 0)	return 0;

/****************CHANGE POLARITY OF NUMBERS*******************/
	//validation for big num if subtraction
	int sub = 0, add_sign1 = 0, add_sign2 = 0, temp = 0;
	if(strstr(argv[2],"-"))
	{
		if(num1 < 0 && num2 < 0)	//num1 (-)    num2 (-) //-10 - -15 => -10 + 15 => 5		//-50 - -10 => -50 + 10 => -40
		{
			num2 *= -1;
			temp = -(num1);
			if(temp > num2)			
			{
				num2 *= -1;
				add_sign1++;	
			}	
			else if(temp < num2)	
			{
				//Always +ve sign
				num2 *= -1;
				add_sign2++;
				goto change_nums;
			}
			if(temp == num2)		goto insert_0;
			
		}
		else if(num1 > 0 && num2 > 0)	//num1 (+)    num2 (+)
		{
			if(num1 < num2)
			{
				change_nums:
				num1 = num1 + num2;
				num2 = num1 - num2;
				num1 = num1 - num2;
				sub++;

			}
			//insert 0 if num1 and num2 are same
			else if(num1 == num2)
			{
				if(insert_first(&headR, &tailR, 0) == FAILURE)   return FAILURE;
				print_output(headR);
				return 0;
			}
		}
		else if(num1 < 0 && num2 > 0)	sub++; //sign always -ve	//num1 (-)    num2 (+) //-123 - 123 => -246

		else if(!num1 && !num2)		goto insert_0;		//0 - 0

		else if(!num1 && num2 > 0)	goto change_nums;	//0 - 1
	}

	//Check and change nums polarity if multiplication
	else if(strstr(argv[2], "x") || (strstr(argv[2], "/") && (num1 <= 0 || num2 <= 0)))
	{
		if((!num2 && num1) && strstr(argv[2], "/"))			// 0 / num
		{
			print_line();
			printf("\n%34s\033[1;37;41m!!!:::CANNOT DIVIDED BY ZERO:::!!!\033[0m\n"," ");
			print_error();
			return 0;
		}
		else if((!num2 && !num1) && strstr(argv[2], "/"))	// 0 / 0
		{
			print_line();
			printf("\n%36s\033[1;37;41m!!!:::RESULT IS UNDEFINED:::!!!\033[0m\n"," ");
			print_error();
			return 0;
		}
		else if((!num2 || !num1) && strstr(argv[2], "x"))
		{
			if(insert_first(&headR, &tailR, 0) == FAILURE)   return FAILURE;
			print_output(headR);
			return 0;
		}
		else if(num1 < 0 && num2 < 0)
		{
			num1 *= -1;	num2 *= -1;
			sub = 0;
		}
		else
		{
			sub++;
			if(num2 < 0)		num2 *= -1;
			else if(num1 < 0)	num1 *= -1;
			else sub = 0;
		}
	}

	else if(strstr(argv[2],"+"))
	{
		if(num2 < 0 && num1 > 0)	//num1 (+)    num2 (-)
		{	//Set both numbers polarity as + and check for big number 
			int temp = -(num2);
			if(temp > num1)
			{
				add_sign2++;
				goto change_nums;
			}		
			else if(temp == num1)
			{
				insert_0:
				if(insert_first(&headR, &tailR, 0) == FAILURE)   return FAILURE;
				print_output(headR);
				return 0;
			}	
		}
		else if(num2 > 0 && num1 < 0)	//num1 (-)    num2 (+)
		{	//Set both numbers polarity as + and check for big number 
			temp = -(num1);
			if(temp > num2)			add_sign1++;		
			else if(temp < num2)	goto change_nums;
			if(temp == num2)		goto insert_0;
		}
	}
	/**************************************************************/
	/***********************List Creation**************************/
	if(num1)
	{
		if(create_list(&head1, &tail1, num1) == FAILURE)
		{
			printf("\n\033[1mINFO:	Error in Create List\033[0m\n");
			return 0;
		}
	}
	//num1 is 0
	else    if(insert_first(&head1, &tail1, 0) == FAILURE)   return FAILURE;

	if(num2)
	{
		if(create_list(&head2, &tail2, num2) == FAILURE)
		{
			printf("\n\033[1mINFO:	Error in Create List\033[0m\n");
			return 0;
		}
	}
	//num2 is 0
	else    if(insert_first(&head2, &tail2, 0) == FAILURE)   return FAILURE;
	/*************************************************************/

	char operator=argv[2][0];
	switch (operator)
	{
		case '+':
			if(addition(&head1, &tail1, &head2, &tail2, &headR, &tailR) == FAILURE)			goto error_exit;

			//remove 0's atfirst
			if(remove_zeros_atFirst(&headR, &tailR) == FAILURE)		return FAILURE;

			if(add_sign2 || add_sign1)	if(change_head_data(&headR, &tailR, headR->data) == FAILURE)	return FAILURE;
			
			print_output(headR);
			break;
		case '-':	
			if(subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR) == FAILURE)		goto error_exit;

			//remove 0's atfirst
			if(remove_zeros_atFirst(&headR, &tailR) == FAILURE)		return FAILURE;

			//result in negative
			if((sub || add_sign1) && (!add_sign2))		if(change_head_data(&headR, &tailR, headR->data) == FAILURE)	return FAILURE;
				
			print_output(headR);
			break;
		case 'x':
			if(multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR) == FAILURE)	goto error_exit;

			//result in negative
			if(sub)		if(change_head_data(&headR, &tailR, headR->data) == FAILURE)	return FAILURE;

			print_output(headR);	
			break;
		case '/':	
			if(division(&head1, &tail1, &head2, &tail2, &headR, &tailR) == FAILURE)	goto error_exit;

			//result in negative
			if(sub)		if(change_head_data(&headR, &tailR, headR->data) == FAILURE)	return FAILURE;
				
			print_output(headR);	
			break;
		default:
			printf("Invalid Input:-( Try again...\n");
	}
	return 0;
	error_exit:
		printf("\n\033[1mINFO:	Error in Arthmetic Operation\033[0m\n");
		return 0;
}
