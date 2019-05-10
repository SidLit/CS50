from cs50 import get_float

while True:
    #Get user input for change owed
    change = get_float("change owed: ")
    if change > 0:
        break

cents = round(change * 100)
coins = 0

#Iterates through the change owed, always looking for the largest coin that will fit
while cents > 0:
    if cents > 24:
        coins += cents // 25
        cents = cents % 25
    elif cents < 25 and cents > 9:
        coins += cents // 10
        cents = cents % 10
    elif cents < 10 and cents > 4:
        coins += cents // 5
        cents = cents % 5
    elif cents < 5 and cents > 0:
        coins += cents // 1
        cents = cents % 1

print(coins)

#Alternative implementation

#while cents > 0:
#    if cents >= 25:
#        cents -= 25
#        coins += 1
#    elif cents < 25 and cents >= 10:
#        cents -= 10
#        coins += 1
#    elif cents < 10 and cents >= 5:
#        cents -= 5
#        coins += 1
#    elif cents < 5 and cents > 0:
#        cents -= 1
#        coins += 1

#print(coins)

