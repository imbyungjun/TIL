#include <stdlib.h>
#include <stdio.h>

/* 
 * getenv함수를 이용하여 CWD를 얻고 
 * 표준출력으로 출력한다.
 */

int main() {
	printf("%s\n", getenv("PWD"));
}
