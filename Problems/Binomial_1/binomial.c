/*
 * binomial.c
 *
 * https://www.acmicpc.net/problem/11050
 *
 */

#include <stdio.h>

int binomial(int n, int k) {
	if (k == 0 || n == k)
		return 1;
	return binomial(n-1, k-1) + binomial(n-1, k);
}

int main() {
	int n, k;

	scanf("%d %d", &n, &k);

	printf("%d\n", ( k < 0 || k > n )? 0 : binomial(n, k));
}
