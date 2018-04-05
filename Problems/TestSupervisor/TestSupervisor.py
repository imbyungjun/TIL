# 13458


N = int(input())

A = list(map(int, input().split()))

B, C = map(int, input().split())

for i in range(N):
    A[i] -= B
    A[i] = 0 if A[i] < 0 else A[i]

total = 0
for i in range(N):
    c = A[i] // C
    if A[i] % C > 0:
        c += 1

    total += c

print(total + N)
