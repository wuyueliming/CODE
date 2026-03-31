#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>          栈         >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

                                                                    //顺序存储结构
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#if 0
#define OK 1
#define Error 0
#define MAXSIZE 100
typedef int status;
typedef int Elementtype;

typedef struct {
    Elementtype arr[MAXSIZE];
    int top;
} STACK;

STACK init(void);
status push(STACK* stack,int num);
status pop(STACK* stack,int* num);

int main()
{
    STACK stack = init();                                             //单栈



    return 0;
}

STACK init(void) {
    STACK stack;
    stack.top = -1;

    return stack;
}
status push(STACK* stack, int num) {
    if (stack->top == MAXSIZE - 1) {
        return Error;
    }
    stack->top++;
    stack->arr[stack->top] = num;
    return OK;
}
status pop(STACK* stack, int* num) {
    if (stack->top == -1) {
        return Error;
    }
    *num = stack->arr[stack->top];
    stack->top--;
    return OK;
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#if 0
#define OK 1
#define Error 0
#define MAXSIZE 100
typedef int status;
typedef int Elementtype;

typedef struct {
    Elementtype arr[MAXSIZE];
    int top1;
    int top2;
} STACK;

STACK init(void);
status push(STACK* stack, int num,int stacknum);
status pop(STACK* stack, int* num, int stacknum);

int main()
{
    STACK stack = init();                                        //双栈



    return 0;
}

STACK init(void) {
    STACK stack;
    stack.top1 = -1;
    stack.top2 = MAXSIZE;
    return stack;
}
status push(STACK* stack, int num, int stacknum) {
    if (stack->top1 + 1 == stack->top2) {
        return Error;
    }
    if (stacknum == 1) {
        stack->top1++;
        stack->arr[stack->top1] = num;
    }
    else if (stacknum == 2) {
        stack->top2--;
        stack->arr[stack->top2] = num;
    }
    return OK;
}
status pop(STACK* stack, int* num, int stacknum) {
    if (stacknum == 1) {
        if (stack->top1 == -1){
            return Error;
        }
        *num=stack->arr[stack->top1];
        stack->top1--;
    }
    else if (stacknum == 2) {
        if (stack->top2 == MAXSIZE) {
            return Error;
        }
        *num=stack->arr[stack->top2];
        stack->top2++;
    }
    return OK;
}

#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                    //链式存储结构
/*

                                                          单链表，以表头做栈顶(不需要头节点)
    typedef struct _NODE{
        int data;
        struct _NODE* next;
    } NODE;

    typedef struct {
        NODE* top;//头指针
        int cnt;
    } STACK;

*/






//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                             //斐波那契数列——使用栈实现了递归



//int fibo(int num) {
//    if (num == 0) {
//        return 0;
//    }else if (num == 1) {
//        return 1;
//    }
//    else {
//        return fibo(num - 1) + fibo(num - 2);
//    }
//
//}
//
//
//int main()
//{
//    int arr[10] = { 0 };
//    for (int i = 1; i < 10; i++) {
//        arr[i] = fibo(i);
//        printf("%d ", arr[i]);
//    }
//   
//    return 0;
//}


                                                              //牛客上的某一题

//#include <stdio.h>
//#include<string.h>
//#define OK 1
//#define ERROR 0
//#define MAXSIZE 100000
//typedef int status;
//typedef struct {
//    int arr[MAXSIZE];
//    int top;
//} STACK;
//
//status push(STACK* stack, int num);
//status pop(STACK* stack, int* num);
//status top(STACK* stack, int* num);
//
//int main() {
//    STACK stack;
//    stack.top = -1;
//    int thetop;
//    char judge[10];
//    int  data = 0;
//
//
//    int n = 0;
//    scanf("%d", &n);
//    for (int i = 0; i < n; i++) {
//        scanf("%s", judge);
//        if (strcmp(judge, "push") == 0) {
//            scanf("%d", &data);
//            push(&stack, data);
//        }
//        else if (strcmp(judge, "pop" == 0)) {
//            if (pop(&stack, &thetop) == OK) {
//                printf("%d\n", thetop);
//            }
//            else {
//                printf("error\n");
//            }
//        }
//        else if (strcmp(judge, "top") == 0) {
//            if (top(&stack, &thetop) == OK) {
//                printf("%d\n", thetop);
//            }
//            else {
//                printf("error\n");
//            }
//        }
//
//    }
//    return 0;
//}
//
//status push(STACK* stack, int num) {
//    if (stack->top == MAXSIZE - 1) {
//        return ERROR;
//    }
//    //stack->top += 1;
//    stack->arr[++stack->top] = num;
//    return OK;
//}
//status pop(STACK* stack, int* num) {
//    if (stack->top == -1) {
//        return ERROR;
//    }
//    *num = stack->arr[stack->top--];
//    return OK;
//}
//status top(STACK* stack, int* num) {
//    if (stack->top == -1) {
//        return ERROR;
//    }
//    *num = stack->arr[stack->top];
//    return OK;
//}





#if 0
#define MAXSIZE 100
int compare(char in, char top) {
    if ((in == '*' || in == '/')&& (top == '+' || top == '-')) {
        return 0;
    }
    else if ((top == '*' || top == '/') && (in == '+' || in == '-')) {
        return 1;
    }
    else if(top == '('){
        return 0;
    }
    else {
        return 1;
    }
}
int main()
{
    int  calculate[MAXSIZE];//运算后缀表达式
    int c_top = -1;
    char transform[MAXSIZE];//将中缀转换成后缀
    int t_top = -1;

    //转化成后缀表达式
    char nifix[50];
    scanf("%s", nifix);//          6-((-2+4)*5)
    int len_ni = strlen(nifix);//  62-4+5*->>>>602-4+5*-(6和2中间的0不见了,试了好多式子，大概在左括号的下一个就是-号就会问题)
    char postfix[50];
    int j = 0;
    int may_fu = 1;//1表示后面可能是一个负数
    int isFirst = 1;
    for (int i = 0; i < len_ni; i++) {
        if (nifix[i] - '0' >= 0 && nifix[i] - '0' <= 9) {
            postfix[j] = nifix[i];
            j++;
        }
        else {
            if (may_fu && nifix[i] == '-') {//如果可能是负数
                postfix[j] = '0';
                j++;
                if (nifix[i] == '(') {
                    t_top++;
                    transform[t_top] = nifix[i];
                    may_fu = 1;
                }
                else {
                    if (t_top == -1) {
                        t_top++;
                        transform[t_top] = nifix[i];
                    }
                    else if (!compare(nifix[i], transform[t_top]) || t_top == -1) {
                        t_top++;
                        transform[t_top] = nifix[i];
                    }
                    else {
                        if (t_top == -1) {
                            continue;
                        }
                        postfix[j] = transform[t_top];
                        t_top--;
                        j++;
                        i--;
                    }
                }
                may_fu = 0;
            }
            else {//如果不可能是负数
                if (nifix[i] == ')') {
                    if (transform[t_top] != '(') {
                        may_fu = 1;
                        postfix[j] = transform[t_top];
                        t_top--;
                        j++;
                        i--;
                    }
                    else {
                        t_top--;
                    }
                }
                else if (nifix[i] == '(') {
                    t_top++;
                    transform[t_top] = nifix[i];
                    may_fu = 1;
                }
                else {
                    if (t_top == -1) {
                        t_top++;
                        transform[t_top] = nifix[i];
                    }
                    else if (!compare(nifix[i], transform[t_top]) || t_top == -1) {
                        t_top++;
                        transform[t_top] = nifix[i];
                    }
                    else {
                        if (t_top == -1) {
                            continue;
                        }
                        postfix[j] = transform[t_top];
                        t_top--;
                        j++;
                        i--;
                    }
                }
            }
        }
        if (isFirst&&nifix[i]!='(') {//这个--的后缀不能直接放在if中，不然就算isFirst不是真（也就是isFirst为0）也会减一。
            isFirst--;
            may_fu = 0;
        }
    }
    while (t_top != -1) {
        postfix[j++] = transform[t_top];
        t_top--;
    }
    for (int i = 0; i < j; i++) {
        printf("%c", postfix[i]);
    }
    printf("\n");

    //计算后缀表达式
    int left = 0;
    int right = 0;
    for (int i = 0; i < j; i++) {
        if (postfix[i] == '+') {
            right = calculate[c_top--];
            left = calculate[c_top--];
            calculate[++c_top] = left + right;
        }
        else if (postfix[i] == '*') {
            right = calculate[c_top--];
            left = calculate[c_top--];
            calculate[++c_top] = left * right;
        }
        else if (postfix[i] == '-') {
            right = calculate[c_top--];
            left = calculate[c_top--];
            calculate[++c_top] = left - right;
        }
        else if (postfix[i] == '/') {
            right = calculate[c_top--];
            left = calculate[c_top--];
            calculate[++c_top] = left / right;
        }
        else {
            calculate[++c_top] = (postfix[i]) - '0';
        }
    }
    printf("%d", calculate[0]);
    return 0;
}
#endif






#if 0
#include <stdbool.h>
int ispair(char top, char cur) {
    if ((top == '(' && cur == ')') || (top == '[' && cur == ']') || (top == '{' && cur == '}')) {
        return 1;
    }
    else {
        return 0;
    }
}
bool isValid(char* s) {
    // write code here
    bool x = true;
    char arr[10000];
    int top = -1;
    int i;
    int pair = 0;
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            arr[++top] = s[i];
        }
        else {
            if (ispair(arr[top], s[i])) {
                top--;
                pair++;
            }
            else {
                x = false;
            }
        }
    }
    if (i % 2 == 1) {
        x = false;
    }
    else if (pair != i / 2) {
        x = false;
    }
    return x;
}
#endif









#if 0
int main() {
    char arr[300000];
    scanf("%s", arr);

    char stack[300000];
    int top = -1;

    for (int i = 0; arr[i] != '\0'; i++) {
        if (top == -1 || stack[top] != arr[i]) {
            stack[++top] = arr[i];
        }
        else if (stack[top] == arr[i]) {
            top++;
            top -= 2;
        }
    }


    if (top == -1) {
        printf("0");
    }
    else {
        for (int i = 0; i < top + 1; i++) {
            printf("%c", stack[i]);
        }

    }
    return 0;
}
#endif 



#if 0
bool IsPopOrder(int* pushV, int pushVLen, int* popV, int popVLen) {
    // write code here
    bool ret = false;
    int stack[1000];
    int top = -1;
    int confirm = 0;
    int x = 0;
    int y = 0;
    stack[++top] = pushV[x++];
    for (int i = 0; i < popVLen + pushVLen - 1; i++) {
        if (top == -1) {
            stack[++top] = pushV[x++];
        }
        else {
            if (stack[top] == popV[y]) {
                top--;
                y++;
                confirm++;
            }
            else {
                stack[++top] = pushV[x++];
            }
        }
    }
    if (y == popVLen) {
        ret = true;
    }
    if (confirm == popVLen) {
        ret = true;
    }
    return ret;
}
#endif 























































#if 1
#define MAXSIZE 100
#define MAXdigit_num 10
int compare(char in, char top) {
    if ((in == '*' || in == '/') && (top == '+' || top == '-')) {
        return 0;
    }
    else if ((top == '*' || top == '/') && (in == '+' || in == '-')) {
        return 1;
    }
    else if (top == '(') {
        return 0;
    }
    else {
        return 1;
    }
}
int main()
{
    int  calculate[MAXSIZE];//运算后缀表达式
    int c_top = -1;
    char transform[MAXSIZE];//将中缀转换成后缀
    int t_top = -1;
    int is_num = 0;
    //转化成后缀表达式
    char nifix[50];//存原始输入
    scanf("%s", nifix);
    int len_ni = strlen(nifix);
    //char postfix[50];
    char** postfix = (char**)malloc(sizeof(char*) * MAXdigit_num);//10是数字的最大位数
    for (int i = 0; i < 25; i++) {
        postfix[i] = (char*)malloc(sizeof(char) * 50);//最多50个加减乘除、数字、括号
    }
    int j = 0;//postfix的下标
    int may_fu = 1;//1表示后面可能是一个负数
    int isFirst = 1;//讨论表达式的第一个字符是否为-号
    for (int i = 0; i < len_ni; i++) {
        if (nifix[i] - '0' >= 0 && nifix[i] - '0' <= 9) {//如果是一个数字
            if (is_num) {//如果上一个字符是数字
                j--;
                int temp = 0;
                if (strlen(postfix[j]) == 1) {
                    temp=(int)(postfix[j] - '0')*10 + (nifix[i] - '0');  
                }
                else {
                    temp = atoi(postfix[j]) * 10 + (nifix[i] - '0');
                }
                char TEMP[MAXdigit_num];
                sprintf(TEMP, "%d", temp);
                strcpy(postfix[j], TEMP);
                j++;
            }
            else {//如果上一个字符不是数字
                postfix[j] = nifix[i];
                j++;
            }
        }
        else {//如果是运算符
            is_num = 0;
            if (may_fu && nifix[i] == '-') {//如果可能是负数
                postfix[j] = '0';
                j++;
                if (nifix[i] == '(') {
                    t_top++;
                    transform[t_top] = nifix[i];
                    may_fu = 1;
                }
                else {
                    if (t_top == -1) {
                        t_top++;
                        transform[t_top] = nifix[i];
                    }
                    else if (!compare(nifix[i], transform[t_top]) || t_top == -1) {
                        t_top++;
                        transform[t_top] = nifix[i];
                    }
                    else {
                        if (t_top == -1) {
                            continue;
                        }
                        postfix[j] = transform[t_top];
                        t_top--;
                        j++;
                        i--;
                    }
                }
                may_fu = 0;
            }
            else {//如果不可能是负数
                if (nifix[i] == ')') {
                    if (transform[t_top] != '(') {
                        may_fu = 1;
                        postfix[j] = transform[t_top];
                        t_top--;
                        j++;
                        i--;
                    }
                    else {
                        t_top--;
                    }
                }
                else if (nifix[i] == '(') {
                    t_top++;
                    transform[t_top] = nifix[i];
                    may_fu = 1;
                }
                else {
                    if (t_top == -1) {
                        t_top++;
                        transform[t_top] = nifix[i];
                    }
                    else if (!compare(nifix[i], transform[t_top]) || t_top == -1) {
                        t_top++;
                        transform[t_top] = nifix[i];
                    }
                    else {
                        if (t_top == -1) {
                            continue;
                        }
                        postfix[j] = transform[t_top];
                        t_top--;
                        j++;
                        i--;
                    }
                }
            }
        }
        if (isFirst && nifix[i] != '(') {//这个--的后缀不能直接放在if中，不然就算isFirst不是真也会减一。
            isFirst--;
            may_fu = 0;
        }
    }

    while (t_top != -1) {//剩余的运算符放入postfix中
        postfix[j++] = transform[t_top];
        t_top--;
    }
    
    for (int i = 0; i < j; i++) {//看看后缀表达式
        printf("%c", postfix[i]);
    }
    printf("\n");

    //计算后缀表达式
    int left = 0;
    int right = 0;
    for (int i = 0; i < j; i++) {
        if (postfix[i] == '+') {
            right = calculate[c_top--];
            left = calculate[c_top--];
            calculate[++c_top] = left + right;
        }
        else if (postfix[i] == '*') {
            right = calculate[c_top--];
            left = calculate[c_top--];
            calculate[++c_top] = left * right;
        }
        else if (postfix[i] == '-') {
            right = calculate[c_top--];
            left = calculate[c_top--];
            calculate[++c_top] = left - right;
        }
        else if (postfix[i] == '/') {
            right = calculate[c_top--];
            left = calculate[c_top--];
            calculate[++c_top] = left / right;
        }
        else {
            if (strlen(postfix[i]) == 1) {
                calculate[++c_top] = (postfix[i]) - '0';
            }
            else {
                calculate[++c_top] = atoi(postfix[i] );
            }
        }
    }
    printf("%d", calculate[0]);
    return 0;
}
#endif 





#if 0
int main()
{
    int col = 12;
    int row = 9;
    int** arr = (int**)malloc(sizeof(int*) * col);
    /*for (int i = 0; i < row; i++) {
        arr[i] = (int *)malloc(sizeof(int) * row);
        arr[i] = "hello";
        printf("%s\n", arr[i]);
    }*/
    
    char a = '8';
    int b = (a - '0')*10;
    printf("%d", b);

    //for (int i = 0; i < row; i++) {
    //    for (int j = 0; j < col; j++) {
    //        //arr[i][j] = i * j;
    //        printf("%d\t", arr[i][j]);
    //    }
    //    printf("\n");
    //}




    //char* postfix[50];
    



    return 0;
}
#endif







