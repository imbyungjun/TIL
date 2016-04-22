#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 80

void decodeURI() {
	int i;
	char str[MAXSIZE+1];
	char hex[3] ;

	scanf("%s", str);

	for (i = 0; i < strlen(str); i++) {
		if (str[i] == '%') {
			memcpy(&hex, &str[i+1], 2);
			printf("%c", (char)strtol(hex, 0, 16));
			i += 2;
		} else {
			printf("%c", str[i]);
		}
	}
	printf("\n");

}

int main() {
	int n;

	scanf("%d", &n);

	while (n--) 
		decodeURI();

}
