// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1 + ('z' * LENGTH);

// Hash table
int sum_words = 0;
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Get hash index
    int index = hash(word);
    
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int sum = 0;
    for (int w = 0; w < strlen(word); w++)
    {
        sum += tolower(word[w]);
    }
    return (sum % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opening dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    
    // Read file one word at a time
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // create a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        
        strcpy(n->word, word);
        n->next = NULL;
        
        // Get hash index
        int index = hash(word);
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        sum_words++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return sum_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Free list
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;
        
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
