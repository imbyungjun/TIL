# 톱니바퀴
8개의 톱니를 갖는 톱니바퀴의 각 톱니가 N극 또는 S극의 자성을 띄는 경우에 톱니바퀴가 회전한 최종 결과를 알아내는 문제이다. 근데 문제 컨셉이 좀 이상해서 이해하기 다소 어려운 문제였다. 회전 방향을 결정하는 특성을 굳이 극성으로 표현해야 했는지 의문이 든다. 4개의 톱니바퀴가 주어지고 그 중 하나의 톱니바퀴를 시계 방향 또는 시계 반대 방향으로 회전시킨다.

## 풀이
이 문제를 이해하는데에 가장 중요한 요소는 **톱니바퀴들은 재귀적으로 회전한다**는 점이다. 톱니바퀴를 회전시키면 그에 인접한 톱니바퀴가 따라서 돌게되는것이 맞지만 이 톱니바퀴들은 **회전을 시작하는 시점의 상태**에 따라서 회전의 여부를 판단하기 때문에 전체 톱니바퀴에 대해서 회전 여부를 판단한 이후에 실제로 톱니바퀴를 회전시켜야 한다.

문제에 대한 자세한 설명은 링크한 문제 페이지에 그림으로 잘 설명되어 있어서 생략

톱니바퀴의 각 톱니에 부여된 자성을 배열에 저장하고 최초에 0번 인덱스를 12시 방향의 인덱스로 선언했다. 12시 방향의 인덱스를 변경함에 따라서 현재 톱니바퀴의 회전된 상태를 판단하여 왼쪽, 오른쪽 톱니에 부여된 자성이 무엇인지 알 수 있다.

인접한 톱니바퀴에 대하여 재귀적으로 회전 여부를 판단하고 모든 회전 여부가 결정된 이후에 현재 12시 방향을 나타내는 톱니바퀴의 인덱스를 변경하는 방식으로 구현하였다.

## 문제 링크
[톱니바퀴](https://www.acmicpc.net/problem/14891)

## 소스 코드
[Gears.py](./Gears.py)
