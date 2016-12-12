/*
 * Longest Increasing Subsequence.c
 *
 * https://www.acmicpc.net/problem/11053
 *
 */

#include <stdio.h>

#define MAX 1000

int arr[MAX];
int dp[MAX];

int lis(int n) {
	int i, j, max = -1;

	for (i = 0; i < n; i++) {
		dp[i] = 1;
		for (j = 0; j < i; j++) 
			if (arr[j] < arr[i] && dp[i] < dp[j] + 1)
				dp[i] = dp[j] + 1;
	}

	for (i = 0; i < n; i++)
		max = (dp[i] < max) ? max : dp[i];

	return max;
}

int main() {
	int i, n;

	scanf("%d", &n);

	for (i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	printf("%d\n", lis(n));
}
