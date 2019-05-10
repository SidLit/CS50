// Copies a BMP file
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    float resiz_fctr = atof(argv[1]);

    if (resiz_fctr <= 0.00 || resiz_fctr > 100)
    {
        fprintf(stderr, "Resize factor should be > 0 or <= 100!\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // separate integer from decimal
    int left_of_decimal = resiz_fctr;
    float xa = resiz_fctr * 10;
    int xb = round(xa);
    int decml_rsz_fctr = xb % 10;
    int intgr_rsz_fctr = resiz_fctr;

    int intgrx = resiz_fctr;
    if (intgrx == 0)
    {
        intgrx = 1;
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
        return 4;
    }

    // determine padding for scanlines
    int orig_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // create copy of input file header info to use later
    long sz_width = bi.biWidth;
    long sz_height = bi.biHeight;
    long wdth = labs(bi.biWidth);
    long hght = labs(bi.biHeight);

    //calculate for smaller image (xf & xh)
    float xc = decml_rsz_fctr;
    float xd = xc / 10;
    float xe = wdth * xd;
    int xf = round(xe);
    float xg = hght * xd;
    int xh = round(xg);

    //calculate for larger image with decimal resize factor
    float xi = decml_rsz_fctr;
    float xj = left_of_decimal;
    if (left_of_decimal == 0) //prevents runtime error (division by 0)
    {
        xj = 1;
    }
    if (xi == 0) //prevents runtime error (division by 0)
    {
        xi = 1;
    }
    float xk = wdth * resiz_fctr;
    float xl = xk - (wdth * xj);
    float xm = xl / wdth;
    int xkint = round(xk);
    int xmint = round(xm * 10);
    float xn = hght * resiz_fctr;
    float xo = xn - (hght * xj);
    float xp = xo / hght;
    int xnint = round(xn);
    int xpint = round(xp * 10);

    // change for output file (header info)
    if (left_of_decimal != 0 && decml_rsz_fctr == 0)
    {
        bi.biWidth = wdth * intgr_rsz_fctr;
        bi.biHeight = hght * intgr_rsz_fctr;
        bi.biHeight = bi.biHeight - (bi.biHeight * 2);
    }
    else if (left_of_decimal != 0 && decml_rsz_fctr != 0)
    {
        bi.biWidth = xkint;
        bi.biHeight = xnint;
        bi.biHeight = bi.biHeight - (bi.biHeight * 2);
    }

    else if (left_of_decimal == 0 && decml_rsz_fctr != 0)
    {
        bi.biWidth = xf;
        bi.biHeight = xh;
        bi.biHeight = bi.biHeight - (bi.biHeight * 2);
    }

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // change for output file
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);

    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // create int for fseek to move back to beginning of line
    int move_cur = orig_padding + (sz_width * 3);

    // create variables for scan & print function
    int check = 0; //switch to avoid an enless loop
    int k = 0; //write pixel if less than k
    int y = 0; //switch to write pixel an extra time
    int za = 1; //counter for lines in infile
    int zb = 1; //counter for pixels in infile
    int zc = 0; //switch to skip scan line in outfile
    int zd = 0; //switch to skip pixel in outfile
    int l = 0; //write line if less than l
    int i = 0; //counter for lines in infile
    int j = 0; //iterate over infile pixel if less than j
    long bihght; //number of lines in infile

    // iterate over infile's scanlines
    for (i = 0, za = 1, bihght = labs(sz_height); i < bihght; za++, i++)
    {
        zc = 0;

        // copy lines n times
        for (l = 0, check = 0; (l < left_of_decimal || (l == 0 && left_of_decimal == 0)); l++)
        {
            // add lines for n.n
            if (left_of_decimal != 0 && decml_rsz_fctr != 0)
            {
                if (check == 0)
                {
                    switch (xpint)
                    {
                        case 1:
                            if (za == 5)
                            {
                                l--;
                                check++;
                            }

                            if (za == 10)
                            {
                                za -= 10;
                            }

                            break;

                        case 2:
                            if (za == 3 || za == 8)
                            {
                                l--;
                                check++;
                            }

                            if (za == 10)
                            {
                                za -= 10;
                            }

                            break;

                        case 3:
                            if (za == 2 || za == 5 || za == 9)
                            {
                                l--;
                                check++;
                            }

                            if (za == 10)
                            {
                                za -= 10;
                            }

                            break;

                        case 4:
                            if (za == 2 || za == 4 || za == 7 || za == 9)
                            {
                                l--;
                                check++;
                            }

                            if (za == 10)
                            {
                                za -= 10;
                            }

                            break;

                        case 5:
                            if (za == 1 || za == 3 || za == 5 || za == 7 || za == 9)
                            {
                                l--;
                                check++;
                            }

                            if (za == 10)
                            {
                                za -= 10;
                            }

                            break;

                        case 6:
                            if (za != 2 && za != 4 && za != 7 && za != 9)
                            {
                                l--;
                                check++;
                            }

                            if (za == 10)
                            {
                                za -= 10;
                            }

                            break;

                        case 7:
                            if (za != 2 && za != 6 && za != 9)
                            {
                                l--;
                                check++;
                            }

                            if (za == 10)
                            {
                                za -= 10;
                            }

                            break;

                        case 8:
                            if (za != 3 && za != 8)
                            {
                                l--;
                                check++;
                            }

                            if (za == 10)
                            {
                                za -= 10;
                            }

                            break;

                        case 9:
                            if (za != 6)
                            {
                                l--;
                                check++;
                            }

                            if (za == 10)
                            {
                                za -= 10;
                            }

                            break;

                    }
                }
            }

            // subtract lines for 0.n
            if (left_of_decimal == 0 && decml_rsz_fctr != 0)
            {
                switch (decml_rsz_fctr)
                {
                    case 1:
                        if (za != 5)
                        {
                            fseek(inptr, move_cur, SEEK_CUR);
                            zc = 1;
                        }

                        if (za == 10)
                        {
                            za -= 10;
                        }

                        break;

                    case 2:
                        if (za != 3 && za != 8)
                        {
                            fseek(inptr, move_cur, SEEK_CUR);
                            zc = 1;
                        }

                        if (za == 10)
                        {
                            za -= 10;
                        }

                        break;

                    case 3:
                        if (za != 2 && za != 5 && za != 9)
                        {
                            fseek(inptr, move_cur, SEEK_CUR);
                            zc = 1;
                        }

                        if (za == 10)
                        {
                            za -= 10;
                        }

                        break;

                    case 4:
                        if (za != 2 && za != 4 && za != 7 && za != 9)
                        {
                            fseek(inptr, move_cur, SEEK_CUR);
                            zc = 1;
                        }

                        if (za == 10)
                        {
                            za -= 10;
                        }

                        break;

                    case 5:
                        if (za == 2 || za == 4 || za == 6 || za == 8 || za == 10)
                        {
                            fseek(inptr, move_cur, SEEK_CUR);
                            zc = 1;
                        }

                        if (za == 10)
                        {
                            za -= 10;
                        }
                        break;

                    case 6:
                        if (za == 2 || za == 4 || za == 7 || za == 9)
                        {
                            fseek(inptr, move_cur, SEEK_CUR);
                            zc = 1;
                        }

                        if (za == 10)
                        {
                            za -= 10;
                        }

                        break;

                    case 7:
                        if (za == 2 || za == 6 || za == 9)
                        {
                            fseek(inptr, move_cur, SEEK_CUR);
                            zc = 1;
                        }

                        if (za == 10)
                        {
                            za -= 10;
                        }

                        break;

                    case 8:
                        if (za == 3 || za == 8)
                        {
                            fseek(inptr, move_cur, SEEK_CUR);
                            zc = 1;
                        }

                        if (za == 10)
                        {
                            za -= 10;
                        }

                        break;

                    case 9:
                        if (za == 6)
                        {
                            fseek(inptr, move_cur, SEEK_CUR);
                            zc = 1;
                        }

                        if (za == 10)
                        {
                            za -= 10;
                        }

                        break;
                }
            }
            // iterate over pixels in scanline
            if (zc == 0)
            {
                for (j = 0, zb = 1, zd = 0; j < sz_width; j++, zb++)
                {
                    zd = 0;

                    // add lines for n.n
                    if (left_of_decimal != 0 && decml_rsz_fctr != 0)
                    {
                        switch (xmint)
                        {
                            case 1:
                                if (zb == 5)
                                {
                                    y++;
                                }

                                if (zb == 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 2:
                                if (zb == 3 || zb == 8)
                                {
                                    y++;
                                }

                                if (zb == 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 3:
                                if (zb == 2 || zb == 5 || zb == 9)
                                {
                                    y++;
                                }

                                if (zb == 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 4:
                                if (zb == 2 || zb == 4 || zb == 7 || zb == 9)
                                {
                                    y++;
                                }

                                if (zb == 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 5:
                                if (zb == 1 || zb == 3 || zb == 5 || zb == 7 || zb == 9)
                                {
                                    y++;
                                }

                                if (zb == 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 6:
                                if (zb != 2 && zb != 4 && zb != 7 && zb != 9)
                                {
                                    y++;
                                }

                                if (zb == 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 7:
                                if (zb != 2 && zb != 6 && zb != 9)
                                {
                                    y++;
                                }

                                if (zb == 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 8:
                                if (zb != 3 && zb != 8)
                                {
                                    y++;
                                }

                                if (zb == 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 9:
                                if (zb != 6)
                                {
                                    y++;
                                }

                                if (zb == 10)
                                {
                                    zb -= 10;
                                }

                                break;

                        }
                    }

                    // delete lines for 0.n
                    if (left_of_decimal == 0 && decml_rsz_fctr != 0)
                    {
                        switch (decml_rsz_fctr)
                        {
                            case 1:
                                if (zb != 5)
                                {
                                    fseek(inptr, 3, SEEK_CUR);
                                    zd = 1;
                                }

                                if (zb >= 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 2:
                                if (zb != 3 && zb != 8)
                                {
                                    fseek(inptr, 3, SEEK_CUR);
                                    zd = 1;
                                }

                                if (zb >= 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 3:
                                if (zb != 2 && zb != 5 && zb != 9)
                                {
                                    fseek(inptr, 3, SEEK_CUR);
                                    zd = 1;
                                }

                                if (zb >= 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 4:
                                if (zb != 2 && zb != 4 && zb != 7 && zb != 9)
                                {
                                    fseek(inptr, 3, SEEK_CUR);
                                    zd = 1;
                                }
                                if (zb >= 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 5:
                                if (zb == 2 || zb == 4 || zb == 6 || zb == 8 || zb == 10)
                                {
                                    fseek(inptr, 3, SEEK_CUR);
                                    zd = 1;
                                }

                                if (zb >= 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 6:
                                if (zb == 2 || zb == 4 || zb == 7 || zb == 9)
                                {
                                    fseek(inptr, 3, SEEK_CUR);
                                    zd = 1;
                                }

                                if (zb >= 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 7:
                                if (zb == 2 || zb == 6 || zb == 9)
                                {
                                    fseek(inptr, 3, SEEK_CUR);
                                    zd = 1;
                                }

                                if (zb >= 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 8:
                                if (zb == 3 || zb == 8)
                                {
                                    fseek(inptr, 3, SEEK_CUR);
                                    zd = 1;
                                }

                                if (zb >= 10)
                                {
                                    zb -= 10;
                                }

                                break;

                            case 9:
                                if (zb == 6)
                                {
                                    fseek(inptr, 3, SEEK_CUR);
                                    zd = 1;
                                }

                                if (zb >= 10)
                                {
                                    zb -= 10;
                                }

                                break;
                        }
                    }

                    if (zd == 0)
                    {
                        // temporary storage
                        RGBTRIPLE triple;

                        // read RGB triple from infile
                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                        // copy pixel n times
                        for (k = (1 - y); k < (intgrx + 1); k++)
                        {
                            // write RGB triple to outfile
                            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                        }
                        y = 0;
                    }
                }
                // skip over padding, if any
                fseek(inptr, orig_padding, SEEK_CUR);

                // then add it back (to demonstrate how)
                for (int n = 0; n < padding; n++)
                {
                    fputc(0x00, outptr);
                }

                // move curser back to beginning of line
                if (left_of_decimal != 0)
                {
                    fseek(inptr, -move_cur, SEEK_CUR);
                }
            }
        }
        // move curser to end of line
        if (left_of_decimal != 0)
        {
            fseek(inptr, move_cur, SEEK_CUR);
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

