#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void)
{
    string s = get_string("Name: ");
    for (int i = 0, n = strlen(s);  i < n; i++)
    {
        printf("%c %i", s[i], s[i]);
    }
}