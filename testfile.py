def ord2(n):
    k = 2
    p = 1
    while k != 1:
        p += 1
        k *= 2
        k %= n
    return p

#returns true if and only if there is some t such that 2^t == (-1) mod n
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

# Computes q(n) according to Ehrlich's definition
def q(n):
    order = ord2(n)
    if neg1exists(n):
        return n*(2**(order//2)-1)
    else:
        return 2**order-1

# returns true iff s(n) divides k
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

# returns true iff s(n) divides k - an optimized version of test
def test2(n, k):
    c = 1; p = 1; t = 1
    while p <= k:
        if k&p:
            c ^= ((c>>(n-t)) | ((c&((1<<(n-t))-1))<< t))
        t = (2*t)%n
        p *= 2
    c ^= 1
    return c == 0 or c == ((1<<n)-1)

# returns true iff s(n) divides q(n)/d
def check(n, d=3):
    qn = q(n)
    if q(n)%d:
        return False
    qn //= d
    return test2(n, qn)

# inefficient methods for finding s(n) designed to make sure test and test2 work
def findk(n):
    t = 1
    while True:
        if test(n, t*n):
            return t*n
        t += 1
def findk2(n):
    t = 1
    while True:
        if test2(n, t*n):
            return t*n
        t += 1

# gives a list containing every odd n <= bound such that s(n) divides q(n)/d
def find_ds(bound, d=3):
    L = []
    for n in range(3, bound, 2):
        if check(n, d):
            L.append(n)
    return L
#find3s(1000)

for d in range(3,100,2):
    print('d = %s: %s' % (d, find_ds(1000, d)))
    
