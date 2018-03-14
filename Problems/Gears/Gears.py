# 14891


class Gear:
    def __init__(self, magnets):
        self.magnets = []
        for c in magnets:
            self.magnets.append(c)
        self.o_clock = 0

    def __str__(self):
        return self.magnets.__str__()

    def left(self):
        return self.magnets[(self.o_clock - 2) % 8]

    def right(self):
        return self.magnets[(self.o_clock + 2) % 8]

    def rotate_clockwise(self):
        self.o_clock = (8 + self.o_clock - 1) % 8

    def rotate_anticlockwise(self):
        self.o_clock = (8 + self.o_clock + 1) % 8

    def rotate(self, d):
        if d == -1:
            self.rotate_anticlockwise()
        else:
            self.rotate_clockwise()


gears = []


def propagate_left(src, before_direction):
    if src <= 0:
        return

    next_direction = before_direction * -1

    if gears[src-1].right() != gears[src].left():
        # print "Gear#{0} rotate {1}".format(src - 1, next_direction)
        propagate_left(src - 1, next_direction)
        gears[src-1].rotate(next_direction)


def propagate_right(src, before_direction):
    if src >= 3:
        return

    next_direction = before_direction * -1

    if gears[src].right() != gears[src+1].left():
        # print "Gear#{0} rotate {1}".format(src + 1, next_direction)
        propagate_right(src + 1, next_direction)
        gears[src + 1].rotate(next_direction)


def rotate_other_gears(src, origin_direction):
    propagate_left(src, origin_direction)
    propagate_right(src, origin_direction)


def score(index):
    if gears[index].magnets[gears[index].o_clock] == "0":
        return 0
    else:
        return 1 << index


def get_score():
    result = 0
    for i in range(4):
        result = result | score(i)

    return result


if __name__ == '__main__':
    for _ in range(4):
        gears.append(Gear(raw_input()))

    K = int(raw_input())

    for _ in range(K):
        which, direction = map(int, raw_input().split())
        which = which - 1

        rotate_other_gears(which, direction)
        gears[which].rotate(direction)
        # print "Gear#{0} rotate {1}".format(which, direction)

    # for i in range(4):
    #     print gears[i], gears[i].o_clock

    print get_score()

