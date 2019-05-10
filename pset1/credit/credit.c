#include<stdio.h>
#include<cs50.h>

int main()
{
    long long cc;
    //Prompt the user for their credit card number
    do
        cc = get_long_long("Credit card number: ");
    while (cc < 0);

    //Count the credit card number and if it does not equal 13, 15, or 16 digits print "INVALID"
    int count = 0;

    for (long long temp = cc; temp > 0; count++)
        temp /= 10;

    if (count != 13 && count != 15 && count != 16){
        printf("INVALID\n");
        return 1;
    }

    //Make an array called "reverse" with credit card number in reverse order
    long long reverse[count];

    for (int i = 0; i < count; i++){
        reverse[i] = cc % 10;
        cc /= 10;
    }

    //Make an array called "eo" that takes every other number and multiplies by two
    int eo[count];

    for (int i = 1; i < count; i += 2)
        eo[i] = reverse[i] * 2;

    //Split the numbers that were multiplied by two into single digits and add them together
    int eosum = 0;

    for (int i = 1; i < count; i += 2)
        eosum += eo[i] % 10 + eo[i] / 10;

    //Make an array called "rest" that collects the rest of the numbers
    int rest[count];

    for (int i = 0; i < count; i += 2)
        rest[i] = reverse[i];

    //Take the numbers from "rest" and add them together
    int restsum = 0;

    for (int i = 0; i < count; i += 2)
        restsum += rest[i];

    //If the total of modulo 10 is not congruent to 0 print "INVALID"
    int total = eosum + restsum;

    if (total % 10 != 0){
        printf("INVALID\n");
        return 2;
    }

    //Identify whether the credit card is "AMEX", "MASTERCARD", "VISA", or "INVALID"
    if (reverse[14] == 3 && (reverse[13] == 4 || reverse[13] == 7))
        printf("AMEX");
    else if (reverse[15] == 4 || reverse[12] == 4)
        printf("VISA");
    else if (reverse[15] == 5 && (reverse[14] == 1 || reverse[14] == 2 || reverse[14] == 3 || reverse[14] == 4 || reverse[14] == 5))
        printf("MASTERCARD");
    else
        printf("INVALID");
    printf("\n");
}





