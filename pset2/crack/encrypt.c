#define _XOPEN_SOURCE

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, string argv[])
{
    char *crypt(const char *key, const char *salt);
    char salt[3] = {argv[2][0], argv[2][1], 0};
    string hash = crypt(argv[1], salt);
    printf("%s\n", hash);
}

