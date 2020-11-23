#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Initialization
    int check = 0;
    int i = 0;
    int j = 0;

    //Error message if key is invalid
    if (argc != 2)
    {
        printf("missing command-lime argument\n");
        return 1;
    }
    int n = strlen(argv[1]);
    if (n != 26)
    {
        printf("The key has to be 26 characters long.\n");
        return 1;
    }
    for (i = 0; i < n; i++)
    {
        if (argv[1][i] < 65 || argv[1][i] > 122 || (argv[1][i] < 97 && argv[1][i] > 90))
        {
            printf("The key has invalid characters");
            return 1;
        }
        for (j = 0; j < n; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                check++;
            }
            if (check > 1)
            {
                printf("The key has repeating values.\n");
                return 1;
            }
        }
        check = 0;
        j = 0;
    }

    //input plaintext
    string plaintext = get_string("plaintext: ");

    //output ciphertext
    printf("ciphertext: ");

    for (i = 0; i < strlen(plaintext); i++)
    {
        if (plaintext[i] >= 65 && plaintext [i] <= 90) //uppercase
        {
            printf("%c", toupper(argv[1][plaintext[i] - 65]));
        }
        else if (plaintext[i] >= 97 && plaintext [i] <= 122) //lowercase
        {
            printf("%c", tolower(argv[1][plaintext[i] - 97]));
        }
        else
        {
            printf("%c", plaintext[i]); //print other symbols without change
        }
    }
    printf("\n");
    return 0;
}