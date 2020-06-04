/*
 * teamproject.c
 *
 *  Created on: 2020. 6. 4.
 *      Author: y2j
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 20

int visited[MAX_VERTEX];

//  Stack
typedef struct _stack
{
	int stackArr[MAX_VERTEX];
	int top;
}Stack;




// Queue
typedef struct _cQueue
{
	int front;
	int rear;
	int queue[MAX_VERTEX];
}Queue;

typedef struct Vertex {
	int num;
	struct Vertext* link;
}Vertex;

typedef struct VertexHead{
	Vertex* head;
} VertexHead;

typedef struct Graph {
	VertexHead* vlist;
} Graph;

void createGraph(Graph* aGraph);
void destroyGraph(Graph* aGraph);
int insertVertex(Graph* aGraph, int input, int key);
int deleteVertex(Graph* aGraph, int key);
void insertEdge(Graph* aGraph, int fromV, int toV);
void deleteEdge(Graph* aGraph, int fromV, int toV);
void depthFS();
void printGraph(Graph* aGraph);

void Stackinit(Stack* pstack);
void Push(Stack* pstack, int data);
int Pop(Stack* pstack);

void Queueinit(Queue *pq);
void Enqueue(Queue * pq, int data);
int Dequeue(Queue * pq);

int main(void)
{
	char command;
	int key,row;
	Graph mygraph;

	do{
		printf("\n");
		printf("------------------------- 2017038068 양영재 -------------------------");
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   !!! Term-Project !!!                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" createGraph       	  = z                                       \n");
		printf(" Insert Vertex        = i      Destroy Vertex	            = d \n");
		printf(" Insert Edge    		  = e	    Delete Edge                  = f \n");
		printf(" DepthFS              = s      BreadthFS                    = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf("%c", &command);

		switch(command) {
			case 'z': case 'Z':
				createGraph(&mygraph);
				break;
			case 'q': case 'Q':

				break;
			case 'i': case 'I':
				printf("Vertex의 값을 입력하시오 : ");
				scanf("%d", &key);
				printf("어느 Vertex 근처에 위치 시킬 것인가 입력하시오 : ");
				scanf("%d", &row);
				insertVertex(&mygraph, row, key);
				break;
			case 'd': case 'D':
				printf("Your Key = ");
				scanf("%d", &key);

				break;

			case 'r': case 'R':

				break;
			case 't': case 'T':

				break;

			case 'l': case 'L':

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

void createGraph(Graph * aGraph)
{
	int a=0;
	VertexHead* nhead = (VertexHead *)malloc(sizeof(VertexHead)* MAX_VERTEX);
	aGraph->vlist = nhead;

	for(a; a< MAX_VERTEX; a++)
	{
		nhead[a].head = NULL;
	}
	return;
}

void destroyGraph(Graph* aGraph)
{
	int a=0;
	Vertex* location = aGraph->vlist->head;
	Vertex* before;

	for(a; a< MAX_VERTEX; a++)
	{
		deleteVertex(aGraph, a);
	}
	return;
}

int insertVertex(Graph* aGraph, int input, int key) //input에 있는 숫자는 배열 순서
{
	Vertex* location = aGraph->vlist[input].head;
	Vertex* newone = (Vertex *)malloc(sizeof(Vertex));
	newone->num = key;
	if(aGraph->vlist[input].head == NULL)	//만약 그래프의 vertexhead가 비어있다면
	{	//위의 식 대신 location도 됨?
		aGraph->vlist[input].head = newone;
		newone->link = NULL;
		return 1;
	}
	//만약 헤드가 어떤 노드를 가리키고 있는 상황이면

	if(location != NULL)
	{
		location = location->link;	// vlist[input]에서 null을 가리키는 노드가 나올 때 까지 위치를 옮김.
	}
	location->link = newone;	//만약 location->link 가 NULL이면 마지막위치에 newone을 가리킨다
	newone->link = NULL;	//newone의 link는 가리키는 값이 없으니까 NULL을 가리키게 한다.
	return 1;
}

int deleteVertex(Graph* aGraph, int key)	//vlist[key]에 있는 값들을 다 삭제한다.
{	//deleteVertex 안에는 deleteNode도 해야함
	VertexHead * here = aGraph->vlist[key];
	Vertex* location = aGraph->vlist[key].head;
	Vertex* before;

	if(location != NULL)
	{
		before = location;
		location = location->link;
		free(before);
	}
	free(aGraph->vlist);

	return 0;
}

void insertEdge(Graph* aGraph, int fromV, int toV)
{
	Vertex* newone = (Vertex*)malloc(sizeof(Vertex));
	newone->num = toV;
	Vertex* location = aGraph->vlist[fromV].head;
	while(location != NULL)
	{
		location = location->link;
		if(location->num == toV)
		{
			insertVertex(aGraph, toV, fromV);
			return;
	}
	//만약에 vlist[fromV]에서 newone->num과 일치하는 값이 없는 경우!
	printf("Edge를 추가 할 Vertex가 존재하지 않습니다!\n");
	return ;
}

void deleteEdge(Graph* aGraph, int fromV, int toV)
{
	Vertex* newone = aGraph->vlist[fromV].head;
	Vertex* before;

	while(newone != NULL)
	{
		before = newone;
		newone = newone->link;
		if(newone->num == toV)
		{
			if(newone->link == NULL) //만약 해당 line에서 마지막 vertex일 시에
			{
				free(newone);
				before->link = NULL;
				return;
			}
			else if(newone->link != NULL)
			{
				before->link = newone->link;
				free(newone);
				return;
			}
		}
	}
	// 값을 찾을 수 없는 경우
	if(newone == NULL)	printf("Vertex들로 연결된 Edge를 찾을 수 없습니다.\n"); return;

	newone = aGraph->vlist[toV].head;
	while(newone != NULL)
		{
			before = newone;
			newone = newone->link;
			if(newone->num == fromV)
			{
				if(newone->link == NULL) //만약 해당 line에서 마지막 vertex일 시에
				{
					free(newone);
					before->link = NULL;
					return;
				}
				else if(newone->link != NULL)
				{
					before->link = newone->link;
					free(newone);
					return;
				}
			}
		}

}

void depthFS(Graph* aGraph, int v)
{
	Vertex* h;
	visited[v] = 1;
	printf("%d", v);

}

void printGraph(Graph* aGraph)
{
	Vertex* loaction = aGraph->vlist->head;

}

void Stackinit(Stack* pstack)
{
	int i;
	for(i=0; i<MAX_VERTEX; i++)
	{
		pstack->stackArr[i] = 0;
	}
	pstack->top = -1;
}

void Push(Stack* pstack, int data)
{
	pstack->top += 1;
	pstack->stackArr[pstack->top] = data;
}

int Pop(Stack* pstack)
{
	int before;
	if(pstack->top == -1)
	{
		printf("Stack is Empty!\n");
		return 0;
	}
	before = pstack->top;
	pstack->top -= 1;

	return pstack->stackArr[before];
}

void Queueinit(Queue *pq)
{
	int i;
	pq->front = -1;
	pq->rear = -1;
	for(i=0;i<MAX_VERTEX;i++)
	{
		pq->queue[i] = 0;
	}
}

void Enqueue(Queue * pq, int data)
{
	if(((pq->rear+1) % MAX_VERTEX) == pq->front)
	{
		printf("Queue is FULL!\n");
		return;
	}

	pq->rear++;
	pq->queue[pq->rear] = data;
}

int Dequeue(Queue * pq)
{
	if(pq->rear == pq->front)
	{

	}



}













