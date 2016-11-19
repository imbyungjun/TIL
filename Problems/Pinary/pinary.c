/*
 * pinary.c
 *
 * https://www.acmicpc.net/problem/2193
 *
 */

#include <stdio.h>

#define MAX 90

unsigned long long arr[MAX];

int main() {
	int i, n;

	scanf("%d", &n);

	arr[0] = arr[1] = 1;

	for (i = 2; i < n; i++) 
		arr[i] = arr[i-1] + arr[i-2];

	printf("%llu\n", arr[n-1]);
}
