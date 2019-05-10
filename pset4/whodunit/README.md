# Questions

## What's `stdint.h`?

a C standard library header file that provides typedefs

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

to be specific aabout the number of bits in an integer so as to work universally across any system environment

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM

## What's the difference between `bfSize` and `biSize`?

bfSize is the total size of the file including pixels, padding and headers... biSize is the size of the image including pixels and padding

## What does it mean if `biHeight` is negative?

the bitmap is a top-down DIB(device independant bitmap) and it's origin is the upper-left corner

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

It means the file may not exist or there is a permission error

## Why is the third argument to `fread` always `1` in our code?

because the program iterates over the file 1 pixel at a time

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

1

## What does `fseek` do?

fseek is a function that we use to move our position in the file

## What is `SEEK_CUR`?

our current position in the file

## Whodunit?

Professor Plum with the candlestick in the library
