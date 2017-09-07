

# Convert a given string from base b1 to base b2
# Eg: str = "615" is in base 7 and we need to
# convert it to base 13 which will become "1A7"


def base_conv(str, b1, b2):
    # First normalize the value to a integer
    val = 0
    for c in str:
        # ord provides the ascii value
        temp = ord(c) - ord('0')

        val = val * b1 + temp

    print val

    # Now convert to base b2
    rem = 0
    res_str = ""
    while val != 0:
        rem = val % b2
        if rem >= 10:
        	c = chr(ord('A')+(rem - 10))
        else:
        	c = chr(ord('0')+rem)
        res_str += c
        val = val / b2

    print res_str

    return res_str[::-1]


print base_conv("615", 7, 13)
