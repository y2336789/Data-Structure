/*
 * p2-2.c
 *
 *  Created on: 2020. 4. 7.
 *      Author: young
 */
#include <stdio.h>

void print1 (int *ptr, int rows);    //첫번 째 매개변수는 int형 포인터를 받는다. 주소를 받는 것이다. 두번째 매개변수는 몇 줄을 출력할 것인지.

int main()
{
    printf("[----양영재 2017038068----]\n");
    int one[] = {0,1,2,3,4};    //one은 길이가 5인 int형 변수를 받는 배열

    printf("one = %p\n", one);    //one의 시작주소, 이는 &one, &one[0]과 같은 의미이다.
    printf("&one = %p\n", &one);
    printf("&one[0] = %p\n", &one[0]);
    printf("\n");

    print1(&one[0],5);    //one의 시작주소를 넘겨주고, 줄 수는 5줄

    return 0;
}

void print1(int *ptr, int rows)
{
    int i;
    printf("Address \t Contents\n");
    for(i=0; i<rows; i++)    //i는 0부터 시작해 4까지 반복문을 돌고, 5가 되면 반복문을 나온다.
        printf("%p \t %5d\n", ptr + i, *(ptr + i));    //ptr+i식으로 시작주소에서 sizeof(int) * i만큼 더해진다. 값은 ptr[i]의 값을 출력.
    printf("\n");
} 
