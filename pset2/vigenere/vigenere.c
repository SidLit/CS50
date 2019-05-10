#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int main(int argc, string argv[])
{
    //Conditions for command line argument
    if (argc != 2)
    {
        printf("Usage: ./vigenere key\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (! isalpha(argv[1][i]))
        {
            printf("Usage: ./vigenere key\n");
            return 1;
        }
    }

    //Prompt the user for text that needs to be encrypted
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    int key[strlen(argv[1])];

    //Pass user supplied keyword into an int array and shift from ascii value to index value
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isupper(argv[1][i]))
        {
            key[i] = argv[1][i] - 'A';
        }
        else if (islower(argv[1][i]))
        {
            key[i] = argv[1][i] - 'a';
        }
    }

    //Uses the new key to encrypt plaintext
    for (int i = 0, j = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                printf("%c", (plaintext[i] + key[j % strlen(argv[1])] - 'A') % 26 + 'A');
            }
            else if (islower(plaintext[i]))
            {
                printf("%c", (plaintext[i] + key[j % strlen(argv[1])] - 'a') % 26 + 'a');
            }
            j++;
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}