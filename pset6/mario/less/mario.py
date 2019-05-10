#Print a hashtag pyramid
from cs50 import get_int

#Prompt user for the pyramid height
while True:
    height = get_int("Height: ")
    if height >= 0 and height < 24:
        break

width = height + 1

#iterate through the rows of the pyramid and print spaces and hashtags
for i in range(height):
    hashes = i + 2
    spaces = width - hashes

    print(" " * spaces, end="")
    print("#" * hashes)

#Another implementation

#    for j in range(height + 1):
#        if i + j >= height - 1:
#            print("#", end="")
#        else:
#            print(" ", end="")
#    print()