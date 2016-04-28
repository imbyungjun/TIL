//  hw23.c
//  20113316 imbyungjun
//
//  Card Game

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000
#define min(a,b) (a)>(b)?(b):(a)
#define max(a,b) (a)>(b)?(a):(b)

int diagonal[MAXSIZE][MAXSIZE];
int card[MAXSIZE][MAXSIZE];

//  print maximum sum of Alice's cards
void selectCard(int card[][MAXSIZE], int size) {
    int i, j, k, d;
    int sum;
    
    /* initialize sum of interval */    
    for (d = 1; d < size; d++) {
        for (i=0; i<size-d; i++) {
            j = i + d;
            
            diagonal[i][j] = diagonal[i][i] + diagonal[i+1][j];
        }
    }
    
    for (d = 1; d < size; d++) {
        for (i = 0; i < size-d; i++) {
            j = i + d;
            card[i][j] = diagonal[i][j] - (min(card[i+1][j], card[i][j-1]));
        }
    }
    
    printf("%d\n", card[0][size-1]);
}
void cardGame(FILE *fin) {
    int i, j, n;
    
    fscanf(fin, "%d", &n);
    
    for (i=0; i<n; i++)  {
        fscanf(fin, "%d", &card[i][i]);
        diagonal[i][i] = card[i][i];
    }
    
    selectCard(card, n);    
}

int main(){
    int testCases, cases;
    FILE* fin = fopen("input.txt", "r");    //input.txt file open
    
    fscanf(fin, "%d", &testCases);      //read testCases
    
    for(cases=0; cases<testCases; cases++)
        cardGame(fin);        //call cardGame func
    
    fclose(fin);            //file close
    
    return 0;           //exit program
}
