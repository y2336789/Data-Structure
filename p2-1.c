/*
 * p2-1.c
 *
 *  Created on: 2020. 4. 6.
 *      Author: young
 */
#include <stdio.h>
#define MAX_SIZE 100    //MAX_SIZE는 100이다.

float sum(float [], int);
float input[MAX_SIZE], answer;
int i;
void main(void)
{
    printf("[----양영재 2017038068 ----]\n");
    for(i=0;i<MAX_SIZE;i++)    //반복문 100번 실행, i가 99까지 일때 실행
        input[i] = i; //input[0]=0 저장, input 배열 i번째에 i가 저장된다. i는 반복문 안에서 1씩 증가.

    printf("address of input = %p\n", input); //input의 시작 주소 출력.
    answer = sum(input, MAX_SIZE);
    printf("The sum is : %f\n", answer); //1부터 99까지 더한 값을 출력.
}

float sum(float list[], int n)    //input의 주소를 list가 받고 있다.
{
    printf("value of list = %p\n", list);    //그래서 list를 출력하면 input의 주소가 출력.
    printf("address of list = %p\n\n", &list);    //list 자체의 주소는 따로 출력된다.

     int i;
     float tempsum = 0;
     for(i=0; i<n; i++)
         tempsum += list[i]; //i는 MAX_SIZE 미만 까지 즉 99까지 유효하고 100이되면 for문을 탈출한다.
     return tempsum;    //1부터 99까지 더한다.
}
 
