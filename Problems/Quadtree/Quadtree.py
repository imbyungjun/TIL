# 1992

MAX = 64
matrix = []


def quad_tree(n):
    if n < 2:
        return

    row, col = 0, 0

    for i in range(0, n, 2):
        for j in range(0, n, 2):
            left_up = matrix[i][j]
            right_up = matrix[i][j+1]
            left_down = matrix[i+1][j]
            right_down = matrix[i+1][j+1]

            if left_up == right_up == left_down == right_down == '1' or \
                    left_up == right_up == left_down == right_down == '0':
                matrix[row][col] = left_up
            else:
                matrix[row][col] = "(" + left_up + right_up + left_down + right_down + ")"

            col += 1

        row += 1
        col = 0

    quad_tree(n / 2)


if __name__ == '__main__':
    N = input()
    for i in range(N):
        matrix.append([0] * N)
        matrix[i] = list(raw_input())

    quad_tree(N)

    print matrix[0][0]
