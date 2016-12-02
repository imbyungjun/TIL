/*
 * tiling.c
 *
 * https://www.acmicpc.net/problem/11726
 *
 */

#include <stdio.h>

#define MAX 1001

int getComb(int n) {
	int i;
	int arr[MAX] = {0};

	arr[1] = 1;
	arr[2] = 2;

	for (i = 3; i <= n; i++)
		arr[i] = (arr[i-1] + arr[i-2]) % 10007;

	return arr[n];
}

int main() {
	int n;

	scanf("%d", &n);

	printf("%d\n", getComb(n));
}
