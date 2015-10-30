//  hw20.c
//  20113316 imbyungjun
//
//  MergingFiles
//  Find out smallest cost of merging files

#include <stdio.h>
#include <stdlib.h>

#define MAX 500

int arr[MAX], min[MAX][MAX], cost[MAX][MAX];

void getCost(int size) {
   int i, j, k, d;
   int sum, nowCost, minSum, minCost;

   /* initialize min array */
   for (i = 0; i<size; i++)
      min[i][i] = arr[i];

   for (d = 1; d<size; d++)      /* diagonal */
      for (i = 0; i<size - d; i++) {
         j = i + d;
         minSum = minCost = 2e9;
         for (k = i; k<j; k++) {
            sum = min[i][k] + min[k + 1][j];
            nowCost = sum + cost[i][k] + cost[k + 1][j];

            if (minCost > nowCost)
            {
               minSum = sum;
               minCost = nowCost;
            }
         }
         min[i][j] = minSum;
         cost[i][j] = minCost;
      }
}

void mergeFile(FILE *fin) {
   int i, size;

   fscanf(fin, "%d", &size);

   for (i = 0; i<size; i++)
      fscanf(fin, "%d", &arr[i]);

   getCost(size);

   printf("%d\n", cost[0][size - 1]);
}

int main() {
   int testCases, cases;
   FILE* fin = fopen("input.txt", "r");    //input.txt file open

   fscanf(fin, "%d", &testCases);      //read testCases

   for (cases = 0; cases<testCases; cases++)
      mergeFile(fin);        //call mergeFile func

   fclose(fin);            //file close

   return 0;           //exit program
}