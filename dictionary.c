// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#define HTSIZE 26

type struct _node 
{
    char word[LENGTH + 1];
    struct _node* next;
}
node;

node* hashtable[HTSIZE];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // properly initialize hashtable to NULL
    for ( i = 0; i < HTSIZE; i++ )
        hashtable[i] = NULL;

    // open dictionary file
    FILE *dictptr = fopen(dictionary, "r");
    if (dictptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    while ( fscanf(dictptr, "%s", word) != EOF )
    {
        // allocate space for a new node, error check
        node* new_node = malloc(sizeof(node));
        if ( new_node == NULL )
        {
            unload();
            return false;
        }

        // copy word into node
        strcopy(new_node->word, word);
        // set next to NULL, to avoid pointing to garbage values
        new_node->next = NULL;

        // hash TODO
        
        // put into hashtable


    }

    fclose(dictptr);
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
