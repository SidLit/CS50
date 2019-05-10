from cs50 import get_string
import sys

if not len(sys.argv) == 2:
    print("Usage: key")
    sys.exit(1)

#User provided encryption key via command line argument
key = int(sys.argv[1])

#conditions for key
if key < 1:
    print("Usage: key")
    sys.exit(2)

#Prompt user for text to be encrypted
plaintext = get_string("plaintext: ")

print("ciphertext: ", end="")


for digit in plaintext:
    #Checks for non alphabetic input and outputs without changes
    if not digit.isalpha():
        print(digit, end="")
        continue

    #Takes alpabetic input, preserves case, encrypts, and outputs ciphertext
    ascii_offset = 65 if digit.isupper() else 97
    index = ord(digit) - ascii_offset
    encrypt = (index + key) % 26

    print(chr(encrypt + ascii_offset), end="")

print()
