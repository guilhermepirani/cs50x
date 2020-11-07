from cs50 import get_string

card_number = get_string("Number: ")

# Luhn's Algorithm
test_number = card_number[::-1]
odd_sum = sum([((int(digit) * 2) // 10) + ((int(digit) * 2) % 10) for digit in test_number[1::2]])
pair_sum = sum([int(digit) for digit in test_number[::2]])

# Checks provider if Luhn' valid
if (pair_sum + odd_sum) % 10 == 0:
    if len(card_number) == 16 and 51 <= int(card_number[:2]) <= 55:
        print("MASTERCARD")
        
    elif len(card_number) == 15 and card_number[:2] in ["34", "37"]:
        print("AMEX")
        
    elif len(card_number) in [13, 16] and card_number[0] == "4":
        print("VISA")
        
    else:
        print("INVALID")

# Prints invalid otherwise        
else:
    print("INVALID")
