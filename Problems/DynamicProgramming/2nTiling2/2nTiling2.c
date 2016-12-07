/*
 * 2nTiling2.c
 *
 * https://www.acmicpc.net/problem/11727
 *
 */

#include <stdio.h>

#define MAX 1001
#define MOD(a) ((a) % 10007)

int arr[MAX];

int main() {
	int i, n;

	scanf("%d", &n);

	arr[1] = 1;
	arr[2] = 3;

	for (i = 3; i <= n; i++)
		arr[i] = MOD(arr[i-1] * 2 + ((i % 2) ? (-1) : (1)));

	printf("%d\n", arr[n]);
}

