// Copies a BMP file
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy key infile outfile\n");
        return 1;
    }

    //remember size multiplier
    int factor = atoi(argv[1]);

    if (factor < 1 || factor > 100)
    {
        fprintf(stderr, "Please provide a resizing key between 0 and 100\n");
        return 2;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    //old width and height
    int oldWidth = bi.biWidth;
    int oldHeight = abs(bi.biHeight);

    //new width and height
    int newWidth = oldWidth * factor;
    int newHeight = oldHeight * factor;

    //determine old padding for scanlines
    int oldPadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //determine new padding for scanlines
    int newPadding = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biHeight *= factor;
    bi.biWidth = newWidth;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * newWidth) + newPadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //allocate memory to store one scanline
    RGBTRIPLE scanline[newWidth * sizeof(RGBTRIPLE)];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int k = 0; k < factor; k++)
            {
                scanline[(j * factor) + k] = triple;
            }
        }
        // skip over padding, if any
        fseek(inptr, oldPadding, SEEK_CUR);

        //write the current scanline key times
        for (int l = 0; l < factor; l++)
        {
            //write a new scanline once
            fwrite(scanline, sizeof(RGBTRIPLE), newWidth, outptr);

            //write new padding
            for (int m = 0; m < newPadding; m++)
            {
                fputc(0x00, outptr);
            }
        }
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
