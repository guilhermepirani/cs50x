import cs50
import csv
from sys import argv

# Check usage
if len(argv) != 2:
    print("Usage: python import.py file.csv")
    exit(1)


db = cs50.SQL("sqlite:///students.db")
with open(argv[-1], "r") as characters:
    
    # Create DictReader
    reader = csv.DictReader(characters)
    
    # Iterate through CSV file
    for row in reader:
        
        current_name = row["name"].split()
        if len(current_name) == 3:
            first = current_name[0]
            middle = current_name[1]
            last = current_name[2]
        else:
            first = current_name[0]
            middle = None
            last = current_name[1]
        
        house = row["house"]
        birth = row["birth"]
        
        # Insert students
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)