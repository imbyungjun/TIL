#include <stdio.h>
#include <stdlib.h>

#define ABS(x) (x)>0?(x):-(x)
#define MAXSIZE 10000

int men[MAXSIZE], women[MAXSIZE];

int cmp(const void* a, const void* b) { return *(int*)a - *(int*)b; }

void meeting() {
	int i, n, num, sum = 0;

	scanf("%d", &n);

	for (i = 0; i < n; i++) 
		scanf("%d", &men[i]);

	for (i = 0; i < n; i++) 
		scanf("%d", &women[i]);

	qsort(men, n, sizeof(men[0]), cmp);
	qsort(women, n, sizeof(women[0]), cmp);

	for (i = 0; i < n; i++)
		sum += ABS(men[i] - women[i]);
	printf("%d\n", ABS(sum));
}

int main() {
	int cases;

	scanf("%d", &cases);

	while(cases--) 
		meeting();

}
