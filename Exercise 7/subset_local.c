#include <stdio.h>
/*
CHECK IF A SUBSET EXISTS THAT WOULD CREATE THE SUM
*/

int main() {
    /*Initialize Values*/

    int s[] = {2, 3, 5, 7, 9}; //set of numbers
    //need to add qsort for inputting
    int rows = sizeof(s) / sizeof(s[0]); //5 elements
    int k = 10; //max sum | 0-10
    int sum = 10; // Sum to be checked
    
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
                subset[subi]=s[i]; //get subset
                subi++;
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