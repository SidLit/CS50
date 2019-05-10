// Copies a BMP file
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy -resize key- infile outfile\n");
        return 1;
    }

    float factor = atof(argv[1]);

    //ensure resizing key is a floating point number between 0.0 and 100.0
    if (factor <= 0.0 || factor > 100.0)
    {
        fprintf(stderr, "please provide a resizing key between 0.0 and 100.0\n");
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
        //determine old width and height
        int oldWidth = bi.biWidth;
        int oldHeight = abs(bi.biHeight);

        //determine new width and height
        int newWidth = (oldWidth * factor);
        int newHeight = (oldHeight * factor);

        // determine padding for scanlines
        int oldPadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        int newPadding = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        bi.biWidth = newWidth;
        bi.biHeight *= factor;
        bi.biSizeImage = ((sizeof(RGBTRIPLE) * newWidth) + newPadding) * newHeight;
        bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

        // write outfile's BITMAPFILEHEADER
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

        // write outfile's BITMAPINFOHEADER
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

        //allocate memory to store one scanline
        RGBTRIPLE scanline[newWidth * sizeof(RGBTRIPLE)];

    if (factor >= 1)
    {
        int n = atoi(argv[1]);

        // iterate over infile's scanlines
        for (int i = 0; i < oldHeight; i++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < oldWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                //copy pixels to scanline factor times
                for (int k = 0; k < factor; k++)
                {
                    scanline[(j * n) + k] = triple;
                }
            }

            // skip over padding, if any
            fseek(inptr, oldPadding, SEEK_CUR);

            //write the current scanline factor times
            for (int l = 0; l < factor; l++)
            {
                // write RGB triple to outfile
                fwrite(scanline, sizeof(RGBTRIPLE), newWidth, outptr);

                //write new padding
                for (int m = 0; m < newPadding; m++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
    }
    else
    {
        int nFactor = (1 / factor);

        //iterate over infiles scanlines
        for (int i = 0; i < oldHeight; i++)
        {
            //iterate over pixels in scanline
            for (int j = 0, k = 0; j < oldWidth; j++)
            {
                //temporary storage
                RGBTRIPLE triple;

                //read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                if (i % nFactor == 0 && j % nFactor == 0)
                {
                    scanline[k] = triple;

                    k++;
                }
            }
            //skip over padding, if any
            fseek(inptr, oldPadding, SEEK_CUR);

            if (i % nFactor == 0)
            {
                //write RGB triple to outfile
                fwrite(scanline, sizeof(RGBTRIPLE), newWidth, outptr);

                //write new padding
                for (int l = 0; l < newPadding; l++)
                {
                    fputc(0x00, outptr);
                }
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
