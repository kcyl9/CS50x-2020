// Implements a dictionary's functionality

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 531441;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
//Should be case insensitive
bool check(const char *word)
{
    int bucket = hash(word);

    //start at the beginning of the node
    node *cursor = table[bucket];

    //traverse the linked list
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0) //if word is found in dictionary
        {
            return true;
        }
        cursor = cursor->next; //move to next item in linked list
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int bucket = 0;
    //Computed sum of ascii codes of first four letters if they exist
    //Power function to separate first letter from second, and so forth
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(&word[i], "\0") != 0)
        {
            bucket += (pow((toupper(word[i]) - 39), (i + 1)));
        }
        else
        {
            break;
        }
    }
    return bucket % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    //Initialize hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = malloc(sizeof(node));
        table[i] = NULL;
    }

    //Read file
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        else
        {
            strcpy(n->word, word);
            int bucket = hash(word);
            //Insert node into hash table
            if (table[bucket] == NULL)
            {
                table[bucket] = n;
            }
            else
            {
                n->next = table[bucket];
                table[bucket] = n;
            }
            size();
        }
    }

    fclose(file);
    return true;
}

int word_count = 0;
int first = true;

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (first)
    {

    }
    else
    {
        word_count++;
    }
    first = false;
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        free(cursor);
    }
    return true;
}