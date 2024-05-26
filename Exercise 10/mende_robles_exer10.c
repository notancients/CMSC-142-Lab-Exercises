#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define N 10
#define BALANCED 0
#define LEFT_LEANING 1
#define RIGHT_LEANING 2

typedef struct node_tag{
	int x, height;
	struct node_tag *parent;
	struct node_tag *left;
	struct node_tag *right;
}avl_node;

int max(int a, int b){
	return(a>b?a:b);
}

void updateheight(avl_node *temp){
	if(temp!=NULL)
		temp->height = max(temp->left==NULL?-1:temp->left->height,temp->right==NULL?-1:temp->right->height)+1;
}

void left_rotate(avl_node **rootptr){
	avl_node *temp1;

	if(rootptr!=NULL && *rootptr!=NULL && (*rootptr)->right!=NULL){
		temp1 = (*rootptr)->right;
		
		(*rootptr)->right = temp1->left;
		if(temp1->left!=NULL)
			temp1->left->parent = (*rootptr);

		temp1->parent = (*rootptr)->parent;

		(*rootptr)->parent = temp1;
		temp1->left = (*rootptr);

		if(temp1->parent != NULL){
			if(temp1->parent->right == *rootptr)
				temp1->parent->right = temp1;
			else
				temp1->parent->left = temp1;
		}

		*rootptr = temp1;

		updateheight(temp1->left);
		updateheight(temp1);

	}

}

void right_rotate(avl_node **rootptr){
	avl_node *temp1;

	if(rootptr!=NULL && *rootptr!=NULL && (*rootptr)->left!=NULL){
		temp1 = (*rootptr)->left;

		(*rootptr)->left = temp1->right;
		if(temp1->right!=NULL)
			temp1->right->parent = (*rootptr);

		temp1->parent = (*rootptr)->parent;

		(*rootptr)->parent = temp1;
		temp1->right = (*rootptr);

		if(temp1->parent != NULL){
			if(temp1->parent->left == *rootptr)
				temp1->parent->left = temp1;
			else
				temp1->parent->right = temp1;
		}

		*rootptr = temp1;

		updateheight(temp1->right);
		updateheight(temp1);

	}

}

void insert_fixup(avl_node **rootptr, avl_node *temp){
	int current = BALANCED, previous, lh, rh;

	do{

		lh= (temp->left==NULL?-1:temp->left->height);
		rh= (temp->right==NULL?-1:temp->right->height);

		previous=current;
		current = (lh==rh?BALANCED:(lh>rh?LEFT_LEANING:RIGHT_LEANING));

		if(abs(lh-rh)>1){
			if(current==LEFT_LEANING){
				if(previous==LEFT_LEANING)
					right_rotate(&temp);
				else{
					left_rotate(&(temp->left));
					right_rotate(&temp);
					
				}
			}
			else{
				if(previous==RIGHT_LEANING)
					left_rotate(&temp);
				else{
					right_rotate(&(temp->right));
					left_rotate(&temp);
					
				}
			}
		} //end if

		updateheight(temp);

		if(temp->parent==NULL)
			*rootptr = temp;

		temp =temp->parent;

	}while(temp!=NULL);
}

void insert_node(avl_node **rootptr, avl_node *temp){
	if(*rootptr==NULL) *rootptr = temp;
	else{
		temp->parent = *rootptr;

		if((*rootptr)->x < temp->x)
			insert_node(&((*rootptr)->right),temp);
		else
			insert_node(&((*rootptr)->left),temp);
	}
}

void insert_value(avl_node **rootptr, int x){
	avl_node *temp;
	temp = (avl_node *)malloc(sizeof(avl_node));
	temp->x = x;
	temp->height = 0;
	temp->parent = temp ->left = temp->right = NULL;
	insert_node(rootptr, temp);
	insert_fixup(rootptr, temp);
}

void view(avl_node *root, int tabs){
	int i;
	if(root != NULL){
		view(root->right, tabs +1);
		for(i=0; i<tabs; i++) printf("\t");
		printf("%2i\n", root->x);
		view(root->left, tabs +1);
	}
}

void swap(int *a, int *b){
	int temp;
	temp = *a; *a= *b; *b =temp;
}

void deleteFixup(avl_node** root, int x) {

}

void bstDelete(avl_node* root, int target) {
	// locate the node
	avl_node* temp = root;
	avl_node* parent;
	avl_node* child; // for second case with 2 interior nodes
	while ( temp->x != target && temp != NULL) {
		if ( temp->x > target) {
			temp = temp->left;
		} else if ( temp->x < target ) {
			temp = temp->right;
		}
	}

	if ( temp == NULL ) {
		printf("Target does not exist.\n");
		return;
	}

	// determine which of the 3 cases
	// case 1, leaf node
	if ( temp->left == NULL && temp->right == NULL) {
		parent = temp->parent;
		if (temp->x > parent->x) {
			parent->right = NULL;
		} else {
			parent->left = NULL;
		}
		insert_fixup(&root, temp);
		free(temp);
	} 
	// case 2, interior node
	else if ( temp->left != NULL && temp->right != NULL) {
		parent = temp->parent;
		child = temp->right;
		avl_node* min_right = child;

		for(min_right; min_right->left!=NULL; min_right=min_right->left) {

		}
		

		temp->x = min_right->x;

		
		if (min_right->parent->left == min_right) {
			min_right->parent->left = min_right->right;
		} else {
			min_right->parent->right = min_right->right;
		}

		if (min_right->right != NULL) {
			min_right->right->parent = min_right->parent;
		}
		insert_fixup(&root, min_right);
    	free(min_right);
	}
	// case 3, one child node
	else {
		parent = temp->parent;
		if (temp->x > parent->x) {
			parent->right = (temp->left==NULL? temp->right:temp->left);
		} else {
			parent->left = (temp->left==NULL? temp->right:temp->left);
		}
		insert_fixup(&root, temp);
		free(temp);
	}

	// delete accordingly
}

void deleteNode(avl_node* root, int target) {
	bstDelete(&root, target);
	

}

int main(){
	avl_node *root = NULL;
	int i,n=10;
	
	
	
	for(i=0; i<n; i++){
		insert_value(&root,i+1);
		view(root,0);
		printf("\n----------------------------------------\n");
	}
	
	

	insert_value(&root,0);	
	
	printf("\n----------------------------------------\n");
	
	deleteNode(&root, 1);
	view(root, 0);
}
