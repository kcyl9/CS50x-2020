from cs50 import get_int
import math

# prompt user for credit card number until positive number is inputted
while(True):
    number = get_int("Number: ")
    if (number > 0):
        break

# calculate length
i = 0
length = 0
while(i <= length):
    if number > pow(10, i):
        length += 1
    i += 1

# calculate checksum
# multiply every other digit by 2, starting with the number's second-to-last digit, and then add those products' digits together
total = 0
for i in range(2, length + 2, 2):
    add = ((number % pow(10, i)) / pow(10, i - 1))
    add = int(add)
    if math.floor(add * 2 / 10) == 0:
        total += (add * 2)
    else:
        total += (((add * 2) % 10) + 1)

# add the sum to the sum of the digits that weren't multiplied by 2
for i in range(1, length + 2, 2):
    add = ((number % pow(10, i)) / pow(10, i - 1))
    total += add
    total = int(total)

# check if checksum is valid
checksum = False
if total % 10 == 0:
    checksum = True

# check for card length and starting digits then print result
if checksum:
    if length == 15 and math.floor((number % pow(10, 15)) / pow(10, 14)) == 3 and math.floor(((number % pow(10, 14)) / pow(10, 13)) == 4 or math.floor((number % pow(10, 14)) / pow(10, 13)) == 7):
        print("AMEX")
    elif length == 16 and math.floor((number % pow(10, 16)) / pow(10, 15)) == 5 and math.floor((number % pow(10, 15)) / pow(10, 14)) <= 5 and math.floor((number % pow(10, 15)) / pow(10, 14)) >= 1:
        print("MASTERCARD")
    elif length == 13 and math.floor((number % pow(10, 13)) / pow(10, 12)) == 4:
        print("VISA")
    elif length == 16 and math.floor((number % pow(10, 16)) / pow(10, 15)) == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")