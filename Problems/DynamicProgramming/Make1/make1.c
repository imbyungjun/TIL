/*
 * Make 1
 *
 * https://acmicpc.net/problem/1463
 *
 */


#include <stdio.h>

#define MAXSIZE 1000001

int arr[MAXSIZE];

int min(int a, int b) { return (a > b)? b:a; }

int main() {
	int i, n;
	int diff[3];

	scanf("%d", &n);

	arr[0] = arr[1] = 0;

	for (i = 2; i <= n; i++) {
		diff[0] = diff[1] = diff[2] = MAXSIZE+1;

		if (i % 3 == 0) diff[0] = arr[i/3];
		if (i % 2 == 0) diff[1] = arr[i/2];
		diff[2] = arr[i-1];

		arr[i] = 1 + min( min(diff[0], diff[1]), diff[2]);
	}

	printf("%d\n", arr[n]);
}
