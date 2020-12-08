#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Accepts exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //Open file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File cannot be opened\n");
        return 1;
    }

    //Calculate the size of the file
    fseek(file, 0, SEEK_END);
    long int size = ftell(file);
    rewind(file);

    //initialize variables
    bool first = true;
    BYTE bytes[512]; //buffer
    int count = 0;
    FILE *img = NULL;

    //Read first four bytes of each 512 byte chunk
    for (int i = 0; i < size; i += 512)
    {
        fseek(file, i, SEEK_SET);
        fread(bytes, 512, 1, file);
        //Check first four bytes
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            //if JPEG and needs new file
            char *filename = malloc(8);
            if (!filename)
            {
                return 1;
            }
            sprintf(filename, "%03i.jpg", count);
            if (first)
            {
                img = fopen(filename, "w"); //open new file
                fwrite(bytes, 512, 1, img); //write new file
                first = false;
            }
            else //if not first image, must close previous img first
            {
                fclose(img);
                img = fopen(filename, "w");
                fwrite(bytes, 512, 1, img);
            }
            count++;
            free(filename);
        }
        else if (!first)
        {
            //continue writing blocks of jpeg without new file
            fwrite(bytes, 512, 1, img);
        }
    }
    //Close files
    fclose(img);
    fclose(file);
}