#!/usr/bin/env python
#-*- coding:utf-8 -*-

import sys
import math
import random
import operator
from fractions import Fraction, gcd
from decimal import Decimal, getcontext
from itertools import product, permutations, combinations
from Queue import Queue, PriorityQueue
from collections import deque, defaultdict, Counter
getcontext().prec = 100

MOD = 10**9 + 7
INF = float("+inf")

raw_input = lambda: sys.stdin.readline().strip()

n, k = map(int, raw_input().split())

arr = raw_input().split()
for i in xrange(len(arr)):
    if arr[i] != "?":
        arr[i] = int(arr[i])
    else:
        arr[i] = None


def find(j):
    while j < n:
        if arr[j] is not None:
            return j
        j += k
    return j - k


def fill(j, jj, curmin, curmax):
    # print "FILL", j, jj, ":", curmin, curmax, ": val",
    nitems = (jj - j) / k + 1
    if nitems & 1 == 0:
        h = nitems >> 1
        h2 = h - 1
    else:
        h = h2 = nitems / 2

    if curmin <= -h <= h2 <= curmax:
        start = -h
    elif curmin <= -h2 <= h <= curmax:
        start = -h2
    elif curmin <= -h:
        start = curmax - nitems + 1
    else:
        start = curmin

    # print start
    cur = start
    while j <= jj:
        arr[j] = cur
        cur += 1
        j += k


def die():
    print "Incorrect sequence"
    quit()


for offset in xrange(k):
    curmin = -10**10

    j = offset
    while j < n:
        if arr[j] is not None:
            curmin = arr[j] + 1
            j += k
            continue

        jj = find(j)
        if arr[jj] is not None:
            curmax = arr[jj] - 1
            nitems = (jj - j) / k
            if not (curmin + nitems - 1 <= curmax):
                die()
            fill(j, jj - k, curmin, curmax)
        else:
            curmax = 10**10
            nitems = (jj - j) / k + 1
            if not (curmin + nitems - 1 <= curmax):
                die()
            fill(j, jj, curmin, curmax)

        curmin = arr[jj] + 1
        j = jj + k

    j = offset
    while j + k < n:
        if arr[j] >= arr[j + k]:
            die()
        j += k

sys.stdout.write(" ".join(str(x) for x in arr))
