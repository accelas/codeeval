import sys

test_cases = open(sys.argv[1], 'r')

def go(n, count):
    r = int(str(n)[::-1])
    if n == r:
        return (count, r)
    else:
        return go(n+r, count+1)


for test in test_cases:
    line = test.split()

    count, res = go(int(line[0]), 0)

    print(str(count) + " " + str(res))
