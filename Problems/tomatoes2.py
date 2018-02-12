# 7569

from Queue import Queue


def full_filled():
    for height in range(h):
        for row in range(d):
            for col in range(w):
                if tomatoes[row, col, height] == 0:
                    return False
    return True


def print_tomatoes():
    for height in range(h):
        for row in range(d):
            for col in range(w):
                print tomatoes[row, col, height],
            print ''
        print '------'


def find_current():
    l = []
    for height in range(h):
        for row in range(d):
            for col in range(w):
                if tomatoes[row, col, height] == 1:
                    l.append((row, col, height))

    return l


def run():
    global w, d, h
    w, d, h = map(int, raw_input().split())

    global tomatoes
    tomatoes = {}
    for height in range(h):
        for row in range(d):
            col = 0
            for n in raw_input().split():
                tomatoes[row, col, height] = int(n)
                col += 1

    days = -1
    current = Queue()  # put / get
    next = Queue()

    next_pos = [(1, 0, 0), (-1, 0, 0), (0, 1, 0), (0, -1, 0), (0, 0, 1), (0, 0, -1)]

    for pos in find_current():
        current.put(pos)

    while not current.empty():
        while not current.empty():
            row, col, height = current.get()
            # tomatoes[row, col, height] = 1
            # print "current:", row, col, height

            for direction in next_pos:
                pos = (row + direction[0], col + direction[1], height + direction[2])

                if d > pos[0] >= 0 and \
                        w > pos[1] >= 0 and \
                        h > pos[2] >= 0 and \
                        tomatoes[pos] is 0:
                    # print pos
                    tomatoes[pos] = 1
                    next.put(pos)

        while not next.empty():
            current.put(next.get())

        days += 1

    if full_filled():
        return days

    return -1


if __name__ == '__main__':
    print run()
