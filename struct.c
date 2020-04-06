/*
 * struct.c
 *
 *  Created on: 2020. 4. 6.
 *      Author: young
 */
#include <stdio.h>

struct student1 {            //typedef 선언이 없기 때문에 후에 student1 구조체를 사용할 때에는 struct를 써줘야 한다.
    char lastName;
    int studentId;
    char grade;
};

typedef struct {            //typedef 선언이 있으므로, student2 구조체를 사용할 때에는 struct가 없어도 가능하다.
    char lastName;
    int studentId;
    char grade;
} student2;

int main() {
    printf("[---- 양영재 2017038068 ----]\n");

    struct student1 st1 = {'A', 100, 'A'};        //typedef 선언을 하지 않았기 때문에 struct 선언을 해줘야 한다. 구조체 임을 알려주는 역할

    printf("st1.lastName = %c\n", st1.lastName);
    printf("st1.studentId = %d\n", st1.studentId);
    printf("st1.grade = %c\n", st1.grade);

    student2 st2 = {'B', 200, 'B'};            //typedef 선언을 하였기 때문에 이와 같이 쓸 수 잇음.

    printf("\nst2.lastName = %c\n", st2.lastName);
    printf("st2.studentId = %d\n", st2.studentId);
    printf("st2.grade = %c\n", st2.grade);

    student2 st3;

    st3 = st2;        //구조 치환이 이루어 진다. st3의 값들이 st2의 lastName, studentId, grade 값들과 같아진다

    printf("\nst3.lastName = %c\n", st3.lastName);
    printf("st3.studentId = %d\n", st3.studentId);
    printf("st3.grade = %c\n", st3.grade);

    return 0;
} 
