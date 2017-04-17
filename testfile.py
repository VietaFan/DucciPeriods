def ord2(n):
    k = 2
    p = 1
    while k != 1:
        p += 1
        k *= 2
        k %= n
    return p
