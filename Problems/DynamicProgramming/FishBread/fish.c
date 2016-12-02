/*
 * fish.c
 *
 * https://www.acmicpc.net/problem/11052
 *
 */

#include <stdio.h>

#define MAX 1001

int arr[MAX];

int main() {
	int i, j, n;
	int sum;

	scanf("%d", &n);

	for (i = 1; i <= n; i++)
		scanf("%d", &arr[i]);

	for (i = 2; i <= n; i++) {
		for (j = 1; j <= i/2; j++) {
			sum = arr[j] + arr[i-j];
			arr[i] = (arr[i] < sum) ? sum : arr[i];
		}
	}

	printf("%d\n", arr[n]);
}
