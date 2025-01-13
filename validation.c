#include "apc.h"

/* 
 * Checks the character is digit or not
 * Inputs: character
 * Output: SUCCESS / FAILURE
 * Return Value: SUCCESS : FAILURE, based on the character
 */
int is_digit(char ch)
{
    return (ch >= '0' && ch <= '9') ? SUCCESS : FAILURE;
}

/* 
 * Checks the string have digit or not
 * Inputs: String
 * Output: SUCCESS / FAILURE
 * Return Value: SUCCESS : FAILURE, based on the string
 */
int my_alnum(char *str)
{
    int i = 0;
    if((str[i] == '+') || (str[i] == '-'))  i++;

    while(str[i] != '\0')
    {
        if(is_digit(str[i]) == FAILURE)
        {
            return FAILURE;
        }
        i++;
    }
    return SUCCESS;
}

/* 
 * Converts the string into integer
 * Inputs: String
 * Output: number
 * Return Value: number, based on the string
 */
int my_atoi(char *str)
{
    int sign = 0, num = 0, i = 0;
    
    //checking the string contains any sign on the starting point
    sign = (str[i] == '-') ? 1 : (str[i] == '+') ? 2 : 0;
    //If sign is there then incrementing the i value to 1
    i = sign != 0 ? 1 : 0;
    
    //Iterate the string charcters
    for(i; str[i] != '\0'; i++)
    {
        //Checks the characters if they are digits or not 
        if(str[i] >= '0' && str[i] <= '9')
            //Assigning the ascii value of character into int variable
            num = (num * 10) + str[i] - 48;
        else break;
    }
    //if sign is present then change the number (i.e. +ve or -ve)
    return (sign != 0) ? (sign == 1) ? -num : num :  num;
}

/* 
 * Validate the command line arguments
 * Inputs: Command Line Arguments, numbers
 * Output: numbers
 * Return Value: SUCCESS : FAILURE, based on the Command Line Arguments
 */
int validate_args(int argc, char* argv[], int *num1, int *num2)
{
    if(argc != 4)   return FAILURE;

    //check for alnum
    if((my_alnum(argv[1]) == SUCCESS) && (my_alnum(argv[3]) == SUCCESS))
    {
        if(!(strcmp(argv[2], "+")) || !(strcmp(argv[2], "-")) || !(strcmp(argv[2], "x")) || !(strcmp(argv[2], "/")))
        {
            //atoi
            *num1 = my_atoi(argv[1]);
            *num2 = my_atoi(argv[3]);
            return SUCCESS;
        }
    }
    return FAILURE;
}