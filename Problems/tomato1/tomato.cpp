/*
 * https://www.acmicpc.net/problem/7576
 */
#include <stdio.h>
#include <queue>

#define MAX 1001

int tomatos[MAX][MAX];

int m, n;

class Point {
public:
	int row, col;
	Point() {}
	Point(int row, int col) {
		this->row = row;
		this->col = col;
	}
};

Point dir[] = { Point(1, 0), Point(-1, 0), Point(0, 1), Point(0, -1) };

std::queue<Point> today;
std::queue<Point> tomorrow;

int days() {
	int count = 0;

	while (!tomorrow.empty() && ++count) {
		while(!tomorrow.empty()) {
			today.push(tomorrow.front());
			tomorrow.pop();
		}
		
		while(!today.empty()) {
			// 퍼져나가기.
			Point now = today.front();
			today.pop();

			for (int i = 0; i < 4; i++) {
				int row = now.row + dir[i].row;
				int col = now.col + dir[i].col;
				
				if (row < 0 || col < 0 || row >= n || col >= m) {
					continue;
				}

				// push to tomorrow queue
				if (tomatos[row][col] == 0) {
					tomatos[row][col] = 1;
					tomorrow.push(Point(row, col));
				} 
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (tomatos[i][j] == 0) {
				return -1;
			}
		}
	}

	return count-1;
}

int main() {
	scanf("%d %d", &m, &n);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &tomatos[i][j]);
			if (tomatos[i][j] == 1) {
				tomorrow.push(Point(i, j));
			}
		}
	}

	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < m; j++) {
	//		printf("%d%c", tomatos[i][j], j==m-1?'\n':' ');
	//	}
	//}

	printf("%d\n", days());

	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < m; j++) {
	//		printf("%d%c", tomatos[i][j], j==m-1?'\n':' ');
	//	}
	//}
}
