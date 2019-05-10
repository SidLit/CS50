// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

//the root node of the trie
node *root;

//counter for the number of words in the dictionary
int word_counter = 0;

//prototype to allow recursion
void clear(node *trav);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int length = strlen(word);

    //points to the current node as the program travels through the trie
    node *trav = root;

    for (int i = 0; i < length; i++)
    {
        char c = tolower(word[i]);

        //check if character is an apostrophe
        if (c == '\'')
        {
            //123 - 'a' = 26 (apostrophes go at children[26)
            c = 123;
        }

        //get the address of the next node in the trie
        struct node *nextNode = trav -> children[c - 'a'];

        if (nextNode == NULL)
        {
            return false;
        }
        else
        {
            trav = nextNode;
        }
    }
    //check if word is in the dictionary
    if (trav -> is_word == true)
    {
        return true;
    }
    return false;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open the dictionary file
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        fclose(dict);
        fprintf(stderr, "fail to open dictionary\n");
        return false;
    }

    //allocate space for the first root node
    root = calloc(1, sizeof(node));

    //points to the current node as the program travels through the trie
    node *trav = root;

    for (char c = tolower(fgetc(dict)); c != EOF; c = fgetc(dict))
    {
        //if the word is finished
        if (c == '\n')
        {
            //check that the word is at least one letter long
            if (trav != root)
            {
                word_counter++;

                trav -> is_word = true;

                //reset the pointer back to the top of the trie
                trav = root;
            }
        }
        else
        {
            //check if the character is an apostrophe
            if (c == '\'')
            {
                //123 - 'a' = 26 (apostrophes go to children[26)
                c = 123;
            }

            //get the address of the next node in the trie
            struct node *nextNode = trav -> children[c - 'a'];

            if (nextNode == NULL)
            {
                //allocate space if needed
                trav -> children[c - 'a'] = calloc(1, sizeof(node));

                trav = trav -> children[c - 'a'];
            }
            else
            {
                trav = nextNode;
            }
        }
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

//recursive function that frees a trie from memory
void clear(node *trav)
{
    for (int i = 0; i < 27; i++)
    {
        if (trav -> children[i] != NULL)
        {
            clear(trav -> children[i]);
        }
    }
    free(trav);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    clear(root);
    return true;
}
