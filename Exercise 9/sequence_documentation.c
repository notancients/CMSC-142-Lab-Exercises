#include <stdio.h>
#include <stdlib.h>
#define N 3

int main(){
	int start, targetStack;
	int stackTopArray[N+2]; //array top of stacks
	int optionGrid[N+2][N+2]; //array stacks of optionGrids
	int i, candidate;

	targetStack = start = 0; 
	stackTopArray[start]= 1;
	
	while (stackTopArray[start] >0)
	{
		if(stackTopArray[targetStack]>0)
		{
			targetStack++;
			stackTopArray[targetStack]=0; //initialize new targetStack

			//print - solution found!
			if(targetStack==N+1){
				for(i=1;i<targetStack;i++)
					printf("%2i",optionGrid[i][stackTopArray[i]]);
				printf("\n");
			}
			//populate
			else //find candidates
			{
				for(candidate = N; candidate >=1; candidate --) 
				{
					stackTopArray[targetStack]++;
					optionGrid[targetStack][stackTopArray[targetStack]] = candidate;
				} 
			}
		}
		else 
		{
			//backtrack
			targetStack--;
			stackTopArray[targetStack]--;
		}
	}

}
