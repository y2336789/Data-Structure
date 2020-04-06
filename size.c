/*
 * size.c
 *
 *  Created on: 2020. 4. 6.
 *      Author: young
 */
#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("[-----양영재 2017038068----]\n");
    int **x;

    printf("sizeof(x) = %lu\n", sizeof(x));    //x가 이중포인터기 때문에 x자체가 가지고 있는 값은 주소이다. 그러므로 8바이트
    printf("sizeof(*x) = %lu\n", sizeof(*x));    //x가 가지고 있는 값이 *x의 주소이다. *x도 가지고 있는 값이 주소이기 때문에 8바이트이다.
    printf("sizeof(**x) = %lu\n", sizeof(**x)); //**x를 하면 *x의 주소에 담겨있는 값을 출력하는데 값의 자료형이 int형이므로 4바이트.

}
 
