/*
 * STRJOIN
 *
 * [https://www.algospot.com/judge/problem/read/STRJOIN]
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

int arr[MAXSIZE];
int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

void strjoin() {
	int i, n, cost = 0; 

	scanf("%d", &n);

	for (i = 0; i < n; i++) 
		scanf("%d", &arr[i]);

	do {
		qsort(&arr[0], n, sizeof(arr[0]), cmp);
	
		arr[0] += arr[1];
		arr[1] = arr[n-1];

		cost += arr[0];
	} while (--n > 1);

	printf("%d\n", cost);
}

int main() {
	int cases;

	scanf("%d", &cases);

	while (cases--)
		strjoin();
}
