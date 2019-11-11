// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

//Initialize dictionary word counting
int word_count = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));

    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;

    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
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
    node *new_node = NULL;

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        node *cursor = root;


        for(int i = 0, L = strlen(word); i < L; i++) //Iterating through the word
        {
            int bucket = word[i] - 'a'; //Which bucket should the letter go into

            if(word[i] == '\'')
            {
                bucket = 26;
            }


            if(cursor-> children[bucket] == NULL)
            {
                new_node = malloc(sizeof(node));

                if (new_node == NULL)
                {
                    return false;
                }
                new_node->is_word = false;

                for (int j = 0; j < 27; j++)
                {
                    new_node-> children[j] = NULL;
                }

                cursor-> children[bucket] = new_node;
                cursor = cursor-> children[bucket];

            }
            else
            {
                cursor = cursor-> children[bucket];
            }

        }


        cursor-> is_word = true;
        word_count++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;


}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = root;

    for(int i = 0, L = strlen(word); i < L; i++)
    {
        int bucket = tolower(word[i]) - 'a';

        if(word[i] == '\'')
            {
                bucket = 26;
            }

        if(cursor-> children[bucket] == NULL)
        {
            return false;
        }
        else
        {
            cursor = cursor-> children[bucket];
        }
    }
    if(cursor-> is_word == true)
    {
        return true;
    }
    else
    {
        return false;
    }

}

void cleanse(node *ptr)
{
    for(int i = 0; i < N; i++)
    {
        if (ptr->children[i] != NULL)
        {
            cleanse(ptr->children[i]);
        }
    }
    free(ptr);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor = root;

    cleanse(cursor);

    return true;
}
