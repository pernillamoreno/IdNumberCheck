/**
 * @file G_assigPernilla.c
 * @author {Nilla Moreno} ({stahlbring@gmail.com})
 * @brief Make a program that read personal id numbers in the format of
 * YYMMDD-nnnC from the terminal and check if the id is correct or not. 
 * The program needs to calculate the control digit of the personid & compare
 * it whit the last digit of the user has entered. 
 * If the calculated are the same as the users input, the program will that the id are correct
 * else enterd id is not a valid id. 
 * Note! The format of the person id shall also be checked. 
 * @version 0.1
 * @date 2023-11-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define IDNUMBER 12//define a macro that store the IDNUMBER

//function prototype
void verify(char idNumb[], int result);
int isLeapYear(int year);

int main()
{
    char idNumb[IDNUMBER];

    printf("Enter your ID(personnummer) (YYMMDD-nnnC): ");
    scanf("%s", idNumb);
    /*checks if idnumber is entered correct right format. 
    strlen(idNumb) != IDNUMBER - 1 : condition checks if the length of the idNumb string is not equal to IDNUMBER - 1.*/
    if (strlen(idNumb) != IDNUMBER - 1 || idNumb[6] != '-')
    {
        printf("Invalid ID format. Please enter format (YYMMDD-nnnC).\n");
        return 1;
    }
/*initilaize year mont and day= date
if year idNumb is not 3 year less tahn 0 or more than 99 or month less than 1
or more than 12, Error messege print to the user.*/
    int year, month, day;
    if (sscanf(idNumb, "%2d%2d%2d", &year, &month, &day) != 3 || year < 0 || year > 99 || month < 1 || month > 12)
    {
        printf("Invalid year, month, or date format.\n");
        return 1;
    }

    // Check if the date is February 29th in a leap year
    /*if month is 2 and date 29 and not leap year. Error message will print to user*/
    if (month == 2 && day == 29)
    {
        if (!isLeapYear(year))
        {
            printf("Invalid date for February 29th in a non-leap year.\n");
            return 1;
        }
    }
    /*check if its a "normal" februari */
    else if (month == 2)
    {
        if (day < 1 || day > 28)
        {
            printf("Invalid date for month of February (28 days).\n");
            return 1;
        }
    }
    /*check if input month have 30 days or not*/
    else if (month == 4 || month == 6 || month == 8 || month == 10 || month == 12)
    {
        if (day < 1 || day > 30)
        {
            printf("Invalid date for months with 30 days (4, 6, 8, 10, 12).\n");
            return 1;
        }
    }

    // Calculate the checksum
   /* Initializes variable totalSum, totalSum will store the sum of the calculated value.
   The for loop iterates as long as i is less than IDNUMBER -2. Count keep track of position in the
   Id number array.
   The if statement check if not '-' . Then the code is executed. 
       This line calculates a value digit. It takes the current character in idNumb at position 
       i and subtracts the ASCII value of '0'. This converts the character representing a digit to 
       its integer value.
    It then multiplies the digit by 2 if count is even (count % 2 == 0), or by 1 if count is odd. 
    The expression (count++ % 2 == 0) ? 2 : 1 is a ternary operator that alternates between 2 and 1 as 
    count increments.*/
    int totalSum = 0;
    for (int i = 0, count = 0; i < IDNUMBER - 2; i++)
    {
        if (idNumb[i] != '-')
        {
            int digit = (idNumb[i] - '0') * ((count++ % 2 == 0) ? 2 : 1);
            totalSum += (digit >= 10) ? digit / 10 + digit % 10 : digit;
        }
    }

     // Calculate the control digit (C)
     /*int result is moduls of totalSum then minus 10, totalSum from previus for loop*/
    int result = (10 - (totalSum % 10));
    printf("Control number C is: %d\n", result);
    
   //calling the fuction 
   verify(idNumb, result);

    return 0;
}

// void verify, validate the control digit
/*Comparing the entered control digit with calulated result
if it match print valid messge else error message and exit.

idNumb[10] retrieves the 11th character in the idNumb array, 
which represents the control digit (C). '0' is subtracted 
to convert the character to an integer.*/
void verify(char idNumb[], int result)
{  
    if (idNumb[10] - '0' == result)
    {
        printf("The control digit matches, a valid ID number!\n");
    }
    else
    { 
        printf("Invalid ID number. Check your input and do it right next time :).\n");
        exit(1);
    }
}
/*function that check if its a leapyear.
/ Leap year if divisible by 4 or leap year if not divisible by 100 dif perfectly divisible by 400*/
int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
