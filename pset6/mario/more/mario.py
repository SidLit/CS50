#Print a hashtag pyramid
from cs50 import get_int

#Get user input for pyramid height
while True:
    height = get_int("height: ")
    width = height
    if height >= 0 and height < 24:
        break

#Iterate through layers of pyramid
for i in range(1, height + 1):
    hashes = i
    spaces = width - hashes

    print(" " * spaces, end="")
    print("#" * hashes, end="")
    print("  ", end="")
    print("#" * hashes)

#Another implementation

#for i in range(height):
    #for j in range(2 * width + 2):
        #if j - i > height + 2:
            #print("", end="")
        #elif j == height or j == height + 1 or i + j < height - 1:
            #print(" ", end="")
        #else:
            #print("#", end="")
    #print()

