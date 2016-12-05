/*
 * FileMerge.c
 *
 * https://www.acmicpc.net/problem/11066
 *
 */

#include <stdio.h>

#define MAX 500

int cost[MAX];
int mat[MAX][MAX];
int sum[MAX][MAX];

int getMinCost(int n) {
	int i, j, d, k, index;
	int min = 2e9, currSum = 0;

	for (i = 0; i < n; i++)
		mat[i][i] = cost[i];

	for (d = 1; d < n; d++) {
		for (i = 0; i + d < n; i++) {
			j = i + d;
			min = 2e9;

			for (k = i; k < j; k++) {
				currSum = mat[i][k] + mat[k+1][j] + sum[i][k] + sum[k+1][j];
				if (currSum < min) {
					min = currSum;
					index = k;
				}
			}

			mat[i][j] = mat[i][index] + mat[index+1][j];
			sum[i][j] = sum[i][index] + sum[index+1][j] + mat[i][j];
		}
	}
	
	return sum[0][n-1];
}

int main() {
	int i, T, n;

	scanf("%d", &T);

	while (T--) {
		scanf("%d", &n);

		for (i = 0; i < n; i++) 
			scanf("%d", &cost[i]);

		printf("%d\n", getMinCost(n));
	}
}
