# Tutorial-Chungbuk
for the Tutorial
/*
 * lab2-1.c
 *
 *  Created on: 2020. 4. 1.
 *      Author: young
 */
#include <stdio.h>
int main(void)
{
    char charType;
    int integerType;
    float floatType;
    double doubleType;

    printf("--------- 소프트웨어학과 2017038068 양영재 ---------\n");

    printf("Size of char : %ld byte\n", sizeof(charType));            //자료형인 char인 변수 charType의 크기 - 1
    printf("Size of int : %ld bytes\n", sizeof(integerType));        //자료형인 int인 변수 intType의 크기 - 4
    printf("Size of float : %ld bytes\n",sizeof(floatType));        //자료형인 float인 변수 floatType의 크기 - 4
    printf("Size of double : %ld bytes\n", sizeof(doubleType));        //자료형인 double인 변수 doubeType의 크기 - 8

    printf("------------------------------------------\n");

    printf("Size of char : %ld byte\n", sizeof(char));                //자료형 char의 크기 - 1
    printf("Size of int : %ld bytes\n", sizeof(int));                //자료형 int의 크기 - 4
    printf("Size of float : %ld bytes\n", sizeof(float));            //자료형 float의 크기 - 4
    printf("Size of double : %ld bytes\n", sizeof(double));            //자료형 double의 크기 - 8

    printf("------------------------------------------\n");

    printf("Size of char* : %ld byte\n", sizeof(char*));                //포인터 변수의 크기는 자료형과 관계없이 8바이트다.
        printf("Size of int* : %ld bytes\n", sizeof(int*));            //32비트는 4바이트로, 64비트는 8바이트로 나온다.
        printf("Size of float* : %ld bytes\n", sizeof(float*));        //64비트 컴퓨터를 사용 중이므로 8바이트가 나온다.
        printf("Size of double* : %ld bytes\n", sizeof(double*));

        return 0;
}
