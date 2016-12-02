/*
 * sum of matrix.c
 *
 * https://www.acmicpc.net/problem/2167
 *
 */

#include <stdio.h>

#define MAX 301

int matrix[MAX][MAX];

int main() {
	int x1, x2, y1, y2;
	int n, i, j;
	int sum;

	scanf("%d %d", &x1, &y1);

	for (i = 1; i <= x1; i++)
		for (j = 1; j <= y1; j++)
			scanf("%d", &matrix[i][j]);

	scanf("%d", &n);

	while (n--) {
		sum = 0;

		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		for (i = x1; i <= x2; i++) 
			for (j = y1; j <= y2; j++) {
				//printf("(%d, %d)\n", i, j);
				sum += matrix[i][j];
			}
		
		printf("%d\n", sum);

	}

}
