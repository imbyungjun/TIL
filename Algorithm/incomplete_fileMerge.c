//  MergingFiles
//  Find out smallest cost of merging files
//  cost = fsize1 + fsize2

	#include <stdio.h>
	#include <stdlib.h>
	
	#define MAXSIZE 500
	#define MAXIMUM 9999999

	 int getCost(int arr[], int begin, int last) {
		int i, min = MAXIMUM;
    int sum;
    
    if (begin == last) return arr[begin];
    
    for (i=begin; i<last; i++) {
        sum = getCost(arr, begin, i) + getCost(arr, i+1, last);
        if (min > sum) min = sum;
    }
    return min;
	} 

void mergeFile() {
    int i, size;
    int arr[MAXSIZE];
    
    scanf("%d", &size);
    for (i=0; i<size; i++)
        scanf("%d", &arr[i]);
    
    printf("%d\n", getCost(arr, 0, size-1));
}

int main(){
    int testCases, cases;
	scanf("%d", &testCases);

    for(cases=0; cases<testCases; cases++)
        mergeFile();        //call mergeFile func
}
