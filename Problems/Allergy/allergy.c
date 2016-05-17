#include <stdio.h>
#include <string.h>

#define MAX 50
#define NAME_LEN 11

char name[MAX][NAME_LEN];
int matrix[MAX][MAX+1];
int check[MAX];
int min = 2e9;
int row, col;

void getmin(int curr, int cnt) {
	int i, sum = 0;
	int tmp[MAX];

	/* Save check array */
	memcpy(&tmp[0], &check[0], col*(sizeof(check[0])));

	/* check */
	for (i = 0; i < col; i++) {
		check[i] = matrix[curr][i] ? 1 : check[i];
		sum += check[i];
	}

	if (sum == col && min > cnt) 
			min = cnt;
	else 
		for (i = curr+1; i < row; i++)
			getmin(i, cnt+1);

	/* Swap array */
	memcpy(&check[0], &tmp[0], col*(sizeof(check[0])));
}

void allergy() {
	int i, j, k, n, sum = 0;
	char str[NAME_LEN];

	/* Read and build matrix */
	scanf("%d %d", &col, &row);

	/* Initialize check array */
	for (i = 0; i < row; i++)
		check[i] = 0;

	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			matrix[i][j] = 0;

	for (i = 0; i < col; i++) 
		scanf("%s", &name[i][0]);

	for (i = 0; i < row; i++) {
		scanf("%d", &n);
		for (j = 0; j < n; j++) {
			scanf("%s", &str[0]);
	
			for (k = 0; k < col; k++) 
				if (!strcmp(str, name[k]))
					matrix[i][k] = 1;
		}
	}
	/* End of building matrix */	

	min = 2e9;

	for (i = 0; i < row; i++) 
		getmin(i, 1);

	printf("%d\n", min);
}

int main() {
	int cases;

	scanf("%d", &cases);

	while (cases--)
		allergy();
}
