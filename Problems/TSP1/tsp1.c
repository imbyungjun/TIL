#include <stdio.h>

#define MAXSIZE 8
#define MIN(a,b) ((a)<(b)?(a):(b))
typedef enum { false, true } bool;

double matrix[MAXSIZE][MAXSIZE];
bool touch[MAXSIZE];
double min;

void findpath(double sum, int row, int n) {
	int i;

	touch[row] = true;

	for (i = 0; i < n && touch[i]; i++) { }
		
	if (i == n) 
		min = MIN(min, sum);

	for (i = 0; i < n; i++) {
		if (touch[i]) continue;
		findpath(sum + matrix[row][i], i, n);
	}

	touch[row] = false;
}


void tsp() {
	int i, j, n;
    double sum = 0.0;

	min = (double)999999.0;

	scanf("%d", &n);

	for (i = 0; i < n; i++) 
	for (j = 0; j < n; j++) 
		scanf("%lf", &matrix[i][j]);

	for (i = 0; i < n; i++)
		findpath(0, i, n);

	printf("%.10lf\n", min);
}

int main() {
	int cases;

	scanf("%d", &cases);

	while(cases--) 
		tsp();
}
