#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //initialize values
    long number = 0;
    int i = 0;
    int length = 0;
    int add = 0;
    int total = 0;
    bool checksum = false;

    //prompt user for credit card number
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0); //reprompt if negative number is inputted

    //calculate length
    while (i <= length)
    {
        if (number > (pow(10, i)))
        {
            length++;
        }
        i++;
    }

    //calculate checksum
    //multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together
    for (i = 2; i <= length; i += 2)
    {
        add = (number % (long)(pow(10, i))) / (pow(10, i - 1));
        if ((add * 2 / 10) == 0)
        {
            total += add * 2;
        }
        else
        {
            total += (((add * 2) % 10) + 1);
        }
    }

    //add the sum to the sum of the digits that weren’t multiplied by 2
    for (i = 1; i <= length; i += 2)
    {
        add = (number % (long)(pow(10, i))) / (pow(10, i - 1));
        total += add;
    }

    //check if checksum is valid
    if ((total % 10) == 0)
    {
        checksum = true;
    }

    //check for card length and starting digits then print result
    if (checksum)
    {
        if (length == 15 && (int)((number % (long)(pow(10, 15))) / (pow(10, 14))) == 3
            && ((int)((number % (long)(pow(10, 14))) / (pow(10, 13))) == 4 || (int)((number % (long)(pow(10, 14))) / (pow(10, 13))) == 7))
        {
            printf("AMEX\n");
        }
        else if (length == 16 && (int)((number % (long)(pow(10, 16))) / (pow(10, 15))) == 5
                 && ((int)((number % (long)(pow(10, 15))) / (pow(10, 14))) == 1 || (int)((number % (long)(pow(10, 15))) / (pow(10, 14))) == 2
                     || (int)((number % (long)(pow(10, 15))) / (pow(10, 14))) == 3 || (int)((number % (long)(pow(10, 15))) / (pow(10, 14))) == 4
                     || (int)((number % (long)(pow(10, 15))) / (pow(10, 14))) == 5))
        {
            printf("MASTERCARD\n");
        }
        else if (length == 13 && (int)((number % (long)(pow(10, 13))) / (pow(10, 12))) == 4)
        {
            printf("VISA\n");
        }
        else if (length == 16 && (int)((number % (long)(pow(10, 16))) / (pow(10, 15))) == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}