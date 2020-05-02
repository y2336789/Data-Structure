/*
 * doubly-linked-list.c
 *
 *  Created on: 2020. 5. 1.
 *      Author: y2j
 */

#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);	//동적할당된 함수를 해제하는 함수

int insertNode(headNode* h, int key);	// 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertLast(headNode* h, int key);	//리스트의 마지막 위치에 접근하여 노드를 추가한다. 이는 값의 비교가 딱히 필요없다.
int insertFirst(headNode* h, int key);	//처음 노드의 위치에 새로운 노드를 추가 한다
int deleteNode(headNode* h, int key);	//list에서 key에 대한 노드 삭제
int deleteLast(headNode* h);	//리스트에 저장된 마지막 노드를 삭제 한다
int deleteFirst(headNode* h);	//리스트의 처음 노드 삭제
int invertList(headNode* h);	//리스트의 링크를 역순으로 재 배치
void printList(headNode* h);	//리스트에 저장된 노드 값을 출력하는 프로그램


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("----- 2017038068 양영재 -----\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {	//헤더노드를 동적할당한다. 이 함수에서 매개변수는 더블 포인터 형이다.

	if(*h != NULL)	//만약 *h = 주소꼴, 즉 누군가를 이미 가르키고 있는 상황이면
		freeList(*h);	//그에 대해서 동적할당을 해제한다.
	headNode* p = (headNode *)malloc(sizeof(headNode));
	p->first = NULL; //헤더노드의 포인터 p가 가르키는 값을 NULL로 한다. 아직 가르키는 노드가 없다는 의미
	*h = p;	//p는 주소,  h가 이중 포인터이니 *h도 주소,

	return 1;
}

int freeList(headNode* h){	//동적할당된 함수를 해제하는 함수
	listNode* lead = h->first;	//각각의 노드들에 접근할 포인터 lead, lead는 마지막 노드까지 순차적으로 이동한다.
	listNode* prev;	//lead의 전 위치를 가르킬 포인터

	while(lead != NULL)
	{
		prev = lead;	//prev를 lead의 위치와 같게 한 후
		lead = lead->rlink;	//lead의 위치를 한 칸 옮긴다
		free(prev);	//prev의 위치에 있는 노드에 대해 동적할당을 해제한다.
	}
	free(h); //연결된 리스트 상에서 노드를 전부 동적할당 해주면 헤더노드 h에 대해서도 동적할당 해제를 해준다.
	return 0;
}


void printList(headNode* h) {	//리스트에 저장된 노드 값을 출력하는 프로그램
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");	//h가 NULL이면 출력 할 게 없다
		return;
	}

	p = h->first;	//h->first가 가르키는 노드의 위치를 포인터 p가 가르키게 한다

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);	//리스트에 접근해서 값을 출력하고
		p = p->rlink;	//p의 위치를 한 칸 옮긴다
		i++;	//몇번째 노드인지를 알려주는 i
	}

	printf("  items = %d\n", i);	//해당 노드의 위치에 접근해서 그 위치에 저장된 값을 출력하는 함수
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {	//리스트의 마지막 위치에 접근하여 노드를 추가한다. 이는 값의 비교가 딱히 필요없다.
	listNode* next = h->first;	//모든 노드의 위치에 접근할 포인터 next
	listNode* last = (listNode *)malloc(sizeof(listNode));	//리스트의 마지막에 삽입할 새로 추가할 동적할당된 노드이다.
	last->key = key;

	while(next->rlink != NULL)	//현재 next가 가르키는 노드가 NULL이 아니면
	{
		next = next->rlink;	//next를 다음 칸으로 옮긴다
	}	//while문을 벗어나는 경우 -> 마지막에 도달한 경우
	next->rlink = last;	//next, 즉 마지막의 위치 다음에 노드가 추가되니 next의 오른 링크가 last를 가르키게 하고
	last->llink = next;	//last의 왼쪽 링크는 next를 가르킨다
	last->rlink = NULL;	//마지막으로 last의 오른 링크는 아무 것도 없으니 NULL을 가르키게 한다
	return 0;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {	//리스트에 저장된 마지막 노드를 삭제 한다
	listNode * next = h->first;
	if(h->first == NULL){	//리스트 내에 노드가 없을 경우
		printf("삭제할 값이 없습니다.\n");	//삭제할 값이 없다고 출력
		return 0;
	}
	while(next->rlink != NULL)	//next가 가르키는 노드가 NULL이 아닌경우!
	{
		next = next->rlink;	//next의 위치를 한 칸 옮김
	}
	if(next == h->first)	//삭제할 마지막 값이 노드의 처음 노드일 경우(즉, 리스트에 처음 노드 밖에 없는 경우)
	{
		h->first = NULL;	//원래 h->first가 처음 노드를 가르키고 있었으나 이것을 NULL로 바꿔주고
		free(next);	//처음 노드인 next를 해제해준다
	}
	else
		(next->llink)->rlink = NULL;	//노드의 마지막인 경우이다
	free(next);

	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {	//처음 노드의 위치에 새로운 노드를 추가 한다
	listNode * next = h->first;
	listNode * fir = (listNode *)malloc(sizeof(listNode));	//처음 노드 위치에 새로 추가될 동적할당 된 노드
	fir->key = key;

	fir->rlink = next;	//값에 상관없이 새로 추가되는 노드는 처음 노드 위치에 들어가게 된다.
	h->first = fir;	//fir의 오른 링크가 next를 가르키게 하고, h->first가 fir를 가르키게 한다
	next->llink = fir;	//이중 연결 리스트이기 때문에 원래 위치했던 처음 노드의 왼쪽 링크가 fir를 가르키게 한다

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {	//리스트의 처음 노드 삭제
	listNode * next = h->first;
	if(h->first == NULL)	//리스트 내에 삭제할 노드가 없는 경우
	{
		printf("삭제할 값이 없습니다.\n");
		return 0;
	}
	if(next->rlink == NULL)	//지금 현재 리스트내에 입력된 노드가 처음 노드 하나 밖에 없는 경우
	{
		free(next);	//next에 대한 동적 할당을 해제 하고
		h->first = NULL;	//h->first가 널을 가르키게 한다
		return 0;
	} //처음 노드 외에도 값이 있는 경우에는
	h->first = next->rlink;	//처음 노드가 가르키는 노드를 h->first가 가르키게 하고
	(next->rlink)->llink = NULL;	//처음 노드가 가르키던 다음 노드의 왼쪽 노드는 null을 가르키게 한다.
	next->rlink = NULL;
	free(next);


	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* next = h->first;
	listNode* middle = NULL;
	listNode* back;

	while(next != NULL)
	{		//single linked list와 유사한 방법을 사용해서 역순으로 만든다
		back = middle;
		middle = next;
		next = next->rlink;
		middle->llink = next;	//뒤집었을때 single linked list는 하나의 연결만 생각하면 되나
		middle->rlink = back;	//뒤집은 리스트 자체도 이중 연결 리스트 이기 때문에 llink와 rlink를 그에 맞게 설정해 주어야 한다
	}
	h->first = middle;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {	//리스트를 오름차순으로 정렬한다
	listNode * lead = h->first;
	listNode * newone = (listNode *)malloc(sizeof(listNode));
	newone->key = key;	//newone에 저장될 key 값 저장
	newone->llink = NULL;	//왼쪽 링크는 현재 아무것도 가르키지 않는다
	newone->rlink = NULL;	//오른 링크도 현재 아무것도 가르키지 않는다

	if(h->first == NULL)	//현재 리스트에 입력된 노드가 하나도 없을 시에
	{
		h->first = newone;	//h->first가 newone을 가르키게 한다
		newone->rlink = NULL;	//새로 추가된 처음 노드 newone의 오른 링크는 NULL을 가르킴
		return 0;
	}
	//입력된 노드가 딱 한 개 있을 시에 실행되는 if문
	if(lead->rlink == NULL)	//
	{
		if(lead->key >= key)	//여기에서는 lead->rlink == NULL이다. 입력될 노드의 값이 처음 노드의 값 이하 일 경우
		{
			newone->rlink = h->first;	//newone의 오른 링크는 h->first가 가르키는 곳과 같은 곳을 가르킴
			lead->llink = newone; //처음 노드의 왼쪽 링크는 newone을 가르킴
			h->first = newone;	//처음 노드가 newone이 되는 경우이다
			return 0;
		}
		else //node에 저장된 key 값보다 저장될 값이 더 큰 경우		(가장 작은 값이 입력될 때는 입력이 잘 이루어지나, 값 사이에 입력이 이루어지면 있었던 값이 다 사라짐)
		{
			lead->rlink = newone;	//그 노드의 다음 위치에 삽입되야 하니, lead의 오른 링크는 newone을 가르킨다
			newone->llink = lead;	//newone 노드가 lead 노드 뒤에 위치하니 newone 노드의 왼쪽 링크는 lead를 가르킨다
			newone->rlink = NULL;	//newone 다음에는 아무 노드도 없으니 오른 링크는 NULL을 가르키게 한다
			return 0;
		}
	}	//만약 lead 노드가 가르키는 노드가 있을 시에
	while(lead->rlink != NULL)	//저장된 노드의 개수가 2개 이상일 때 while문을 돌게 된다.
	{
		if(lead->key < key)	//lead의 위치에 저장된 key값과 비교해서 값이 클 경우에는
			lead = lead->rlink;	//lead의 위치를 한 칸 옮겨서 비교를 실시한다
		else if(lead->key >= key)	//만약 lead에 저장된 key값 이하일 경우
		{	//두 가지 경우로 나뉘게 되는데 그 중 첫 번 째는 lead의 위치가 h->first가 가르키는 위치 일 때
			if(lead == h->first)
			{
				newone->rlink = lead;	//처음 노드 전에 위치하게 된다. newone의 오른 링크가 lead(처음 노드)를 가르키고
				lead->llink = newone;	//lead의 왼쪽 노드는 newone을 가르킨다
				h->first = newone;	//처음 노드가 newone이 되었으니 h->first는 newone을 가르키게 된다
				return 0;
			}	//만약에 비교할 lead의 위치가 처음 노드가 아닐 경우 실행된다
			newone->rlink = lead;	//newone의 오른 링크는 lead를 가르키고
			newone->llink = lead->llink;	//newone의 왼쪽 링크는 lead의 왼쪽 링크가 가르키던 곳을 가르키게 되고
			(lead->llink)->rlink = newone;	//lead의 전에 있던 노드의 오른 링크는 newone을 가르키게 된다
			lead->llink = newone;	//마지막으로 lead의 왼쪽 링크는 newone을 가르킨다
			return 0;
		}
	}
	if(lead->key >= key)	//마지막 노드까지 왔을 경우 중에서 저장되있는 값 이하의 값이 들어올 때
	{
		newone->rlink = lead;	//newone 노드가 마지막 노드 전에 위치하게 되니 newone의 오른 링크가 lead를 가르키고
		newone->llink = lead->llink;	//newone의 왼쪽 노드는 lead의 왼쪽 노드가 가르키는 위치를 가르키게 된다
		(lead->llink)->rlink = newone;	//lead의 전에 있던 노드의 입장에서는 노드가 뒤에 하나 추가되는 것이니 그 오른 링크는 newone을 가르키고
		lead->llink = newone;	//마지막으로 lead의 왼쪽 링크 newone을 가르키게 된다
		return 0;
	}
	else	//마지막 노드 까지 왔는데 마지막 노드의 key값보다 입력될 값이 더 큰 경우
	{
		lead->rlink = newone; //마지막 노드가 neweone이 되니 lead의 오른 링크가 newone을 가르키게 되고
		newone->llink = lead;	//newone의 왼쪽 노드는 lead를 가르키게 된다
		newone->rlink = NULL;	//newone의 다음에 위치하는 것은 아무것도 없으니 오른 링크는 NULL을 가르키게 한다
		return 0;
	}

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {//리스트에서 입력한 key값이 저장되어 있으면 그 노드를 삭제한다
	listNode * lead = h->first;

	if(lead->key == key)	//처음 노드가 삭제할 노드일 경우
	{
		deleteFirst(h);	//deleteFirst 함수 호출해서 삭제하였음
		return 0;
	}
	while(lead != NULL && lead->rlink != NULL) //리드가 널이 아니고, 리드의 다음 노드가 널이 아닐때
	{
		if(lead->key == key) //만약 한 칸 앞으로 옮긴 위치의 key 값과 일치 할 경우
		{
			(lead->llink)->rlink = lead->rlink;	//삭제할 lead의 전에 위치한 노드의 오른 링크가 삭제할 lead의 다음에 있는 노드를 가르키고
			(lead->rlink)->llink = lead->llink;	//삭제할 lead의 다음에 있는 노드의 왼쪽 링크는 삭제할 lead의 전에 있는 노드를 가르키고
			free(lead);	//lead를 삭제한다
			return 0;
		}
		lead = lead->rlink;	//삭제를 하거나, 만약 해당 lead의 key값과 일치하지 않으면 lead의 위치를 옮긴다
	}
	if(lead->key == key)	//리드의 마지막 노드의 위치까지 와서 검색하는 경우, key 값이 같으면
	{
		(lead->llink)->rlink = NULL;	//마지막 노드의 전에 있던 링크의 오른 링크는 NULL을 가르키고
		free(lead);	//lead의 동적 할당을 해제 한다
		return 0;
	}
	else	// key값이 리스트에 없을 경우
		printf("삭제 할 값을 찾을 수 없습니다.\n");

	return 1;
}
