# 다리 놓기
서쪽에서 동쪽으로 강을 건너는 다리를 지을때 각각의 다리가 겹치지 않도록 최대한 많은 다리를 지을 수 있는 경우의 수를 출력하는 문제. 반드시 서쪽의 다리 건설 지점이 동쪽의 다리 건설 지점보다 적거나 같다는 조건이 있다.

## 풀이
동적 계획법으로 memoization하여 풀면 간단하다. 서쪽의 다리 건설 지점이 한 곳 뿐인 경우엔 다리를 지을 수 있는 경우의 수가 동쪽의 다리 건설 지점 수와 같다. 서쪽의 다리 건설 지점이 한 곳 보다 많은 경우에 대해서 살펴보자.

서쪽 다리 건설 지점의 수를 N, 동쪽 다리 건설 지점의 수를 M 이라고 표현하면 N = 2, M = 4인 경우의 다리 건설 경우의 수는 다음과 같다.
![img](./bridge_1.png) ![img](./bridge_2.png) ![img](./bridge_3.png)

이것을 점화식으로 표현하면 아래와 같다.
```
F(N, M) = SUM { F(N-1, M-1) + F(N-1, M-2) + ... + F(N-1, 1) }
```

## 문제 링크
https://www.acmicpc.net/problem/1010

## 소스 코드
[Bridge.py](./Bridge.py)