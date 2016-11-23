/*
 * bridge.c
 *
 * https://www.acmicpc.net/problem/1010
 *
 */

#include <stdio.h>

#define MAX 30

int matrix[MAX][MAX];

void setMatrix() {
	int i, j;

	for (i = 0; i < MAX; i++)
		matrix[i][i] = matrix[0][i] = 1;

	for (i = 1; i < MAX; i++) 
		for (j = 1; j < MAX; j++)
			matrix[i][j] = matrix[i][j-1] + matrix[i-1][j-1];
}

int main() {
	int testCases;
	int n, m;

	scanf("%d", &testCases);

	setMatrix();

	while (testCases--) {
		scanf("%d %d", &n, &m);
	
		printf("%d\n", matrix[n][m]);
	}
}
