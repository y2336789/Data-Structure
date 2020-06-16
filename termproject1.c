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

int count=0; //카운트를 계산함으로, vlist가 활성화만 되었는지 아니면 Vertex들이 연결된 상태인지 알 수 있다.

int visited[MAX_VERTEX]={0,};	//그래프에서 vertex들을 방문했는지 값을 저장하는 visited 배열
int Svisited[MAX_VERTEX]={0,};	//depthFS에서 어떤 vertex를 방문했는지 기록한다, visit flag
int Qvisited[MAX_VERTEX]={0,};	//breadthFS에서 어떤 vertex를 방문했는지 기록한다

int DFStack[MAX_VERTEX]= {0,};
int StackTop = -1;

typedef struct QNode	//queue를 linked list로 나타내었다.
{
	int data;	//QNode안에 int 값을 저장하는 변수
	struct QNode *link;	//다음 QNode를 가리킬 link
}QNode;

typedef struct	// queue를 linked list로 나타내었기에 front와 rear를 가리키는 LQ선언
{
	QNode *front;
	QNode *rear;
}LQ;

LQ *createLinkedQ() //linked list로 표현하였기에 동적할당 및 초기화를 해주는 함수
{
	LQ * lq;	//queue의 front와 rear를 가리킬 LQ 구조체 포인터 변수 lq를 선언
	lq = (LQ*)malloc(sizeof(LQ));	//lq가 가르킬 QNode를 동적할당 하였음
	lq->front = NULL;	//front가 가리키는 것이 아직 없으니 NULL로 할당한다
	lq->rear = NULL;	//rear가 가리키는 것도 없으니 NULL로 할당
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
void enQueue(LQ *lq, int key);
int deQueue(LQ *lq);

int main(void)
{
	char command;
	int key,row,from,to;
	Graph mygraph;	// 그래프에 관련된 함수의 매개변수로 전달될 mygraph

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
				break;
			case 'e': case 'E':
				printf("Edge를 추가할 vertex 값을 입력하시오. ex)0 1: ");
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

int checkempty()	//활성화가 이뤄지었는지 확인해 주는 함수이다.
{
	int a;
	for(a=0;a<MAX_VERTEX; a++)
	{
		if(visited[a]==1)	//만약  visited[a]가 1이라면 활성화가 이루어 진 것이다.
		{
			count++; //그러면 count를 추가한다.
		}
	}
	return count;
}

void createGraph(Graph * aGraph)	//그래프를 생성하는 함수이다. 그래프가 가리키는 vlist를 동적할당해주는 함수
{
	count = 0;	//초기화 혹은 새로 Graph를 만들기에 count를 0으로 만들어 준다
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
	count = 0; //Graph에 대한 모든 것을 삭제하기에 count를 0으로 만들어준다.
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
		Svisited[a] = 0;	//dfs에 visit flag에 대한 정보를 저장하고 있는 Svisited를 전부 0으로 초기화시켜준다.
		Qvisited[a] = 0; //bfs에 visit flag에 대한 정보를 저장하고 있는 Qvisited를 전부 0으로 초기화시켜준다.
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
	if(visited[key] == 0)	//만약 활성화 시키지 않은 vertex를 삭제 할 시에
	{
		printf("해당 Vertex가 그래프에 없습니다!\n");
		return;
	}

	location = aGraph->vlist[key].head;
	while(location != NULL)	//만약 location에 값이 들어있다면
	{
		before = location;	//before로 location의 위치를 기록하고
		location = location->link;	//location의 위치를 수정한다.
		a= before->num;	//before->num 값을 받은 후
		deleteEdge(aGraph,key,a);	//Vertex를 삭제하면서 간선도 삭제를 시켜준다.
		free(before);	//간선 삭제 후 before를 동적 해제시킨다.
	}	//반복문을 반복하면서 vlist[key].head에 연결된 동적할당된 Vertex들이 해제된다.
	aGraph->vlist[key].head = NULL; //다 해제했으면 vlist[key].head가 가리키는 것을 NULL로 바꿔준다
	visited[key] = 0; //Vertex를 삭제하기 때문에 방문기록을 0으로 바꾼다
	return ;
}

void insertEdge(Graph* aGraph, int fromV, int toV)	//fromV와 toV 사이 간선을 추가한다.
{
	Vertex* location;
	if(visited[fromV] == 0 || visited[toV]==0)	//만약 둘 중 하나가 활성화 되지 않았을 경우
	{
		printf("그래프에 없는 정점입니다!\n");
		return ;
	}
	Vertex* newone = (Vertex*)malloc(sizeof(Vertex));	//vlist[fromV]에서 활용될 newone
	newone->num = toV;
	Vertex* newone2 = (Vertex*)malloc(sizeof(Vertex));	//vlist[toV]에서 활용될 newone2
	newone2->num = fromV;
	if(aGraph->vlist[fromV].head == NULL)	//만약 vlist[fromV].head가 비었다면
	{
		aGraph->vlist[fromV].head = newone; //head가 newone을 가리키게하고
		newone->link = NULL;	//newone의 link를 NULL로 설정해준다
	}
	else
	{
		if(aGraph->vlist[fromV].head->num != toV)	//만약 vlist[fromV].head가 채워져 있으면서, head->num이 toV와 일치하지 않으면
		{
			location = aGraph->vlist[fromV].head;	//location를 head로 잡고, 위치를 옮긴다
			while(location->link != NULL)	//location의 link가 NULL이 아니면
			{
				location = location->link; //location의 위치를 옮긴다. 해당 코드를 실행하는 이유는 중복된 값의 입력을 방지하기 위해서다
				if(location->num == toV)	//l위치를 넘기다 만약 location->num 값이 toV와 일치하면
				{
					break;	//반복문 while을 탈출한다.
				}
			}//탈출한 상태에서는 밑의 if문을 절대 실행 될 수 없다. 입력을 무시한다.
			if(location->num != toV)	//location->num이 toV와 일치하지 않는다면,
			{	//즉 입력될 값을 vlist[fromV]에서 찾을 수 없다면
				location->link = newone;	//location->link는 newone을 가리키게한다. 여기서 원래 location->link는 NULL이었다.
				newone->link = NULL;	//그리고 newone->link를 NULL로 만든다.
			}
		}
	}

	if(aGraph->vlist[toV].head == NULL)	//위의 코드에서 fromV를 toV로 바꾸었고, newone을 newone2로 적용하였다.
	{	//만약 vlist[toV].head가 비었다면
		aGraph->vlist[toV].head = newone2; //head가 newone2을 가리키게하고
		newone2->link = NULL;	//newone2의 link는 NULL을 가리킨다.
	}
	else
	{
		if(aGraph->vlist[toV].head->num != fromV)//만약 vlist[toV].head가 채워져 있으면서, head->num이 fromV와 일치하지 않으면
		{
			location = aGraph->vlist[toV].head;	//location을 vlist[toV].head로 설정한다
			while(location->link != NULL)	//location의 link가 NULL이 아니면
			{
				location = location->link;	//location의 위치를 옮겨준다
				if(location->num == fromV)	//만약 vlist[toV]내에 이미 fromV를 가진 Vertex가 있을 경우
				{
					break;	//입력을 생략한다
				}
			}
			if(location->num != fromV)	//이 if문이 도는 조건은 location의 link가 NULL일 때이다
			{
				location->link = newone2;	//location의 link를 newone2를 가리키게하고
				newone2->link = NULL;	//newone2의 link를 NULL을 가리키게한다
			}
		}
	}
	return ;
}

void deleteEdge(Graph* aGraph, int fromV, int toV)	//fromV와 toV에 연결된 간선을 삭제하는 함수
{
	Vertex* flocation= aGraph->vlist[fromV].head;		//vlist[fromV]를 검색할 flocation
	Vertex* tlocation= aGraph->vlist[toV].head;	//vlist[toV]를 검색할 tlocation
	Vertex* before;

	if(flocation == NULL && tlocation == NULL)	//둘다 Null일 경우
	{
		printf("해당 vertex들은 연결되어 있지 않습니다.\n");
		return;
	}
	if(flocation->num == toV) //만약 flocation->num이 toV와 일치하면
	{
		if(flocation->link == NULL)	//flocation->link가 NULL일 때
		{
			free(flocation);	//flocatio을 동적 해제하고
			aGraph->vlist[fromV].head = NULL;	//vlist[fromV].head를 NULL로 바꾸어준다
		}
		else	//그 외의 경우는 flocation이 가리키는 Vertex가 있는 경우는
		{
			aGraph->vlist[fromV].head = flocation->link;	//head가 flocation이 가리키는 Vertex를 가리키게 하고
			free(flocation); //flocation을 동적 해제 한다
		}
	}
	else //만약 flocation->num이 toV와 일치하지 않는다면 linked list를 탐색한다
	{
		while(flocation != NULL)	//flocation이 NULL이 아니면 위치를 옮긴다
		{
			if(flocation->num != toV)	//flocation->num과 toV가 일치하지 않으면
			{
				before = flocation;	//before로 flocation의 위치를 기억해주고
				flocation = flocation->link;	//flocation의 위치를 옮겨준다
				if(flocation == NULL)	//만약 이렇게 계속 flocation의 위치를 옮김에도 불과하고 flocation이 NULL이면
				{
					printf("해당 edge가 그래프에 없습니다.\n");
					return ;
				}

				if(flocation->num == toV) //만약 flocation->num이 toV와 일치하면
				{
					if(flocation->link == NULL) //만약 해당 line에서 마지막 vertex일 시에
					{
						free(flocation);	//flocation을 동적 해제하고
						before->link = NULL;	//전에 위치한 before의 link는 NULL이 된다.
						break;
					}
					else if(flocation->link != NULL)	//만약 일치하는 Vertex를 찾았는데 다음에 가리키는 Vertex가 있는 경우
					{
						before->link = flocation->link;	//before->link가 flocation->link를 가리키게 하고
						free(flocation);	//flocation을 동적 해제한다
						break;
					}
				}
			}
		}
	}
	//[fromV]에서 한 것을 [toV]에서도 동일하게 실시한다
	if(tlocation->num == fromV)	//tlocation->num이 fromV와 일치하는데
	{
		if(tlocation->link == NULL)	//만약 tlocation->link가 NULL이면
		{
			free(tlocation); //tlocation을 동적 해제하고
			aGraph->vlist[toV].head = NULL; //vlist[toV].head가 NULL이 되게한다
			return;
		}
		else if(tlocation->link != NULL)	//만약 tlocation이 가리키는 Vertex가 있는 경우
		{
			aGraph->vlist[toV].head = tlocation->link;	//head가 tlocation이 가리키는 Vertex를 가리키고
			free(tlocation); //tlocation을 동적 해제한다.
			return ;
		}
	}
	else	//만약 일치하지 않는다면
	{
		while(tlocation != NULL)	//tlocation이 NULL이 아닌 경우에서
		{
			if(tlocation->num != fromV)	//tlocation->num이 fromV와 다른 경우
			{
				before = tlocation;	//before로 tlocation의 위치를 잡고
				tlocation = tlocation->link;	//tlocation의 위치를 옮긴다
				if(tlocation->num == fromV)	//만약 tlocation->num이 fromV와 일치하는데
				{
					if(tlocation->link == NULL) //만약 해당 line에서 마지막 vertex일 시에
					{
						free(tlocation);	//tlocation을 동적 해제하고
						before->link = NULL;	//before->link는 NULL이 된다
						break;
					}
					else if(tlocation->link != NULL)	//만약 tlocation이 가리키는 Vertex가 있는 경우
					{
						before->link = tlocation->link;	//before의 link가 tlocation의 link가 가리키는 Vertex를 가리키게 한다
						free(tlocation); //tlocation을 동적 해제 한다
						break;
					}
				}
			}
		}
	}

	return;
}

void depthFS(Graph* aGraph, int v)	//깊이 우선 탐색이다
{
	Vertex* w;
	Svisited[v] = TRUE;	//우선 기준 값인 v에 대해 visited flag를 표기한다
	Push(v);	//표기 한 후에 v의 값을 스택에 push한다
	printf("%d",v);	//값을 출력한다
	while(StackTop != -1)	//스택이 비어있지 않으면 반복한다.
	{
			w = aGraph->vlist[v].head;	//처음에 w는 vlist[v]에서 시작한다
			while(w) //w가 NULL이 아니라면
			{
				if(Svisited[w->num] == 0)	//게다가 Svisited에 w->num에 해당하는 곳에 visit flag가 없다면
				{
					Push(w->num);	//stack에 w->num을 push하고
					Svisited[w->num] = 1; //visit flag를 표기한다
					printf("->%d", w->num);	//해당 값을 표기하고
					v = w->num;	//v를 w->num의 값으로 바꿔준다.
					w = aGraph->vlist[v].head; //w도 위치가 바뀐 vlist[v].head로 이동시켜준다
				}
				else w = w->link; // visit flag가 1이라면 w를 옮겨주고
			}
			v = Pop();	//옮겨도 옮겨도 찾을 수 없다면 스택에서 값을 pop
	}
	return;
}

void breadthFS(Graph* aGraph, int v) //너비 우선 탐색이다
{
	Vertex* w;
	LQ *q;
	q = createLinkedQ();
	Qvisited[v] = TRUE;	//Qvisited[v]의 값을 TRUE로 바꿔준다
	printf("%d", v);	//해당 v값을 출력 한 후
	enQueue(q,v);	//q에 v를 집어 넣는다.

	while(!isEmpty(q))	//queue가 비었지 않았다면
	{
		v=deQueue(q); //queue에서 값을 꺼내서 v에 저장한다.
		for(w=aGraph->vlist[v].head; w; w = w->link)	//꺼내진 v의 값을 통해서  vlist[v]에 있는 모든 Vertex에 접근한다
		{
			if(Qvisited[w->num] == FALSE) //만약 Qvisited[w->num]에 visit flag가 없는 경우
			{
				Qvisited[w->num] = TRUE;	//방문했다는 visit flag를 입력하고
				printf("%5d", w->num);	//w->num의 값을 출력한 뒤에
				enQueue(q, w->num); //w->num의 값을 queue에 집어 넣는다.
			}//그 다음에는 vlist[v]상의 남은 Vertex의 값에 대해서 반복문이 실행될 것이다.
		}	//vlist[v]상의 모든 Vertex에 대해서 enQueue를 했다면 처음에 넣었던 값을 DeQueue로 빼고 뺀 값으로 vlist[값]에 접근하서 반복한다.
	}
	return;
}

void printGraph(Graph* aGraph)
{
	//만약 createGraph를 하거나 destroyGraph를 하고나서 바로 출력하면 아무 값도 나오지 않는다
	int a,chek;
	chek = checkempty();
	/*if(aGraph->vlist == NULL && chek == 0)
	{
		printf("그래프 정보가 없습니다.\n");
		return;
	}*/
	if(chek == 0) //만약 vlist가 동적할당만 되고 활성화 되지 않았다면 출력할 것이 없고, 즉 count는 0이다
	{
		printf("출력할 것이 아무 것도 없습니다.\n");
		return;
	}

	// 그 외의 경우

	for(a=0; a<MAX_VERTEX; a++)	//최대 크기인 MAX_VERTEX만큼 접근한다
	{
		Vertex* location = aGraph->vlist[a].head;	//vlist[a]에 연결된 모든 Vertex에  접근 할 것이다
		if(location != NULL)	//location이 NULL이 아닌 경우
		{
			printf("Vertex [%d] 와 연결된 정점 : ", a);
			while(location != NULL)
			{
				printf("%d ",location->num);	//location에 저장된 값을 출력하고
				location = location->link;		//location의 위치를 옮긴다
			}
			printf("\n");
		}
		else
		{
			if(visited[a] == 1)	//만약 vlist[a]가 활성화 되었는데 연결된 Vertex가 없다면
			{
				printf("Vertex [%d] 와 연결된 정점 : ", a);
				printf("아무런 값도 없습니다.\n");	//linked list로 연결된 것이 아무것도 없다.
			}
		}
	}
	return;
}

void Push(int x)	//dfs와 관련해서 stack에 Push하는 것
{
	StackTop++;	//StackTop에 1을 더해준다. 처음엔 -1을 가리키므로, 1을 더한 0의 자리에 저장한다
	DFStack[StackTop] = x;
}

int Pop() //Stack에  있는 값을 꺼내는 것!
{
	if (StackTop == -1)	//만약 top이 -1을 가리키면 스택은 빈 상황이다!
	{
		printf("Stack is empty!\n");
		return 0;
	}
	return DFStack[StackTop--]; //Pop을 하면 top에 있는 값을 받아오고, top의 값은 -1이 이루어진다.
}

int isEmpty(LQ *lq)
{
	if(lq->front == NULL)	//lq->front가 NULL이면 비었다는 것을 1을 리턴해서 알 수 있다
	{
		//printf("Queue is empty!\n");
		return 1;
	}
	else
		return 0;	//그 외의 경우는 0을 리턴
}

void enQueue(LQ *lq, int key)
{
	QNode *newNode = (QNode*)malloc(sizeof(QNode));
	newNode->data = key;
	newNode->link = NULL;

	if(lq->front == NULL)	//만약 lq에 연결된 값이 없는 경우
	{
		lq->front = newNode;	//front가 newNode를 가리킨다. front가 newNode를 가리키는 이유는 deQueue에서 확인 가능
		lq->rear = newNode;	//rear도 newone를 가리킨다
	}
	else	//만약 front에 값이 있으면
	{
		lq->rear->link = newNode; //우선 rear->link가 newNode를 가리키고
		lq->rear = newNode;	//rear의 위치를 옮긴다
	}

}

int deQueue(LQ *lq)
{
	QNode *location = lq->front;	//front의 값을 빼야하니 location으로 위치를 잡는다
	int key;
	if(isEmpty(lq))	//만약 queue가 비었으면 값을 뺄 수 없음
		return 0;
	else //비지 않았다면
	{
		key = location->data;	//location의 값을 key에 저장
		lq->front = lq->front->link;	//값을 삭제하면 front는 1 증가하기에  front의 위치를 옮겨준다
		if(lq->front == NULL)	//만약 옮긴 front가 NULL이라면, 더 이상 가리킬게 없다는 뜻이다. 이게 마지막 값이라는 의미
			lq->rear = NULL;	//rear가 NULL을 가리키게한다
		free(location);	//그리고 location을 동적 해제 하고
		return key;	//key값을 반환한다.
	}
}
