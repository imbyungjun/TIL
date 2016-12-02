/*
 * add123.c
 *
 * https://www.acmicpc.net/problem/9095
 *
 */

#include <stdio.h>

#define MAX 11

int arr[MAX];

void setMatrix() {
	int i;

	arr[0] = arr[1] = 1;
	arr[2] = 2;

	for (i = 3; i < MAX; i++)
		arr[i] = arr[i-1] + arr[i-2] + arr[i-3];
}

int main() {
	int testCases, n;

	scanf("%d", &testCases);

	setMatrix();

	while (scanf("%d", &n) && testCases--) 
		printf("%d\n", arr[n]);
}
