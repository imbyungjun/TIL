# 2098

N = int(raw_input())
cost = []
dp = []
INF = 16 * 1000000


def travel(to, visit):
    # g(to, visit:{x, x, x})
    min = INF

    # print "travel(", to, ",", "{0:b}".format(visit), ")"

    # Already visited
    if dp[to][visit] > 0:
        return dp[to][visit]

    # g(to, null)
    if (1 << N) - 1 == visit:
        if cost[to][0] == 0:
            return INF
        else:
            return cost[to][0]

    for i in range(N):
        # visited
        if visit & (1 << i):
            continue

        if cost[to][i] == 0:
            continue

        sum = cost[to][i] + travel(i, visit | (1 << i))

        if sum < min:
            min = sum

    dp[to][visit] = min
    return min


if __name__ == '__main__':
    for i in range(N):
        cost.append([int(n) for n in raw_input().split()])
        dp.append([-1] * (1 << N))

    print travel(0, 1)
