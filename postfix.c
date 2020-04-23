/*
 * postfix.c
 *
 *  Created on: 2020. 4. 20.
 *      Author: young
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen이 가장 낮음 */
typedef enum{
    lparen,  /* ( 왼쪽 괄호 */
    rparen,  /* ) 오른쪽 괄호*/
    plus,   /* * 곱셈 */
    minus,  /* / 나눗셈 */
    times,    /* + 덧셈 */
    divide,   /* - 뺄셈 */
    operand /* 피연산자 */
} precedence;		//원래 저장되어 있던 우선순위를 삭제하고 추후에 isp와 icp를 통해서 우선순위를 가릴 예정이다


char infixExp[MAX_EXPRESSION_SIZE];       /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];    /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];    /* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];        /* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;       /* evalStack용 top */

int evalResult = 0;       /* 계산 결과를 저장 */


void postfixPush(char x)	//postfixStack에 값을 집어 넣는 함수
{
    postfixStack[++postfixStackTop] = x;	//값을 집어넣고 postfixStackTop 값을 1 늘린다
}

char postfixPop()	//스택에 Top에 저장된 값을 빼내는 함수, char형 데이터를 반환한다.
{
    char x;	//문자 하나를 저장할 변수 x를 선언하였다
    if(postfixStackTop == -1)	//top이 -1 일 경우, 즉 스택에 값이 없는 경우
        return '\0';	//널을 반환하고 함수 종료
    else {
        x = postfixStack[postfixStackTop--];	//x에 스택의 top에 있었던 문자가 저장된다
    }
    return x;	//x를 반환한다
}


void evalPush(int x)	//계산을 담당하는 evalStack에 값을 집어넣는 함수
{
    evalStack[++evalStackTop] = x;	//값을 집어 넣은 뒤에 evalStackTop의 값을 1 증가 시킨다
}

int evalPop()	//계산 담당 스택의 top에 있는 값을 빼내는 함수
{
    if(evalStackTop == -1)	//top이 -1이면 값이 없는 것이다
        return -1;
    else
        return evalStack[evalStackTop--];	//스택에서 값을 빼고 top을 -1 한다.
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);    //우리가 흔히 아는 수식 입력, 중위 연산자를 입력하여 infixExp 배열에 저장한다.
}

precedence getToken(char symbol)	//symbol에 저장된 값을 precedence와 비교하는 함수이다
{
    switch(symbol) {		//각각의 문자와 같을 경우와 피연산자일 경우로 나뉘어서 값들을 반환한다.
    case '(' : return lparen;
    case ')' : return rparen;
    case '+' : return plus;
    case '-' : return minus;
    case '/' : return divide;
    case '*' : return times;
    default : return operand;
    }

}

precedence getPriority(char x)
{
    return getToken(x);	//GetToken함수를 함수 내에서 실행하고 있다.
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)	//c의 값을 postfixExp 배열에 저장하는 함수이다.
{
    if (postfixExp == '\0')	//처음 입력되는 경우
        strncpy(postfixExp, c, 1);	//c를 postfixExp에 1개 저장하는 것이다.
    else
        strncat(postfixExp, c, 1);	//위와 일치
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	static int isp[]={0,19,12,12,13,13,0};	//스택 내애서의 우선 순위
	static int icp[]={20,19,12,12,13,13,0};	//스택으로 들어올 값의 우선순위
    char *exp = infixExp;    // infixExp의 문자 하나씩을 읽기위한 포인터
    char x,y,z; //

    while(*exp != '\0')	//값 하나가 널이 아닐 경우
    {
    	 x=*exp;	//exp에 저장된 값을 x에 저장하고있다
        if(getPriority(x)==operand)	//x가 피연산자일 경우
         {
        	charCat(&x);	//스택에 보내지 않고 변환되는 과정의 배열 postfixExp에 저장한다.
         }
        else//피연산자가 아닌경우
         {
        	if(getPriority(x)== lparen)	//'('일 경우
        	{
        		postfixPush(x);	//바로 push해서 stack에 집어넣는다.
        	}
        	else if(getPriority(x)== rparen)	//')'일 경우
        	{
        		while(getPriority(postfixStack[postfixStackTop]) != lparen)	//top에 있는 값이 '(' 아니면 계속 뺀다
        		{
        			y=postfixPop();	//pop해서 꺼낸 값을 y에 저장
        			charCat(&y);	//y의 값을 postfixExp에 저장
        		}postfixPop();	// ')일 경우 pop한다.
        	}
        	else	//나머지 연산자들에 대해서(+, -, *, /)
			{
        		if(postfixStackTop == -1)	//만약 연산자에 상관없이 스택에 값이 저장되있지 않은 경우(lparen으로 시작하지 않는 식)
        		{
        			postfixPush(x);	//연산자를 push해서 스택에 저장한다.
        		}
        		else	//만약에 스택에 값이 저장되있는 상태이면
        		{
        			if(isp[getPriority(postfixStack[postfixStackTop])] >= icp[getPriority(x)])	//스택에 저장되있는 값과 들어올 값의 우선순위를 비교한다.
        			{		//스택에 있는 연산자의 우선순위가 들어올 연산자의 우선순위보다 크거나 같은 경우에는 저장되어있던 연산자를 팝한다.
        			 y=postfixPop();	//pop을 호출하여 값을 y에 저장
        			 charCat(&y);	//y를 postfixExp에 저장한다
        			 postfixPush(x);	//그리고 push해서 x를 스택에 저장한다.
        			}
        			else
        				postfixPush(x);	//들어올 연산자의 우선순위가 높은 경우이므로 x를 스택에 바로 저장한다.
        		}
			}
         }
        exp++;	//exp를 1더해줌으로 다음 글자를 가르킨다.
    }
   while(postfixStackTop != -1)	//반복문이 다 끝났는데 만약 스택이 채워진 상태라면 pop을 하고 postfixExp에 넣어준다
    {
    	z=postfixPop();
    	charCat(&z);
    }
}




void debug()	//원래 중위 표기의 식과 후위 표기의 식, 그리고 계산된 값, 그리고 스택에 저장된 문자를 출력한다
{
    printf("\n---DEBUG\n");
    printf("infixExp =  %s\n", infixExp);
    printf("postExp =  %s\n", postfixExp);
    printf("eval result = %d\n", evalResult);

    printf("postfixStack : ");
    for(int i = 0; i < MAX_STACK_SIZE; i++)
        printf("%c  ", postfixStack[i]);

    printf("\n");

}

void reset()	//저장되어 있는 모든 값을 reset한다.
{
    infixExp[0] = '\0';
    postfixExp[0] = '\0';

    for(int i = 0; i < MAX_STACK_SIZE; i++){
        postfixStack[i] = '\0';
        postfixExp[i]='\0';

    }
    postfixStackTop = -1;
    evalStackTop = -1;
    evalResult = 0;
}

void evaluation()	//후위 연산자로 바뀐 식을 계산하는 프로그램
{
    /* postfixExp, evalStack을 이용한 계산 */
	char *exp = postfixExp;	//후위 연산자로 바꿔주는 함수와 동일하게 postfixExp에서 문자 하나를 받는 char형 포인터 exp 선언
	char x,y;
	int oper1, oper2;	//피연산자 두 개의 값을 저장할 변수 두개 선언

	while(*exp != '\0')	//문자 하나가 널이 아닐 경우
	{
		x=getToken(*exp);
		if(x == operand)	//x가 피연산자일 경우
		{
			y = *exp - '0';	//char으로 저장된 숫자를 -'0'을 해줌으로써 정수로 저장한다.
			evalPush(y);	//바뀐 값을 계산에 사용되는 evalStack에 저장한다
		}
		else
		{
			oper2 = evalPop();	//만약에 evalStack에 저장될 값이 연산자이면 그 전에 저장된 두 개의 정수를 가각에 받아주고 있다.
			oper1 = evalPop();
			switch(x)	//그래서 x가 무슨 연산자이냐에 따라서 switch문을 돌려준다.
			{		//여기서 연산자에 따라서 계산을 다르게 한 뒤에 stack에 저장하는데 이 저장된 값을 또 pop하고 밑에 있던 값을 pop해서 마지막에는 최종 값을 얻을 수 있다
			case plus:		//받아들일 문자가 +일 경우
				evalPush(oper1 + oper2);//두 정수의 값을 더해 준 뒤에 그 값을 evalStack에 저장
				break;
			case minus:	//받아들일 문자가 -일 경우
				evalPush(oper1 - oper2);	//두 정수의 값을 빼 준 뒤에 그 값을 evalStack에 저장
				break;
			case times:	//받아들일 문자가 *일 경우
				evalPush(oper1 * oper2);	//두 정수의 값을 곱해 준 뒤에 그 값을 evalStack에 저장
				break;
			case divide:	//받아들일 문자가 /일 경우
				evalPush(oper1 / oper2);	//두 정수의 값을 나눠 준 뒤에 그 값을 evalStack에 저장
				break;
			}
		}
		exp++;	//다음 문자를 가르키기 위해서 ++한다.
	}
	 evalResult = evalPop();	//최종 나온 값을 result에 저장한다.
}


int main()
{
    char command;

    do{
        printf("----------------------------------------------------------------\n");
        printf("               Infix to Postfix, then Evaluation               \n");
        printf("----------------------------------------------------------------\n");
        printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'i': case 'I':
            getInfix();
            break;
        case 'p': case 'P':
            toPostfix();
            break;
        case 'e': case 'E':
            evaluation();
            break;
        case 'd': case 'D':
            debug();
            break;
        case 'r': case 'R':
            reset();
            break;
        case 'q': case 'Q':
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 0;
}
