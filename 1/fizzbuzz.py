import sys

test_cases = open(sys.argv[1], 'r')

for test in test_cases:
    line = test.split()
    f = int(line[0])
    b = int(line[1])
    num = int(line[2])

    for i in range(1, num+1):
        if i % f == 0 and i % b == 0:
            print("FB", end = " ")
        elif i % f == 0:
            print("F", end = " ")
        elif i % b == 0:
            print("B", end = " ")
        else:
            print(i, end = " ")

    print("")



    # ignore test if it is an empty line
    # 'test' represents the test case, do something with it
    # ...
    # ...

test_cases.close()
