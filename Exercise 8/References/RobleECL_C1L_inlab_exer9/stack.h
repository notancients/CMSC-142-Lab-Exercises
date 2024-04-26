/* DO NOT EDIT THIS FILE */

/* STACK ADT */

typedef struct node_tag{
	int value;
	struct node_tag* next;
}NODE;


typedef struct list_tag{
	NODE* head;
}STACK;



/*
** printStack()
** requirements: none
** results:
	if list is empty, prints "*empty*"
	otherwise, prints the contents of a list
*/
void printStack(STACK *L);



/*
** createNode()
** requirements: an integer data
** results:
	creates an empty node with value `data`
	initializes fields of the structure
	returns the created node
*/
NODE* createNode(int data);



/*
** createStack()
** requirements: none
** results:
	creates an empty list
	initializes `head` field of the structure
	returns the created list
*/
STACK* createStack();



/*
** isEmpty()
** requirements: none
** results:
	returns 1 if the list is empty
	otherwise returns 0
*/
int isEmpty(STACK *L);



/*
** push()
** requirements: a list and a node to be inserted
** results:
	inserts `node` before the current `head` of the list
*/
void push(STACK *L, NODE* node);



/*
** pop()
** requirements: a list that must not be empty
** results:
	deletes the `head` node of the list
	returns the value of the deleted node
*/
int pop(STACK *L);
