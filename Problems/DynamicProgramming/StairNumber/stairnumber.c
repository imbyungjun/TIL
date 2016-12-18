/*
 * stairnumber.c
 *
 * https://www.acmicpc.net/problem/10844
 *
 */

#include <stdio.h>

#define MAX 101
#define MOD 1000000000

int mat[10][MAX];

int main() {
	int i, j, n;
	int sum = 0;

	scanf("%d", &n);

	for (i = 0; i < 10; i++)
		mat[i][0] = 1;

	for (j = 1; j < n; j++) {

		mat[0][j] = mat[1][j-1];

		for (i = 1; i < 9; i++) 
			mat[i][j] = ((mat[i-1][j-1] + mat[i+1][j-1]) % MOD);

		mat[9][j] = mat[8][j-1];
	}

	/*
	for (i = 0; i < 10; i++) 
		for (j = 0; j < n; j++)
			printf("%d%c", mat[i][j], (j == n-1)?'\n':' ');
	*/

	for (i = 1; i < 10; i++)
		sum = ((sum + mat[i][n-1]) % MOD);

	printf("%d\n", sum);
}
