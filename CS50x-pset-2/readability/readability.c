#include <stdio.h>
#include <cs50.h>
#include <string.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);

int main(void)
{
    string s = get_string("Text: "); //input reading passage from user

    int letters = count_letters(s); //find number of letters
    int words = count_words(s); //find number of words
    int sentences = count_sentences(s); //find number of sentences

    //calculate grade (index)
    float grade = 0.0588 * ((float)100 * letters / words) - 0.296 * ((float)100 * sentences / words) - 15.8;

    //Output
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", grade);
    }
}

int count_letters(string s)
{
    //initialization
    int letters = 0;

    //count letters by using ascii codes
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))
        {
            letters++;
        }
    }

    //return number of letters
    return letters;
}

int count_words(string s)
{
    //initialization
    int words = 1;

    //count words - Ascii code for space = 32
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == 32)
        {
            words++;
        }
    }

    //return number of words
    return words;
}

int count_sentences(string s)
{
    //initialization
    int sentences = 0;

    //count sentences each time there is '.', '!', or '?'
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == 46 || s[i] == 63 || s[i] == 33)
        {
            sentences++;
        }
    }

    //return number of sentences
    return sentences;
}
