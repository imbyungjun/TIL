/*
 * sticker.c
 *
 * https://www.acmicpc.net/problem/9465
 *
 */

#include <stdio.h>

#define MAX 100000

int points[MAX][2];
int cost[MAX][4];

int max_of_4(int index) {
	int i, max = -1;

	for (i = 0; i < 4; i++)
		if (max < cost[index-2][i])
			max = cost[index-2][i];

	return max;
}

int max(int a, int b) {
	return (a < b)?b:a;
}

int getCost() {
	int n, i;

	scanf("%d", &n);

	for (i = 0; i < 2 * n; i++)
		scanf("%d", &points[i%n][i/n]);

	cost[0][0] = cost[0][2] = points[0][0];
	cost[0][1] = cost[0][3] = points[0][1];
	
	cost[1][0] = points[0][1] + points[1][0];
	cost[1][1] = points[0][0] + points[1][1];

	cost[1][2] = points[1][0];
	cost[1][3] = points[1][1];

	for (i = 2; i < n; i++) {
		cost[i][0] = max(cost[i-1][1], cost[i-1][3]) + points[i][0];
		cost[i][1] = max(cost[i-1][0], cost[i-1][2]) + points[i][1];
		cost[i][2] = max_of_4(i) + points[i][0];
		cost[i][3] = max_of_4(i) + points[i][1];
	}

	/*
	for (i = 0; i < n; i++)
		printf("%03d ", cost[i][0]);
	puts("");

	for (i = 0; i < n; i++)
		printf("%03d ", cost[i][1]);
	puts("");

	for (i = 0; i < n; i++)
		printf("%03d ", cost[i][2]);
	puts("");

	for (i = 0; i < n; i++)
		printf("%03d ", cost[i][3]);
	puts("");
	*/

	return max_of_4(n+1);
}

int main() {
	int testCases;

	scanf("%d", &testCases);

	while (testCases--)
		printf("%d\n", getCost());
}

