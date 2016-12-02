/*
 * wine.c
 *
 * https://www.acmicpc.net/problem/2156
 *
 */

#include <stdio.h>

#define MAX 10000

int cost[MAX];
int arr[MAX][3];

int max(int a, int b) {
	return (a < b) ? b : a;
}

int getMaxWine(int n) {
	int i, j;
	int max_wine = -1;
	
	for (i = 0; i < n; i++)
		scanf("%d", &cost[i]);

	arr[0][0] = arr[0][1] = arr[0][2] = cost[0];
	arr[1][0] = cost[0] + cost[1];
	arr[1][1] = arr[1][2] = cost[1];
	arr[2][0] = cost[1] + cost[2];
	arr[2][1] = cost[0] + cost[2];
	arr[2][2] = cost[2];

	for (i = 3; i < n; i++) {
		arr[i][0] = max( arr[i-1][1], arr[i-1][2]) + cost[i];
		arr[i][1] = max( max(arr[i-2][0], arr[i-2][1]), arr[i-2][2]) + cost[i];
		arr[i][2] = max( max(arr[i-3][0], arr[i-3][1]), arr[i-3][2]) + cost[i];
	}

	for (i = n-2; i < n; i++) {
		for (j = 0; j < 3; j++) {
			if (max_wine < arr[i][j])
				max_wine = arr[i][j];
		}
	}

	/*
	for (i = 0; i < n; i++)
		printf("%d ", arr[i][0]);
	puts("");

	for (i = 0; i < n; i++)
		printf("%d ", arr[i][1]);
	puts("");

	for (i = 0; i < n; i++)
		printf("%d ", arr[i][2]);
	puts("");
	*/
	return max_wine;
}

int main() {
	int n;

	scanf("%d", &n);

	printf("%d\n", getMaxWine(n));
}
