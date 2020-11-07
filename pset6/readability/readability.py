from cs50 import get_string

text = get_string("Text: ")

# Starting variables, words starts as 1 cus we count a word per space
letters = sentences = 0
words = 1

# Counting
for item in text:
    if item.isalpha():
        letters += 1
    if item.isspace():
        words += 1
    if item in ["?", ".", "!"]:
        sentences += 1

# Applying formula
L = (letters * 100) / words
S = (sentences * 100) / words

result = round(0.0588 * L - 0.296 * S - 15.8)

# Printing results
if result < 1:
    print("Before Grade 1")
    
elif result >= 16:
    print("Grade 16+")
    
else:
    print(f"Grade {result}")