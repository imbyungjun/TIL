/*
 * DRAWRECT
 *
 * [https://www.algospot.com/judge/problem/read/DRAWRECT]
 *
 */

#include <stdio.h>

void drawrec() {
	int i, rec[6], x, y;

	for (i = 0; i < 6; i++)
		scanf("%d", &rec[i]);

	x = rec[0]; y = rec[1];

	for (i = 2; i < 6; i+=2) {
		x ^= rec[i];	y ^= rec[i+1];
	}

	printf("%d %d\n", x, y);
}

int main() {
	int cases;

	scanf("%d", &cases);

	while(cases--)
		drawrec();
}
