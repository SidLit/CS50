#include<stdio.h>
#include<cs50.h>

bool valid_triangle(float a, float b, float c);

int main(void)
{
    int x = get_float("Give me a number: ");
    int y = get_float("Give me a number: ");
    int z = get_float("Give me a number: ");

    if (x <= 0 || y <= 0 || z <= 0)
    {
        return false;
    }
    if ((x + y <= z) || (y + z <= x) || (z + x <= y))
    {
        printf("false");
    }
    else
    {
        printf("true");
    }
    printf("\n");

}