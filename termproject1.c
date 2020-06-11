/*
 * teamproject.c
 *
 *  Created on: 2020. 6. 4.
 *      Author: y2j
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 20
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTEX]={0,};
int Svisited[MAX_VERTEX];
int Qvisited[MAX_VERTEX];


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

// 주어진 자료 구조
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
void insertVertex(Graph* aGraph, int input);
void deleteVertex(Graph* aGraph, int key);
void insertEdge(Graph* aGraph, int fromV, int toV);
void deleteEdge(Graph* aGraph, int fromV, int toV);
void depthFS(Graph* aGraph, int v);
void breadthFS(Graph* aGraph, int v);
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
	int key,row,from,to;
	Graph mygraph;

	do{
		printf("\n");
		printf("------------------------- 2017038068 양영재 -------------------------");
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   !!! Term-Project !!!                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" createGraph       	  = z      DestroyGraph       = x \n");
		printf(" Insert Vertex         = i      Delete Vertex      = d \n");
		printf(" Insert Edge       	  = e	    Delete Edge        = f \n");
		printf(" DepthFS       	  = s      BreadthFS       	  = b \n");
		printf(" Print Graph       	  = p      Quit       	  = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
			case 'z': case 'Z':
				createGraph(&mygraph);
				break;
			case 'x': case 'X':
				destroyGraph(&mygraph);
				break;
			case 'i': case 'I':
				printf("몇 번 vertex를 활성화 할 것인지 입력하시오 : ");
				scanf("%d", &row);
				insertVertex(&mygraph, row);
				break;
			case 'd': case 'D':
				printf("Your Key = ");
				scanf("%d", &key);
				deleteVertex(&mygraph, key);
				printf("1\n");
				break;
			case 'e': case 'E':
				printf("Edge를 추가할 vertex 값을 입력하시오 : ");
				scanf("%d %d", &from, &to);
				insertEdge(&mygraph, from, to);
				break;
			case 'f': case 'F':
				printf("Edge를 삭제 할 vertex 값을 입력하시오 : ");
				scanf("%d %d", &from, &to);
				deleteEdge(&mygraph, from, to);
				break;
			case 's': case 'S':
				printf("Your key = ");
				scanf("%d", &key);
				depthFS(&mygraph, key);
				break;
			case 'b': case 'B':
				printf("Your Key = ");
				scanf("%d", &key);
				breadthFS(&mygraph, key);
				break;
			case 'p': case 'P':
				printGraph(&mygraph);
				break;
			case 'q': case 'Q':
				destroyGraph(&mygraph);
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
	aGraph->vlist = (VertexHead *)malloc(sizeof(VertexHead)* MAX_VERTEX);

	for(a; a< MAX_VERTEX; a++)
	{
		aGraph->vlist[a].head = NULL;
	}
	return;
}

void destroyGraph(Graph* aGraph)
{
	int a=0;
	Vertex* before;
	Vertex* location;
	for(a; a< MAX_VERTEX; a++)
	{
		if(aGraph->vlist[a].head != NULL)
		{
			location = aGraph->vlist[a].head->link;
			while(location != NULL)
			{
				before = location;
				location = location->link;
				free(before);
			}
		}
		aGraph->vlist[a].head = NULL;
		visited[a] = 0;
	}
	return;
}

void insertVertex(Graph* aGraph, int input) //input에 있는 숫자는 배열 순서
{
	if(visited[input] == 0)
	{
		visited[input] = 1;
	}

	return ;
}

void deleteVertex(Graph* aGraph, int key)	//vlist[key]에 있는 값들을 다 삭제한다.
{	//deleteVertex 안에는 deleteNode도 해야함
	//지금 현재 Node는 안되는 상태
	Vertex* location;
	Vertex* before;
	printf("1\n");
	if(visited[key] == 0)
	{
		printf("해당 Vertex가 그래프에 없습니다!\n");
		return;
	}

	location = aGraph->vlist[key].head->link;
	while(location != NULL)
	{
		before = location;
		location = location->link;
		free(before);
	}
	aGraph->vlist[key].head = NULL;
	return ;
}

void insertEdge(Graph* aGraph, int fromV, int toV)
{
	Vertex* location;
	if(visited[fromV] == 0 || visited[toV]==0)
	{
		printf("그래프에 없는 정점입니다!\n");
		return ;
	}
	Vertex* newone = (Vertex*)malloc(sizeof(Vertex));
	newone->num = toV;
	Vertex* newone2 = (Vertex*)malloc(sizeof(Vertex));
	newone2->num = fromV;
	if(aGraph->vlist[fromV].head == NULL)
	{
		aGraph->vlist[fromV].head = newone;
		newone->link = NULL;
	}
	else
	{
		if(aGraph->vlist[fromV].head->num != toV)
		{
			location = aGraph->vlist[fromV].head;
			while(location->link != NULL)
			{
				location = location->link;
				if(location->num == toV)
				{
					break;
				}
			}
			if(location->num != toV)
			{
				location->link = newone;
				newone->link = NULL;
			}
		}
	}

	if(aGraph->vlist[toV].head == NULL)
	{
		aGraph->vlist[toV].head = newone2;
		newone2->link = NULL;
	}
	else
	{
		if(aGraph->vlist[toV].head->num != fromV)
		{
			location = aGraph->vlist[toV].head;
			while(location->link != NULL)
			{
				location = location->link;
				if(location->num == fromV)
				{
					break;
				}
			}
			if(location->num != fromV)
			{
				location->link = newone2;
				newone2->link = NULL;
			}
		}
	}
	return ;
}

void deleteEdge(Graph* aGraph, int fromV, int toV)
{
	Vertex* flocation= aGraph->vlist[fromV].head;
	Vertex* tlocation= aGraph->vlist[toV].head;
	Vertex* before;

	if(flocation == NULL || tlocation == NULL)
	{
		printf("해당 vertex들은 연결되어 있지 않습니다.\n");
		return;
	}
	if(flocation->num == toV)
	{
		if(flocation->link == NULL)
		{
			free(flocation);
			aGraph->vlist[fromV].head = NULL;
		}
		else
		{
			aGraph->vlist[fromV].head = flocation->link;
			free(flocation);
		}
	}
	else
	{
		while(flocation != NULL)
		{
			if(flocation->num != toV)
			{
				before = flocation;
				flocation = before->link;
				if(flocation== NULL)
				{
					printf("해당 edge가 그래프에 없습니다.\n");
					return ;
				}

				if(flocation->num == toV)
				{
					if(flocation->link == NULL) //만약 해당 line에서 마지막 vertex일 시에
					{
						free(flocation);
						before->link = NULL;
						break;
					}
					else if(flocation->link != NULL)
					{
						before->link = flocation->link;
						free(flocation);
						break;
					}
				}
			}
		}
	}

	if(tlocation->num == fromV)
	{
		if(tlocation->link == NULL)
		{
			free(tlocation);
			aGraph->vlist[toV].head = NULL;
			return;
		}
		else
		{
			aGraph->vlist[toV].head = tlocation->link;
			free(tlocation);
		}
	}
	else
	{
		while(tlocation != NULL)
		{
			if(tlocation->num != fromV)
			{
				before = tlocation;
				tlocation = tlocation->link;
				if(tlocation->num == fromV)
				{
					if(tlocation->link == NULL) //만약 해당 line에서 마지막 vertex일 시에
					{
						free(tlocation);
						before->link = NULL;
						break;
					}
					else if(tlocation->link != NULL)
					{
						before->link = tlocation->link;
						free(tlocation);
						break;
					}
				}
			}
		}
	}

	return;
}

void depthFS(Graph* aGraph, int v)
{
	Vertex* w;
	Stack st1;
	Stackinit(&st1);
	Push(&st1, v);
	Svisited[v] = TRUE;
	printf("%5d ",v);
	while(st1.top != NULL)
	{
		w = aGraph->vlist[v].head;
		while(w)
		{
			if(!Svisited[w->num])
			{
				Push(&st1, w->num);
				Svisited[w->num] = TRUE;
				printf("%d ", w->num);
				//v = w->num;
				//w = aGraph->vlist[v].head;
			}
			else {
				w = w->link;
			}
		}
		v= Pop(&st1);
	}
return;
}

void breadthFS(Graph* aGraph, int v)
{
	Vertex* w;
	Queue q;
	Queueinit(&q);
	printf("%d", v);
	Qvisited[v] = TRUE;
	Enqueue(&q, v);
	while(q.queue[q.front] != NULL)
	{
		v = Dequeue(&q);
		for(w = aGraph->vlist[v].head; w; w= w->link)
		{
			if(!visited[w->num])
			{
				printf("%d ", w->num);
				Enqueue(&q, w->num);
				visited[w->num] = TRUE;
			}
		}
	}
	return;
}

void printGraph(Graph* aGraph)
{
	int a;
	if(aGraph == NULL)
	{
		printf("그래프 정보가 없습니다.\n");
		return;
	}

	for(a=0; a<MAX_VERTEX; a++)
	{
		Vertex* location = aGraph->vlist[a].head;
		if(location != NULL)
		{
			printf("Vertex [%d] 와 연결된 정점 : ", a);
			while(location != NULL)
			{
				printf("%d ",location->num);
				location = location->link;
			}
			printf("\n");
		}

	}
	return;
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
		return 0;
	}
	pq->front = (pq->front+1) % MAX_VERTEX;
	return pq->queue[pq->front];
}
