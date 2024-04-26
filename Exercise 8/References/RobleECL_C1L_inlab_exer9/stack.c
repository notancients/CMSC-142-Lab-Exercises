#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_tag{
	int value;
	struct node_tag* next;
}NODE;


typedef struct list_tag{
	NODE* head;
}STACK;

/*
** isEmpty()
** requirements: none
** results:
	returns 1 if the list is empty
	otherwise returns 0
*/
int isEmpty(STACK *L) {
    if(L->head == NULL) {
        return 1;
    }
    return 0;
}

/*
** printStack()
** requirements: none
** results:
	if list is empty, prints "*empty*"
	otherwise, prints the contents of a list
*/
void printStack(STACK *L){
    if (isEmpty(L)) {
        printf("*empty*\n");
        return;
    }

    NODE *temp = L->head;

    while(temp != NULL) {
        printf("%c ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}



/*
** createNode()
** requirements: an integer data
** results:
	creates an empty node with value `data`
	initializes fields of the structure
	returns the created node
*/
NODE* createNode(int data){
    NODE *node = (NODE *)malloc(sizeof(NODE));
    node->value = data;
    node->next = NULL;
    // printf("Node created.\n");
    return(node);
}



/*
** createStack()
** requirements: none
** results:
	creates an empty list
	initializes `head` field of the structure
	returns the created list
*/
STACK* createStack() {
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    stack->head = NULL;
    // printf("Stack created.\n");
    return stack;
}

/*
** push()
** requirements: a list and a node to be inserted
** results:
	inserts `node` before the current `head` of the list
*/
void push(STACK *L, NODE* node) {
    node->next = L->head;
    L->head = node;
    // printf("Pushed a node: %c.\n", node->value);
}



/*
** pop()
** requirements: a list that must not be empty
** results:
	deletes the `head` node of the list
	returns the value of the deleted node
*/
int pop(STACK *L) {
    NODE *temp = L->head;
    L->head = L->head->next;
    int num = temp->value;
    free(temp);
    // printf("Popped a node: %c.\n", num);
    return num;
}
