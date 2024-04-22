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
            // E.G if N = 3, targetStack must be 4 (the arrow here is the targetStack)
            // 0 | 1 | 2 | 3 | 4
            //                 ^
			if(targetStack==N+1) {     //solution found!
                // CHECK: This part prints the actual answers somehow.
				for(i=1;i<targetStack;i++)
					printf("%2i",optionGrid[i][stackTopArray[i]]);
				printf("\n");
			}
            // This triggers if targetStack is pointing at the first index, meaning the first actual value
            // E.G If N=3 (the arrow here is the targetStack)
            // 0 | 1 | 2 | 3 | 4
            //     ^
			else if(targetStack == 1) {
                // set candidate to the last stack and then decrement until it reaches 0 (not inclusive)
				// I believe this would only really repopulate the first stack?
				for(candidate = N; candidate >=1; candidate --) {
					stackTopArray[targetStack]++;	// increment the top of stack at the first stack since we are repopulating, it would eventually become N
					optionGrid[targetStack][stackTopArray[targetStack]] = candidate; // this is the part that puts 3, 2, 1 descending onto the grid
					printf("stackTopArray[targetStack] %i candidate %i:\n", stackTopArray[targetStack], candidate);           
				}
			}
			else {
				// set the candidate to the bottom row since we are using an inverted stack, this means that whatever is
				// candidate is the top of stack; we would do this until we reach row 0 (not inclusive)
				for(candidate=N;candidate>=1;candidate--) {
					//
					for(i=targetStack-1;i>=1;i--)
						if(candidate==optionGrid[i][stackTopArray[i]]) break; //
					
					//
					if(i<1)
						optionGrid[targetStack][++stackTopArray[targetStack]] = candidate;
				}
			}
		} 
        // This is the back tracking part. This only triggers if the value of the top of stack at the target stack is zero
        // 1 | 0 | 0 | 0 | 0
        // 0 | 1 | 2 | 3 | 4
        //     ^
        else { 
			targetStack--; // point to the previous stack
			stackTopArray[targetStack]--; // then decrement the value of the top stack to the new target stack
            // this would be the part that would cause the value stackTopArray[start] to become zero terminating the entire while loop
        }
	}
}