def main():
    s = input("Text: ")  # input reading passage from user

    letters = count_letters(s)  # find number of letters
    words = count_words(s)  # find number of words
    sentences = count_sentences(s)  # find number of sentences

    # calculate grade (index)
    grade = 0.0588 * 100 * letters / words - 0.296 * 100 * sentences / words - 15.8

    # output
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print("Grade", round(grade))


def count_letters(s):
    letters = 0
    # count letters by using ascii codes
    for c in s:
        c = ord(c)
        if (c >= 65 and c <= 90) or (c >= 97 and c <= 122):
            letters += 1

    # return number of letters
    return letters


def count_words(s):
    words = 1
    # count words - Ascii code for space = 32
    for c in s:
        c = ord(c)
        if c == 32:
            words += 1

    # return number of words
    return words
    

def count_sentences(s):
    sentences = 0
    # count sentences each time there is '.', '!', or '?'
    for c in s:
        c = ord(c)
        if (c == 46 or c == 63 or c == 33):
            sentences += 1

    # return number of sentences
    return sentences


main()