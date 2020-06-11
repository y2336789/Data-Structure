/*
 * hw11-sorting-hasing.c
 *
 *  Created on: 2020. 6. 5.
 *      Author: y2j
 */

/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;	//값들을 저장할 리스트를 array 포인터를 사용하여 작성한다.
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {	//만약 a에 저장된 값이 null이라면
		printf("nothing to print.\n");	//아무런 값도 할당되있지 않은 것이다.
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)	//만약 값이 저장되어있다면
		printf("a[%02d] ", i); // a[위치] : 저장된 값 과 같은 형식으로 출력을 하게 된다.
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)  //삽입 정렬에 대한 코드이다.
{
	int min; //가장 작은 값을 저장할 int형 변수 int
	int minindex; //가장 작은 값의 위치를 저장할 int형 변수 minindex
	int i, j; //반복문 안에서 횟수를 정할 int형 변수 i,j

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //리스트에 저장된 값을 출력한다. (정렬되기 전의 값)

	for (i = 0; i < MAX_ARRAY_SIZE; i++) //반복문은 리스트의 사이즈, 즉 13번 실행된다.
	{
		minindex = i; //for문이 반복 때 마다 최소값을 가리키는 위치가 바뀐다.
		min = a[i]; //최소값을 리스트 a에서 i번째에 저장된 값으로 정한다.
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)	//비교할 대상은 그 다음 값부터 비교하면 된다.
		{
			if (min > a[j])	//만약 최소값으로 정한 값보다 a리스트의 j번째 원소의 값이 더 크다면
			{
				min = a[j];	//최소값을 j번째 원소의 값으로 바꾼다.
				minindex = j;	//최소값을 가리키는 위치의 값도 j로 바꾼다, 가장 작은 원소로 한 번 바꾼후 for문을 돌게 된다.
			}	//만약에 min < a[j]이면 반복문을 다시 돈다.
		}
		a[minindex] = a[i];	//만약에 이중 for문 안에서 안의 for문을 다 돌았는데 값의 변경이 없는 경우에는, 지금 선택된 값이 정렬이 이뤄지지 않은 리스트에서 가장 작은 값을 의미한다.
		a[i] = min; //그러면 현재 선택된 값을 위치의 변경없이 현 위치로 정렬시킨다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬된 후의 리스트에 저장된 값들을 출력한다.
	return 0;
}

int insertionSort(int *a) //삽입 정렬에 관한 코드이다
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬되기 전의 리스트를 출력한다.
	//삽입 정렬은 정렬된 앞부분의 원소들과 정렬되지 않은 원소들로 나누어서 정렬을 실시한다.
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{	//삽입 정렬을 처음 하면 맨 처음의 원소는 정렬된 것으로 생각한다. 즉 a[0]번은 미리 정렬된 상태이다.
		t = a[i]; //t에 a[i]에 위치한 값이 저장되고,
		j = i; //j는 위치를 가리키는 용도로 사용된다.
		while (a[j-1] > t && j > 0) //만약 a[i]에 위치한 값보다 그 전의 값이 큰 경우와 j가 0보다 큰 경우, 즉 a[0]이후의 값 들을 비교 할 때
		{
			a[j] = a[j-1]; //a[j-1]의 값이 t값보다 더 크기에 a[j-1]의 값이 뒤로 가야한다.
			j--; //그리고 j에 1을 빼서 j의 위치를 옮겨준다.
		}
		a[j] = t; //그러면 앞에 있었던 값이 뒤로 가게 되고, 처음 값을 저장한 t를 이용하여 a[j]에 t를 넣어주어서 저장을 한다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬된 리스트를 새로 출력한다.

	return 0;
}

int bubbleSort(int *a)	//버블 정렬에 관한 코드이다.
{	//버블 정렬은 반복문을 한 번 돌게 되면 최대 값이 리스트의 맨 마지막으로 이동하는 방식이다.
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);	//정렬되기 전의 리스트 값을 출력한다.

	for(i = 0; i < MAX_ARRAY_SIZE; i++)	//안의 for문을 총 MAX_ARRAY_SIZE만큼 반복시켜주는 for문
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)	//두 개의 값을 비교해서 값을 바꿔주는 for문
		{
			if (a[j-1] > a[j]) //처음 실행되면 건너뛰게 된다. 만약 a[j-1]의 값이 a[j]보다 클 경우에
			{
				t = a[j-1]; //만약 비교하고자 하는 값 보다 앞에 있는 값이 더 클 경우에
				a[j-1] = a[j];	//그 둘의 위치를 바꿔주는데
				a[j] = t;	//이 경우를 끝까지 반복하기 때문에 한 번 반복문을 실행하게 되면
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);	//정렬된 리스트를 출력한다.

	return 0;
}

int shellSort(int *a) //쉘 정렬을 구현한 코드이다
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬되기 전의 리스트를 출력한다.

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)	//초기의 h값을 MAX_ARRAY_SIZE/2로 지정해주고, 반복문을 돌면 h값은 절반이 된다. 반복문을 도는 조건은 h가 0보다 클 경우이다.
	{
		for (i = 0; i < h; i++) //h가 전체사이즈 / 2 부터 시작하기에, i가 0 부터 h만큼 반복하여도 모든 값에 접근 가능하다
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)	//j는 i에서 h만큼 떨어진 값을 의미한다.
			{
				v = a[j];	//a[j]에 저장된 값을 v에 저장한다
				k = j;	// j의 위치를 k에 저장한다.
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



