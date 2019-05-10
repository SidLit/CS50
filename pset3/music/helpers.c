// Helper functions for music
#include <math.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
    int numerator = atoi(&fraction[0]);
    int denominator = atoi(&fraction[2]);

    if (denominator == 8)
    {
        return numerator;
    }
    else if (denominator == 4)
    {
        return numerator * 2;
    }
    else if (denominator == 2)
    {
        return numerator * 4;
    }
    else
    {
        return false;
    }

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO
    int count = strlen(note);
    float base = 440;
    float key = 0;

    //identify the octave of natural notes and check it's proximity to octave 4 and adjusts base up or down accordingly
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
    //identify the octave of sharp or flat notes check it's proximity to octave 4 and adjusts base up or down accordingly
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

    //identify the note and its proximity to note A and adjusts key up or down accordingly
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

    //Identify sharp and flat and notes adjust up or down one semitone
    if (note[1] == '#')
    {
        key += 1;
    }
    else if (note[1] == 'b')
    {
        key -= 1;
    }

    //Uses the result of base(octave) and key(note) and figures frequency
    int tone = round(pow(2, (key / 12)) * base);

    return tone;

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO
    if (s[0] == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }
}
