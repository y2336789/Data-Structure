/*
 * ap2.c
 *
 *  Created on: 2020. 4. 6.
 *      Author: young
 */
#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("[----양영재 2017038068 ----]\n");
    int list[5];    //int형 변수를 저장하는 길이가 5인 배열 list
    int *plist[5];    //int형 포인터를 저장하는 길이가 5인 배열 plist

    list[0] = 10;
    list[1] = 11;

    plist[0] = (int*)malloc(sizeof(int));    //plist[0]에 저장되는 값은 heap에 동적할당 된 메모리의 주소값이다.

    printf("list[0] \t= %d\n", list[0]);    //list[0]에 저장된 값 10이 출력
    printf("address of list \t= %p\n", list);    //list, &list[0], list+0 의 주소는 모두 같은 의미이다.
    printf("address of list[0] \t= %p\n", &list[0]);
    printf("address of list + 0 \t= %p\n", list+0);
    printf("address of list + 1 \t= %p\n", list+1);    //list의 주소에서 sizeof(int)만큼 더해진 주소 값 출력, 이는 &list[1]과 같다.
    printf("address of list + 2 \t= %p\n", list+2);    //sizeof(int) * 2만큼 더해짐, &list[2]와 동일
    printf("address of list + 3 \t= %p\n", list+3);    //sizeof(int) * 3만큼 더해짐, &list[3]과 동일하다
    printf("address of list + 4 \t= %p\n", list+4);    //sizeof(int) * 4만큼 더해짐, &list[4]와 동일
    printf("address of list[4] \t= %p\n", &list[4]);    //위와 동일한 값 출력

    free(plist[0]);    //free 함수로 동적할당 된 메모리를 소멸시킨다.
}
