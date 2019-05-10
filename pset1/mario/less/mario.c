#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Prompt user for a number
    int n;

    do
    {
        n = get_int("Height:");
    }
    while (n < 0 || n > 23);

    // Print hashtag pyramid
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            if (i + j >= n - 1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

        printf("\n");
    }

}