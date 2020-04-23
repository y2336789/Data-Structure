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

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
    lparen,  /* ( 왼쪽 괄호 */
    rparen,  /* ) 오른쪽 괄호*/
    plus,   /* * 곱셈 */
    minus,  /* / 나눗셈 */
    times,    /* + 덧셈 */
    divide,   /* - 뺄셈 */
    operand /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];       /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];    /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];    /* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];        /* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;       /* evalStack용 top */

int evalResult = 0;       /* 계산 결과를 저장 */


void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
        x = postfixStack[postfixStackTop--];
    }
    return x;
}


void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);    //우리가 흔히 아는 수식 입력
}

precedence getToken(char symbol)
{
    switch(symbol) {
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
    return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
    if (postfixExp == '\0')
        strncpy(postfixExp, c, 1);
    else
        strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	static int isp[]={0,19,12,12,13,13,0};
	static int icp[]={20,19,12,12,13,13,0};
    char *exp = infixExp;    // infixExp의 문자 하나씩을 읽기위한 포인터
    char x,y,z; //

    while(*exp != '\0')
    {
    	 x=*exp;
        if(getPriority(x)==operand)
         {
        	charCat(&x);
         }
        else//피연산자가 아닌경우
         {
        	/*if(getPriority(x)== lparen)	//'('일 경우
        	{
        		postfixPush(x);
        	}
        	else*/ if(getPriority(x)== rparen)	//')'일 경우
        	{
        		while(getPriority(postfixStack[postfixStackTop]) != lparen)	//top에 있는 값이 '(' 아니면 계속 뺀다
        		{
        			y=postfixPop();
        			charCat(&y);
        		}postfixPop();	// ')일 경우 pop한다.
        	}
        	else	//나머지 연산자들에 대해서
			{
        		if(postfixStackTop == -1)
        		{
        			postfixPush(x);
        		}
        		else
        		{
        			if(isp[getPriority(postfixStack[postfixStackTop])] >= icp[getPriority(x)])
        			{
        			 y=postfixPop();
        			 charCat(&y);
        			 postfixPush(x);
        			}
        			else
        				postfixPush(x);
        		}
			}
         }
        exp++;
    }
   while(postfixStackTop != -1)
    {
    	z=postfixPop();
    	charCat(&z);
    }
}




void debug()
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

void reset()
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

void evaluation()
{
    /* postfixExp, evalStack을 이용한 계산 */
	char *exp = postfixExp;
	char x,y;
	int oper1, oper2;

	while(*exp != '\0')
	{
		x=getToken(*exp);
		if(x == operand)
		{
			y = *exp - '0';
			evalPush(y);
		}
		else
		{
			oper2 = evalPop();
			oper1 = evalPop();
			switch(x)
			{
			case plus:
				evalPush(oper1 + oper2);
				break;
			case minus:
				evalPush(oper1 - oper2);
				break;
			case times:
				evalPush(oper1 * oper2);
				break;
			case divide:
				evalPush(oper1 / oper2);
				break;
			}
		}
		exp++;
	}
	 evalResult = evalPop();
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
