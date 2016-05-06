#include <stdio.h>

#define MAXSIZE 100000
#define MIN -101
#define MAX(a,b) (a)>(b)?(a):(b)

int arr[MAXSIZE];

int findmax(int n) {
	int i, max_end, max_far;

	max_end = max_far = arr[0];

	for (i = 1; i < n; i++) {
		max_end = MAX(arr[i], max_end+arr[i]);
		max_far = MAX(max_far, max_end);
	}

	return max_far;
}

void maxsum() {
	int i, n;

	scanf("%d", &n);

	for (i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	printf("%d\n", findmax(n));
}

int main() {
	int cases;

	scanf("%d", &cases);

	while(cases--) 
		maxsum();

}
