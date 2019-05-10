#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

//Takes plaintext and key from user and as input, and outputs ciphertext
int main(int argc, string argv[])
{
    //Conditions for command line argument
    if (argc != 2)
    {
        printf("Usage: key\n");
        return 1;
    }

    //argument 1 is program name and argument 2 is cryptography key
    int key = atoi(argv[1]);

    if (key <= 0)
    {
        printf("Usage: key\n");
        return 1;
    }

    //Prompt the user for text that needs to be encrypted
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    //Uses the key supplied by user to encrypt plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                //takes uppercase plaintext as input, preserves case, and outputs uppercase ciphertext
                printf("%c", (plaintext[i] + key - 'A') % 26 + 'A');
            }
            else if (islower(plaintext[i]))
            {
                //takes lowercase plaintext as input, preserves case, and outputs lowercase ciphertext
                printf("%c", (plaintext[i] + key - 'a') % 26 + 'a');
            }
        }
        else
        {
            //takes non-alphabetic input and outputs without changes
            printf("%c", plaintext[i]);
        }

    }
    printf("\n");
}