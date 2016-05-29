/*
 * Hamming Code
 *
 * [https://www.algospot.com/judge/problem/read/HAMMINGCODE]
 *
 */

#include <stdio.h>
#include <string.h>

#define MAXSIZE 8

void hamming() {
	char bits[MAXSIZE+1] = "";
	int i;
	int syndrome = 0;

	scanf("%s", &bits[1]);

	for (i = 1; i < MAXSIZE; i++) 
		bits[i] -= 48;

	// 3rd
	syndrome += bits[4] ^ bits[5] ^ bits[6] ^ bits[7];
	syndrome = syndrome << 1;

	// 2nd
	syndrome += bits[2] ^ bits[3] ^ bits[6] ^ bits[7];
	syndrome = syndrome << 1;

	// 1st
	syndrome += bits[1] ^ bits[3] ^ bits[5] ^ bits[7];

	bits[syndrome] = !bits[syndrome];

	printf("%d%d%d%d\n", bits[3], bits[5], bits[6], bits[7]);
}

int main() {
	int cases;

	scanf("%d", &cases);

	while(cases--)
		hamming();
}
