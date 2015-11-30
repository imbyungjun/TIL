/*
 * pwd.c
 *
 * 컴퓨터공학부
 * 20113316 임병준
 *
 * Current Working Directory를
 * 표준출력으로 출력하는 프로그램.
 */


#include <stdlib.h>
#include <stdio.h>

/*
 * get CWD from getenv() function,
 * print it to standard out.
 */
int main() {
	printf("%s\n", getenv("PWD"));
}
