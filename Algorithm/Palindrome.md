#Palindrome
-
A number is a palindrome if it reads the same backward or forward.  
For example, 747 is a palindrome. 255 is
also a palindrome as it is FF in hexadecimal. Given a positive integer, write a program whether it can be a
palindrome with a certain base B(2 <= B <= 64).  
Note that the base is the number of unique digits (including zero) used to represent numbers. For example, for the decimal system the base B is 10.  

**Input**  
Your program is to read from standard input. The input consists of T test cases. The number of test cases T is
given in the first line of the input. Each test case consists of a line containing a positive integer between 64 and 1,000,000, inclusively.

**Output**  
Your program is to write to standard output. Print exactly one line for each test case. The line should contain 1 if the number can be a palindrome with a certain base B(2 <= B <= 64), and 0 otherwise.  
The following shows sample input and output for three test cases

**Sameple Input**
	
	3
	747
	255
	946734
	
**Output for the Sample Input**

	1
	1
	0
-
#Code
	//  Palindrome
	//  Test for palindrome in base 2 ~ 64.

	#include <stdio.h>
	#define MAX 1000000

	//  return 1 if arr is palindrome, 0 on not
	int isPalindrome(int arr[], int size) {
		int left = 0, right = size-1;
		while(left < right) {
			if(arr[left++] != arr[right--])
				return 0;
		}
		return 1;
	}

	//  return 1 if palindrome in 2 ~ 64 base. else return 0
	int palindrome(FILE *fin) {
		int i, k = 0, arr[MAX] = {0};
		int N, n, base = 2;
    
		fscanf(fin, "%d", &N);
    
		for(base=2; base<=64; base++) {
			n = N;
			k = 0;
			while(n > 0) {
				arr[k++] = n%base;
				n /= base;
			}
			if(isPalindrome(arr,k))
				return 1;
		}
		return 0;
	}

	int main(){
		int testCases, cases;
		FILE* fin = fopen("input.txt", "r");    //input.txt file open
    
		fscanf(fin, "%d", &testCases);      //read testCases
    
		for(cases=0; cases<testCases; cases++)
		printf("%d\n", palindrome(fin));          //call palindrome func
    
		fclose(fin);            //file close
    
		return 0;           //exit program
	}
