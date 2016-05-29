/* 
 * Endians
 *
 * [https://www.algospot.com/judge/problem/read/ENDIANS]
 *
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

void invert(char *str) {
	int i;
	char tmp;

	for (i = 0; i < 4; i++) {
		tmp = str[i];
		str[i] = str[7-i];
		str[7-i] = tmp;
	}
}

void endian() {
	char str[4][9];
	char digit[2];
	unsigned int n, sum = 0;
	int i, j, cnt = 0;

	scanf("%d", &n);

	for (i = 0; i < 4; i++)
		strcpy(str[i], "");

	for (i = 0; i < 32; i++, n/=2) {
		sprintf(digit, "%d", n%2);

		strcat(str[i/8], digit);
	}

	//for (i = 0; i < 4; i++)
	//	invert(str[i]);

	for (i = 3; i >= 0; i--) 
		for (j = 0; j < 8; j++)
			sum += (pow(2, cnt++) * (str[i][j] - '0'));

	printf("%ld\n", sum == -1 ? 4294967295 : sum);
}

int main() {
	int cases;

	scanf("%d", &cases);

	while (cases--)
		endian();
}
