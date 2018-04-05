# 14888


def foo(operand1, operator, operand2):
    return {
        '+': operand1 + operand2,
        '-': operand1 - operand2,
        '*': operand1 * operand2,
        '/': operand1 // operand2 if operand1 > 0 else -1 * ((-1 * operand1) // operand2)
    }[operator]


def calculate(operands, operators):
    sub_result = operands[0]
    for i in range(len(operands) - 1):
        sub_result = foo(sub_result, operators[i], operands[i+1])
        # sub_result = "{} {} {}".format(sub_result, operators[i], operands[i+1])

    return sub_result


def calculate_and_find_max_min(permutation):
    global A, MAX, MIN

    result = calculate(A, permutation)
    # print(result)

    MIN = min(result, MIN)
    MAX = max(result, MAX)


def recursion(remain_operators, permutation):
    if len(permutation) == N - 1:
        calculate_and_find_max_min(permutation)
    else:
        for i, op in enumerate(["+", "-", "*", "/"]):
            if remain_operators[i] > 0:
                remain_operators[i] -= 1
                permutation.append(op)

                recursion(remain_operators, permutation)

                remain_operators[i] += 1
                permutation.pop(-1)


MAX = -1_000_000_000
MIN = 1_000_000_000

N = int(input())

A = list(map(int, input().split()))

plus, minus, multiply, divide = map(int, input().split())

recursion([plus, minus, multiply, divide], [])

print(MAX)
print(MIN)
