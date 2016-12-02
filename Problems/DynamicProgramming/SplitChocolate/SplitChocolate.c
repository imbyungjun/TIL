/*
 * SplitChocolate.c
 *
 * https://www.acmicpc.net/problem/2163
 *
 */

#include <stdio.h>

#define MAX 301

int arr[MAX];

int split(int n, int m) {
	int i;

	arr[1] = m - 1;
	arr[2] = 2 * arr[1] + 1;

	for (i = 3; i <= n; i++)
		arr[i] = arr[i-1] + arr[1] + 1;


	return arr[n];
}

int main() {
	int n, m;

	scanf("%d %d", &n, &m);

	if (n < m) 
		printf("%d\n", split(n, m));
	else
		printf("%d\n", split(m, n));

}
