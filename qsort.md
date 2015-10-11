#Using QuickSort - qsort
The **qsort** is included in \<stdlib.h\>.

	void qsort (void *base, size_t num, size_t size, 
				int (*compar)(const void*, const void*));
				
**Parameters**

base - Pointer to starting point of array be sorted.

num - How many elements in the array.

size - Size of each element.

compar - It's function pointer. We have to explicitly declare compar function. The compar function have to return like this.

	if a > b, return integer > 0
	if a = b, return 0
	if a < b, return integer < 0
	
So, usually we use compare function like this.

	int cmpfunc(const void *a, const void *b)
	{ return *(int *)a - *(int *)b; }
	
We can use qsort() like this...

	#include <stdlib.h>     
	#define MAX 5

	int cmpfunc (const void * a, const void * b)
	{ return ( *(int*)a - *(int*)b ); }
	
	int main ()
	{
	  int a[MAX] = { 10, 70, 30, 100, 20 };
	  qsort (a, MAX, sizeof(int), comfunc);
	}