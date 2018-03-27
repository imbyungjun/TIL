# 3190
import Queue


class Node:
    def __init__(self, n):
        self.value = n
        self.left = None
        self.right = None


def link_nodes(a, b):
    a.right = b
    b.left = a


def createDirection():
    right = Node((0, 1))
    down = Node((1, 0))
    left = Node((0, -1))
    up = Node((-1, 0))

    link_nodes(right, down)
    link_nodes(down, left)
    link_nodes(left, up)
    link_nodes(up, right)

    return right


class Snake:
    def __init__(self):
        self.position = (0, 0)
        self.direction = createDirection()
        self.tail = Queue.Queue()

    def move(self):
        self.tail.put(self.position)

        self.position = (self.position[0] + self.direction.value[0],
                         self.position[1] + self.direction.value[1])

        if self.is_end():
            return False

        if board[self.position] == 0:  # No apple
            self.tail.get()  # Pop last tail position
        else:
            board[self.position] = 0    # Eat an apple

    def change_direction(self, left_or_right):
        if left_or_right == "L":  # left
            self.direction = self.direction.left
        else:  # right
            self.direction = self.direction.right

    def is_end(self):
        if 0 <= self.position[0] < N and \
                0 <= self.position[1] < N and \
                self.position not in self.tail.queue:
            return False
        return True


N = input()
board = {}
for i in range(N):
    for j in range(N):
        board[i, j] = 0

K = input()
for _ in range(K):
    row, col = map(int, raw_input().split())
    board[row-1, col-1] = 1

turn = []
turn_index = 0
L = input()
for _ in range(L):
    X, C = raw_input().split()
    turn.append((int(X), C))

time = 0
snake = Snake()
while True:
    time = time + 1

    if snake.move() is False:
        break

    if turn_index < L and time == turn[turn_index][0]:
        snake.change_direction(turn[turn_index][1])
        turn_index = turn_index + 1

print time
