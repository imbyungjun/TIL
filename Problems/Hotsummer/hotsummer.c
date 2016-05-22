#include <stdio.h>

#define MAX 9

void hot() {
	int i, sum = 0, n, limit;

	scanf("%d", &limit);

	for (i = 0; i < MAX; i++) {
		scanf("%d", &n);
		sum += n;
	}

	printf("%s\n", limit >= sum ? "YES":"NO");
}

int main() {
	int cases;

	scanf("%d", &cases);

	while(cases--)
		hot();
}
