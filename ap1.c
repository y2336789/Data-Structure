/*
 * ap1.c
 *
 *  Created on: 2020. 4. 6.
 *      Author: young
 */
#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("[----양영재 2017038068----]\n");
    int list[5];
    int *plist[5] = {NULL,}; //int형 포인터를 담는 길이가 5인 배열을 NULL로 전부다 초기화


    plist[0] = (int *)malloc(sizeof(int));        //heap에 int형으로 동적배열 할당. 크기는 4바이트이다.

    list[0] = 1;
    list[1] = 100;

    *plist[0] = 200;    //동적할당된 heap 메모리에 200을 저장

    printf("value of list[0] = %d\n", list[0]);    //저장된 값 1이 출력
    printf("address of list[0] = %p\n", &list[0]);    //배열의 이름 list와 같은 의미.
    printf("value of list = %p\n", list);    //배열의 이름은 주소와 같다. 이는 list[0]의 주소와도 같은 말이다.
    printf("address of list (&list) = %p\n", &list);

    printf("-------------------------------------\n\n");
    printf("value of list[1] = %d\n", list[1]);    //저장된 값 100이 출력
    printf("address of list[1] = %p\n", &list[1]);    //list[1]의 주소 값을 출력
    printf("value of *(list+1) = %d\n", *(list+1));    //list[1]에 저장된 값, 100을 출력한다.
    printf("address of list+1 = %p\n", list+1);    //list[1]의 주소, list는 int형 배열이니 list+1를 하면 sizeof(int)= 4바이트가 옮겨진다.
    printf("-------------------------------------\n\n");

    printf("value of *plist[0] = %d\n", *plist[0]);    //저장된 값 200 출력
    printf("&plist[0] = %p\n", &plist[0]);    //plist[0]의 주소는 plist와 같다. 시작주소이다.
    printf("&plist = %p\n", &plist);    //위와 동일한 원리
    printf("plist = %p\n", plist);        //&plist[0] = &plist = plist 값은 모두 같다.
    printf("plist[0] = %p\n", plist[0]);    // heap영역에 동적할당된 메모리의 주소값이 출력된다.
    printf("plist[1] = %p\n", plist[1]);    //초기화를 하지 않았으니 null을 출력, 가다지고 있는 값이 없음. 밑의 나머지 3줄도 동일하다.
    printf("plist[2] = %p\n", plist[2]);
    printf("plist[3] = %p\n", plist[3]);
    printf("plist[4] = %p\n", plist[4]);

    free(plist[0]);    //동적할당된 메모리를 free 함수를 호출함으로 소멸시킨
}
