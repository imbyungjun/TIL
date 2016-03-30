#Regex in C

```
#include <sys/types.h>
#include <regex.h>

int regcomp(regex_t *preg, const char *regex, int cflags);
// Prepare your regex for fast processing
int regexec(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
// Do the matching
void regfree(regex_t *preg);
// Free your compiled regex for a new "compiling"
size_t regerror(int errcode, const regex_t *preg, char *errbuf, size_t errbuf_size);
// Retrieve some more information on why the regexec() failed
```

###Example)  
```
#include <sys/types.h>
#include <regex.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    regex_t regex;
    int reti;
    char msgbuf[100];
    
/* Compile regular expression */
    reti = regcomp(&regex, "^a[[:alnum:]]", 0);
    if( reti ) { 
        fprintf(stderr, "Could not compile regex\n"); 
        exit(1); 
    }
    
/* Execute regular expression */
    reti = regexec(&regex, "abc", 0, NULL, 0);
    if( !reti ) { puts("Match"); }
    else if ( reti == REG_NOMATCH ) { puts("No match"); }
    else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }
    
/* Free compiled regular expression if you want to use the regex_t again */
    regfree(&regex);
    
    return 0;
}    
```