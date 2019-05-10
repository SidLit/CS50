import sys
import crypt

if not len(sys.argv) == 2:
    sys.exit("Usage: hash")

ahash = sys.argv[1]
salt = ahash[0:2]
letters = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

for fifth in letters:
    for fourth in letters:
        for third in letters:
            for second in letters:
                for first in letters:
                    password = f"{first}{second}{third}{fourth}{fifth}".strip()

                    if crypt.crypt(password, salt) == ahash:
                        print(password)
                        sys.exit(0)