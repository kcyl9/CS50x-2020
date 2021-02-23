from sys import argv, exit
from cs50 import SQL

# database connection to execute SQL queries from Python script
db = SQL("sqlite:///students.db")

# checks for two command-line arguments, prompting an error if not fulfilled
if len(argv) != 2:
    print("Missing command-line argument")
    exit(1)

# query database for all students in house
student_list = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first;", argv[1])

# print
for row in student_list:
    if row["middle"] == None:
        print(row["first"], row["last"] + ", born " + str(row["birth"]))
    else:
        print(row["first"], row["middle"], row["last"] + ", born " + str(row["birth"]))