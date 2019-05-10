from cs50 import get_int

while True:
    #Get credit card number from user
    cc_number = get_int("Credit card number: ")
    if cc_number > 0:
        break

length = 0
digit_one = 0
digit_two = 0
sum_of_doubles = 0
sum_of_singles = 0

while cc_number > 0:
    digit_two = digit_one
    digit_one = cc_number % 10

    if length % 2 == 0:
        sum_of_singles += digit_one
    else:
        multiple = 2 * digit_one
        sum_of_doubles += (multiple // 10 + multiple % 10)

    cc_number //= 10
    length += 1

is_valid = sum_of_singles + sum_of_doubles
first_two_digits = (digit_one * 10) + digit_two

#Check card number for length
if length == 13 or length == 15 or length == 16:
    #Check algorithm for valid number
    if is_valid % 10 == 0:
        if digit_one == 4:
            print("VISA")
        elif first_two_digits >= 51 and first_two_digits <= 55:
            print("MASTERCARD")
        elif first_two_digits == 34 or first_two_digits == 37:
            print("AMEX")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")
