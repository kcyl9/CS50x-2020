#include "helpers.h"
#include <math.h>

int avg(int height, int width, RGBTRIPLE placeholder[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) //iterate through rows
    {
        for (int j = 0; j < width; j++) //iterate through pixels
        {
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            //change all RGB values to average value
            image[i][j].rgbtBlue = (int) avg;
            image[i][j].rgbtGreen = (int) avg;
            image[i][j].rgbtRed = (int) avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) //iterate through rows
    {
        for (int j = 0; j < width; j++) //iterate through pixels
        {
            //algorithm for converting an image to sepia
            int sepiaRed = (int) round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = (int) round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = (int) round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            //if value is larger than 255, reduce back to 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            //set original equal to Sepia version
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //initialize values
    int count = 0;
    RGBTRIPLE placeholder[height][width];

    for (int i = 0; i < height; i++) //iterate through rows
    {
        for (int j = 0; j < (int)width / 2; j++) //iterate through pixels until halfway point
        {
            //switch pixels with corresponding reflected values
            placeholder[i][j] = image[i][j];
            image[i][j] = image[i][j + width - 1 - 2 * count];
            image[i][j + width - 1 - 2 * count] = placeholder[i][j];
            count++;
        }
        count = 0;
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make a copy
    RGBTRIPLE placeholder[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            placeholder[i][j] = image[i][j];
        }
    }

    //blur
    for (int i = 0; i < height; i++) //iterate through rows
    {
        for (int j = 0; j < width; j++) //iterate through pixels
        {
            if (i == 0) //if top row
            {
                if (j == 0) //if top, left corner
                {
                    image[i][j].rgbtRed = (int) round((placeholder[i][j].rgbtRed + placeholder[i + 1][j].rgbtRed + placeholder[i][j + 1].rgbtRed +
                    placeholder[i + 1][j + 1].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = (int) round((placeholder[i][j].rgbtGreen + placeholder[i + 1][j].rgbtGreen + placeholder[i][j + 1].rgbtGreen
                    + placeholder[i + 1][j + 1].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = (int) round((placeholder[i][j].rgbtBlue + placeholder[i + 1][j].rgbtBlue + placeholder[i][j + 1].rgbtBlue +
                    placeholder[i + 1][j + 1].rgbtBlue) / 4.0);
                }
                else if (j == (width - 1)) //if top, right corner
                {
                    image[i][j].rgbtRed = (int) round((placeholder[i][j].rgbtRed + placeholder[i + 1][j].rgbtRed + placeholder[i][j - 1].rgbtRed +
                    placeholder[i + 1][j - 1].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = (int) round((placeholder[i][j].rgbtGreen + placeholder[i + 1][j].rgbtGreen + placeholder[i][j - 1].rgbtGreen
                    + placeholder[i + 1][j - 1].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = (int) round((placeholder[i][j].rgbtBlue + placeholder[i + 1][j].rgbtBlue + placeholder[i][j - 1].rgbtBlue +
                    placeholder[i + 1][j - 1].rgbtBlue) / 4.0);
                }
                else //top row
                {
                    image[i][j].rgbtRed = (int) round((placeholder[i][j].rgbtRed + placeholder[i + 1][j].rgbtRed + placeholder[i][j + 1].rgbtRed +
                    placeholder[i + 1][j + 1].rgbtRed + placeholder[i][j - 1].rgbtRed + placeholder[i + 1][j - 1].rgbtRed) / 6.0);
                    image[i][j].rgbtGreen = (int) round((placeholder[i][j].rgbtGreen + placeholder[i + 1][j].rgbtGreen + placeholder[i][j + 1].rgbtGreen
                    + placeholder[i + 1][j + 1].rgbtGreen + placeholder[i][j - 1].rgbtGreen + placeholder[i + 1][j - 1].rgbtGreen) / 6.0);
                    image[i][j].rgbtBlue = (int) round((placeholder[i][j].rgbtBlue + placeholder[i + 1][j].rgbtBlue + placeholder[i][j + 1].rgbtBlue +
                    placeholder[i + 1][j + 1].rgbtBlue + placeholder[i][j - 1].rgbtBlue + placeholder[i + 1][j - 1].rgbtBlue) / 6.0);
                }
            }
            else if (i == (height - 1)) //if bottom row
            {
                if (j == 0) //if bottom, left corner
                {
                    image[i][j].rgbtRed = (int) round((placeholder[i][j].rgbtRed + placeholder[i - 1][j].rgbtRed + placeholder[i][j + 1].rgbtRed +
                    placeholder[i - 1][j + 1].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = (int) round((placeholder[i][j].rgbtGreen + placeholder[i - 1][j].rgbtGreen + placeholder[i][j + 1].rgbtGreen
                    + placeholder[i - 1][j + 1].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = (int) round((placeholder[i][j].rgbtBlue + placeholder[i - 1][j].rgbtBlue + placeholder[i][j + 1].rgbtBlue +
                    placeholder[i - 1][j + 1].rgbtBlue) / 4.0);
                }
                else if (j == (width - 1)) //if bottom, right corner
                {
                    image[i][j].rgbtRed = (int) round((placeholder[i][j].rgbtRed + placeholder[i - 1][j].rgbtRed + placeholder[i][j - 1].rgbtRed +
                    placeholder[i - 1][j - 1].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = (int) round((placeholder[i][j].rgbtGreen + placeholder[i - 1][j].rgbtGreen + placeholder[i][j - 1].rgbtGreen
                    + placeholder[i - 1][j - 1].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = (int) round((placeholder[i][j].rgbtBlue + placeholder[i - 1][j].rgbtBlue + placeholder[i][j - 1].rgbtBlue +
                    placeholder[i - 1][j - 1].rgbtBlue) / 4.0);
                }
                else //bottom row
                {
                    image[i][j].rgbtRed = (int) round((placeholder[i][j].rgbtRed + placeholder[i - 1][j].rgbtRed + placeholder[i][j + 1].rgbtRed +
                    placeholder[i - 1][j + 1].rgbtRed + placeholder[i][j - 1].rgbtRed + placeholder[i - 1][j - 1].rgbtRed) / 6.0);
                    image[i][j].rgbtGreen = (int) round((placeholder[i][j].rgbtGreen + placeholder[i - 1][j].rgbtGreen + placeholder[i][j + 1].rgbtGreen
                    + placeholder[i - 1][j + 1].rgbtGreen + placeholder[i][j - 1].rgbtGreen + placeholder[i - 1][j - 1].rgbtGreen) / 6.0);
                    image[i][j].rgbtBlue = (int) round((placeholder[i][j].rgbtBlue + placeholder[i - 1][j].rgbtBlue + placeholder[i][j + 1].rgbtBlue
                    + placeholder[i - 1][j + 1].rgbtBlue + placeholder[i][j - 1].rgbtBlue + placeholder[i - 1][j - 1].rgbtBlue) / 6.0);
                }
            }
            else if (j == 0) //if left column
            {
                image[i][j].rgbtRed = (int) round((placeholder[i][j].rgbtRed + placeholder[i + 1][j].rgbtRed + placeholder[i][j + 1].rgbtRed +
                placeholder[i + 1][j + 1].rgbtRed + placeholder[i - 1][j].rgbtRed + placeholder[i - 1][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = (int) round((placeholder[i][j].rgbtGreen + placeholder[i + 1][j].rgbtGreen + placeholder[i][j + 1].rgbtGreen
                + placeholder[i + 1][j + 1].rgbtGreen + placeholder[i - 1][j].rgbtGreen + placeholder[i - 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = (int) round((placeholder[i][j].rgbtBlue + placeholder[i + 1][j].rgbtBlue + placeholder[i][j + 1].rgbtBlue +
                placeholder[i + 1][j + 1].rgbtBlue + placeholder[i - 1][j].rgbtBlue + placeholder[i - 1][j + 1].rgbtBlue) / 6.0);
            }
            else if (j == (width - 1)) //if right column
            {
                image[i][j].rgbtRed = (int) round((placeholder[i][j].rgbtRed + placeholder[i + 1][j].rgbtRed + placeholder[i][j - 1].rgbtRed +
                placeholder[i + 1][j - 1].rgbtRed + placeholder[i - 1][j].rgbtRed + placeholder[i - 1][j - 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = (int) round((placeholder[i][j].rgbtGreen + placeholder[i + 1][j].rgbtGreen + placeholder[i][j - 1].rgbtGreen
                + placeholder[i + 1][j - 1].rgbtGreen + placeholder[i - 1][j].rgbtGreen + placeholder[i - 1][j - 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = (int) round((placeholder[i][j].rgbtBlue + placeholder[i + 1][j].rgbtBlue + placeholder[i][j - 1].rgbtBlue +
                placeholder[i + 1][j - 1].rgbtBlue + placeholder[i - 1][j].rgbtBlue + placeholder[i - 1][j - 1].rgbtBlue) / 6.0);
            }
            else //all middle
            {
                image[i][j].rgbtRed = (int) round((placeholder[i][j].rgbtRed + placeholder[i + 1][j].rgbtRed + placeholder[i][j + 1].rgbtRed +
                placeholder[i + 1][j + 1].rgbtRed + placeholder[i - 1][j].rgbtRed + placeholder[i - 1][j + 1].rgbtRed + placeholder[i - 1][j -
                1].rgbtRed + placeholder[i][j - 1].rgbtRed + placeholder[i + 1][j - 1].rgbtRed) / 9.0);
                image[i][j].rgbtGreen = (int) round((placeholder[i][j].rgbtGreen + placeholder[i + 1][j].rgbtGreen + placeholder[i][j + 1].rgbtGreen
                + placeholder[i + 1][j + 1].rgbtGreen + placeholder[i - 1][j].rgbtGreen + placeholder[i - 1][j + 1].rgbtGreen + placeholder[i - 1][j
                - 1].rgbtGreen + placeholder[i][j - 1].rgbtGreen + placeholder[i + 1][j - 1].rgbtGreen) / 9.0);
                image[i][j].rgbtBlue = (int) round((placeholder[i][j].rgbtBlue + placeholder[i + 1][j].rgbtBlue + placeholder[i][j + 1].rgbtBlue +
                placeholder[i + 1][j + 1].rgbtBlue + placeholder[i - 1][j].rgbtBlue + placeholder[i - 1][j + 1].rgbtBlue + placeholder[i - 1][j -
                1].rgbtBlue + placeholder[i][j - 1].rgbtBlue + placeholder[i + 1][j - 1].rgbtBlue) / 9.0);
            }
        }
    }
    return;
}