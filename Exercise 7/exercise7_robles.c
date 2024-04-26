/*
INSTRUCTIONS:
Implement the dynamic programming solution for the Subset Sum problem in C. 
Print the matrix, say whether a subsets exists or not, then print the subset if it does.

Also answer the following questions:
1) What do you think are the advantages or disadvantages of this dynamic programming solution.
2) What is the running time of this dynamic programming solution? 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int** createTable(int elementCount, int target) {
    int** table = (int**)malloc(sizeof(int*)*elementCount);
    for (int i = 0; i < elementCount; i++) {
        int* row = (int*)malloc( sizeof(int) * (target+1) );
        row[0] = 1;
        for (int j = 1; j < (target+1); j++) {
            row[j] = 0;
        }
        table[i] = row;
    }

    return table;
}

void printTable(int** table, int* elements, int elementCount, int target) {
    int i;

    printf("\t");
    for(i = 0; i <= target; i++) {
        printf("%d\t", i);
    }
    printf("\n");

    for (i = 0; i < elementCount; i++) {
        printf("%d\t", elements[i]);
        for (int j = 0; j < (target + 1) ; j++) {
            printf("%d\t", table[i][j]);
        }
        printf("\n");
    }
}

int** subsetSolver(int* numberSet, int elementCount, int target) {
    int i;
    int** table = createTable(elementCount, target);

    // This would be the loop that would create a growing subset
    // from all the elements in the number set
    for (i=0; i <= elementCount; i++) {
        
    }
}

int subsetHelper(int* numberSet, int subsetSize, int target) {
    int valid = 0;
    int currentSum;
    int i, j, k;
    

    for (i = 0; i < subsetSize; i++) {
        currentSum = numberSet[i];
        for (j = i; j<(subsetSize-i); j++) {
            for (k = i; k < subsetSize; k++) {
                currentSum += numberSet[k];
                printf("Currrent sum: %d.\n", currentSum);
                if(currentSum == target) {
                    valid = 1;
                    break;
                }
            } // end of inner loop
            if (valid == 1) {
                break;
            }
        } // end of middle loop
        printf("Current sum at the end of the outer loop for %d: %d.\n", numberSet[i], currentSum);
        if (valid == 1) {
                break;
            }
    } // end of outer loop  
}

int subsetTraceback(int** table, int target) {

}

int main() {
    int set1[] = {1, 3, 4, 5, 6, 10};
    int size1 = 6;
    int target1 = 10;
    int** table1 = createTable(size1, target1);
    printTable(table1, set1, size1, target1);
    

    // subsetHelper(set1, size1, target1);
    return 0;
}