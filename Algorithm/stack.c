#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1024

#define push(num) do {		\
	if (stack.top != MAXSIZE -1) 		\
		stack.arr[++stack.top] = num;		\
}while(0)		

#define pop() stack.arr[stack.top--]		/* You must check top index */

typedef struct {
	int arr[MAXSIZE];
	int top;	
} Stack;
Stack stack;

int main() {
	int i;
	
	for (i = 0; i < 10; i++) 
		push(i);

	for ( ; stack.top > 0; )
		printf("poped item : %d\n", pop());
}
