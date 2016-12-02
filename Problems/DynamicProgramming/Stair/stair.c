/*
 * pb03.c
 *
 * 계단오르기
 *
 * https://www.acmicpc.net/problem/2579
 *
 */

#include <stdio.h>

#define MAX 301

int points[MAX];
int matrix[MAX][2];

int max(int a, int b) { return (a>b)?a:b; }

int maxStair(int n) {
	int i;

	matrix[1][0] = points[1];

	for (i = 2; i <= n; i++) {
		matrix[i][0] = max(matrix[i-2][0], matrix[i-2][1]) + points[i];
		matrix[i][1] = matrix[i-1][0] + points[i]; 

	}	

	for (i = 0; i <= n; i++) 
		printf("%d ", matrix[i][0]);
	puts("");
	for (i = 0; i <= n; i++)
		printf("%d ", matrix[i][1]);
	puts("");

	return max(matrix[n][0], matrix[n][1]);
}

int main() {
	int i, n;

	scanf("%d", &n);

	for (i = 1; i <= n; i++)
		scanf("%d", &points[i]);

	printf("%d\n", maxStair(n));
}
