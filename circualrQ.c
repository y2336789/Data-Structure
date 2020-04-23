/*
 * circularQ.c
 *
 *  Created on: 2020. 4. 19.
 *      Author: young
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 4		//q의 최대 사이즈를 4로 지정한다

typedef char element;
typedef struct {
    element queue[MAX_QUEUE_SIZE];		//element queue는 char queue와 같다
    int front, rear;
}QueueType;	//QueueType이란 구조체 선언


QueueType *createQueue();	//QueueType 구조체 포인터. createQueue는 QueueType 구조체의 주소를 가지고 있음
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);

element getElement();


int main(void)
{
    QueueType *cQ = createQueue(); //QueueType 구조체 포인터인 cQ를 createQueue란 함수로 생성하고 있다
    element data;			//char를 저장하는 변수 data를 선언

    char command;

    do{
        printf("\n-----------------------------------------------------\n");
        printf("                     Circular Q                   \n");
        printf("------------------------------------------------------\n");
        printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
        printf("------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'i': case 'I':
            data = getElement();
            enQueue(cQ, data);
            break;
        case 'd': case 'D':
            deQueue(cQ,&data);
            break;
        case 'p': case 'P':
            printQ(cQ);
            break;
        case 'b': case 'B':
            debugQ(cQ);
            break;
        case 'q': case 'Q':
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');


    return 1;
}


QueueType *createQueue()		//구조체 QueueType을 가르키는 구조체 포인터를 만든다
{
    QueueType *cQ;
    cQ = (QueueType *)malloc(sizeof(QueueType));	//구조체 QueueType 의 크기만큼 cQ를 동적할당한다
    cQ->front = 0;	//cQ가 가르키는 구조체의 front를 0으로 초기화 시켜 주고 있다
    cQ->rear = 0;		//cQ가  가르키는 구조체의 rear를 0으로 초기화 시켜 주고 있다
    return cQ;		//만들어진 QueueType 구조체 포인터의 주소를 리턴해주고 있다
}

element getElement()	//사용자로부터 문자 한 개를 입력 받는 함수
{
    element item;	//char item과 같은 의미이다
    printf("Input element = ");
    scanf(" %c", &item);	//사용자가 입력한 문자 한개를 item에 저장한다
    return item;	//문자를 반환
}


/* complete the function */
int isEmpty(QueueType *cQ)	//구조체 포인터가 가르키는 구조체의 큐가 비었는지 확인하는 함수
{
    if(cQ->front == cQ->rear){	//원형 큐에서 큐가 비었을 조건은 front와 rear가 같은 조건이다.
        printf("비었습니다.\n");	//cQ가 가르키는 구조체의 원형 큐의 front와 rear가 같을 경우 비었다는 것을 알 수 있다
        return 1;	//같으면 1을 반환
    }
    else return 0;	//같지 않으면, 즉 원형 큐가 비어있지 않으면 0을 반환한다.
}

/* complete the function */
int isFull(QueueType *cQ)		//구조체 포인터가 가르키는 구조체의 큐가 꽉 찼는지 확인하는 함수
{
  if(((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front){	//원형 큐에서 큐가 꽉찬 조건은 rear에 1을 더한 값에 큐의 크기를 나눈 값이 front가 같은 조건이다
      printf("꽉 찼습니다.");	//원래 큐에서는 꽉 찼을 때랑 비었을 때 의 조건을 구분하기 어렵기 때문에 원형 큐에서는 공간 하나를 비워 둔다.
      return 1;	//꽉 찼다면 1을 반환
  }
  else return 0;//아니면 0을 반환
}


/* complete the function */
void enQueue(QueueType *cQ, element item)	//구조체 포인터 cQ가 가르키는 구조체의 큐에 item을 집어 넣는 함수
{
    if(isFull(cQ)){	//값을 집어 넣기 전에 구조체, 즉 원형 큐가 꽉 찼는지 검사를 해야한다.
        return;	//꽉 찼을 시에 리턴 하여서 함수를 종료
    }
    else {	//만약 꽉 차지 않았다면?
        cQ->rear = (cQ->rear+1) % MAX_QUEUE_SIZE;	//rear의 위치를 rear의 앞 단게로 위치 시킨다. MAX_QUEUE_SIZE로 나눈 이유는 MAX_QUEUE_SIZE보다 커졌을 때 값을 나누면 다시 0,1,2 부터 MAX_QUEUE_SIZE-1의 값까지 나오기 때문이다
        cQ->queue[cQ->rear] = item;	//rear의 위치를 옮긴 후에 cQ가 가르키는 구조체 내에 있는 queue의 새로운 rear의 위치에 값을 저장한다.
    }
    return;
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)	//cq가 가르키는 구조체 내에 있는 원형 큐에서 값을 삭제하는 함수
{
    if(isEmpty(cQ)){	//값을 삭제 하기 전에, 값이 존재하는지, 혹시 원형 큐가 비었을 수 있으니 검사를 한다
        return;	//비었다면 함수를 종료
    }
    else{	//비었지 않았다면?
    cQ->front = (cQ->front+1) % MAX_QUEUE_SIZE;	//front의 위치를 한 칸 앞으로 이동한다. 원래 front는 빈 칸이다
    cQ->queue[cQ->front] = '\0';	//새로 옮긴 front의 위치에 값이 있으니 그 값을 삭제한다. 널로 바꾼다
    }
    return ;
}


void printQ(QueueType *cQ)		//cQ가 가르키는 구조체의 원형큐를 출력하는 함수
{
    int i, first, last;

    first = (cQ->front + 1)%MAX_QUEUE_SIZE;	//first, 즉 원형 큐에 값이 처음 있는 위치를 front를 통해서 first라 지정한다
    last = (cQ->rear + 1)%MAX_QUEUE_SIZE;		//원형 큐에 마지막 값이 있는 위치를 rear를 통해서 last로 설정하고 있다

    printf("Circular Queue : [");

    i = first;	//i를 first로 지정해주고
    while(i != last){	//i가 last가 아니면
        printf("%3c", cQ->queue[i]);	//큐의 i번째 위치에 저장된 값을 출력
        i = (i+1)%MAX_QUEUE_SIZE;	//그리고 i를 더해줘서 다음 위치에 저장된 값을 출력하도록 한다.

    }
    printf(" ]\n");
}


void debugQ(QueueType *cQ)	//현재 원형 큐에 어떤 값이 저장되있는지와 원형 큐의 front와 rear의 값을 알려주는 함수이다.
{

    printf("\n---DEBUG\n");
    for(int i = 0; i < MAX_QUEUE_SIZE; i++)
    {
        if(i == cQ->front) {
            printf("  [%d] = front\n", i);
            continue;
        }
        printf("  [%d] = %c\n", i, cQ->queue[i]);

    }
    printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}
