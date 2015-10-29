#Pythagorean Expectation
-
A formula similar to the famous Pythagorean Theorem has been used in baseball. This is called Pythagorean
Expectation, invented by Bill James. This expectation is used to estimate how many games a baseball team
should have won during a season. The Pythagorean Expectation W for a baseball team is defined as follows.  

W = S\*S / (S\*S + A\*A)  

where S is the number of runs the team scored, and A is the number of runs the team allowed. The formula name comes from the resemblance to the Pythagorean Theorem.  

Given records of the games between n baseball teams, you are to write the largest and the smallest
Pythagorean expectations of the teams.

**Input**  
Your program is to read from standard input. The input consists of T test cases. The number of T test cases is
given in the first line of the input. Each test case starts with a line containing two integers, n(2 <= n <= 1,000) and m(2 <= m <= 1,000), where n is the number of baseball teams, and m is the total number of games
between n teams. In the following m lines, a record for each game is given line by line. Each record is
represented by four numbers a,b,p,q, separated by a single space, which means team a has played against
team b, and team a has scored p runs and team b has scored q runs. Note that 1 <= a != b <= n, and p and q are non-negative integers no more than 20. Note that teams in a test case may have different number of games. If a team has no scored and allowed runs, then its expectation value becomes zero.

**Output**  
Your program is to write to standard output. Print two integers for each test case. The first line should contain
the integer part of the value, the largest Pythagorean Expectation of the teams times 1,000. The second line
should contain the integer part of the value, the smallest Pythagorean Expectation of the teams times 1,000.

**Sample Input**
	
	2
	3 5
	1 2 3 5
	1 3 10 1
	1 2 0 7
	2 3 9 3
	3 2 4 5
	4 6
	1 2 0 11
	1 3 17 13
	1 4 17 1
	2 3 7 12
	2 4 19 17
	3 4 17 0
	
**Output for the Sample Input**

	871
	100
	753
	103
	
-
#Code
	
	//  Pythagorean
	//  Get pythagorean expectation
	//  W = S*S / (S*S + A*A)
	
	#include <stdio.h>
	
	#define MAX 1001
	//  Equation of W*1000
	#define EXP(a,b) 1000*(a)*(a)/((a)*(a)+(b)*(b))
	
	//  Get pythagorean expectation
	void expectation(FILE *fin) {
	    int n, m, a, b, p, q, w;
	    int i;
	    int max = -1, min = 20002;
	    
	    int S[MAX] = {0};       /* scored */
	    int A[MAX] = {0};       /* allowed */
	    
	    fscanf(fin, "%d %d", &n, &m);
	    for(i=0; i<m; i++) {
	        fscanf(fin, "%d %d %d %d", &a, &b, &p, &q);
	        S[a] += p;  A[a] += q;
	        S[b] += q;  A[b] += p;
	    }
	    for(i=1; i<=n; i++) {
	        if((w = EXP(S[i],A[i])) == 0)
	            w = 0;
	        if(w < min)
	            min = w;
	        if(w > max)
	            max = w;
	    }
	    
	    printf("%d\n%d\n", max, min);
	}
	
	int main(){
	    int testCases, cases;
	    FILE* fin = fopen("input.txt", "r");    //input.txt file open
	    
	    fscanf(fin, "%d", &testCases);      //read testCases
	    
	    for(cases=0; cases<testCases; cases++)
	        expectation(fin);       //call expectation func
	    
	    fclose(fin);            //file close
	    
	    return 0;           //exit program
	}
