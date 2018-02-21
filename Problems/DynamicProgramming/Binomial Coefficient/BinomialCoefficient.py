# 11051

MAX = 1001
N, K = map(int, raw_input().split())

dp = []

for _ in range(MAX):
    dp.append([0] * MAX)

for i in range(K + 1):
    dp[i][i] = 1

for i in range(N + 1):
    dp[i][0] = 1
    dp[i][1] = i

for j in range(2, K + 1):
    for i in range(j + 1, N + 1):
        dp[i][j] = (dp[i-1][j-1] + dp[i-1][j]) % 10007

print dp[N][K]
