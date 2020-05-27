/*
 * binary-search-tree-2.c
 *
 *  Created on: 2020. 5. 24.
 *      Author: young
 */
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
		printf("\n");
		printf("------------------------- 2017038068 양영재 -------------------------");
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
		printf("[%d] ", ptr->key);
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
		for(;node;node = node->left)	//노드가 널이 아니면, 왼쪽 자식 노드로 반복한다. 노드의 위치를 바꿈.
			push(node); //반복문에서의 node를 스택에 push한다
		node = pop();	//노드가 널이면 스택에 저장된 값을 pop한다. node의 위치는 pop을 통해서 바뀐다.

		if(!node) break;	//node가 널이 아니면 밑에 두 줄 실행

		printf("[%d] ", node->key);	//노드의 key값을 출력한다
		node = node->right;	//노드의 위치를 오른 자식 노드로 바꾼다.
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)	//레벨 순서 순회
{
	if(ptr == NULL) return;	//ptr이 널이면 함수 종료
	enQueue(ptr);		//널이 아니면 원형 큐에 ptr을 집어 넣는다

	for(;;)
	{
		ptr = deQueue(); //우선 큐에 있는 값을 디큐한다.
		if(ptr) {	//ptr 이 널이 아니면
			printf("[%d] ", ptr->key);	//ptr의 key값을 출력한다
			if(ptr->left)	//ptr의 왼쪽을 가리키는 노드가 널이 아니면, 즉 다음 레벨에 노드가 있으면
				enQueue(ptr->left);	//가리키는 왼쪽의 노드를 인큐한다.
			if(ptr->right)	//ptr의 오른쪽을 가리키는 노드가 널이 아니면
				enQueue(ptr->right);	//가리키는 오른쪽의 노드를 인큐한다.
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

	if (head->left == NULL) {	//값을 처음 집어 넣는 경우
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
		if(parent-> right == where) //리프 노드가 부모 노드의 오른쪽에 위치 했을 때
		{
			free(where); //where를 동적 할당 해제
			parent->right = NULL;	//부모의 오른쪽 자식은 null이 된다
			printf("%d 값을 가진 node를 삭제하였습니다.\n", key);
			return 1;
		}
		else	//리프 노드가 부모 노드의 왼쪽의 위치 할 때
		{
			free(where);
			parent->left = NULL;	//부모의 왼쪽 자식은 null이 된다
			printf("%d 값을 가진 node를 삭제하였습니다.\n", key);
			return 1;
		}
	}
	else if(where->left == NULL && where->right != NULL)	//만약 한 쪽에만 자식 노드가 있는경우
	{	//그 중에서도 오른쪽 자식만 있는 경우
		newkey = where->right->key;	//옮겨줄 key의 값을 newkey에 저장
		where->key = newkey;	//where의 key를 newkey로 바꾼다.
		free(where->right); //where의 오른 자식을 삭제한다.
		where->right = NULL;//where의 오른쪽은 비어있다
		return 1;
	}
	else if(where->left != NULL && where->right == NULL)	//왼쪽에만 자식이 있는 경우
	{
		newkey = where->left->key; //위의 경우에서 오른쪽이 왼쪽으로만 바뀌고 나머지는 동일하다.
		where->key = newkey;
		free(where->left);
		where->left = NULL;
		return 1;
	}
	else if(where->left !=NULL && where->right !=NULL)	//만약 삭제할 노드가 두 개의 자식노드를 가질 경우
	{
		/*printf("자식 노드가 두 개 입니다. 방법 2개 중 한 개를 선택하시오.\n");
		printf("1. 왼쪽 트리에서 최댓 값을 찾기,  2. 오른쪽 트리에서 최소 값을 찾기 \n");
		scanf("%d", &choice);

		if(choice == 1)
		{*/
			location = where;	//where의 위치의 key값이 바뀔 테니까 위치를 기억해준다,
			where = where->left; //우선 왼쪽에서 최댓값을 찾는 경우로 할 것이니 where의 위치를 왼쪽으로 이동
			while(where->right !=NULL){	//만약 where의 오른 자식이 널이 아니면, 즉 더 큰 값이 있는 경우
				parent = where;	where = where->right;	//where의 위치와 parent의 위치를 옮겨준다.
			}
			newkey = where->key;	//반복문을 다 돌면 최대값에 도달 했을 때이다. 최댓값의 key값을 newkey에 저장
			location->key = newkey;	//location의 key 값을 수정한다.
			if(location->left == where)	//만약 최댓값이 바로 location의 왼쪽에 위치하면서
			{
				if(where->left == NULL && where->right == NULL){	//그 where의 자식이 둘다 없는 경우
					free(where); //동적 할당 해제
					location->left = NULL;	//location의 왼쪽은 널이다.
					return 1;
				}
				else	//만약에 자식이 있는 경우
				{
					location->left = where->left;	//where가 최댓값이니 있어도 왼쪽 자식밖에없다
					free(where);	//where를 동적 할당 하기전에 where의 왼쪽 자식을 location의 왼쪽이 가리키게 한다.
					return 1;
				}
			}
			else	//location의 왼쪽값이 최대값이 아닌경우
			{
				if(where->left == NULL && where->right == NULL)	//만약에 최댓값을 찾았는데 그 경우가 리프노드일 경우
				{
					free(where);	//key값은 위에서 바꿔 줬으니 where를 free해주고ㅓ
					parent->right = NULL;	//부모의 오른 노드를 NULL로 바꾼다
					return 1;
				}
				else //왼쪽 노드가 있다면
				{
					where->key = where->left->key; //where의 왼쪽 자식의 key값을 where의 key에 저장한다
					free(where->left);	//where의 왼쪽 자식 노드를 동적해제
					where->left = NULL;	//where의 left를 NULL로 바꿔준다.
					return 1;
				}
			}
		/*}		//오른쪽에서 가장 작은 노드 값을 가지는 코드, 둘 중 하나만 구현하게 했으니 주석처리 하였음
		else if(choice == 2)
		{
			location = where;
			where = where->right;
			while(where->left != NULL){
				parent = where; where = where->left;
			}
			newkey = where->key;
			location->key = newkey;
			if(location->right == where)
			{
				if(where->left == NULL && where->right == NULL){
					free(where);
					location->right = NULL;
					return 1;
				}
				else
				{
					location->right = where->right;
					free(where);
					return 1;
				}
			}
			else
			{
				if(where->left == NULL && where->right == NULL)
				{
					free(where);
					parent->left = NULL;
					return 1;
				}
				else //오른쪽 노드가 있다면
				{
					where->key = where->right->key;
					free(where->right);
					where->right = NULL;
					return 1;
				}
			}
		}*/
	}

	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) { //ptr이 널이 아니면
		freeNode(ptr->left);		//왼쪽 자식과 오른쪽 자식에 대해서 재귀함수를 호출해서 동적할당 해제
		freeNode(ptr->right);
		free(ptr);	//그 후에 ptr 해제
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
	if(top == -1)	//만약에 top이 -1이면
	{
		return NULL;	//비어있는 상황이기 때문에 pop이 불가능하다
	}
	return stack[top--];	//한 개를 pop했기에 top을 하나 줄인다

}

void push(Node* aNode)
{
	if(top >= MAX_STACK_SIZE -1)	//top이 19 이상이면 스택이 꽉찬 것이다
	{
		printf("Error : stack is FULL \n");
		return;
	}
	stack[++top]= aNode;	//stack에 저장한다. 꽉차지 않앗으면, top 증가
}

Node* deQueue()
{
	if(front == rear)	//이 두개가 같다면, 원형 큐에서 큐가 빈 것이다
	{
		return NULL;
	}
	front = (front+1) % MAX_QUEUE_SIZE;	//원형 큐는 한 개를 비어놓으니 +1한 값에서 큐의 크기만큼 나눠주고
	return queue[front];	//front의 위치에 있는 값을 리턴해준다
}

void enQueue(Node* aNode)
{
	if((rear+1) % MAX_QUEUE_SIZE == front)	//rear 다음이 front이면 큐는 꽉 찼다.
	{
		printf("Queue is FULL\n");
		return;
	}
	rear = (rear+1) % MAX_QUEUE_SIZE;	//리어의 위치를 한 칸 옮기고 그것을 큐의 크기만큼 나눠준다
	queue[rear] = aNode;	//rear의 위치에 값을 넣어준다.
}
