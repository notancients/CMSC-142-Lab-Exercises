#include <stdio.h>
#include <stdlib.h>

// This has been created using the permutation version

void getCombination(int N);

int main(){
    int N;
    printf("Enter N: ");
    scanf(" %d", &N);
    printf("\n");
	
    getCombination(N);
}

void getCombination(int N) {
    int start, targetStack;
	int stackTopArray[N+2]; //array of top of stacks
	int optionGrid[N+2][N+2]; //array of stacks of optionGrids
	int i, candidate;

    start = 0;

	targetStack = 0; 
	stackTopArray[start]= 1;
	
    
	while (stackTopArray[start] >0) //while dummy stack is not empty
	{
		if(stackTopArray[targetStack]>0) {
			targetStack++;
			stackTopArray[targetStack]=0; //initialize new targetStack

            // This part triggers if targetStack is now pointing to the last index in the array
            // E.G if N = 3, targetStack must be 4
			if(targetStack==N+1) {     //solution found!
                // CHECK: This part prints the actual answers somehow.
				for(i=1;i<targetStack;i++)
					printf("%2i",optionGrid[i][stackTopArray[i]]);
				printf("\n");
			}
            // This triggers if targetStack is pointing at the first index, meaning the first actual value
            // E.G If N=3
            // 0 | 1 | 2 | 3 | 4
            //     ^
			else if(targetStack == 1) {

				for(candidate = N; candidate >=1; candidate --) {
					stackTopArray[targetStack]++;
					optionGrid[targetStack][stackTopArray[targetStack]] = candidate;
					printf("stackTopArray[targetStack] %i candidate %i:\n", stackTopArray[targetStack], candidate);           
				}
			}
			else {
				for(candidate=N;candidate>=1;candidate--) {
					for(i=targetStack-1;i>=1;i--)
						if(candidate==optionGrid[i][stackTopArray[i]]) break;
                        
					if(!(i>=1))
						optionGrid[targetStack][++stackTopArray[targetStack]] = candidate;
				}
			}
		} else {
			targetStack--;
			stackTopArray[targetStack]--;
        }
	}
}