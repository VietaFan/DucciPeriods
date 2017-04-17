def ord2(n):
    k = 2
    p = 1
    while k != 1:
        p += 1
        k *= 2
        k %= n
    return p
def neg1exists(n):
    k = 2
    p = 1
    while k != 1:
        p += 1
        k *= 2
        k %= n
        if k == n-1:
            return True
    return False
def q(n):
    order = ord2(n)
    if neg1exists(n):
        return n*(2**(order//2)-1)
    else:
        return 2**order-1
def test(n, k):
    current = [0]*n
    current[0] = 1
    temp = [0]*n
    p = 1
    while p <= k:
        if not (k&p):
            p *= 2
            continue
        t = -(p%n)
        for r in range(n):
            s = r+t
            if s < 0:
                s += n
            temp[r] = current[r]^current[s]
        for i in range(n):
            current[i] = temp[i]
        p *= 2
    current[0] ^= 1
    ans = 1
    for i in range(1,n):
        if current[i] != current[0]:
            ans = 0
            break
    return ans
def check3(n):
    qn = q(n)
    if q(n)%3:
        return False
    qn //= 3
    return test(n, qn)
def findk(n):
    t = 1
    while True:
        if test(n, t*n):
            return t*n
        t += 1
def find3s(bound):
    for n in range(3, bound, 2):
        if check3(n):
            print(n, end=',')
find3s(1000)
