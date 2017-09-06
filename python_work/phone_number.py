# Dictionary to map digit to letter
digit = {
    '0': ['-'],
    '1': ['$'],
    '2': ['a', 'b', 'c'],
    '3': ['d', 'e', 'f'],
    '4': ['g', 'h', 'i'],
    '5': ['j', 'k', 'l'],
    '6': ['m', 'n', 'o'],
    '7': ['p', 'q', 'r', 's'],
    '8': ['t', 'u', 'v'],
    '9': ['w', 'x', 'y', 'z']
}


def num_to_letters(num, i, res_str):

    if i >= len(num):
        str = ''.join(res_str)
        print str
        return

    l = digit[num[i]]

    # print l

    for elem in l:
        res_str.append(elem)
        num_to_letters(num, i + 1, res_str)
        res_str.pop()


num_to_letters("23", 0, [])
