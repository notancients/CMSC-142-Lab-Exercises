typedef struct node_tag{
    int data;
    struct node_tag* next;
}NODE;

typedef struct linkedlist_tag {
    struct node_tag* head;
} LIST;

LIST* createList();

NODE* createNode(int n);

void addToHead(LIST* list, int n);

void printList(LIST* list);
