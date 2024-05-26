#include <stdio.h>
#include <stdlib.h>
#define N 4


int main(){
	int start, move;
	int nopts[N+2]; //array of top of stacks
	int option[N+2][N+2]; //array of stacks of options
	int i, candidate;

	move = start = 0; 
	nopts[start]= 1;
	
	while (nopts[start] >0) //while dummy stack is not empty
	{
		if(nopts[move]>0) 
		{
			move++;
			nopts[move]=0; //initialize new move

			//populate move
			if(move == 1){
				for(candidate = N; candidate >=1; candidate --) 
				{
					nopts[move]++;
					option[move][nopts[move]] = candidate;
					printf("nopts[move] %i candidate %i:\n", nopts[move], candidate);           
				}
			}
			else if(move<=N){
				for(candidate=N;candidate>=1;candidate--)
				{
					for(i=move-1;i>=1;i--)
						if(candidate==option[i][nopts[i]]) break;
					if(!(i>=1))
						option[move][++nopts[move]] = candidate;
				}
			}
		}
		else 
		{
           printf("ELSE======== move:%d \n",move);
           
            for(i=1;i<move;i++)
                printf("%2i",option[i][nopts[i]]); //print top of stack
            printf("\n");

			
            (nopts[--i])--; //pop the top of stack

			
			//condition to go back 
            // n + 1 - input for the reverse order
            if(nopts[i]>0){
				if(option[i][nopts[i]]<option[move][nopts[move]]){ //move-1's top of stack < move's top of stack
					//nopts[move]= nopts[i] - 1;
					nopts[move]= N + 1 - move;
					move++;
				}
			}

			
            if(nopts[i]==0){ //if Last TOS==0  
                move--; //backtrack move
                printf("=====Backtracking move:%d\n",move);
            }
			
            if(move==0){
                nopts[move]--;
            }
		}
	}
}

