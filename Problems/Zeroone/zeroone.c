/*
 * Zero-One
 *
 * Judge that given sequence's number of specific section has same value.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000000
#define ABS(x) ((x)<0?(-(x)):(x))

char sequence[MAXSIZE+1];
int arr[MAXSIZE];

int zeroone() {
	int i, j, k, tmp;
	int len, sum = 0;

	scanf("%d %d", &i, &j);
	
	/* swap */
	if (i > j) {
		tmp = i;
		i = j;
		j = tmp;
	}

	if (arr[j] >= ABS(i-j))
		return 1;
	else
		return 0;
}


int main() {
	int cases, i, j;

	scanf("%s", &sequence[0]);
	
	/* Initialize sequence index arry */
	for (i = 0, j = 0; sequence[i]; i++) {
		if (sequence[i] != sequence[j]) j = i;
		arr[i] = i-j;
	}

	scanf("%d", &cases);
	
	while(cases--)
		printf("%s\n", zeroone()?"Yes":"No");
}
