// Implements a dictionary's functionality
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 
#include <stdbool.h>

#include "dictionary.h"

#define HTSIZE 26

typedef struct _node 
{
    char word[LENGTH + 1];
    struct _node* next;
}
node;

node* hashtable[HTSIZE];

// returns hash
int hash(const char *word)
{
    int baseAsciiIndex = 97;
    int alphaIndex = ( tolower(word[0]) - baseAsciiIndex ) % 26;
    return alphaIndex;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // get hash of the word
    int h = hash(word);

    node* ptr = hashtable[h];

    // copy with 'tolower' in tmp var for case insensitive search
    int size = strlen(word);
    char lword[size + 1];
    for ( int i = 0; i < size + 1; i++ )
        lword[i] = tolower(word[i]);

    while ( ptr != NULL )
    {
        if ( strcmp(ptr->word, lword) == 0 )
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // properly initialize hashtable to NULL
    for ( int i = 0; i < HTSIZE; i++ )
        hashtable[i] = NULL;

    // open dictionary file
    FILE *dictptr = fopen(dictionary, "r");
    if (dictptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];

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
        strcpy(new_node->word, word);
        // set next to NULL, to avoid pointing to garbage values
        new_node->next = NULL;

        // hash 
        int h = hash(word); //TODO
        
        // put into hashtable
        new_node->next = hashtable[h];
        hashtable[h] = new_node;
    }

    fclose(dictptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;

    for ( int i = 0; i < HTSIZE ; i++ )
    {
        node* ptr = hashtable[i];
        while ( ptr != NULL )
        {
            count++;
            ptr = ptr->next;
        }
    }
    
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for ( int i = 0; i < HTSIZE ; i++ )
    {
        node* ptr = hashtable[i];
        while ( ptr != NULL )
        {
            node* next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    return true;
}
