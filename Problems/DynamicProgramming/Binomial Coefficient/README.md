# 이항계수 2
이항계수를 구하는 문제이다. 이항계수의 정의는 다음과 같다. (출처: 위키피디아)   
![img](https://wikimedia.org/api/rest_v1/media/math/render/svg/af575850eec19a2efa2ac71d38c3a4c7af88bf5d)

## 풀이
사실 이항계수가 뭐하는건지 정확하게 모른다. 다만 위키피디아에 이미 점화식이 나와있다.  
![img](https://wikimedia.org/api/rest_v1/media/math/render/svg/3027846f5d02235fd0759030edbeae293b76d2e7)

그리고 K = 1일 경우를 대입해보면 언제나 **이항계수(N, 1) = N** 이라는 성질을 알 수 있다.  
위의 점화식을 참고해서 아래와 같은 함수를 만들었다.
```
F(N, K) = F(N - 1, K - 1) + F(N - 1, K),    K > 1
F(N, K) = N,              K = 1
F(N, K) = 1,              K = 0 or K = N
F(N, K) = 0,              K > N
```

> 0 <= K <= N 이고, 0! = 1 임에 주의  
> 출력할 값은 10007로 나눈 나머지라는 점을 주의

## 문제 링크
https://www.acmicpc.net/problem/11051

## 소스 코드
[BinomialCoefficient.py](./BinomialCoefficient.py)
