/*
 * aaa.c
 *
 *  Created on: 2020. 5. 16.
 *      Author: y2j
 */
/*
 * binary-search-tree-1.c
 *
 *  Created on: 2020. 5. 15.
 *      Author: y2j
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr != NULL)
	{
		inorderTraversal(ptr->left);
		printf("%d ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr != NULL)
	{
		printf("%d ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr != NULL)
	{
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf("%d ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node* newone = (Node *)malloc(sizeof(Node));
	Node* location = head->left;
	Node* parent;
	newone->key = key;


	if(head->left == NULL)		//처음 실행할 떄에만 실행 된다
	{
		head->left = newone;
		newone->left = NULL;
		newone->right = NULL;
		return 1;
	}

	while(location != NULL)
	{
		if(location->key != key)
		{
			parent = location;
			if(location->key > key)
				location = location->left;
			else
				location = location->right;
		}
		else
			return 0;
	}
		newone->left = NULL;
		newone->right = NULL;
		if(key < parent->key)
			parent->left = newone;
		else parent->right = newone;
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	Node* where = head->left;
	Node* parent = NULL;

	while(where != NULL && where->key != key){
		if(where->key > key){
			parent = where;
			where = where->left;
		}
		if(where->key < key){
			parent = where;
			where = where->right;
		}
	}
	if(where == NULL)
	{
		printf("찾고자 하는 key가 트리에 없습니다.\n");
		return 0;
	}

	if(where->left == NULL && where->right == NULL)	//리프 노드 삭제 할 때
	{
		if(parent-> right == where) //리프 노드가 부모 노드가 오른 쪽을 가르키는 곳에 위치 했을 때
		{
			parent->right = NULL;
			printf("%d 값을 가진 node를 삭제하였습니다.\n", key);
			free(where);
			return 1;
		}
		else
		{
			parent->left = NULL;
			printf("%d 값을 가진 node를 삭제하였습니다.\n", key);
			free(where);
			return 1;
		}
	}


	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	Node* save = NULL;

	if(ptr != NULL && ptr->key != key)
	{
		if(ptr->key < key){
			save = searchRecursive(ptr->right, key);
			return save;
		}
		else
		{
			save = searchRecursive(ptr->left, key);
			return save;
		}
	}
	if(ptr->key == key)
		return ptr;
}

Node* searchIterative(Node* head, int key)
{
	Node * where = head->left;
	while(where->key != key)
	{
		if(where->key < key)
		{
			where = where->right;
		}
		else
			where = where->left;
	}
	return where;
}


int freeBST(Node* head)
{
	Node* location = head->left;
	if(head == NULL)
	{
		postorderfree(location->left);
		postorderfree(location->right);
	}
	free(head);
	return 1;
}

int postorderfree(Node* ptr)
{
	if(ptr != NULL)
	{
		postorderfree(ptr->left);
		postorderfree(ptr->right);
		free(ptr);
	}
	return 1;
}







