#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 100
#define MAX_NUMBER 11

const char *Number[] = {
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
	"ten"
};

int cmp(const void *a, const void *b) {
	return *(char*)a - *(char*)b;
}

int diff(const char *A, const char *B) {
	char a[MAXSIZE], b[MAXSIZE];

	strcpy(a, A);
	strcpy(b, B);

	qsort(a, strlen(a), sizeof(char), cmp);
	qsort(b, strlen(b), sizeof(char), cmp);

	if (!strcmp(a, b))
		return 1;
	else 
		return 0;
}

int getNumber(char *buffer) {
	int i;

	for (i = 0; i < MAX_NUMBER; i++)
		if (!strcmp(buffer, Number[i]))
			return i;

	return -1;
}

int operate(int a, char op, int b) {
	switch(op) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		default :
			return -1;
	}
}

void jei() {
	int a, b, result;
	char buffer[MAXSIZE] = "";
	char op;

	/* Get operand A */
	scanf("%s ", &buffer[0]);
	a = getNumber(buffer);

	/* Get operation */
	scanf("%c ", &op);
	
	/* Get operand B */
	scanf("%s ", &buffer[0]);
	b = getNumber(buffer);

	result = operate(a, op, b);

	scanf("%s ", buffer); 		// =
	scanf("%s", buffer);

	if (result > 10 || result < 0)
		printf("No\n");
	else if (diff(Number[result], buffer))
		printf("Yes\n");
	else
		printf("No\n");
}

int main() {
	int n;

	scanf("%d", &n);

	while (n--)
		jei();
}
