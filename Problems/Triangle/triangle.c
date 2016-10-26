/*
 * pb05.c
 *
 * https://www.acmicpc.net/problem/1932
 *
 */

#include <stdio.h>

#define MAX 500

int cost[MAX][MAX];
int max_cost[MAX][MAX];

int max(int a, int b) { return (a>b)?a:b; }

int getMaxCost(int n) {
	int i, j;
	int max_will_return = -1;

	max_cost[0][0] = cost[0][0];

	for (i = 1; i < n; i++) 
		max_cost[i][0] = cost[i][0]+ max_cost[i-1][0];

	for (i = 1; i < n; i++) 
		for (j = 1; j < n; j++) 
			max_cost[i][j] = max(max_cost[i-1][j], max_cost[i-1][j-1]) + cost[i][j];
	
	for (i = 0; i < n; i++)
		max_will_return = max(max_will_return, max_cost[n-1][i]);

	return max_will_return;

}


int main() {
	int i, j, n;
	
	scanf("%d", &n);

	for (i = 0; i < n; i++) 
		for (j = 0; j <= i; j++) 
			scanf("%d", &cost[i][j]);

	printf("%d\n", getMaxCost(n));
}
