#include <stdio.h>

#define MAX 100000

int arr[MAX];

int getContSum(int n) {
	int i;
	int sum, max;

	sum = 0;
	max = arr[0];

	for (i = 0; i < n; i++) {
		sum += arr[i];

		max = (max < sum) ? sum : max;

		sum = (sum < 0) ? 0 : sum;
	}

	return max;
}

int main() {
	int i, n;

	scanf("%d", &n);

	for (i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	printf("%d\n", getContSum(n));
}

