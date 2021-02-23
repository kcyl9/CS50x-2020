from cs50 import SQL
from sys import argv, exit
import csv

# database connection to execute SQL queries from Python script
db = SQL("sqlite:///students.db")

# checks for two command-line arguments, prompting an error if not fulfilled
if len(argv) != 2:
    print("Missing command-line argument")
    exit(1)

# open CSV file
with open(argv[1], "r", newline='') as data:
    reader = csv.reader(data)
    line_count = 0
    for row in reader:
        if line_count == 0: # ignore header line
            line_count += 1
            continue
        line_count += 1
        # set first column to name and split into first, middle, and last names
        name = row[0]
        name = name.split()
        first = name[0]
        if len(name) == 2:
            middle = None
            last = name[1]
        elif len(name) == 3:
            middle = name[1]
            last = name[2]

        # make students database
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, row[1], row[2])

# close file
data.close()