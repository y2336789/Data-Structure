/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


//void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
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
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			//printStack();
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

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	for(;;)
	{
		for(;node;node->left)
			push(node);
		node = pop();

		if(!node) break;	//node가 널이 아니면 밑에 두 줄 실

		printf("[ %d ] ", node->key);
		node = node->right;

	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if(ptr == NULL) return;
	enQueue(ptr);

	for(;;)
	{
		ptr = deQueue();
		if(ptr) {
			printf("[ %d ] ", ptr->key);
			if(ptr->left)
				enQueue(ptr);
			if(ptr->right)
				enQueue(ptr);
		}
		else break;
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* where = head->left;
	Node* parent = NULL;
	Node* location = NULL;
	int newkey, choice;

	while(where != NULL && where->key != key)
	{	//만약 where가 널이거나 key 값이 일치하면 반복문 탈출
		parent = where;
		if(parent->key > key)
		{	//반복문 내에서 들어올 값이 where의 key 값보다 작은 경우에는
			where = parent->left;	//where의 위치를 왼쪽으로 옮김
		}
		if(parent->key < key)
		{	//들어올 값이 큰 경우에는
			where = parent->right;	//where의 위치를 오른쪽으로 넘김
		}
	}
	if(where==NULL)	//where가 NULL이면
	{
		printf("찾고자 하는 key가 트리에 없습니다.\n");	//찾고자하는 key 값을 가진 노드가 없다는 의미
		return 0;
	}
	if(where->left == NULL && where->right == NULL)	//리프 노드를 삭제 할 때
	{
		if(parent-> right == where) //리프 노드가 부모 노드가 오른쪽을 가리키는 곳에 위치 했을 때
		{
			free(where); //where를 동적 할당 해제
			parent->right = NULL;	//부모의 오른쪽 자식은 null이 된다
			printf("%d 값을 가진 node를 삭제하였습니다.\n", key);
			return 1;
		}
		else
		{
			free(where);
			parent->left = NULL;	//반대 경우, 리프 노드가 부모의 왼쪽에 위치 할 경우
			printf("%d 값을 가진 node를 삭제하였습니다.\n", key);
			return 1;
		}
	}
	else if(where->left == NULL && where->right != NULL)
	{
		newkey = where->right->key;
		where->key = newkey;
		free(where->right);
		where->right = NULL;
		return 1;
	}
	else if(where->left != NULL && where->right == NULL)
	{
		newkey = where->left->key;
		where->key = newkey;
		free(where->left);
		where->left = NULL;
		return 1;
	}
	else if(where->left !=NULL && where->right !=NULL)
	{
		printf("자식 노드가 두 개 입니다. 방법 2개 중 한 개를 선택하시오.\n");
		printf("1. 왼쪽 트리에서 최댓 값을 찾기,  2. 오른쪽 트리에서 최소 값을 찾기 \n");
		scanf("%d", &choice);

		if(choice == 1)
		{
			location = where;
			while(where->right !=NULL){
				parent = where; where = where->right;
			}
			newkey = where->key;
			location->key = newkey;
			free(where);
			parent->right = NULL;
			return 1;
		}
		else if(choice == 2)
		{
			location = where;
			while(where->left != NULL){
				parent = where; where = where->left;
			}
			newkey = where->key;
			location->key = newkey;
			free(where);
			parent->left = NULL;
			return 1;
		}
	}


}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if(top == -1)
	{
		printf("Stack is empty \n");
		return NULL;
	}
	return stack[top--];

}

void push(Node* aNode)
{
	if(top >= MAX_STACK_SIZE -1)
	{
		printf("Error : stack is FULL \n");
		return;
	}
	stack[++top]= aNode;
}



Node* deQueue()
{
	if(front == rear)
	{
		printf("Queue is empty \n");
		return NULL;
	}
	return queue[++front];
}

void enQueue(Node* aNode)
{
	if(rear == MAX_QUEUE_SIZE-1)
	{
		printf("Queue is FULL\n");
		return;
	}
	queue[++rear] = aNode;
}




