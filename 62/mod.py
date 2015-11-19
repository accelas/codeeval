import sys

test_cases = open(sys.argv[1], 'r')

for test in test_cases:
    line = test.split(',')
    a = int(line[0])
    b = int(line[1])
    print(a - (a//b)*b)

