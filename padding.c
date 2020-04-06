/*
 * padding.c
 *
 *  Created on: 2020. 4. 6.
 *      Author: young
 */
#include <stdio.h>

struct student {
    char lastName[13];    //sizeof(char) = 1바이트, 1*13 = 13바이트
    int studentId;        //4바이트
    short grade;            //2바이트
};

int main()
{
    printf("[----양영재 2017038068----]\n");
    struct student pst; //typedef를 안해주었기 때문에 struct를 써준다.

    printf("size of student = %ld\n", sizeof(struct student));    //4바이트의 배수만큼 계산된다. lastName같은 경우에는 12바이트하고 1바이트이나, 패딩이 이루어져서 3바이트가 더 채워짐.
    printf("size of int = %ld\n", sizeof(int));        //int는 4바이트 이므로 4의 배수니까 변화 없음.
    printf("size of short = %ld\n", sizeof(short));    //short는 2바이트 이므로 4의 배수까지 2바이트가 모자라니 2바이트가 패딩으로 채워진다.

    return 0;
}
