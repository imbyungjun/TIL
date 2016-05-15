#include <stdio.h>
#define MAX 100001
void lis() {
	int n, i, before, now, count, max;

	scanf("%d", &n);

	before = MAX;
	max = -1;

	for (i = 0; i < n; i++) {
		scanf("%d", &now);
		count = now > before ? count+1 : 1;
		max = count > max ? count : max;
		before = now;
	}

	printf("%d\n", max);
}

int main() {
	int cases;
	
	scanf("%d", &cases);

	while(cases--) 
		lis();
}
