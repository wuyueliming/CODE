#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>




//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                              //十以内加减乘除
#if 0
#define MAXSIZE 100
int compare(char in, char top) {//比较优先级
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
    char transform[MAXSIZE];
    int t_top = -1; // 将中缀转换成后缀
    
    int arr[50];
    int a = 0;
    
    //转化成后缀表达式
    char nifix[50];//存原始输入
    char nifix_copy[50];
    scanf("%s", nifix);
    int len_ni = strlen(nifix);
    for (int i = 0; nifix[i] != '\0'; i++) {
        nifix_copy[i] = nifix[i];
    }
    nifix_copy[len_ni] = '\0';

    char* token = strtok(nifix_copy, "+-*/");
    while (token != NULL) {
        arr[a++] = atoi(token);
        token= strtok(NULL, "+-*/");
    }
    a = 0;

    
    char postfix[50];
    int j = 0;//postfix的下标

    int may_fu = 1;//1表示后面可能是一个负数（开头和左括号后面可能是一个负数）
    int isFirst = 1;//讨论第一个是否为负号
    int isNum = 0;


    for (int i = 0; i < len_ni; i++) {
        if (nifix[i] - '0' >= 0 && nifix[i] - '0' <= 9) {//如果是一个数字
            if (isNum) {
                continue;
            }
            else {
                postfix[j] = nifix[i];
                j++;
            }
            isNum = 1;
        }
        else {//如果是一个符号
            isNum = 0;
            if (may_fu && nifix[i] == '-') {//如果可能是负数
                postfix[j] = '0';//在-号前面加上一个0，用0-2来代替-2。
                j++;
                if (nifix[i] == '(') {//剩余的和不可能是负数的一样
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
                    if (transform[t_top] != '(') {//如果不是'('就放入postfix
                        may_fu = 1;
                        postfix[j] = transform[t_top];
                        t_top--;
                        j++;
                        i--;//for循环一轮就i++，这里i--让下一次进来还是指向nifix的')'，直到transform遇到'('。
                    }
                    else {//如果是'('就直接丢掉
                        t_top--;
                    }
                }
                else if (nifix[i] == '(') {
                    t_top++;
                    transform[t_top] = nifix[i];
                    may_fu = 1;
                }
                else {//不是(,也不是)。
                    if (t_top == -1) {//如果top没有符号就直接放入栈中
                        t_top++;
                        transform[t_top] = nifix[i];
                    }
                    else if (!compare(nifix[i], transform[t_top]) || t_top == -1) {//如果优先级高于top的符号
                        t_top++;
                        transform[t_top] = nifix[i];
                    }
                    else {//如果优先级小于等于top：弹出top的符号
                        if (t_top == -1) {
                            continue;
                        }
                        postfix[j] = transform[t_top];
                        t_top--;
                        j++;
                        i--; //让下一次进来还是指向nifix的这个运算符
                    }
                }
            }
        }
        if (isFirst && nifix[i] != '(') {//
            isFirst--;//这个--的后缀不能直接放在if中，不然就算isFirst不是真也会减一。
            may_fu = 0;
        }
    }
        
    
    while (t_top != -1) {//把剩下的运算符放到postfix里面
        postfix[j++] = transform[t_top];
        t_top--;
    }
    for (int i = 0; i < j; i++) {//看一看nifix转化后的postfix
        printf("%c", postfix[i]);
    }
    printf("\n");

    
    
    //计算后缀表达式
    int  calculate[MAXSIZE];//运算后缀表达式的栈
    int c_top = -1;
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
            calculate[++c_top] = postfix[i] - '0';               
        }
    }
    printf("%d", calculate[0]);
    return 0;
}

#endif
//升级想法：
//一、postfix要换成二维数组，因为一个数字可能不止一位数
//二、第169行把字符串转换成数字用atoi函数
//三、is_num判断上一个字符是否为数字，如果是就让变量j指回上一个，把那个数字更改，然后再让j指向下一个






//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                 //十位数以内加减乘除



//#define MAXSIZE 100                 
//#define MAXdigit_num 10
//int compare(char in, char top) {
//    if ((in == '*' || in == '/') && (top == '+' || top == '-')) {
//        return 0;
//    }
//    else if ((top == '*' || top == '/') && (in == '+' || in == '-')) {
//        return 1;
//    }
//    else if (top == '(') {
//        return 0;
//    }
//    else {
//        return 1;
//    }
//}
//int main()
//{
//    int  calculate[MAXSIZE];
//    int c_top = -1;
//    char transform[MAXSIZE];
//    int t_top = -1;
//    
//    
//    char nifix[50];
//    scanf("%s", nifix);
//    int len_ni = strlen(nifix);
//    
//
//    char** postfix = (char**)malloc(sizeof(char*) * MAXdigit_num);//10是数字的最大位数
//    for (int i = 0; i < 25; i++) {
//        postfix[i] = (char*)malloc(sizeof(char) * 50);//最多50个加减乘除、数字、括号
//    }
//
//
//    int j = 0;//postfix的下标
//    int may_fu = 1;//1表示后面可能是一个负数
//    int isFirst = 1;//讨论表达式的第一个字符是否为-号
//    int is_num = 0;
//    for (int i = 0; i < len_ni; i++) {
//        if (nifix[i] - '0' >= 0 && nifix[i] - '0' <= 9) {//如果是一个数字
//            if (is_num) {
//                j--;
//                int temp = 0;
//                if (strlen(postfix[j]) == 1) {
//                    temp = (int)(postfix[j] - '0') * 10 + (nifix[i] - '0');
//                }
//                else {
//                    temp = atoi(postfix[j]) * 10 + (nifix[i] - '0');        
//                }
//                char TEMP[MAXdigit_num];
//                sprintf(TEMP, "%d", temp);
//                strcpy(postfix[j], TEMP);
//                j++;
//            }
//            else {//如果上一个字符不是数字
//                postfix[j] = nifix[i];
//                j++;
//            }
//        }
//        else {//如果是运算符
//            is_num = 0;
//            if (may_fu && nifix[i] == '-') {//如果可能是负数
//                postfix[j] = '0';
//                j++;
//                if (nifix[i] == '(') {
//                    t_top++;
//                    transform[t_top] = nifix[i];
//                    may_fu = 1;
//                }
//                else {
//                    if (t_top == -1) {
//                        t_top++;
//                        transform[t_top] = nifix[i];
//                    }
//                    else if (!compare(nifix[i], transform[t_top]) || t_top == -1) {
//                        t_top++;
//                        transform[t_top] = nifix[i];
//                    }
//                    else {
//                        if (t_top == -1) {
//                            continue;
//                        }
//                        postfix[j] = transform[t_top];
//                        t_top--;
//                        j++;
//                        i--;
//                    }
//                }
//                may_fu = 0;
//            }
//            else {//如果不可能是负数
//                if (nifix[i] == ')') {
//                    if (transform[t_top] != '(') {
//                        may_fu = 1;
//                        postfix[j] = transform[t_top];
//                        t_top--;
//                        j++;
//                        i--;
//                    }
//                    else {
//                        t_top--;
//                    }
//                }
//                else if (nifix[i] == '(') {
//                    t_top++;
//                    transform[t_top] = nifix[i];
//                    may_fu = 1;
//                }
//                else {
//                    if (t_top == -1) {
//                        t_top++;
//                        transform[t_top] = nifix[i];
//                    }
//                    else if (!compare(nifix[i], transform[t_top]) || t_top == -1) {
//                        t_top++;
//                        transform[t_top] = nifix[i];
//                    }
//                    else {
//                        if (t_top == -1) {
//                            continue;
//                        }
//                        postfix[j] = transform[t_top];
//                        t_top--;
//                        j++;
//                        i--;
//                    }
//                }
//            }
//        }
//        if (isFirst && nifix[i] != '(') {
//            isFirst--;
//            may_fu = 0;
//        }
//    }
//
//    while (t_top != -1) {//剩余的运算符放入postfix中
//        postfix[j++] = transform[t_top];
//        t_top--;
//    }
//
//    for (int i = 0; i < j; i++) {//看看后缀表达式
//        printf("%c", postfix[i]);
//    }
//    printf("\n");
//
//    //计算后缀表达式
//    int left = 0;
//    int right = 0;
//    for (int i = 0; i < j; i++) {
//        if (postfix[i] == '+') {
//            right = calculate[c_top--];
//            left = calculate[c_top--];
//            calculate[++c_top] = left + right;
//        }
//        else if (postfix[i] == '*') {
//            right = calculate[c_top--];
//            left = calculate[c_top--];
//            calculate[++c_top] = left * right;
//        }
//        else if (postfix[i] == '-') {
//            right = calculate[c_top--];
//            left = calculate[c_top--];
//            calculate[++c_top] = left - right;
//        }
//        else if (postfix[i] == '/') {
//            right = calculate[c_top--];
//            left = calculate[c_top--];
//            calculate[++c_top] = left / right;
//        }
//        else {
//            if (strlen(postfix[i]) == 1) {
//                calculate[++c_top] = (postfix[i]) - '0';
//            }
//            else {
//                calculate[++c_top] = atoi(postfix[i]);
//            }
//        }
//    }
//    printf("%d", calculate[0]);
//   
//    return 0;
//}





















































#if 1
#define MAXdigit 100                  //    <<《《《====-----原本是10，现在改成100就没问题了！！！！！！！！
#define MAXSIZE 100
int compare(char in, char top) {//比较优先级
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
void string_in(char** postfix, char* transform, int j, int t_top) {
    if (transform[t_top] == '+') {
        postfix[j] = "+\0";
    }
    else if (transform[t_top] == '-') {
        postfix[j] = "-\0";
    }
    else if (transform[t_top] == '*') {
        postfix[j] = "*\0";
    }
    else if (transform[t_top] == '/') {
        postfix[j] = "/\0";
    }
    else if (transform[t_top] == '(') {
        postfix[j] = "(\0";
    }
    else if (transform[t_top] == ')') {
        postfix[j] = ")\0";
    }
}


int main()
{
    char transform[MAXSIZE];
    int t_top = -1; // 将中缀转换成后缀

    int arr[MAXSIZE];
    int a = 0;

    //转化成后缀表达式
    char nifix[MAXSIZE];//存原始输入
    char nifix_copy[MAXSIZE];
    scanf("%s", nifix);//       -21/((1+1)*2-1)+42/21-125/25
    int len_ni = strlen(nifix);
    for (int i = 0; nifix[i] != '\0'; i++) {
        nifix_copy[i] = nifix[i];
    }
    nifix_copy[len_ni] = '\0';

    char* token = strtok(nifix_copy, "(+-*/)");
    while (token != NULL) {
        arr[a++] = atoi(token);//21  1   1   2   1   42  21  125  25   
        printf("%d\t", arr[a - 1]);
        token = strtok(NULL, "(+-*/)");
    }
    printf("\n");
    a = 0;


    char** postfix = (char**)malloc(sizeof(char*) * MAXSIZE);//二级指针中第一次申请的是行数，对应postfix后面的第一个中括号。
    for (int i = 0; i < MAXSIZE; i++) {
        postfix[i] = (char*)malloc(sizeof(char) * MAXdigit);//每一行都申请MAXSIZE列，对应postfix后面的第二个中括号。
    }
    int j = 0;//postfix的下标

    
    int may_fu = 1;//1表示后面可能是一个负数（开头和左括号后面可能是一个负数）
    int isFirst = 1;//讨论第一个是否为负号
    int isNum = 0;


    for (int i = 0; i < len_ni; i++) {
        if (nifix[i] - '0' >= 0 && nifix[i] - '0' <= 9) {//如果是一个数字
            may_fu = 0;
            if (isNum) {
                continue;
            }
            else {
                sprintf(postfix[j], "%d", arr[a++]);//我真的是无语了，同一个式子，前面用这个函数用的好好的，现在数字是42就不行了。
                printf("%s ", postfix[j]);
                j++;
            }
            isNum = 1;
        }
        else {//如果是一个符号
            isNum = 0;
            if (may_fu && nifix[i] == '-') {//如果可能是负数
                strcpy(postfix[j], "0\0");//在-号前面加上一个0，用0-2来代替-2。
                printf("%s ", postfix[j]);
                j++;
                if (nifix[i] == '(') {//剩余的和不可能是负数的一样
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
                        //postfix[j] = transform[t_top];
                        string_in(postfix, transform, j, t_top);
                        printf("%s ", postfix[j]);
                        t_top--;
                        j++;
                        i--;
                    }
                }
                may_fu = 0;
            }
            else {//如果不可能是负数
                if (nifix[i] == ')') {
                    if (transform[t_top] != '(') {//如果不是'('就放入postfix
                        
                        //postfix[j] = transform[t_top];
                        string_in(postfix, transform, j, t_top);
                        printf("%s ", postfix[j]);
                        t_top--;
                        j++;
                        i--;//for循环一轮就i++，这里i--让下一次进来还是指向nifix的')'，直到transform遇到'('。
                    }
                    else {//如果是'('就直接丢掉
                        t_top--;
                    }
                }
                else if (nifix[i] == '(') {
                    t_top++;
                    transform[t_top] = nifix[i];
                    may_fu = 1;
                }
                else {//不是(,也不是)。
                    if (t_top == -1) {//如果top没有符号就直接放入栈中
                        t_top++;
                        transform[t_top] = nifix[i];
                    }
                    else if (!compare(nifix[i], transform[t_top]) || t_top == -1) {//如果优先级高于top的符号
                        t_top++;
                        transform[t_top] = nifix[i];
                    }
                    else {//如果优先级小于等于top：弹出top的符号
                        if (t_top == -1) {
                            continue;
                        }
                        //postfix[j] = transform[t_top];
                        string_in(postfix, transform, j, t_top);
                        printf("%s ", postfix[j]);
                        t_top--;
                        j++;
                        i--; //让下一次进来还是指向nifix的这个运算符
                    }
                }
            }
        }
        if (isFirst && nifix[i] != '(') {//
            isFirst--;//这个--的后缀不能直接放在if中，不然就算isFirst不是真也会减一。
            may_fu = 0;
        }
    }
    while (t_top != -1) {//把剩下的运算符放到postfix里面
        //postfix[j++] = transform[t_top];
        string_in(postfix, transform, j, t_top);
        printf("%s ", postfix[j]);
        j++;
        t_top--;
    }

    printf("\n");
    for (int i = 0; i < j; i++) {//看一看nifix转化后的postfix
        printf("%s\t", postfix[i]);
    }
    printf("\n***********************************\n");



    //计算后缀表达式
    int  calculate[MAXSIZE];//运算后缀表达式的栈
    int c_top = -1;
    int left = 0;
    int right = 0;
    for (int i = 0; i < j; i++) {
        if (strchr(postfix[i], '+')) {
            right = calculate[c_top--];
            left = calculate[c_top--];
            calculate[++c_top] = left + right;
        }
        else if (strchr(postfix[i], '*')) {
            right = calculate[c_top--];
            left = calculate[c_top--];
            calculate[++c_top] = left * right;
        }
        else if (strchr(postfix[i], '-')) {
            right = calculate[c_top--];
            left = calculate[c_top--];
            calculate[++c_top] = left - right;
        }
        else if (strchr(postfix[i],'/')) {
            right = calculate[c_top--];
            left = calculate[c_top--];
            calculate[++c_top] = left / right;
        }
        else {
            calculate[++c_top] = atoi(postfix[i]);
        }
    }
    printf("reslut=%d", calculate[0]);
    return 0;
}
#endif



#if 0
int main()
{
    //char arr[10];
    ////sprintf(arr, "%d", 1234);
    //strcpy(arr, "0\0");
    //printf("%s", arr);


    int ** transform = (int**)malloc(sizeof(int*) * 12);
    for (int i = 0; i < 12; i++) {
        transform[i] = (int*)malloc(sizeof(int) * 9);
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 12; j++) {
            transform[i][j] = i * j;
            printf("%3d", transform[i][j]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < 12; i++) {
        free(transform[i]);
    }
    free(transform);



    return 0;
}
#endif