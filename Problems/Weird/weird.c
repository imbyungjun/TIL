/*
 *	Weird
 *
 *	If input is weird number, print "weird"
 *	if not, print "not weird"
 */


#include <stdio.h>

#define MAXSIZE 1000

int div[MAXSIZE];

/*
 * isMakeSum() function
 *
 * If set of divisors can make 'diff' variable, return 1
 * else return 0
 */
int isMakeSum(int diff, int start, int end) {
	int i;

	if (start >= end | diff < 0) 
		return 0;
	else if (diff == 0)
		return 1;

	for (i = start; i < end; i++)
		if(isMakeSum(diff - div[i], i+1, end))
			return 1;

	return 0;
}


int weird() {
	int i, n, sum = 0;
	int diff = 0, index = 0;

	scanf("%d", &n);

	for (i = 1; i <= n/2; i++) 
		if (n % i == 0)
			sum += div[index++] = i;


	diff = sum - n;

	if (diff < 2) return 0;

	return isMakeSum(diff, 0, index) ? 0 : 1;
}

int main() {
	int cases;

	scanf("%d", &cases);

	while (cases--)
		printf("%s\n", weird() ? "weird" : "not weird");

}
