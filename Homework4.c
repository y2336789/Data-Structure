/*
 * howework4.c
 *
 *  Created on: 2020. 4. 10.
 *      Author: young
 */
#include <stdio.h>
#include <stdlib.h>	//랜덤으로 난수 생성에 필요한 srand 함수를 쓰기위해 선언.
#include <time.h>		//실행시간에 따라서 난수 생성이 달라지기 때문에 선언.

int** create_matrix(int row, int col);		//사용자가 입력한 row와 col만큼 행렬을 동적할당하여 생성해 주는 함수.
int fill_data(int **matrix, int row, int col);	//생성된 행렬안에 값을 채워주는 함수.
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col);	//행렬a와 행렬b를 더해주는 함수.
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col);	//행렬a와 행렬b를 뺄셈 계산하는 함수.
void print_matrix(int** matrix, int row, int col);	//함수를 출력해주는 함수
int transpose_matrix(int **matrix, int **matrix_t, int row, int col);	//첫번째 매개변수로 전달된 행렬의 전치행렬을 만들어 주는 함수.
int multiply_matrix(int **matrix_a, int** matrix_t, int **matrix_axt, int row, int col);	//첫번째 매개변수로 전달된 행렬과 그 행렬의 전치함수를 곱하는 함수.
int free_matrix(int **matrix, int row, int col); //동적 할당한 배열을 해제하는 함수
void check_wrong(int num);	//int를 반환하는 함수들의 오류 값을 판단하는 함수.


int main(void)
{
	srand((unsigned)time(NULL));	//실행 시간에 따라서 난수를 생성할 때 값이 달라지도록 함. 이를 메인에 선언함으로 다른 함수에 또 선언할 필요가 없음.
	int a,b = 0;
	int** matrixA = 0; int** matrixB = 0; int** summatrix =0; int** submatrix =0; int** T_matrixA=0; int** mulmatrix=0;
	printf("[ ----- 양영재  2017038068 -----]\n");

	printf("행과 열을 입력하시오 (입력 예시 : 3 4 ) : ");
	scanf("%d %d", &a,&b);
	matrixA = create_matrix(a,b);	// int형 이중포인터를 반환 하니 그에 맞는 matrixA로 값을 받고 있다.
	matrixB = create_matrix(a,b);	// 위와 마찬가지로, 이들이 받는 값은 동적할당된 메모리에 대한 주소 값을 받는 것이다.
	if(matrixA == NULL && matrixB == NULL){ //만약에 create_matrix 함수에서 오류가 발생하면 프로그램을 종료.
		printf("행과 열의 크기를 확인하시오!\n");
		return 0;
	}
	check_wrong(fill_data(matrixA,a,b)); //랜덤으로 행렬에 값을 채운다. 값의 범위는 0~19 사이. 반환형이 int이지만, int를 반환해서 전달 받는 값이 구현에 큰 의미가 없기에 이와 같이 호출하였음.
	check_wrong(fill_data(matrixB,a,b));	//메인 함수에 srand((unsigned)time(NULL)) 을 선언함으로 매번 값이 달라짐.

	printf("A 행렬 입니다.\n");
	print_matrix(matrixA,a,b); printf("\n");

	printf("B 행렬 입니다.\n");
	print_matrix(matrixB,a,b); printf("\n");

	summatrix = create_matrix(a,b);		//두 행렬을 더할 행렬을 저장할 행렬을 동적 할당 한다.
	check_wrong(addition_matrix(matrixA, matrixB, summatrix, a, b)); //matrixA와 matrixB를 더한 후에 summartrix에 저장한다.

	printf("두 행렬을 더한 행렬입니다.\n");
	print_matrix(summatrix,a,b); printf("\n");	//더한 행렬의 값을 출력.

	submatrix = create_matrix(a,b);		//두 행렬을 뺄 행렬을 저장할 행렬을 동적 할당 한다.
	check_wrong(subtraction_matrix(matrixA, matrixB, submatrix, a, b)); //matrixA와 matrixB에 저장된 값들을 뺀 후 submatrix에 저장한다.

	printf("두 행렬을 뺀 행렬입니다.\n");
	print_matrix(submatrix,a,b); printf("\n");	//뺀 행렬의 값들을 출력.

	T_matrixA = create_matrix(b,a);		//행렬A의 전치행렬을 저장하기 위해서 동적 할당 해준다. 전치 행렬이니 b,a 의 순서로 전달한다.
	check_wrong(transpose_matrix(matrixA, T_matrixA, a,b));	//행렬A의 전치행렬 의 값을 T_matrixA에 저장.

	printf("A행렬의 전치행렬입니다.\n");
	print_matrix(T_matrixA,b,a); printf("\n");	//b행 a열이니까 b,a로 전달.
	mulmatrix = create_matrix(a,a);		//전치행렬과 행렬A를 곱할 행렬을 동적 할당 한다. 크기는 a*a이니 a,a를 써준다.
	check_wrong(multiply_matrix(matrixA, T_matrixA, mulmatrix, a, b));	//행렬A와 전치행렬을 곱한다.
	printf("첫번째 행렬과 전치행렬을 곱한 행렬입니다.\n");
	print_matrix(mulmatrix,a,a); printf("\n");

	check_wrong(free_matrix(matrixA,a,b));	//각각 동적 할당한 행렬들을 free 선언을 해줌으로써 메모리를 반환한다.
	check_wrong(free_matrix(matrixB,a,b));
	check_wrong(free_matrix(summatrix,a,b));
	check_wrong(free_matrix(submatrix,a,b));
	check_wrong(free_matrix(T_matrixA,b,a));
	check_wrong(free_matrix(mulmatrix,a,a));	//동적 할당한 모든 행렬들에 대해 free를 해줘야 한다.

}

int** create_matrix(int row, int col) {

		int **x;	//2차원 배열의 정보를 저장하기 위해서 이중포인터 형식으로 선언.
		if(row<=0 || col<=0)		//만약에 main 함수에서 행과 열에 대한 값을 0이하로 입력을 하였으면
		{
			return NULL;	//NULL을 반환하게 되고, 만약에 반환이 되었다면 31행에 의해 프로그램이 종료된다.
		}
		x = (int **)malloc(sizeof(int*) * row);	//x에는 row의 수만큼 동적할당을 해주는데, 여기에는 각 row에 해당되는 column의 값들이 저장되는 동적 할당된 배열의 주소가 담겨있다.
		//또 x에는 주소의 값이 저장이 되니까 sizeof(int *)로 해줘야 한다. 배열의 세로
		for(int a=0;a<row;a++)	//row만큼의 배열을 할당해야하므로
			x[a]=(int *)malloc(sizeof(int)*col);		//x[a]는 이중 포인터가 아닌 싱글 포인터의 형태이므로 이에 맞게 동적할당을 하고, 이에는 정수의 값이 저장되기에 sizeof(int)를 써준다. 배열의 가로
		return x;	//그리고 해당 이중포인터의 주소를 리턴한다.
}

int fill_data(int **matrix, int row, int col) {

	for(int a=0; a<row; a++)		//해당 배열에 모든 곳에 값을 넣어줘야 하니 이중 반복문을 이용한다. row번 반복
		for(int b=0; b<col; b++)		//col번 반복.
			matrix[a][b] = rand()%20;	//rand()를 쓰면 난수가 생성하는데 이를 20으로 나눠서 남는 나머지들을 출력하게 되면, 여기서는 0~19까지의 숫자들이 출력된다.
	if(matrix == NULL)	//matrix가 주소가 없다면, 동적할당이 되지 않았다면 오류발생.
			return -1;		//-1을 반환한다
	else
		return 1;	//정상 처리되었으므로 1을 반환.
}

int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col)		//매개변수로 전달받는 matrix_a와 matrix_b 를 더해주는 함수, 그 결과를 matrix_sum에 저장
{
	for(int a=0; a<row; a++)
		for(int b=0; b<col; b++)
			matrix_sum[a][b] = matrix_a[a][b] + matrix_b[a][b];	//call by reference 형식으로 선언되었기 때문에 이 함수내에서 계산이 이루어져도, main 함수에도 이 결과가 유지된다.
	if(matrix_sum == NULL)
			return -1;
	else
		return 1;	//정상 처리되었으므로 1을 반환.
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col) //매개변수로 전달받는 matrix_a와 matrix_b 를 빼주는 함수, 그 결과를 matrix_sub에 저장
{
	for(int a=0; a<row; a++)
			for(int b=0; b<col; b++)
				matrix_sub[a][b] = matrix_a[a][b] - matrix_b[a][b];	//matrix_a의 a행 b열의 값과 matrix_b의 a행 b열의 값을 빼준 값을 matrix_sub[a][b]에 저장한다.
	if(matrix_sub == NULL)
			return -1;
	return 1;	//정상 처리되었으므로 1을 반환.
}
void print_matrix(int** matrix, int row, int col)	//해당 matrix에 저장된 값을 출력해주는 함수.
{
	for(int a=0; a<row; a++){
		for(int b=0; b<col; b++)
			printf("\t[%d] ", matrix[a][b]);	//각각의 row와 col에 접근하여 값을 출력해준다.
		printf("\n");
	}	//리턴형이 void이기 때문에 리턴값이 없음.
}

int transpose_matrix(int **matrix, int **matrix_t, int row, int col)	//matrix의 전치행렬을 matrix_t에 저장하는 함수.
{
	for(int a=0; a<row; a++)
		for(int b=0; b<col; b++)
			matrix_t[b][a] = matrix[a][b];	//call by reference의 형태로 매개변수로 전달된 T_matrixA에 값이 저장된다. 전치행렬이므로 matrix[a][b] 값은 matrix[b][a]에 저장된다.
	if(matrix_t == NULL)
			return -1;
	else
		return 1; //정상 처리되었으므로 1을 반환.
}

int multiply_matrix(int **matrix_a, int** matrix_t, int **matrix_axt, int row, int col)	//matrix_a와 해당 행렬의 전치행렬인 matrix_t의 값을 곱한 뒤에 matrix_axt에 저장하는 함수.
{
	int sum;	 //matrix_a의 a행에서 column 값들과 과 matrix_t의 b열의 row값들을 곱한 값을 저장하는 sum
	for(int a=0; a<row; a++){
		for(int b=0; b<row; b++){	//곱해서 생기는 행렬이 a x a행렬이니 b의 값을 여기선 a와 같게 설정해준다.
			sum=0;
			for(int c=0;c<col;c++){
				sum += matrix_a[a][c] * matrix_t[c][b];	//전치행렬을 곱하는 것이니까 행과 열을 바꿔준 후 계산
			}
			matrix_axt[a][b] = sum;	//이 행렬의 크기는 a x a의 크기이므로 a,b를 씀.
		}
	}
	if(matrix_axt == NULL)
		return -1;
	else
		return 1; //정상 처리될 때 1을 반환.
}
int free_matrix(int **matrix, int row, int col)	//동적할당된 2차원 배열을 free선언함으로 메모리를 반환한다.
{
	for(int a = 0; a<row; a++)
		free(matrix[a]);	//col의 값이 저장된 동적 할당 배열들에 대해서 먼저 free함수를 사용 한 후에
	free(matrix);	//그 배열들의 주소를 담고있는 matrix에 대해서 한번 더 free를 사용한다.

	if(matrix==NULL)
		return -1;
	else
		return 1;
}
void check_wrong(int num)	//대부분의 함수에서 int값을 반환하면
{
	if(num == -1){	//매개변수로 -1을 받고
		fputs("오류발생!! 프로그램 종료합니다.\n", stderr); 	//오류 발생 메세지 출력후
		exit(1);	//프로그램 종료
	}
}
