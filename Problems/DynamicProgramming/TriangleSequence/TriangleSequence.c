/*
 * TriangleSequence.c
 *
 * https://www.acmicpc.net/problem/9461
 *
 */

#include <stdio.h>

#define MAX 100

unsigned long long arr[MAX];

int main() {
	int i, T, n;

	scanf("%d", &T);
	
	arr[0] = arr[1] = arr[2] = 1;

	for (i = 3; i < MAX; i++)
		arr[i] = arr[i-2] + arr[i-3];

	/*
	for (i = 0; i < MAX; i++)
		printf("%llu ", arr[i]);
	*/

	while (T--) {
		scanf("%d", &n);

		printf("%llu\n", arr[n-1]);
	}

}	
