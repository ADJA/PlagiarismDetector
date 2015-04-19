def foo(left, right, number):
    left += 1
    right -= 1
    if right - left + 1 < number:
        return 10 ** 10 
    num = number // 2
    if number % 2:
        if num <= right and -num >= left:
            return -num
    else :
        if -num >= left and num- 1 <= right:
            return -num
        if -num  + 1 >= left and num <= right:
            return -num + 1
    if abs(left) < abs(right):
        return left
    else :
        return right - number + 1


con = 10 ** 10
n, k = map(int, input().split())
a = list(input().split())
for i in range(k):
    left = -con
    number = 0
    place = i
    for j in range(i, n, k):
        if (a[j][0] == '?') :
            number += 1
            if number == 1:
                place = j
        else:
            right = int(a[j])
            t = foo(left, right, number)
            if t == con:
                print("Incorrect sequence")
                exit()
            for r in range(place, j, k):
                a[r] = t
                t += 1
            number = 0
            left = right
            place = j + k
    if number:
        t = foo(left, con, number)
        if t == con:
            print("Incorrect sequence")
            exit()
        for r in range(place, n, k):
            a[r] = t
            t += 1
        number = 0
        left = con

print(" ".join(map(str,a)))

