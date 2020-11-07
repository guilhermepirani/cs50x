from cs50 import get_int

while True:
    heigth = get_int("Heigth: ")
    if 1 <= heigth <= 8:
        break
    
for row in range(1, heigth + 1):
    print(" " * (heigth - row) + "#" * row)