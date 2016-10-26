/*
 * pb04.c
 *
 * RGB Street
 *
 * https://www.acmicpc.net/problem/1149
 *
 */

#include <stdio.h>

#define MAX 1000

#define R 0
#define G 1
#define B 2

int arr[MAX][3];
int cost[MAX][3];

int min(int a, int b) { return (a<b)?a:b; }

int rgbSt(int n) {
	int i;

	arr[0][R] = cost[0][R];
	arr[0][G] = cost[0][G];
	arr[0][B] = cost[0][B];

	for (i = 1; i < n; i++) {
		arr[i][R] = min(arr[i-1][G], arr[i-1][B]) + cost[i][R];
		arr[i][G] = min(arr[i-1][R], arr[i-1][B]) + cost[i][G];
		arr[i][B] = min(arr[i-1][R], arr[i-1][G]) + cost[i][B];
	}

	puts("------------");

	for (i = 0; i < n; i++) 
		printf("%d ", arr[i][0]);
	puts("");

	for (i = 0; i < n; i++) 
		printf("%d ", arr[i][1]);
	puts("");

	for (i = 0; i < n; i++) 
		printf("%d ", arr[i][2]);
	puts("");

	return min( min(arr[n-1][R], arr[n-1][G]), arr[n-1][B]);
}

int main() {
	int i, n;

	scanf("%d", &n);

	for (i = 0; i < n; i++)
		scanf("%d %d %d", &cost[i][R], &cost[i][G], &cost[i][B]);


	printf("%d\n", rgbSt(n));
}
