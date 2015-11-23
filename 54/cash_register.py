import sys
from decimal import *

changes = [
    ('ONE HUNDRED', Decimal('100.00')),
    ('FIFTY', Decimal('50.00')),
    ('TWENTY', Decimal('20.00')),
    ('TEN', Decimal('10.00')),
    ('FIVE', Decimal('5.00')),
    ('TWO', Decimal('2.00')),
    ('ONE', Decimal('1.00')),
    ('HALF DOLLAR', Decimal('.50')),
    ('QUARTER', Decimal('.25')),
    ('DIME', Decimal('.10')),
    ('NICKEL', Decimal('.05')),
    ('PENNY', Decimal('.01')),
]

def calc(number):
    counts = []
    for (k, v) in changes:
        while number >= v:
            number -= v
            counts.append(k)
    return ",".join(counts)

if __name__ == "__main__":
    test_cases = open(sys.argv[1], 'r')

    for test in test_cases:
        numbers = test.split(';')
        amount = Decimal(numbers[0])
        pay    = Decimal(numbers[1])
        c = pay - amount
        if c < 0:
            print("ERROR")
        elif c == 0:
            print("ZERO")
        else:
            print(calc(c))

    test_cases.close()
