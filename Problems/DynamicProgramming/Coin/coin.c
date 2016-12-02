#include <stdio.h>

#define MAX_COINS 101
#define MAX_CHANGES 5001

int coins[MAX_COINS];
unsigned long long matrix[MAX_COINS][MAX_CHANGES];

void coin () {
	int i, j, changes, n;	// kinds of coin

	scanf("%d %d", &changes, &n);

	for (i = 0; i < n; i++)
		scanf("%d", &coins[i]);

	for (i = 1; i <= n; i++) 
		for (j = 1; j <= changes; j++) 
			matrix[i][j] = matrix[i-1][j] + matrix[i][j-coins[i-1]];
	
	printf("%d\n", matrix[n][changes] % 1000000007L);	
}

int main() {
	int i, cases;

	for (i = 0; i < MAX_COINS; i++)
		matrix[i][0] = 1;

	scanf("%d", &cases);

	while(cases--) 
		coin();
}
