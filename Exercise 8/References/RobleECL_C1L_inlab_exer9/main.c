#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "graph.h"

//Implement your functions here

/*
	CREATE GRAPH
	- allocates memory for the graph
	- initializes the members of the structure + arrays
	- returns the newly created graph
*/
GRAPH *createGraph(int vertices) {
	int i, j;
	GRAPH* newGraph = (GRAPH*)malloc(sizeof(GRAPH));
	int** newMatrix = (int**)malloc(sizeof(int*)*vertices);
	for(i = 0; i<vertices; i++) {
		newMatrix[i] = (int*)malloc(sizeof(int)*vertices);
	}
	newGraph->matrix = newMatrix;
	newGraph->num_vertices = vertices;

	for (i = 0; i<vertices; i++) {
		for(j = 0; j<vertices; j++){
			newMatrix[i][j] = 0;
		}
	}
	return newGraph;
}

/*
	INSERT EDGE
	- plots the adjacent vertices in the adjacency matrix
*/
void insertEdge(GRAPH *G, int u, int v) {
	G->matrix[u][v] = 1;
	G->matrix[v][u] = 1;
}

/*
	CREATE VISITED
	- returns an integer array called visited - allocate and initialize your array properly
	- this will be used in the dfs() function to mark visited nodes
	- 0: visited, 1: not visited yet
*/
int *createVisited(GRAPH *G) {
	int* visited = (int*)malloc(sizeof(int)*G->num_vertices);

	for(int i = 0; i<G->num_vertices; i++) {
		visited[i] = 0;
	}
	return visited;
}

/*
	DFS
	- implements a non-recursive DFS traversal
	- you may use the functions in the stack.h file 
*/
void dfs(GRAPH *G, int start) {
	int i;
	int n = G->num_vertices;
	STACK* stack = createStack();
	int* visited = createVisited(G);
	int** matrix = G->matrix;

	push(stack, createNode(start));

	while(!isEmpty(stack)) {
		int v = pop(stack);
		if(!visited[v]) {
			visited[v] = 1;
			printf("%d\t", (v+1));
		}

		for(i = n; i>=0; i--) {
			if(matrix[v][i] && !visited[i]) {
				push(stack, createNode(i));
			} 
		}
	}
}

/*
	PRINT MATRIX
	- prints the values of the adjacency matrix
	- follow the layout provided in the sample run
*/
void printMatrix(GRAPH *G) {

	int** matrix = G->matrix;
	for(int i = 0; i<G->num_vertices; i++) {
		for (int j = 0; j<G->num_vertices; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

/*
	FREE MATRIX
	- frees the allocated memory for the adjacency matrix
*/
void freeMatrix(GRAPH *G) {

	if(G->matrix == NULL) {
		return;
	}

	int i, j;
	for(i = 0; i<G->num_vertices; i++) {
		int* curr = G->matrix[i];
		free(curr);
	}

	free(G->matrix);
	G->matrix = NULL;
}

/////////////////////////////////////////////////////////////////////////

int main() {
	char command;
	int vertices, lines, u, v;

	scanf("%d", &vertices);
	GRAPH *G = createGraph(vertices);

	while(1) {
		scanf(" %c", &command);

		switch(command) {
			case '+':
				scanf(" %d %d", &u, &v);
				insertEdge(G, u-1, v-1); //there's a -1 since we use 0-indexing in the arrays
				printf("Successfully inserted edge %d %d\n", u, v);
				break;
			case '#':
				printf("\nDFS: ");
				dfs(G, 0); //0 is the initial value since we use 0-indexing (it still represents vertex 1)
				printf("\n");
				break;
			case 'p':
				printf("\nADJACENCY MATRIX: \n");
				printMatrix(G);
				break;
			case 'f':
				freeMatrix(G);
				break;
			case 'Q':
				freeMatrix(G);
				free(G);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}
}
