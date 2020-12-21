from cs50 import get_int

# get height from user within range of 1 to 8
while True:
    height = get_int("Height: ")
    if (height <= 8 and height >= 1):
        break

# make pyramid
for row in range(height):
    # print spaces
    for spaces in range((height - row - 1)):
        print(" ", end="")

    # print right-aligned hashes
    for hashes in range(row + 1):
        print("#", end="")

    # separate two pyramids
    print("  ", end="")

    # print left-aligned hashes
    for hashes in range(row + 1):
        print("#", end="")

    # separate rows
    print("")