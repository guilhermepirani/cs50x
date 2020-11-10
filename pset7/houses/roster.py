import cs50
from sys import argv

# Check usage
if len(argv) != 2:
    print("Usage: python roster.py House Name")
    exit(1)
    
# Open db as db
db = cs50.SQL("sqlite:///students.db")
students = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", argv[-1])

# Prints formated info
for row in students:
    print(row["first"] + " " + (row["middle"] + " " if row["middle"] else "") + row["last"] + ", " + "Born " + str(row["birth"]))