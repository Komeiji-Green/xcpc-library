from functools import cmp_to_key

lst = [(1, 5), (2, 4), (3, 6), (9, 9), (5, 1)]

def cmp(a, b):
    return a[1] * b[0] - a[0] * b[1]

sortedlst = sorted(lst, key=cmp_to_key(cmp))

print(lst)
print(sortedlst)