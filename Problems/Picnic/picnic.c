#include <stdio.h>
#include <string.h>

#define MAXSIZE 45

typedef struct {
	int a;
	int b;
}Pair;

int n, m;
Pair arr[MAXSIZE];
int check [MAXSIZE];
int cnt;

void backtrack(int curr, int depth) {
	int i, sum = 0;
	int tmp[MAXSIZE];
	
	/* Save */
	memcpy(&tmp[0], &check[0], n*sizeof(check[0]));

	/* Check a pair */
	check[arr[curr].a] = check[arr[curr].b] = 1;

	if (++depth == n/2) {
		for (i = 0; i < n; i++)
			sum += check[i];
		
		/* When all elements are checked */
		if (sum == n)
			cnt++;
	} else {
		for (i = curr+1; i < m; i++)
			backtrack(i, depth);
	}

	/* Reload */
	memcpy(&check[0], &tmp[0], n*sizeof(check[0]));
}

void picnic() {
	int i;

	scanf("%d %d", &n, &m);

	for (i = 0; i < m; i++)
		scanf("%d %d", &arr[i].a, &arr[i].b);

	cnt = 0;

	for (i = 0; i < m; i++) 
		backtrack(i, 0);

	printf("%d\n", cnt);
}

int main() {
	int cases;

	scanf("%d", &cases);

	while(cases--)
		picnic();
}
