#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //initalization
    int height;
    
    //get height from user within range of 1 to 8
    do
    {
        height = get_int("Height: ");
    } 
    while (height > 8 || height < 1);
    
    //make pyramid
    for (int row = 0; row < height; row++)
    {
        //print spaces
        for (int spaces = 1; spaces < (height - row); spaces++)
        {
            printf(" ");
        }
        
        //print right-aligned hashes
        for (int hash = 0; hash < (row + 1); hash++)
        {
            printf("#");
        }
        
        //separate two pyramids
        printf("  ");
        
        //print left-aligned hashes
        for (int hash = 0; hash < (row + 1); hash++)
        {
            printf("#");
        }
        
        //separate rows
        printf("\n");
    }   
}