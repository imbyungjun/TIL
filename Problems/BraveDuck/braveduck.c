/*
 * BRAVEDUCK
 *
 * [https://www.algospot.com/judge/problem/read/BRAVEDUCK]
 *
 */

#include <stdio.h>

#define MAXSIZE 1000

typedef struct {
	int x;
	int y;
} Point;

Point arr[MAXSIZE];

int braveduck() {
	int i, n, jump_power;
	Point src, dest;

	scanf("%d", &jump_power);

	scanf("%d %d", &src.x, &src.y);
	scanf("%d %d", &dest.x, &dest.y);

	scanf("%d", &n);

	for (i = 0; i < n; i++) 
		scanf("%d %d", &arr[i].x, &arr[i].y);

	// End of input

	/*	
	printf("jump power : %d\n", jump_power);
	printf("src : (%d, %d) dest : (%d, %d)\n", src.x, src.y, dest.x, dest.y);
	printf("Points\n");
	for (i = 0; i < n; i++)
		printf("(%d, %d)\n", arr[i].x, arr[i].y);
	*/

	return 0;
}

int main() {
	int cases;

	scanf("%d", &cases);

	while(cases--)
		printf("%s\n", braveduck()?"YES":"NO");
}
