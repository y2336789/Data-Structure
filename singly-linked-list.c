/*
 * singly-linked-list.c
 *
 *  Created on: 2020. 4. 24.
 *      Author: young
 */

#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;	//listNode 구조체에는 정수 값을 저장할 key와 동일한 구조체를 가르키는 포인터 link가 있다.
} listNode;

typedef struct Head {
	struct Node* first;	//headNode 구조체에는 listNode를 가르키는 포인터가 있다
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);	//헤더노드를 동적할당하는데, 이미 되어있으면 초기화
int freeList(headNode* h);	//동적할당된 헤더노드를 free해주는 함수

int insertFirst(headNode* h, int key);	// 처음 노드위치에 노드를 삽입하는 함수
int insertNode(headNode* h, int key);	// 스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입하는 함수
int insertLast(headNode* h, int key);	//마지막 노드 뒤에 노드를 삽입하는 함수

int deleteFirst(headNode* h);	//처음 노드를 삭제하는 함수
int deleteNode(headNode* h, int key);	//삭제하고자 하는 key값을 가진 노드를 찾은 뒤 삭제하는 함수
int deleteLast(headNode* h);	//마지막 노드를 삭제하는 함수
int invertList(headNode* h);	//노드를 역순으로 출력하는 함수

void printList(headNode* h);	//연결 리스트를 출력하는 함수

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("========== 양영재 2017038068 ==========\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {	//각각의 노드의 위치에 접근해서
		prev = p;	//삭제하고자 하는 노드의 전 노드의 위치를 잡은 후에
		p = p->link;	//p를 위치를 옮긴다. 즉 이 위치가 삭제하고자 하는 노드의 위치이다
		free(prev);	//노드 삭제
	}
	free(h);	//반복문을 다 돌려서 노드들을 전부 삭제했으면 헤더노드도 해제한다.
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//추가 할 노드를 동적 할당해서 생성
	node->key = key;	//노드의 key값에 받아들인 값을 저장

	node->link = h->first;	//노드가 h->first가 가르키는 곳을 가르키고
	h->first = node;	//h->first는 노드를 가르킨다.

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key)
{
	listNode* newone = (listNode*)malloc(sizeof(listNode));		//새로 입력할 노드
	listNode* next = h->first;		//처음 노드의 위치를 next라 한다
	listNode* pre;	//next 전의 노드의 위치를 pre라 한다
	newone->key = key;	//받은 key값을 newone에 저장한다
	if(h->first == NULL){	//노드가 하나도 입력되지 않은 경우
		newone->link = NULL;	//insertFirst 함수와 동일하게 첫 노드를 추가한다.
		h->first = newone;
		return 0;
	}
	if(next->key >= key){	//처음 노드가 이미 있을 시에 비교를 하는데, 처음 노드의 key값이 더 크거나 같은 경우
		newone->link = h->first;	//처음 노드의 전에 삽입할 노드를 배치 시킨다.
		h->first = newone;
		return 0;
		}	//삽입할 노드의 key 값이 큰 경우는

	while(next->link != NULL && next->key < key)	//next에 저장된 값이 key보다 작으면,
	{
		pre = next;	//우선 전의 위치를 알 필요가 있으니 pre를 사용
		next = next->link;	//next의 위치를 한 칸 앞으로 옮긴다.
		if(next->key >= key)	//다음에 위치한 노드의 key값 보다 작으면 그 노드 위치의 전에 배치시킨다.
		{
			newone->link = pre->link;
			pre->link = newone;
			return 0;
		} //아니면 반복문
	} //만약에 next가 가르키는 곳이 NULL이면 반복문 탈출
	if(next->key < key){	//이제 마지막 노드까지 갔을때 두 가지 경우에 대해서 생각해야함
		newone->link = NULL;	//탈출 한 경우는 마지막의 노드까지 갔는데, 마지막 노드의 key값 보다도 큰 경우이다
		next->link = newone;	//마지막 노드 뒤에 노드를 추가
	}
	if(next->key >= key){	//마지막 노드의 값보다 작거나 같을 경우에는
		newone->link = pre->link;	//전의 위치인 pre를 이용해서 마지막 노드 전에 배치시킨다.
		pre->link=newone;
	}
	return 0;
}

/*
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {		//마지막 노드 뒤에 노드를 추가하는 함수
	listNode * new = (listNode *)malloc(sizeof(listNode));	//추가할 노드를 동적할당 받고있다.
	listNode * next = h->first;	//각각의 노드 위치에 접근할 위치 next 선언
	new->key = key;	//동적할당 받은 노드에 key 값을 저장

	while(next->link !=NULL){	//마지막 노드까지 접근하는 과정
		next = next->link;
	}
	new->link = NULL;	//마지막 노드에 접근 했을 경우	마지막 노드 뒤에 노드 추가
	next->link = new;
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {	//처음 노드를 삭제하는 함수
	listNode * Fst;	//삭제할 노드, 즉 처음 노드를 가르킬 포인터
	Fst= h->first;	//Fst가 처음 노드를 가르키게 한다
	h->first = Fst->link;	//바로 Fst를 삭제하면 끊어지기 때문에 h->first를 처음 노드가 가르키던 곳을 가르키게한다
	free(Fst);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {	//값을 입력받아서 그 값을 가지고 있는 노드를 삭제
	listNode * next;	//각각의 노드 위치를 가르킬 next
	listNode * temp;	//삭제할 노드 위치를 가르킬 temp
	listNode * prev;	//next의 전 위치를 가르킬 prev

	next = h->first;	//next는 처음 노드부터 시작한다
	if(h->first->key == key)	//처음 노드가 만약 삭제할 값을 가지고 있다면
	{
		temp = h->first;	//temp로 그 위치를 잡아준 뒤
		h->first= h->first->link;	//처음 노드가 가르키고 있는 노드를 h->first가 가르키게 한다
		free(temp);	//temp 삭제
		return 0;	//함수 종료
	}
	else	//처음 노드랑 값이 다르다면
	{
		prev=next;	//prev 위치 선정
		next=next->link;	//next를 한 칸 앞으로 옮김, prev는 next의 한 칸 뒤에 있다
		while(next->link != NULL)	//next가 가르키는게 NULL이 아닌 이상 반복
		{
			if(next->key == key)	//next의 값이 key값과 같은 경우
			{
				temp = next;	//temp 위치 선정
				next = next->link;	//next의 위치를 한 칸 옮김
				prev->link = next;	//prev는 옮긴 next를 가르킴
				free(temp);	//temp삭제
				return 0;	//삭제했으니 종료
			}
			prev = next;	//아닌 경우 prev와 next의 위치를 옮긴다
			next = next->link;
		}
		if(next->key == key)	//NULL 일 때, 즉 마지막까지 가서 노드를 삭제 할 때
		{
			prev->link = next->link;	//마지막 노드의 전 노드가 NULL을 가르키게 한 후
			temp = next;	//temp의 위치를 잡아준다
			free(temp);	//temp 삭제
		}
	}
	printf("can not find the node for key = %d\n", key);	//NULL까지 갓는데 삭제 할 값이 없는경우 출력
	return 0;
}

/*
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {	//마지막 노드를 삭제하는 함수
	listNode* next=h->first;	//각각의 노드의 위치에 접근할 next
	listNode* prev;	//next 전에 위치를 가르킬 prev
	while(next->link != NULL)	//마지막 노드 까지 쭉 이동한다
	{
		prev = next;
		next = next->link;
	}
	free(next);	//마지막 노드에 도달 하면 next를 삭제
	prev->link = NULL;
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode * middle;//middle에 위치한 노드는 trail이 가르키고 있는 노드를 가르키게 되서 역순으로 만들어준다
	listNode * trail;	//middle 앞에 위치한다
	listNode * next;	//모든 노드에 접근할 next

	middle = NULL; //middle은 처음에 널을 가르킨다. 처음 노드부터 가르키는 것을 역순으로 해야하기 때문
	next = h->first;	//next는 처음 노드부터 시작한다
	while(next)
	{
		trail = middle;	//trail은 middle의 위치와 같아진다
		middle = next;		//middle의 위치는 next와 같아지고
		next = next->link;	//next는 한 칸 뒤로 옮겨진다
		middle->link = trail;	//그리고 middle에 위치한 노드는 trail, 즉 전에 위치한 노드를 가르키게 된다.
	}
	h->first=middle;	//반복문이 끝나면 next가 널이기 때문에 값이 있는 노드의 마지막 위치는 middle이다. 역순으로 정렬된 연결 리스트의 middle을 가르키게 한다.

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");	//헤더노드가 널을 가르키면 출력 할 것이 없음
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);	//몇번째 노드에 어떤 값이 저장되어 있는지 출력
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);	//현재 리스트에 저장된 노드의 개수
}


