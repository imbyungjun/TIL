/*
 * coin1.c
 *
 * https://www.acmicpc.net/problem/2293
 *
 */

#include <stdio.h>

#define MAX_CHANGE 20001
#define MAX_COINS 100

int coins[MAX_COINS];
int arr[MAX_CHANGE];

int getComb(int n, int k) {
	int i, j;

	for (i = 0; i < n; i++) {
		arr[coins[i]] += 1;
		for (j = 1; j <= k - coins[i]; j++) {
			arr[j+coins[i]] += arr[j];
		}
	}

	/*
	for (i = 0; i <= k; i++)
		printf("%d ", arr[i]);
	puts("");
	*/
	return arr[k];
}

int main() {
	int i, n, k;

	scanf("%d %d", &n, &k);

	for (i = 0; i < n; i++)
		scanf("%d", &coins[i]);

	printf("%d\n", getComb(n, k));
}
