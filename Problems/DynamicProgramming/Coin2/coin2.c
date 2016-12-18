/*
 * coin2.c
 *
 * https://www.acmicpc.net/problem/2294
 *
 */

#include <stdio.h>

#define MAX 100
#define MAX_CHANGE 10001

int coins[MAX];
int dp[MAX_CHANGE];

int main() {
	int i, j, n, k, min, tmp;

	scanf("%d %d", &n, &k);

	for (i = 0; i < n; i++)
		scanf("%d", &coins[i]);

	for (i = 1; i <= k; i++) {
		min = 2e9;
		for (j = 0; j < n; j++) {
			if (coins[j] <= i && dp[i - coins[j]] >= 0) {
				tmp = dp[i - coins[j]] + 1;
				min = (min < tmp) ? min : tmp;
			}
		}
		dp[i] = (min==2e9)?-1:min;
	}
	
	/*
	for (i = 0; i <= k; i++)
		printf("%d ", dp[i]);
	puts("");
	*/

	printf("%d\n", dp[k]);
}
