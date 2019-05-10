import sys
from cs50 import get_string

if not len(sys.argv) == 2:
    print("Usage: key")
    sys.exit(1)

#User provided encryption key via command line argument
key = sys.argv[1]

#Key must be alphabetic
for c in key:
    if not c.isalpha():
        print("Usage: key")
        sys.exit(1)

#Prompt user for text to be encrypted
plaintext = get_string("plaintext: ")
i = 0

print("ciphertext: ", end="")

for c in plaintext:
    #Checks for non-alphabetic input and outputs without changes
    if not c.isalpha():
        print(c, end="")
        continue

    #Takes alphabetic input, preserves case, encrypts, and outputs ciphertext
    ascii_offset = 65 if c.isupper() else 97
    p_index = ord(c) - ascii_offset
    key_index = ord(key[i % len(key)].upper()) - 65
    cipher = (p_index + key_index) % 26
    i += 1

    print(chr(cipher + ascii_offset), end="")

print()