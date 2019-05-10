#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;

    //Prompt user for a number between 0 and 24
    do
        n = get_int("Height: ");
    while (n < 0 || n > 23);

    for (int i = 0; i < n; i++){  //i determines # of rows
        for (int j = 0; j < 2 * n + 2; j++){    //j determines # of characters
            if (j - i > n + 2)
                printf("");
            else if (j == n || j == n + 1 || i + j < (n - 1))
                printf(" ");
            else
                printf("#");
        }
        printf("\n");
    }
}

