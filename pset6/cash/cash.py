from cs50 import get_float

# Get change owed value
while True:
    owed = get_float("Change owed: ")
    if owed > 0:
        break

# Trasforming dollars to cents, making sure it's an integer
cents = int(owed * 100)

coins = 0
# For each value in the list it divides cents by the value
# Adding the result to coins and refreshing cents with the modulo
for coin in [25, 10, 5, 1]:
    coins += cents // coin
    cents %= coin

print(coins)