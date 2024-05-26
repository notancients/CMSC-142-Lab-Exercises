/*
CMSC 142-EF2L
Exer 7
Mende, Tajan Caeli B.
Robles, Erjoy Constantine L.

Description: CHECK IF A SUBSET EXISTS THAT WOULD CREATE THE SUM
Where n is the number of rows and k is the maximum sum.
The advantages would be having to run O(n*k) once and the rest of finding the subset will be O(1).
The disadvantae would be having to use up a lot of storage depending on the values of n and k.

*/
#include <stdio.h>
#include <stdlib.h>

int comp(const void *a, const void *b){
	int *x, *y;
	x = (int *) a;
	y = (int *) b;
	return (*x - *y);
}

int main() {
    /*Initialize Values*/

    int s[] = {2, 3, 7, 5, 9}; //set of numbers
    int rows = sizeof(s) / sizeof(s[0]); //5 elements
    qsort(s, rows, sizeof(int), comp);//sort out array


    int k = 11; //max sum | 0-10
    int sum = 11; // Sum to be checked
    
    /*Create Dynamic Table Matrix*/

    int matrix[rows][k+1];

    for(int i = 0; i <rows; i++){
        for (int j =0; j< k+1; j++){
            if(j==0){
                matrix[i][j] = 1; //populating 1s in the 1st Column (sum == 0)
            } else if (i == 0) {
                matrix[i][j] = (s[i] == j) ? 1 : 0; //populating the first row 
            } else { 
                if (j >= s[i]){ //find the sum max
                     matrix[i][j]= (matrix[i-1][j]>=matrix[i-1][j-s[i]]) ? matrix[i-1][j]: matrix[i-1][j-s[i]];
                }else{ //copy previous values
                    matrix[i][j]= matrix[i-1][j]; 
                }
            }
        }
    }

    /* Print dynamic table */
    printf("  j: ");
    for (int j = 0; j < k+1; j++) {
        printf("%3d", j);
    }
    printf("\n-----------------------------------------\n");

    for (int i = 0; i < rows; i++) {
        printf("%3d: ", s[i]);
        for (int j = 0; j < k+1; j++) {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }


    /* Check if subset exists */
    int subset[rows];
    int subi=0;
    int j = sum;
    int i = rows -1;


    if(matrix[i][j]==1){
        while(i>=0 && j!=0){
            if(matrix[i-1][j]==0||i==0){ //current is highest i
                subset[subi++]=s[i]; //get subset
                j= j-s[i]; //go left
            }
            i--; //go up
            
        }
    }

    if (subi==0){
        printf("\nNo such sum of %d exists!!!!!\n", sum);
    }else{
        printf("\nThe subset sum of %d exists and is \n {", sum);
        for(int x=0; x<subi; x++){
            printf("%d, ", subset[x]);
        }
        printf("}\n");
    }

    
    return 0;
}