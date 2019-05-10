//recovers JPEG files from memory
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover memory file\n");
        return 1;
    }
    // open input file
    char *inptr = argv[1];
    FILE *memoryCard = fopen(inptr, "r");
    if (memoryCard == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", inptr);
        return 2;
    }
    //allocate memory for one block of memory in memory card & create array for file name
    unsigned char block[512];
    char filename[8];

    //set counter for filename
    int counter = 0;

    //create output file
    FILE *img = NULL;

    //set flag
    bool fileOpen = false;

    //read the file
    while (fread(&block, 512, 1, memoryCard) == 1)
    {
        //check for beginning of JPEG file
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            //close current JPEG so we can start reading the next one
            if (fileOpen == true)
            {
                fclose(img);
            }
            //condition for found JPEG
            else
            {
                fileOpen = true;
            }
            sprintf(filename, "%03i.jpg", counter);

            img = fopen(filename, "w");

            counter++;
        }
        if (fileOpen == true)
        {
            fwrite(&block, 512, 1, img);
        }
    }
    //close all files
    fclose(memoryCard);
    fclose(img);

    //success
    return 0;
}


