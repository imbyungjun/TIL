#include <stdio.h>

#define MAXSIZE 12
#define ABS(x) (x > 0 ? (x) : -(x))
int col[MAXSIZE];
int sumOfAnswers;

int isPromising(int row) {
	int k = 0;
	int promising = 1;

	while (k < row && promising) {
		if (col[row] == col[k] || ABS(col[row]-col[k]) == (row - k))
			promising = 0;
		k++;
	}
	return promising;
}

void nQueen(int row, int end) {
	int i;

	if (!isPromising(row)) 
		return;
	
	if (row == end-1) 
		sumOfAnswers += 1;
	else{
		for (i = 0; i < end; i++) {
			col[row+1] = i;
			nQueen(row+1, end);
		}
	}
}

void getNQueen() {
	int i, n;

	scanf("%d", &n);

	sumOfAnswers = 0;

	for (i = 0; i < n; i++) {
		col[0] = i;
		nQueen(0, n);
	}
	printf("%d\n", sumOfAnswers);
}

int main() {
	int cases;

	scanf("%d", &cases);

	while(cases--)
		getNQueen();
}
