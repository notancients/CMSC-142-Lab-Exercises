/*
	Exercise Vertex Coloring
	1. Complete the basic greedy coloring program below.
	2. Analyze the running time of the program.
	3. Improve the quality of your solution by determining a good starting vertex.
*/

#include<stdio.h>
#include<malloc.h>

typedef struct node{
	int x;
	struct node *next;
} graph;

graph **createAdjList(int *, int *);
void viewList(graph **, int);
int * graphColoring(graph **, int);
int getAvailableColor(graph **, int *, int, int);
void viewColor(int *, int);
void deleteGraph(graph **, int);


int main(){
	graph **g;
	int v, e;
	int *color;
	
	g = createAdjList(&v, &e);
	color = graphColoring(g, v);
	viewList(g, v);
	viewColor(color, v);
	
	free(color);
	deleteGraph(g, v);

    return 0;
}

graph **createAdjList(int *v, int *e){
	/*insert code here for creating an adjacency list*/
	int i;
    int from, to;
    graph* newNode;
    // Code for reading the .in file

    // printf("Enter amount of vertices:");
    scanf(" %d", v);
    // printf("Enter amount of edges: ");
    scanf(" %d", e);

    printf("Amount of Vertices: %d | Amount of Edges: %d\n", (*v), (*e));

    graph** adjacencyList = (graph**)malloc(sizeof(graph*)*(*v));

    // Initializing to null just to be safe
    for(i = 0; i < (*v); i++) {
        adjacencyList[i] = NULL;
    }

    for(i=0; i<(*e); i++) {
        //////////////////////////////////////////////
        // Get the from and to as inputs from the user
        scanf( "%d", &from);
        scanf( "%d", &to);
        //////////////////////////////////////////////
        // First append the to node to the from row

        newNode = (graph*)malloc(sizeof(graph));
        newNode->next = NULL;
        newNode->x = to;

        if (adjacencyList[from] == NULL) {
            adjacencyList[from] = newNode;
        } else {
            newNode->next = adjacencyList[from];
            adjacencyList[from] = newNode;
        }

        /////////////////////////////////////
        // Now append to from node to the to row

        newNode = (graph*)malloc(sizeof(graph));
        newNode->next = NULL;
        newNode->x = from;

        if (adjacencyList[from] == NULL) {
            adjacencyList[to] = newNode;
        } else {
            newNode->next = adjacencyList[to];
            adjacencyList[to] = newNode;
        }
        //////////////////////////////////////////////////
        printf("Successfully inserted a node from %d to %d.\n", from, to);
   }
    
    // End of code for reading the .in file

    return adjacencyList;
}

void viewList(graph **g, int v){
	int i;
	graph *p;
	
	for(i = 0; i < v; i++){
		p = g[i];
		printf("%d: ", i);
		//traverse the list connected to vertex i
		while(p != NULL){
			printf("%3d", p->x);
			p = p->next;
		}
		printf("\n");
	}
}

// TODO CHECK RUNNING TIME
int * graphColoring(graph **g, int v){
	int *colorOfTheVertices, availCol, i;
	
	//colors are represented as integers starting from 0
	colorOfTheVertices = (int *)malloc(sizeof(int)*v);
	for(i = 0; i < v; i++)
		colorOfTheVertices[i] = -1; // -1 means they dont have colors yet
	
	colorOfTheVertices[0] = 0;	//assign first vertex with the first color
	for(i = 1; i < v; i++){
		availCol = getAvailableColor(g, colorOfTheVertices, v, i);
		colorOfTheVertices[i] = availCol;
	}
	return colorOfTheVertices;
}

int getAvailableColor(graph **g, int *color, int v, int curr){
	graph *p;
	int *available, i, availCol;
	
	//keeps track of the colors used on any previously colored vertices adjacent to it
	available = (int *)malloc(sizeof(int)*(v));
	for(i = 0; i < v; i++)
		available[i] = 1;
	///////////////////////////////////////////////////////////

	// set p to the row (or vertex) we are analyzing
	p = g[curr];
	
	//traverse that row to check if the vertices adjacent to the target vertex
	//has a color that are not available for us
	for(p; p!=NULL; p = p->next) {
		available[color[p->x]] = 0;
	}

	//////////////////////////////////////////////////////////

	for(i = 0; i < v; i++){				//get the smallest color that is available
		if(available[i] == 1){
			availCol = i;
			break;
		}
	}
	
	free(available);
	return availCol;
}

void viewColor(int *color, int v){
	int i;
	
	for(i = 0; i < v; i++){
		printf("Vertex %d -> Color %d\n", i, color[i]);
	}
}

void deleteGraph(graph **g, int v){
	int i;
	graph *p;
	for(i = 0; i < v; i++){
		while(g[i] != NULL){
			p = g[i];
			g[i] = g[i]->next;
			free(p);
		}
	}
	free(g);
};