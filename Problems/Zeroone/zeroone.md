#Zero-one
###문제

0과 1로 구성된 수열이 있다. 수열의 길이가 N이라 하고, 각각의 수열의 원소마다 순서대로 번호를 매길 경우 첫 번째 숫자는 0번이 되고 두 번째 숫자는 1번, 그리고 마지막 숫자는 N-1이 된다. 임의적으로 0이상 N-1이하의 2개의 숫자 i,j를 잡고 i번째부터 j번째 까지의 숫자 중에서의 최대값과 최소값을 찾아서 두 값이 일치하는지 알아보고자 한다.

###입력

첫 번째 줄에는 최대 길이 1,000,000의 수열이 들어온다. 수열의 사이에는 빈칸이 없다. 그 다음 줄에는 질문의 개수를 뜻하는 정수 N(N<=100,000)이 입력된다. 그 다음줄부터 해당구간 i,j를 의미하는 2개의 숫자가 N개의 줄로 입력된다.

###출력

각각의 질문의 순서대로 해당구간 i,j의 최대값과 최소값이 같을 경우 Yes를, 그렇지 않을 경우는 No를 출력한다.

###예제 입력
```
0000011111
3
0 5
4 2
5 9
```
###예제 출력
```
No
Yes
Yes
```
###노트
```
0,5 : 000001 -> 최대값 : 1, 최소값 : 0
4,2 : 000 -> 최대값 : 0, 최소값 : 0
5,9 : 11111 -> 최대값 : 1, 최소값 : 1
```