/*
 * circular-linked-list.c
 *
 *  Created on: 2020. 5. 12.
 *      Author: young
 */

#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{

		printf(" ======================= 양영재 2017038068 =======================\n");
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	listNode* local = h->rlink;	//헤더 노드가 가르키는 처음 노드를 local이라 하자

	while(local->rlink != h)	//local의 다음 노드가 h가 아닌 경우
	{
		local = (local->rlink);	//local을 한 위치 옮긴 후에
		free(local->llink);	//바로 전에 local이 위치했던 곳을 free 해준다.
	}
	free(local); //반복문이 탈출할 조건은 local이 가르키는 노드가 h일때이니 local만 해재시켜주면 h만 남게된다
	free(h);	//h만 남으면 h도 free해준다.

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* newone = (listNode *)malloc(sizeof(listNode));	//새로 추가할 노드인 newone을 동적 할당
	listNode* last = NULL;	//마지막 노드를 가르킬 last
	newone->key = key;	//입력받은 key 값을 새로 추가할 노드인 newone에 저장

	if(h->rlink == h)	//헤더 노드 외에 다른 노드가 없는 경우
	{
		h->rlink = newone;	//h->rlink가 newone을 가리킨다
		newone->rlink = h;	//newone->rlink는 h를 가리킨다
		newone->llink = h;	//newone->llink는 h를 가리킨다
		h->llink = newone;	//h->llink는 newone을 가리킨다
		return 1;
	}	//헤더 노드 외에도 다른 노드가 있는 경우
	last = h->llink;	//last가 가리키는 곳을 h->llink, 즉 마지막 노드가 있는 곳으로

	newone->rlink=h;		//newone이 마지막 노드가 될 것이니 rlink는 h를 가리킨다
	last->rlink=newone;	//원래 마지막에 위치했던 last의 rlink는 마지막에 추가되는 newone을 가리킴
	newone->llink=last;	//newone의 llink는 원래의 마지막이었던 last를 가리킨다
	h->llink=newone;		//마지막을 가리키는 h->llink는 새롭게 newone을 가리킨다

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	listNode * last = h->llink;	//마지막을 가리키는 h->llink를 last라 한다

	if(last == h)	//만약 last가 h이면? 이 말은 즉슨 현재 노드가 헤더 노드 밖에 없다는 의미이다
	{
		printf("삭제 할 값이 없습니다!\n");
		return 0;
	}
	(last->llink)->rlink = h;	//그렇지 않다면 last 전에 위치한 노드의 rlink가 h를 가리키게 한다. last가 삭제 될 것이기 때문
	h->llink = (last->llink);	//마지막을 가리키는 헤더노드의 llink는 last의 전 노드를 가리킨다
	free(last);	//last를 free 시켜준다.

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode * newone = (listNode *)malloc(sizeof(listNode));	//새롭게 추가될 노드 newone을 동적할당
	newone->key = key;	//newone에 key값 저장

	if(h->rlink == h)	//만약 입력된 값이 하나도 없을 시에
	{
		h->rlink = newone;	//헤더노드가 newone을 가리킨다
		newone->rlink = h;	//newone도 헤더노드를 가리킨다
		newone->llink = h;
		h->llink = newone;
		return 1;
	}
	else
	{
		newone->rlink = h->rlink;	//newone이 첫번째 노드가 될 것이므로 h->rlink가 가리키는 곳을 newone도 가리킨다
		newone->llink = h;	//첫번째 노드의 llink는 헤더노드를 가리킨다
		(newone->rlink)->llink = newone;	//원래 위치했던 처음 노드의 llink는 원래 헤더노드를 가리켰으나 이제는 newone을 가리키게 한다
		h->rlink = newone;	//h->rlink는 항상 처음 노드를 가리키므로 newone을 가리킨다
		return 1;
	}


}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	listNode* first = h->rlink;		//첫 번째 노드를 가리키는 h->rlink, 처음 노드를 first라 한다

	if(first == h)	//헤더 노드 밖에 없는 경우
	{
		printf("삭제 할 값이 없습니다!\n");
		return 0;
	}
	(first->rlink)->llink = h;	//처음 노드 다음에 있는 노드의 llink는 h를 가리키게 한다. first가 사라질 예정
	h->rlink = (first->rlink);	//h->rlink는 first의 다음 노드를 가리킨다
	free(first);	//first를 free해준다

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	listNode* firstone = h->rlink;	//처음 노드를 가리키게 될 firstone, 함수 안에서 위치가 변경됨
	listNode* tail = NULL;		//3개 중에서 마지막을 가리킬 tail
	listNode* middle = NULL;	//중간 값을 가리킬 middle

	while(firstone != NULL)
	{
		tail = middle;
		middle = firstone;
		firstone = firstone->rlink;	//firstone의 위치를 한 칸 앞으로 옮긴다
		if(middle == h->rlink)	//만약 middle이 h->rlink, 즉 middle이 처음 노드일 경우(딱 한번 실행된다)
		{
			middle->rlink = h;	//이 노드는 역순으로 배치되면 마지막 노드가 될 것이니 rlink가 h를 가리키게 하고
			middle->llink = firstone;	//llink는 자신의 뒤에 위치했던 firstone을 가리키게 한다
			h->llink = middle;	//h->llink는 마지막 노드를 가리키니, 마지막 노드가 될 middle을 가리키게 한다
		}
		else //그 외에 경우에는
		{
			middle->rlink = tail;	//middle의 rlink는 전에 위치했던 tail를 가르키게 된다. 역순으로 배치하면 자기 뒤에 위치할 것이 tail이기 때문
			middle->llink = firstone;	//llink는 firstone을 가리키게 한다
		}
		if(firstone == h)	//만약 위에 경우들을 제외했을때, 마지막으로 firstone이 h일때, 즉 middle이 헤더노드를 제외하고 마지막 노드에 위치할때
		{
			h->rlink = middle;	//h->rlink는 middle을 가리키게 한다. 마지막에 위치하는 노드는 역순으로 배치하면 처음 노드가 되기 때문
			return 1;
		}
	}

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	listNode* newone = (listNode *)malloc(sizeof(listNode));	//새로 삽입할 노드 newone 동적할당
	listNode* location = h->rlink; //삽입할 위치를 찾을 location
	newone->key = key;

	if(h->rlink == h)	//노드가 헤더노드 밖에 없는 경우 노드를 추가한다
	{
		h->rlink = newone;
		newone->rlink = h;
		newone->llink = h;
		h->llink = newone;
		return 1;
	}

	while(location != NULL)
	{
		if(location->key < newone->key)	//만약 location의 key값 보다 newone의 key값이 더 클 때
		{
			if(location->rlink !=h)	//location의 다음 노드가 h가 아니면
				location = location->rlink;	//location의 위치를 한 칸 옮긴다
			else	//만약 다음 노드가 헤더 노드이면 마지막 노드보다 key값이 더 큰 것이니 마지막에 삽입한다
			{
				newone->rlink = h;
				h->llink = newone;
				location->rlink = newone;
				newone->llink = location;
				return 1;
			}
		}
		else	//location의 key값 이하일 경우에는 전의 위치에 삽입한다.
		{
			newone->rlink = (location->llink)->rlink; //newone의 rlink는 location의 llink의 rlink가 가리키는 곳을 가리킨다.
			newone->llink = location->llink;	//newone의 llink는 location의 llink가 가리키는 곳을 가리킨다
			(location->llink)->rlink = newone;	//location의 llink의 rlink는 newone을 가리킨다. newone의 location의 llink와 location 사이에 들어오기 때문
			location->llink = newone; //locatino의 llink는 자기 전에 새로 위치 할 newone을 가리킨다.
			return 1;
		}
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode * delete = h->rlink;

	if(delete == h)	//삭제할 노드가 없는 경우, 헤더 노드 밖에 없는 경우
	{
		printf("삭제할 노드가 없습니다.\n");
		return 1;
	}

	while(delete != NULL)
	{
		if(delete->key == key)	//처음 노드부터 검색해서 삭제하고자 하는 값이 delete의 key값과 일치 할 경우
		{
			(delete->rlink)->llink = (delete->llink);	//delete의 뒤에 위치한 노드의 llink는 delete의 전 노드를 가리킨다
			(delete->llink)->rlink = (delete->rlink);	//delete 전에 위치한 노드의 rllink는 delete의 뒤에 위치한 노드를 가리킨다
			free(delete);	//전과 뒤 사이에 있는 delete 노드를 free한다.
			return 1;
		}
		else
		{
			delete = delete->rlink;	//값이 같지 않은 경우 delete의 위치를 옮기고
			if(delete == h) //만약 옮긴 위치가 헤드 노드일 경우에는
				break;	//반복문을 탈출한다. 이 말은 즉슨 삭제할 값이 없다는 말이다.
		}
	}
	printf("삭제할 노드가 없습니다.\n");

	return 0;
}
