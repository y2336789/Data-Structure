/*
 * teamproject.c
 *
 *  Created on: 2020. 6. 4.
 *      Author: y2j
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 30
#define TRUE 1
#define FALSE 0

int count=0;

int visited[MAX_VERTEX]={0,};	//그래프에서 vertex들을 방문했는지 값을 저장하는 visited 배열
int Svisited[MAX_VERTEX]={0,}; //깊이 우선 탐색에서 visit flag를
int Qvisited[MAX_VERTEX]={0,};

int DFStack[MAX_VERTEX]= {0,};
int StackTop = -1;

typedef struct QNode
{
	int data;
	struct QNode *link;
}QNode;

typedef struct
{
	QNode *front;
	QNode *rear;
}LQ;

LQ *createLinkedQ()
{
	LQ * lq;
	lq = (LQ*)malloc(sizeof(LQ));
	lq->front = NULL;
	lq->rear = NULL;
	return lq;
}

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

int checkempty();
void createGraph(Graph* aGraph);
void destroyGraph(Graph* aGraph);
void insertVertex(Graph* aGraph, int input);
void deleteVertex(Graph* aGraph, int key);
void insertEdge(Graph* aGraph, int fromV, int toV);
void deleteEdge(Graph* aGraph, int fromV, int toV);
void depthFS(Graph* aGraph, int v);
void breadthFS(Graph* aGraph, int v);
void printGraph(Graph* aGraph);

int Pop();
void Push(int x);

int isEmpty(LQ *lq);
void enqueue(LQ *lq, int key);
int deQueue(LQ *lq);

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

int checkempty()
{
	int a;
	for(a=0;a<MAX_VERTEX; a++)
	{
		if(visited[a]==1)
		{
			count++;
		}
	}
	return count;
}

void createGraph(Graph * aGraph)	//그래프를 생성하는 함수이다. 그래프가 가리키는 vlist를 동적할당해주는 함수
{
	count = 0;
	int a=0;
	aGraph->vlist = (VertexHead *)malloc(sizeof(VertexHead)* MAX_VERTEX);	//aGrpah는 main에서 mygraph가 넘어온건데 선언 외에는 지정해 준 것이 없다. 동적 할당을 해준다.
	//vlist는 MAX_VERTEX의 size를 가진 배열이다.
	for(a; a< MAX_VERTEX; a++)
	{
		aGraph->vlist[a].head = NULL;	//MAX_VERTEX만큼 동적할당을 해주었고, 현재 아무것도 가리키는 것이 아무것도 없으니 NULL을 가리키게 한다.
	}
	return;
}

void destroyGraph(Graph* aGraph)	//동적할당한 요소를 해제하고, 그래프에 저장된 값을 다 없애주는 함수
{
	count = 0;
	int a=0;
	Vertex* before;	//location의 전 위치를 담고 있을 before 변수
	Vertex* location;	//그래프의 값들을 삭제하기 위해 위치를 저장할 변수 location
	for(a; a< MAX_VERTEX; a++) //vlist의 모든 곳에 접근한다.
	{
		if(aGraph->vlist[a].head != NULL)	//만약 vlist[a].head에 값이 저장되어있다면
		{
			location = aGraph->vlist[a].head->link;	//location을 해당 위치를 잡게 설정해준다.
			while(location != NULL)	//location이 NULL이 아니라면
			{
				before = location;	//location의 위치를 옮기기 위해, before를 location와 같은 곳을 가리키게 한 뒤에
				location = location->link;	//location의 위치를 옮겨준다
				free(before);	//before를 동적 할당을 해제시켜준다. 이 방법을 location이 NULL이 될 때 까지 반복한다.
			}
		}
		//만약 해제가 다 이뤄지고 location이 NULL인 상태가 되면 해당 vlist[a]에 삽입된 Vertex는 없는 것이다
		aGraph->vlist[a].head = NULL;	//그래서 vlist[a].head에 NULL을 저장해준다.
		visited[a] = 0; //visited 배열은 그래프 상에서 어느 vertex를 방문했는지 값을 담고있는 배열인데 값의 삭제가 이루어졌으니 a를 방문했다는 정보를 0(False)로 바꾸어 준다.
		Svisited[a] = 0;
		Qvisited[a] = 0;
	}
	return;
}

void insertVertex(Graph* aGraph, int input) //input에 있는 저장되어 있는 값은 몇 번 Vertex를 활성화 할 것인지이다.
{
	if(visited[input] == 0)	//visited[input]의 값이 0이면(방문하지 않은 값이라면)
	{
		visited[input] = 1; //값을 1로 바꿔준다.
	}

	return ;
}

void deleteVertex(Graph* aGraph, int key)	//vlist[key]에 있는 값들을 다 삭제한다.
{	//deleteVertex 안에는 deleteNode도 해야함
	//지금 현재 Node는 안되는 상태
	Vertex* location;
	Vertex* before;
	int a;
	if(visited[key] == 0)
	{
		printf("해당 Vertex가 그래프에 없습니다!\n");
		return;
	}
	/*for(a=0;a<MAX_VERTEX; a++)
	{
		if(visited[a] == 1)
		{
			deleteEdge(aGraph,key,a);
		}
	}
	visited[key] = 0;*/

	location = aGraph->vlist[key].head;//->link
	while(location != NULL)
	{
		before = location;
		location = location->link;
		a= before->num;
		deleteEdge(aGraph,key,a);
		free(before);
	}
	aGraph->vlist[key].head = NULL;
	visited[key] = 0;


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

	if(flocation == NULL && tlocation == NULL)
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
				flocation = flocation->link;
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
			printf("1\n");
			return;
		}
		else if(tlocation->link != NULL)
		{
			aGraph->vlist[toV].head = tlocation->link;
			free(tlocation);
			return ;
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
	Svisited[v] = TRUE;
	Push(v);
	printf("%d",v);
	while(StackTop != -1)
	{
			w = aGraph->vlist[v].head;
			while(w)
			{
				if(Svisited[w->num] == 0)
				{
					Push(w->num);
					Svisited[w->num] = 1;
					printf("->%d", w->num);
					v = w->num;
					w = aGraph->vlist[v].head;
				}
				else w = w->link;
			}
			v = Pop();
	}
	return;
}

void breadthFS(Graph* aGraph, int v)
{
	Vertex* w;
	LQ *q;
	q = createLinkedQ();
	Qvisited[v] = TRUE;
	printf("%d", v);
	enqueue(q,v);

	while(!isEmpty(q))
	{
		v=deQueue(q);
		for(w=aGraph->vlist[v].head; w; w = w->link)
		{
			if(Qvisited[w->num] == FALSE)
			{
				Qvisited[w->num] = TRUE;
				printf("%5d", w->num);
				enqueue(q, w->num);
			}
		}
	}
	return;
}

void printGraph(Graph* aGraph)
{
	int a, chek;
	chek = checkempty();
	if(chek == 0)
	{
		printf("출력할 것이 아무 것도 없습니다.\n");
		return;
	}
	if(aGraph->vlist == NULL)
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
		else
		{
			if(visited[a] == 1)
			{
				printf("Vertex [%d] 와 연결된 정점 : ", a);
				printf("아무런 값도 없습니다.\n");
			}
		}
	}
	return;
}

void Push(int x)
{
	StackTop++;
	DFStack[StackTop] = x;
}

int Pop()
{
	if (StackTop == -1)
	{
		printf("Stack is FULL!\n");
		return 0;
	}
	StackTop--;
	return DFStack[StackTop];
}


int isEmpty(LQ *lq)
{
	if(lq->front == NULL)
	{
		//printf("Queue is empty!\n");
		return 1;
	}
	else
		return 0;
}

void enqueue(LQ *lq, int key)
{
	QNode *newNode = (QNode*)malloc(sizeof(QNode));
	newNode->data = key;
	newNode->link = NULL;

	if(lq->front == NULL)
	{
		lq->front = newNode;
		lq->rear = newNode;
	}
	else
	{
		lq->rear->link = newNode;
		lq->rear = newNode;
	}

}

int deQueue(LQ *lq)
{
	QNode *location = lq->front;
	int key;
	if(isEmpty(lq))
		return 0;
	else
	{
		key = location->data;
		lq->front = lq->front->link;
		if(lq->front == NULL)
			lq->rear = NULL;
		free(location);
		return key;
	}
}

