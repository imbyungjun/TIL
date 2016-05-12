#include <stdio.h>

#define RATIO(n, m) ((100*(m))/(n))
#define MAX 2000000000

int ratio() {
	long n, m;
    long origin, curr, begin, end, mid;

	scanf("%ld %ld", &n, &m);

	if ((origin = RATIO(n, m)) >= 99) 
		return -1;

	begin = 1;
	end = MAX;

	while (end >= begin) {
		mid = (begin + end) / 2;
		curr = RATIO(n+mid, m+mid);
		
		if ((curr == origin + 1) && (RATIO(n+mid-1, m+mid-1) == origin))  
			return mid;
		else if (curr >= origin + 1) 
			end = mid-1;
		else
			begin = mid+1;
	}

	return mid;
}

int main() {
	int cases;

	scanf("%d", &cases);

	while(cases--)
		printf("%d\n", ratio());
}
