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
		printf("\n");
		printf("=====================    양영재   2017038068 =======================\n");
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
		inorderTraversal(ptr->left); //왼쪽 자식 노드가 없을 때까지 왼쪽으로 이동한다
		printf("%d ", ptr->key);		//해당 ptr의 key값을 출력한다
		inorderTraversal(ptr->right);	//후에 오른쪽 자식 노드를 탐색한다. 오른쪽 자식 노드가 없을 때 까지
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr != NULL)
	{
		printf("%d ", ptr->key);	//먼저 해당 ptr의 key값을 출력한다
		preorderTraversal(ptr->left);	//왼쪽 자식 노드가 없을 때까지 왼쪽으로 이동하여 탐색한다.
		preorderTraversal(ptr->right);	//오른쪽 자식 노드가 없을 때까지 오른쪽으로 이동하여 탐색한다.
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr != NULL)
	{
		postorderTraversal(ptr->left);	//왼쪽 자식 노드가 없을 때까지 왼쪽으로 이동하여 탐색한다.
		postorderTraversal(ptr->right);	//오른쪽 자식 노드가 없을 때까지 오른쪽으로 이동하여 탐색한다.
		printf("%d ", ptr->key);			//해당 ptr의 key 값을 출력한다.
	}
}


int insert(Node* head, int key)
{
	Node* newone = (Node *)malloc(sizeof(Node));	//새로 추가할 노드인 newone, 동적 할당으로 받았다
	Node* location = head->left;
	Node* parent;
	newone->key = key;


	if(head->left == NULL)		//처음 실행할 때에만 실행 된다
	{
		head->left = newone;	//헤드 노드의 왼쪽 포인터가 newone을 가리키게 한다
		newone->left = NULL;	//newone의 왼쪽 포인터와 오른쪽 포인터는 가리키는게 없으니 NULL을 가리키게 한다
		newone->right = NULL;
		return 1;
	}

	while(location != NULL)	//만약 location이 널이 아니라면
	{
		if(location->key != key)	//location의 key 값과 비교, 값이 다르다면
		{
			parent = location;		//다를 시에 부모가 현재 location과 같은 위치에 위치한다
			if(location->key > key)	//location의 값이 입력될 값보다 더 크다면
				location = location->left; //location의 위치를 원래 위치의 노드에서 왼쪽 포인터가 가리키는 노드로 옮긴다
			else
				location = location->right;	//반대 경우에는 오른쪽으로 옮긴다
		}
		else	//만약 들어올 값이 이미 있는 값이라면
			return 0;	//바로 종료, 값의 추가가 이뤄지지 않는다
	}
		newone->left = NULL;	//location이 NULL이라면 아래 문장들을 실행
		newone->right = NULL;
		if(key < parent->key)	//만약 부모의 키 값보다 값이 작으면
			parent->left = newone;	//부모의 왼쪽 자식 노드에 newone이 위치
		else parent->right = newone; //반대 경우에는 오른쪽 자식 노드에 newone이 위치
	return 1;
}

int deleteLeafNode(Node* head, int key)	//리프 노드를 삭제하는 함수
{
	Node* where = head->left;
	Node* parent = NULL;

	while(where != NULL && where->key != key){	//만약 where가 널이거나 key 값이 일치하면 반복문 탈출
		if(where->key > key){	//반복문 내에서 들어올 값이 where의 key 값보다 작은 경우에는
			parent = where;		//부모가 원래 위치 기억
			where = where->left;	//where의 위치를 왼쪽으로 옮김
		}
		if(where->key < key){	//들어올 값이 큰 경우에는
			parent = where;
			where = where->right;	//where의 위치를 오른쪽으로 넘김
		}
	}
	if(where == NULL)	//where가 NULL이면
	{
		printf("찾고자 하는 key가 트리에 없습니다.\n");	//찾고자하는 key 값을 가진 노드가 없다는 의미
		return 0;
	}

	if(where->left == NULL && where->right == NULL)	//리프 노드를 삭제 할 때
	{
		if(parent-> right == where) //리프 노드가 부모 노드가 오른쪽을 가리키는 곳에 위치 했을 때
		{
			parent->right = NULL;	//부모의 오른쪽 자식은 null이 된다
			printf("%d 값을 가진 node를 삭제하였습니다.\n", key);
			free(where); //where를 동적 할당 해제
			return 1;
		}
		else
		{
			parent->left = NULL;	//반대 경우, 리프 노드가 부모의 왼쪽에 위치 할 경우
			printf("%d 값을 가진 node를 삭제하였습니다.\n", key);
			free(where);
			return 1;
		}
	}


	return 1;
}

Node* searchRecursive(Node* ptr, int key)	//재귀 방식으로 위치를 찾는 함수
{
	Node* save = NULL;

	if(ptr != NULL && ptr->key != key)	//ptr이 null이 아니고, key 값이 일치하지 않는 경우
	{
		if(ptr->key < key){ //위 경우에서 ptr의 값보다 key 값이 클 경우
			save = searchRecursive(ptr->right, key); //ptr의 위치를 오른쪽으로 옮겨서 재귀 함수 실행
			return save;	//호출된 재귀 함수가 끝나면 최종적으로 위치를 반환해줄 save
		}
		else	//반대 경우
		{
			save = searchRecursive(ptr->left, key);	//ptr의 위치를 왼쪽을 옮겨서 재귀 실행
			return save;
		}
	}
	if(ptr->key == key)	//만약 여러 번의 재귀 끝에 key 값이 일치하는 곳을 찾으면
		return ptr; 	//ptr을 return하게 하고, 재귀 함수 내에서 ptr의 값이 save로 계속 옮겨지게 된다

}

Node* searchIterative(Node* head, int key)	//반복적으로 위치를 찾는 함수
{
	Node * where = head->left;
	while(where->key != key)	//where의 값과 일치하지 않으면
	{
		if(where->key < key)	//where의 값과 대소를 비교한다
		{
			where = where->right;	//클 경우 where의 위치를 오른쪽으로 옮긴다
		}
		else
			where = where->left;	//반대 경우 왼쪽으로 옮긴다
	}
	return where; //반복해서 찾은 위치 where를 반환해준다.
}


int freeBST(Node* head)
{
	Node* location = head->left;
	if(head != NULL)
	{
		postorderfree(location->left);	//location의 왼쪽에 있는 노드들을 재귀적으로 전부 동적 할당 해제
		postorderfree(location->right);	// 오른 노드들도 전부 해제
	}
	free(head);	//그 후 head도 해제시킨다
	return 1;
}

int postorderfree(Node* ptr)	//재귀적으로 접근해 동적할당된 노드들을 해제
{
	if(ptr != NULL)	//ptr이 null이 아닐 경우
	{
		postorderfree(ptr->left); //ptr의 왼쪽 자식노드로 재귀 함수 실행
		postorderfree(ptr->right); //오른쪽 자식노드로 재귀 함수 실행
		free(ptr);	//마지막으로 free
	}
	return 1;
}



