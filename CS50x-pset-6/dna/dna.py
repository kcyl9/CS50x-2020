from sys import argv, exit
import csv

# check for correct command-line argument amount
if len(argv) != 3:
    print("missing command-line argument")
    exit(1)

# initialization
first = True
count = 0
flag = True
start = 0
i = 0
j = 0
strs_amount = []
read = open(argv[2], "r")
seq = read.read()

# open the CSV file and read for STRs
with open(argv[1], "r", newline='') as data:
    reader = csv.reader(data)
    for strs in reader:
        # check for amount of STRs in the sequence
        if first:
            first = False
            for j in strs:
                letters = 0
                start = 0
                high = 0
                count = 0
                flag = True
                new = True
                while flag:
                    letters += 1
                    # if the STR amount is new
                    if new:
                        a = seq.find(j, start)
                    # if the STR amount is old
                    else:
                        a = seq.find(j, start, (start + (len(j)*2)))
                    # iterate through sequence to find STRs
                    if a == -1:
                        new = True
                        if count > high:
                            high = count
                        if letters >= len(seq):
                            flag = False
                        count = 0
                    else:
                        new = False
                        count += 1
                        start = a + 1
                strs_amount.append(high)
                i += 1

        # check if the amount of STRs correlate with a person
        else:
            j = 1
            check = False
            for j in range(1, i):
                if (strs_amount[j] == int(strs[j])):
                    check = True
                else:
                    check = False
                    break
                # if the STR counts match, print individual's name
                if check and j == (i - 1):
                    print(strs[0])
                    data.close()
                    read.close()
                    exit(0)

# print message if the STR counts do not match with any individuals
if check == False:
    print("No match")

# close files
data.close()
read.close()