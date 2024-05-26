#include <stdlib.h>
#include <stdio.h>


void getCombination(int);
int** initializeTable(int);
void printTable(int**, int);

int main() {

    int N;
    printf("Enter N: ");
    scanf(" %d", &N);
    printf("\n");
	
    getCombination(N);

    return 0;
}

int** initializeTable(int N) {
    int** options = (int**)malloc(sizeof(int*)*(N+2));
    for(int i = 0; i<(N+2); i++){
        options[i] = (int*)malloc(sizeof(int)*(N+2));
    }

    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < N+2; j++) {
            options[i][j] =0;
        }
    }

    return options;
}

void printTable(int** table, int N) {
    int i, j;
    i = j = (N+2);
    printf("Calling print table.\n");
    printf("%d, %d\n", i, j);
    for (i; i<N+2; i++) {
        for (j; j<N+2; j++) {
            printf("%d\t", table[i][j]);
        }
        printf("\n");
    }
}

void getCombination(int N) {
    int** table = initializeTable(N);
    printTable(table, N);
}