#include <stdio.h>
#include <stdlib.h>

void getCombination(int N);

int main() {
    int N;
    printf("Enter N: ");
    scanf("%d", &N);
    printf("\n");
	
    getCombination(N);
    return 0;
}

void printCombination(int N, int** grid, int* stackTopArray) {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= stackTopArray[i]; j++) {
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void getCombination(int N) {
    int stackTopArray[N + 2];
    int optionGrid[N + 2][N + 2];
    for (int i = 0; i <= N + 1; i++) {
        stackTopArray[i] = 0;
    }
    
    int targetStack = 1;
    while (targetStack > 0) {
        if (stackTopArray[targetStack] > 0) {
            targetStack++;
            stackTopArray[targetStack] = 0;
            if(targetStack==N+1) {     //solution found!
                // CHECK: This part prints the actual answers somehow.
				for(int i=1;i<targetStack;i++)
					printf("%2i",optionGrid[i][stackTopArray[i]]);
				printf("\n");
			}
        } else {
            targetStack--;
            stackTopArray[targetStack]--;
        }

        if (targetStack < 1) {
            break;
        }

        for (int candidate = 1; candidate <= N; candidate++) {
            int flag = 0;
            for (int i = targetStack - 1; i > 0; i--) {
                if (candidate == optionGrid[i][stackTopArray[i]]) {
                    flag = 1;
                    break;
                }
            }
            if (!flag) {
                optionGrid[targetStack][++stackTopArray[targetStack]] = candidate;
            }
        }
    }
}
