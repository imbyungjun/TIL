# 2579
N = int(input())
score = [0]
dp = [(0, 0)]


def go_up_stair():
    for i in range(1, N + 1):
        dp.append((dp[i-1][1] + score[i], max(dp[i-2][0], dp[i-2][1]) + score[i]))


if __name__ == '__main__':
    for _ in range(N):
        score.append(int(input()))

    go_up_stair()

    print max(dp[N][0], dp[N][1])
