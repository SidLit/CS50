#include<stdio.h>
#include<cs50.h>
#include<math.h>

int main(void)
//Print the least number of coins for change owed the user
{
    float co;

    //Prompt user for change owed
    do
    {
        co = get_float("change owed: ");
    }
    while (co <= 0);

    int cents = round(co * 100);
    int output = 0;

    int qtrs = 0;
    int dmes = 0;
    int nckls = 0;
    int pnnies = 0;

    //Check to see if we can use quarters
    while (cents >= 25)
    {
        cents -= 25;
        output += 1;
        qtrs++;
    }

    //Check to see if we can use dimes
    while (cents < 25 && cents > 9)
    {
        cents -= 10;
        output += 1;
        dmes++;
    }

    //Check to see if we can use nickels
    while (cents < 10 && cents > 4)
    {
        cents -= 5;
        output += 1;
        nckls++;
    }

    //Check to see if we can use pennies
    while (cents < 5 && cents > 0)
    {
        cents -= 1;
        output += 1;
        pnnies++;
    }
    printf("%i\n", output); //Print the least number of coins
    printf("quarters: %i\ndimes: %i\nnickels: %i\npennies: %i\n", qtrs, dmes, nckls, pnnies);
}