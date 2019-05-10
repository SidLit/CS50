#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void)
{
    string s = get_string("before: ");
    printf("after: ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            printf("%c", s[i] - ('a' - 'A'));
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}