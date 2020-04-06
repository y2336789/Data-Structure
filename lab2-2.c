/*
 * lab2-2.c
 *
 *  Created on: 2020. 4. 1.
 *      Author: young
 */
#include <stdio.h>
int main(void)
{
    int i;
    int *ptr;
    int **dptr;

    i = 1234;

    printf("--------- 소프트웨어학과 2017038068 양영재 ---------\n\n");

    printf("[checking values before ptr = &i] \n");
    printf("value of i == %d\n", i);
    printf("address of i == %p\n", &i);        //변수 i의 주소값
    printf("value of ptr == %p\n", ptr);        // 초기화하지 않았기 때문에 쓰레기 값 출력
    printf("address of ptr == %p\n", &ptr);    //위와 동일, 쓰레기 값

    ptr = &i;    //ptr에 i의 주소를 저장

    printf("\n[checking values after ptr = &i] \n");
    printf("value of i == %d\n", i);            //i의 값은 변동이 없음
    printf("address of i == %p\n",&i);
    printf("value of ptr == %p\n", ptr);        //ptr에 i의 주소를 저장했기 때문에 i의 주소가 출력
    printf("address of ptr == %p\n", &ptr);    //원래 ptr의 주소를 출력
    printf("value of *ptr == %d\n", *ptr);        //ptr이 가르키는 곳, 즉 i가 가지고 있는 값을 출력, 1234가 출력

    dptr = &ptr;    //dptr에 ptr의 주소를 저장

    printf("\n[checking values after dptr = &ptr] \n");
        printf("value of i == %d\n", i);
        printf("address of i == %p\n",&i);
        printf("value of ptr == %p\n", ptr);
        printf("address of ptr == %p\n", &ptr);
        printf("value of *ptr == %d\n", *ptr);
        printf("value of dptr == %p\n", dptr);            //dptr이 가지고 있는 값 = ptr의 주소
        printf("address of dptr == %p\n", &dptr);        //초기화 하지 않았으니 쓰레기 값이 출력
        printf("value of *dptr == %p\n", *dptr);        //dptr이 ptr의 주소를 가지고 있으니 ptr이 가지고 있는 값을 출력한다.
        printf("value of **dptr == %d\n", **dptr);    //ptr이 가르키는 i의 값을 출력

        *ptr = 7777;    //i를 7777로 바꾼다.

        printf("\n[after *ptr = 7777] \n");
        printf("value of i == %d\n", i);
        printf("value of *ptr == %d\n", *ptr);            //i가 7777로 바뀌었으니 포인터로 접근하여 출력하여도 값이 동일
        printf("value of **dptr == %d\n", **dptr);    //위와 동일

        **dptr = 8888;    //i를 8888로 바꾼다

        printf("\n[after **dptr = 8888] \n");
        printf("value of i == %d\n", i);
        printf("value of *ptr == %d\n", *ptr);
        printf("value of **dptr == %d\n", **dptr);

        return 0;
}
 
