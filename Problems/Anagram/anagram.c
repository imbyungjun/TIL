#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 101

char a[MAXLEN], b[MAXLEN];

int cmp(const void *a, const void *b) { return *(char *)a - *(char *)b; }

int anagram() {
	int i, sum1 = 0, sum2 = 0;

	scanf("%s %s", &a[0], &b[0]);

	if (!strcmp(a, b)) return 0;

	for (i = 0; a[i] && b[i]; i++) {
		sum1 += a[i];
		sum2 += b[i];
	}

	if (a[i] != b[i])
		return 0;

	if (sum1 != sum2)
		return 0;

	qsort(&a[0], i, sizeof(a[0]), cmp);
	qsort(&b[0], i, sizeof(b[0]), cmp);

	while (--i)
		if (a[i] != b[i])
			return 0;
	return 1;
}

int main() {
	int cases;

	scanf("%d", &cases);

	while(cases--)
		printf("%s\n", anagram()?"Yes":"No.");
}
