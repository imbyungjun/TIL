#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 4096

int main() {
	char buf[BUFSIZE];

	if (getcwd(buf, BUFSIZE) == NULL)
		perror("getcwd error");
	else
		printf("%s\n", buf);
}
