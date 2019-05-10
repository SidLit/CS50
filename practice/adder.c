#include<stdio.h>
#include<cs50.h>

float add_two_floats(float a, float b);

int main(void)
{
    float x = get_float("Give me an integer: ");
    float y = get_float("Give me an integer: ");

    float z = add_two_floats(x, y);

    printf("%f + %f = %f\n", x, y, z);
}

float add_two_floats(float a, float b)
{
    float sum = a + b;
    return sum;
}