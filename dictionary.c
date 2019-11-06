// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

int c = 0; //initialize the dictionary word counter

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }


    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        int head = hash(word);

        node *new_node = malloc(sizeof(node)); //Allocate space for a new node



        if (new_node == NULL)  //Checks if we ran out of memory
        {
            unload();
            return false;
        }



        strcpy(new_node -> word, word); //copy the word into the node

        new_node-> next = NULL;

        if(hashtable[head] == NULL) //if we're at the first node
        {

            hashtable[head] = new_node;

        }
        else
        {

            new_node-> next = hashtable[head];
            hashtable[head] = new_node;

        }

        c++;    //count the words
    }
    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return c;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    int head = hash(word);

    node *cursor = hashtable[head];

    while (cursor != NULL)
    {
        int result = strcasecmp(word, cursor-> word);
        if (!result)
        {
            cursor = cursor -> next;

        }
        else
        {
            return true;
        }
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }

    }

    return true;
}
