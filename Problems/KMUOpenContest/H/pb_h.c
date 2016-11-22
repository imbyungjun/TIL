/*
 * Arithmetic operation
 *
 * https://www.acmicpc.net/problem/13420
 *
 */

#include <stdio.h>

int main() {
	long long n, a, b, c;
	char op, equal;
	int flag;

	scanf("%lld", &n);

	while (n --) {
		flag = 0;

		scanf("%lld %c %lld %c %lld", &a, &op, &b, &equal, &c);

		switch (op) {
			case '+':
				flag = (a + b == c) ? 1 : 0;
				break;
			case '-':
				flag = (a - b == c) ? 1 : 0;
				break;
			case '*':
				flag = (a * b == c) ? 1 : 0;
				break;
			case '/':
				flag = (a / b == c) ? 1 : 0;
				break;
		}

		printf("%s\n", (flag) ? "correct" : "wrong answer");
	}
}
