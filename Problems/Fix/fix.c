/*
 * Fix
 *
 * [https://www.algospot.com/judge/problem/read/FIX]
 *
 */
#include <stdio.h>

void fix() {
	int i, n, pb, cnt = 0;

	scanf("%d", &n);

	for (i = 0; i < n && scanf("%d", &pb); i++)
		cnt += (i+1==pb) ? 1 : 0;

	printf("%d\n", cnt);
}

int main() {
	int cases;

	scanf("%d", &cases);

	while(cases--) 
		fix();
}
