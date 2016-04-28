#include <stdio.h>
#include <string.h>

#define BUFSIZE 10
#define MAXDAY 7

char* week[MAXDAY] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

int day_per_month[] = {
	31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

int getday(char *day) {
	int i;

	for (i = 0; i < MAXDAY; i++)
		if (!strcmp(day, week[i]))
				return i;
	return -1;
}

void weekly_calendar() {
    int i, m, d, k = 0;
    char buffer[BUFSIZE];
    int start, count;

    scanf("%d %d %s", &m, &d, &buffer[0]);

	/* get start day */
	start = d - getday(buffer);

	if (start <= 0) 
		start += day_per_month[--m];

	for (i = start, count = 0; count < MAXDAY; i++, count++) {
		if (i > day_per_month[m]) k = i % day_per_month[m];
		else k = i;
		printf("%d%c", k, count+1 == MAXDAY ? '\n' : ' ');
	}
}

int main() {
    int cases;

    scanf("%d", &cases);

    while(cases--)
        weekly_calendar();

}
