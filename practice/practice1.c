#include <stdlib.h>
#include <math.h>
#include <cs50.h>
#include <string.h>
#include <stdio.h>

int main()
{
    string note = get_string("note: ");

    int count = strlen(note);
    float base = 440;
    float key = 0;

    if (count == 2)
    {
        int octave = atoi(&note[1]);
        for (int n = 4; n < octave; n++)
        {
            base *= 2;
        }
        for (int n = 4; n > octave; n--)
        {
            base = round(base / 2);
        }
    }
    else if (count == 3)
    {
        int octave = atoi(&note[2]);
        for (int n = 4; n < octave; n++)
        {
            base *= 2;
        }
        for (int n = 4; n > octave; n--)
        {
            base = round(base / 2);
        }
    }

    if (note[0] == 'B')
    {
        key = 2;
    }
    else if (note[0] == 'C')
    {
        key = -9;
    }
    else if (note[0] == 'D')
    {
        key = -7;
    }
    else if (note[0] == 'E')
    {
        key = -5;
    }
    else if (note[0] == 'F')
    {
        key = -4;
    }
    else if (note[0] == 'G')
    {
        key = -2;
    }

    if (note[1] == '#')
    {
        key += 1;
    }
    else if (note[1] == 'b')
    {
        key -= 1;
    }

    int tone = round(pow(2, (key / 12)) * base);

    printf("%i\n", tone);
    return 0;
}
