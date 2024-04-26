#include <stdio.h>
#include <stdlib.h>
#include "list.h"
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
void insertEdge(GRAPH *G, int u, int v, int w) {
	G->matrix[u][v] = w;
}



/*
	CREATE VISITED
	- returns an integer array called visited - allocate and initialize your array properly
	- this will be used in the dijkstra() function to mark visited nodes
	- 1: visited, 0: not visited yet
*/
int *createVisited(GRAPH *G) {
	int* visited = (int*)malloc(sizeof(int)*G->num_vertices);
	for(int i =0; i <G->num_vertices; i++) {
		visited[i] = 0;
	}
	return visited;
}


/*
	CREATE DISTANCE
	- returns an integer array called distance - allocate and initialize your array properly
	- this will be used in the dijkstra() function to keep track of the distance of the vertices
	- initialize to 99999 (maximum distance possible)
*/
int *createDistance(GRAPH *G) {
	int* distance = (int*)malloc(sizeof(int)*G->num_vertices);
	for(int i =0; i <G->num_vertices; i++) {
		distance[i] = 9999;
	}
	return distance;
}


/*
	CREATE PARENT
	- returns an integer array dijkstra parent - allocate and initialize your array properly
	- this will be used in the dijisktra() function to keep track of the parent of a visited vertex
	- initialize to -1 (no parent yet)
*/
int *createParent(GRAPH *G) {
	int* parent = (int*)malloc(sizeof(int)*G->num_vertices);
	for(int i =0; i <G->num_vertices; i++) {
		parent[i] = -1;
	}
	return parent;
}

/*
	DIJKSTRA
	- implements dijkstra's algorithm to find the shortest path from a source to a target
	- computes for the distance of the path
	- you may create additional functions for the different operations needed in the dijkstra's algorithm
*/
void dijkstra(GRAPH *G, int source, int target) {
	int i, j, k, l, v, d, min, dist, p;
	int* matRow;
	LIST* list = createList();

	int** matrix = G->matrix;
	int n = G->num_vertices;
	int* visited = createVisited(G);
	int* distance = createDistance(G);
	int* parent = createParent(G);

	distance[source] = 0;
	parent[source] = -1;
	
	for(i = 0; i<n; i++) {
		/* STEPS
			- Find the non-visited node with minimum distance
			- Mark the minimum as visited
			- For every node adjacent that minimum, update their distance
			if they are not yet visited
		*/

		// FIND THE MINIMUM
		// printf("i: %d.\n",i);
		min = 9999;
		for(j=0; j<n; j++) {
			if(!visited[j] && distance[j] < min) {
				v = j;
				min = distance[j];
			}
			// printf("j: %d.\n",j);
		}
		// printf("v: %d.\n",v);
		visited[v] = 1;

		matRow = matrix[v];
		for(k=0; k<n; k++) {
			if(v==k) continue;

			d = distance[v] + matRow[k];
			if(!visited[k] && matRow[k] > 0 && d<distance[k]) {
				distance[k] = d;
				parent[k] = v;
				// printf("d:%d, v:%d\n",d,v);
			}
			// printf("k: %d.\n",k);
		}
	}

	for(l = 0; l<n; l++) {
		printf("Vertex: %d | V: %d | D: %d | P: %d .\n", l+1, visited[l], distance[l], parent[l]+1);
	}


	printf("The path from %d to %d: ", source+1, target+1);
	if(parent[target] == -1) {printf("Impossible!\n");}
	else {
		addToHead(list, target+1);
		p = parent[target];
		while(p!=-1) {
			addToHead(list, p+1);
			p = parent[p];
		}
		printList(list);
	}
	printf("Distance: from %d to %d: %d.\n", source+1, target+1, distance[target]);
	printMatrix(G);
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

LIST* createList() {
	LIST* newList = (LIST*)malloc(sizeof(LIST));
	newList->head = NULL;
	return(newList);
}

NODE* createNode(int n) {
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->data = n;
	newNode->next = NULL;
	return newNode;
}

void addToHead(LIST* list, int n) {
	NODE* newNode = createNode(n);
	newNode->next = list->head;
	list->head = newNode;
}

void printList(LIST* list) {
    NODE* temp = list->head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// End of function implementations

int main() {
	char command;
	int vertices, lines, u, v, w, source, target;

	scanf("%d", &vertices);
	GRAPH *G = createGraph(vertices);

	while(1) {
		scanf(" %c", &command);

		switch(command) {
			case '+':
				scanf(" %d %d %d", &u, &v, &w);
				insertEdge(G, u-1, v-1, w); //there's a -1 since we use 0-indexing in the arrays
				printf("Successfully inserted edge %d %d\n", u, v);
				break;
			case '#':
				scanf(" %d %d", &source, &target);
				dijkstra(G, source-1, target-1);
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