
def rem_dup(arr):
    # Define a dictionary to hold the elements
    d = {}
    res = []

    for elem in arr:
        if elem not in d:
            d[elem] = 1
        else:
            d[elem] += 1

    write_idx = 0

    for key in d:
        if d[key] == 1:
            res.append(key)
            arr[write_idx] = key
            write_idx += 1

    arr = res
    print res
    print arr


arr = [1, 2, 3, 1, 5, 6, 5, 3, 2, 7, 8, 9, 1, 10, 1]

print rem_dup(arr)
