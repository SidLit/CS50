#define _XOPEN_SOURCE

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>


int main(int argc, string argv[])
{
    //Be sure user inputs a hash to be decrypted
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    char *crypt(const char *key, const char *salt);
    //Make an array with all possible password characters
    char alpha[52] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char salt[3] = {argv[1][0], argv[1][1], 0};
    char password_one[2];
    password_one[1] = 0;

    //Check all single character possibilities
    for (int i = 0; i < 52; i++)
    {
        password_one[0] = alpha[i];
        if (strcmp(argv[1], crypt(password_one, salt)) == 0)
        {
            printf("%s\n", password_one);
            return 0;
        }
    }

    char password_two[3];
    password_two[2] = 0;

    //Check all possible two character combinations
    for (int i = 0; i < 52; i++)
    {
        password_two[0] = alpha[i];
        for (int j = 0; j < 52; j++)
        {
            password_two[1] = alpha[i];
            {
                if (strcmp(argv[1], crypt(password_two, salt)) == 0)
                {
                    printf("%s\n", password_two);
                    return 0;
                }
            }
        }
    }

    //Check all three character combinations
    char password_three[4];
    password_three[3] = 0;

    for (int i = 0; i < 52; i++)
    {
        password_three[0] = alpha[i];
        for (int j = 0; j < 52; j++)
        {
            password_three[1] = alpha[j];
            for (int k = 0; k < 52; k++)
            {
                password_three[2] = alpha[k];
                {
                    if (strcmp(argv[1], crypt(password_three, salt)) == 0)
                    {
                        printf("%s\n", password_three);
                        return 0;
                    }
                }
            }
        }
    }

    char password_four[5];
    password_four[4] = 0;

    //Check all four character combinations
    for (int i = 0; i < 52; i++)
    {
        password_four[0] = alpha[i];
        for (int j = 0; j < 52; j++)
        {
            password_four[1] = alpha[j];
            for (int k = 0; k < 52; k++)
            {
                password_four[2] = alpha[k];
                for (int l = 0; l < 52; l++)
                {
                    password_four[3] = alpha[l];
                    {
                        if (strcmp(argv[1], crypt(password_four, salt)) == 0)
                        {
                            printf("%s\n", password_four);
                            return 0;
                        }
                    }
                }
            }
        }
    }

    char password_five[6];
    password_five[5] = 0;

    //Check all five character combinations
    for (int i = 0; i < 52; i++)
    {
        password_five[0] = alpha[i];
        for (int j = 0; j < 52; j++)
        {
            password_five[1] = alpha[j];
            for (int k = 0; k < 52; k++)
            {
                password_five[2] = alpha[k];
                for (int l = 0; l < 52; l++)
                {
                    password_five[3] = alpha[l];
                    for (int m = 0; m < 52; m++)
                    {
                        password_five[4] = alpha[m];
                        {
                            if (strcmp(argv[1], crypt(password_five, salt)) == 0)
                            {
                                printf("%s\n", password_five);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
}