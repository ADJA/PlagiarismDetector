n, k = map(int, input().split())
arr = [[-2 * 10 ** 9] for i in range(k)]
for i, j in enumerate(input().split()):
    arr[i % k].append(j)
b = True
for i in range(k):
    arr[i].append(2 * 10 ** 9)
    z, c = 1, 0
    while z < len(arr[i]):
        while arr[i][z] == '?':
            z += 1
        arr[i][z] = int(arr[i][z])
        d = z - c - 1
        if arr[i][z] - arr[i][c] < d + 1:
            b = False
            break
        if arr[i][c] > 0:
            s = arr[i][c] + 1
        else:
            #print(d, arr[i][c], arr[i][z])
            s = min(-(d // 2), arr[i][z] - d)
            s = max(s, arr[i][c] + 1)
        for j in range(c + 1, z):
            arr[i][j] = s
            s += 1
        c = z
        z += 1
    if not b:
        print('Incorrect sequence')
        break
else:
    z = 1
    i = 0
    j = 0
    while i < n:
        i += 1
        print(arr[j][z], end = ' ')
        j += 1
        if j == k:
            j = 0
            z += 1