#define _CRT_SECURE_NO_WARNINGS  1;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>       栈               >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                //模板栈
#if 0
#include <stdio.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 100000
typedef int status;
typedef struct {
    int arr[MAXSIZE];
    int top;
} STACK;

status push(STACK* stack, int num);
status pop(STACK* stack, int* num);
status top(STACK* stack, int* num);

int main() {
    STACK stack;
    stack.top = -1;
    int thetop;
    char judge[10];
    int  data = 0;


    int n = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", judge);
        if (strcmp(judge, "push") == 0) {
            scanf("%d", &data);
            push(&stack, data);
        }
        else if (strcmp(judge, "pop") == 0) {
            if (pop(&stack, &thetop) == OK) {
                printf("%d\n", thetop);
            }
            else {
                printf("error\n");
            }
        }
        else if (strcmp(judge, "top") == 0) {
            if (top(&stack, &thetop) == OK) {
                printf("%d\n", thetop);
            }
            else {
                printf("error\n");
            }
        }

    }
    return 0;
}

status push(STACK* stack, int num) {
    if (stack->top == MAXSIZE - 1) {
        return ERROR;
    }
    //stack->top += 1;
    stack->arr[++stack->top] = num;
    return OK;
}
status pop(STACK* stack, int* num) {
    if (stack->top == -1) {
        return ERROR;
    }
    *num = stack->arr[stack->top--];
    return OK;
}
status top(STACK* stack, int* num) {
    if (stack->top == -1) {
        return ERROR;
    }
    *num = stack->arr[stack->top];
    return OK;
}
#endif

                                                                //栈的压入弹出序列
#if 0
bool IsPopOrder(int* pushV, int pushVLen, int* popV, int popVLen) {
    // write code here
    bool ret = false;
    int x = 0, y = 0;
    int stack[pushVLen];
    int top = -1;
    for (int i = 0; i < pushVLen; i++) {
        stack[++top] = pushV[x++];
        while (top != -1 && y <= pushVLen && stack[top] == popV[y]) {
            top--;
            y++;
        }
    }


    if (y == pushVLen) {
        ret = true;
    }

    return ret;
}
#endif 



                                                                //有效括号序列
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

                                                                   //逆波兰求值
#if 0
#define OK 1
#define Error 0
#define MAXSIZE 10000
typedef int status;
typedef int  Elementtype;

typedef struct {
    Elementtype arr[MAXSIZE];
    int top;
} STACK;

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

int evalRPN(char** tokens, int tokensLen) {
    // write code here
    STACK stack;
    stack.top = -1;
    int left = 0;
    int right = 0;
    int temp = 0;
    for (int i = 0; i < tokensLen; i++) {
        if (strcmp(tokens[i], "+") == 0) {
            pop(&stack, &left);
            pop(&stack, &right);
            temp = right + left;
            push(&stack, temp);
        }
        else if (strcmp(tokens[i], "-") == 0) {
            pop(&stack, &left);
            pop(&stack, &right);
            temp = right - left;
            push(&stack, temp);
        }
        else if (strcmp(tokens[i], "*") == 0) {
            pop(&stack, &left);
            pop(&stack, &right);
            temp = left * right;
            push(&stack, temp);
        }
        else if (strcmp(tokens[i], "/") == 0) {
            pop(&stack, &left);
            pop(&stack, &right);
            temp = right / left;
            push(&stack, temp);
        }
        else {
            temp = atoi(tokens[i]);
            push(&stack, temp);
        }
    }
    return stack.arr[0];
}
#endif

                                                                 //点击消除
#if 0
#include <stdio.h>

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

                                                                    //表达式求值
#if 0
#define MAXdigit 200
#define MAXSIZE 200
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

int solve(char* s) {
    char transform[MAXSIZE];
    int t_top = -1; // 将中缀转换成后缀

    int arr[MAXSIZE];
    int a = 0;

    //转化成后缀表达式
        //char s[MAXSIZE];//存原始输入
    char s_copy[MAXSIZE];

    int len_ni = strlen(s);
    for (int i = 0; s[i] != '\0'; i++) {
        s_copy[i] = s[i];
    }
    s_copy[len_ni] = '\0';

    char* token = strtok(s_copy, "(+-*/)");
    while (token != NULL) {
        arr[a++] = atoi(token);//21  1   1   2   1   42  21  125  25
        token = strtok(NULL, "(+-*/)");
    }

    a = 0;


    char** postfix = (char**)malloc(sizeof(char*) * MAXSIZE);
    for (int i = 0; i < MAXSIZE; i++) {
        postfix[i] = (char*)malloc(sizeof(char) * MAXdigit);
    }
    int j = 0;//postfix的下标

    int may_fu =
        1;//1表示后面可能是一个负数（开头和左括号后面可能是一个负数）
    int isFirst = 1;//讨论第一个是否为负号
    int isNum = 0;


    for (int i = 0; i < len_ni; i++) {
        if (s[i] - '0' >= 0 && s[i] - '0' <= 9) {//如果是一个数字
            may_fu = 0;
            if (isNum) {
                continue;
            }
            else {
                sprintf(postfix[j], "%d", arr[a++]);
                j++;
            }
            isNum = 1;
        }
        else { //如果是一个符号
            isNum = 0;
            if (may_fu && s[i] == '-') {//如果可能是负数
                strcpy(postfix[j], "0\0");//在-号前面加上一个0，用0-2来代替-2。
                j++;
                if (s[i] == '(') {//剩余的和不可能是负数的一样
                    t_top++;
                    transform[t_top] = s[i];
                    may_fu = 1;
                }
                else {
                    if (t_top == -1) {
                        t_top++;
                        transform[t_top] = s[i];
                    }
                    else if (!compare(s[i], transform[t_top]) || t_top == -1) {
                        t_top++;
                        transform[t_top] = s[i];
                    }
                    else {
                        if (t_top == -1) {
                            continue;
                        }
                        //postfix[j] = transform[t_top];
                        string_in(postfix, transform, j, t_top);
                        t_top--;
                        j++;
                        i--;
                    }
                }
                may_fu = 0;
            }
            else { //如果不可能是负数
                if (s[i] == ')') {
                    if (transform[t_top] != '(') {//如果不是'('就放入postfix

                        //postfix[j] = transform[t_top];
                        string_in(postfix, transform, j, t_top);
                        t_top--;
                        j++;
                        i--;//for循环一轮就i++，这里i--让下一次进来还是指向nifix的')'，直到transform遇到'('。
                    }
                    else { //如果是'('就直接丢掉
                        t_top--;
                    }
                }
                else if (s[i] == '(') {
                    t_top++;
                    transform[t_top] = s[i];
                    may_fu = 1;
                }
                else { //不是(,也不是)。
                    if (t_top == -1) {//如果top没有符号就直接放入栈中
                        t_top++;
                        transform[t_top] = s[i];
                    }
                    else if (!compare(s[i], transform[t_top]) ||
                        t_top == -1) { //如果优先级高于top的符号
                        t_top++;
                        transform[t_top] = s[i];
                    }
                    else { //如果优先级小于等于top：弹出top的符号
                        if (t_top == -1) {
                            continue;
                        }
                        //postfix[j] = transform[t_top];
                        string_in(postfix, transform, j, t_top);
                        t_top--;
                        j++;
                        i--; //让下一次进来还是指向nifix的这个运算符
                    }
                }
            }
        }
        if (isFirst && s[i] != '(') {//
            isFirst--;//这个--的后缀不能直接放在if中，不然就算isFirst不是真也会减一。
            may_fu = 0;
        }
    }
    while (t_top != -1) {//把剩下的运算符放到postfix里面
        //postfix[j++] = transform[t_top];
        string_in(postfix, transform, j, t_top);
        j++;
        t_top--;
    }


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
        else if (strchr(postfix[i], '/')) {
            right = calculate[c_top--];
            left = calculate[c_top--];
            calculate[++c_top] = left / right;
        }
        else {
            calculate[++c_top] = atoi(postfix[i]);
        }
    }
    return calculate[0];
}
#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>          队列          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                //模板队列
#if 0
#include <stdio.h>
#include<stdlib.h>
typedef int status;

#define MAXSIZE 100000
#define ERROR 0
#define OK 1
typedef int status;
typedef struct {
    int  arr[MAXSIZE];
    int head;//指向头元素
    int tail;//指向尾元素的下一个位置
} QUEUE;

status push(QUEUE* queue, int num) {
    if (queue->tail == MAXSIZE - 1) {
        return ERROR;
    }
    queue->arr[queue->tail] = num;
    queue->tail += 1;
    return OK;
}
status pop(QUEUE* queue, int* num) {
    if (queue->head == queue->tail) {
        return ERROR;
    }
    *num = queue->arr[queue->head];
    for (int i = 1; i < queue->tail; i++) {
        queue->arr[i - 1] = queue->arr[i];
    }
    queue->tail -= 1;
    return OK;
}
status front(QUEUE* queue, int* num) {
    if (queue->head == queue->tail) {
        return ERROR;
    }
    *num = queue->arr[queue->head];
    return OK;
}

int main() {
    QUEUE queue;
    queue.head = 0;
    queue.tail = 0;

    int time = 0;
    scanf("%d", &time);

    char operate[5];
    int num = 0;
    int ret = 0;

    for (int i = 0; i < time; i++) {
        scanf("%s", operate);
        if (strcmp(operate, "push") == 0) {
            scanf("%d", &num);
            push(&queue, num);
        }
        else if (strcmp(operate, "pop") == 0) {
            if (pop(&queue, &ret)) {
                printf("%d\n", ret);
            }
            else {
                printf("error\n");
            }
        }
        else if (strcmp(operate, "front") == 0) {
            if (front(&queue, &ret)) {
                printf("%d\n", ret);
            }
            else {
                printf("error\n");
            }
        }
    }

    return 0;
}
#endif

                                                                    //模板循环队列
#if 0
#include <stdio.h>
#include<stdlib.h>

typedef int status;
#define ERROR 0
#define OK 1
typedef int status;
typedef struct {
    int* arr;
    int head;//指向头元素
    int tail;//指向尾元素的下一个位置
} QUEUE;

status push(QUEUE* queue, int num, int maxsize) {
    if ((queue->tail + 1) % maxsize == queue->head) {
        return ERROR;
    }
    queue->arr[queue->tail] = num;
    queue->tail = (queue->tail + 1) % maxsize;
    return OK;
}
status pop(QUEUE* queue, int* num, int maxsize) {
    if (queue->head == queue->tail) {
        return ERROR;
    }
    *num = queue->arr[queue->head];
    queue->head = (queue->head + 1) % maxsize;
    return OK;
}
status front(QUEUE* queue, int* num) {
    if (queue->head == queue->tail) {
        return ERROR;
    }
    *num = queue->arr[queue->head];
    return OK;
}

int main() {
    int n = 0;
    int q = 0;
    scanf("%d %d", &n, &q);
    QUEUE queue;
    queue.arr = (int*)malloc(sizeof(int) * (n + 1));
    queue.head = 0;
    queue.tail = 0;

    char operate[5];
    int num = 0;
    int ret = 0;
    for (int i = 0; i < q; i++) {
        scanf("%s", operate);
        if (strcmp(operate, "push") == 0) {
            scanf("%d", &num);
            if (push(&queue, num, n + 1)) {

            }
            else {
                printf("full\n");
            }
        }
        else if (strcmp(operate, "pop") == 0) {
            if (pop(&queue, &ret, n + 1)) {
                printf("%d\n", ret);
            }
            else {
                printf("empty\n");
            }
        }
        else if (strcmp(operate, "front") == 0) {
            if (front(&queue, &ret)) {
                printf("%d\n", ret);
            }
            else {
                printf("empty\n");
            }
        }
    }




    return 0;
}
#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>          链表          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                 //模板链表
#if 0
#include <stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define OK 1
#define Erroe 0
typedef int status;

typedef struct node {
    struct node* next;
    int num;
} NODE;

status insert(NODE* list, int x, int num);
status delete(NODE* list, int x);

int main() {
    NODE* list = (NODE*)malloc(sizeof(NODE));
    list->next = NULL;
    int n = 0;
    scanf("%d", &n);
    char arr[10];
    int x = 0;
    int num = 0;

    for (; n; n--) {
        scanf("%s", arr);
        if (strcmp(arr, "insert") == 0) {
            scanf("%d%d", &x, &num);
            insert(list, x, num);
        }
        else if (strcmp(arr, "delete") == 0) {
            scanf("%d", &x);
            delete(list, x);
        }
    }
    NODE* p = list->next;
    int cnt = 0;
    while (p) {
        printf("%d ", p->num);
        cnt++;
        p = p->next;
    }
    if (cnt == 0) {
        printf("NULL");
    }

    return 0;
}

status insert(NODE* list, int x, int num) {
    NODE* p = list;
    NODE* q = p->next;
    while (q) {
        if (q->num == x) {
            NODE* new = (NODE*)malloc(sizeof(NODE));
            new->num = num;
            new->next = q;
            p->next = new;
            return OK;
        }
        p = q;
        q = q->next;
    }
    NODE* last = (NODE*)malloc(sizeof(NODE));
    last->num = num;
    last->next = p->next;
    p->next = last;
    return OK;
}
status delete(NODE* list, int x) {
    NODE* p = list;
    NODE* q = p->next;
    while (q) {
        if (q->num == x) {
            p->next = q->next;
            free(q);
        }
        p = q;
        q = q->next;
    }
    return OK;
}

#endif

                                                                //反转链表
#if 0
struct ListNode* ReverseList(struct ListNode* head) {
    // write code here
    struct ListNode* HEAD = NULL;
    struct ListNode* p = head;
    if (head == NULL) {
        return NULL;
    }
    else {
        while (p) {
            head = head->next;
            p->next = HEAD;
            HEAD = p;
            p = head;;//移动后就和原来的链表接不上了
        }
        return HEAD;
    }


}
#endif

                                                                //合并有序链表
#if 0
struct ListNode* Merge(struct ListNode* pHead1, struct ListNode* pHead2) {
    // write code here
    struct ListNode* newhead = NULL;
    struct ListNode* p1 = pHead1;
    struct ListNode* p2 = pHead2;
    struct ListNode* final = newhead;

    int isFirst = 1;
    if (pHead1 == NULL)
    {
        return pHead2;
    }
    else if (pHead2 == NULL)
    {
        return pHead1;
    }
    while (pHead1 != NULL && pHead2 != NULL) {
        if (p1->val < p2->val) {
            pHead1 = pHead1->next;
            if (isFirst) {
                p1->next = final;
                final = p1;
                newhead = p1;
                p1 = pHead1;
                isFirst--;
            }
            else {
                p1->next = final->next;
                final->next = p1;
                final = p1;
                p1 = pHead1;
            }

        }
        else if (p1->val > p2->val) {
            pHead2 = pHead2->next;
            if (isFirst) {
                p2->next = final;
                final = p2;
                newhead = p2;
                p2 = pHead2;
                isFirst--;
            }
            else {
                p2->next = final->next;
                final->next = p2;
                final = p2;
                p2 = pHead2;
            }
        }
        else {
            pHead1 = pHead1->next;
            if (isFirst) {
                p1->next = final;
                final = p1;
                newhead = p1;
                p1 = pHead1;
                isFirst--;
            }
            else {
                p1->next = final->next;
                final->next = p1;
                final = p1;
                p1 = pHead1;
            }

            pHead2 = pHead2->next;
            p2->next = final->next;
            final->next = p2;
            final = p2;
            p2 = pHead2;
        }
    }

    if (pHead2 != NULL) {
        final->next = p2;
    }
    if (pHead1 != NULL) {
        final->next = p1;
    }
    return newhead;
}
#endif


                                                                //删除链表节点
#if 0
struct ListNode* deleteNode(struct ListNode* head, int val) {
    // write code here
    struct ListNode* p = head;
    struct ListNode* q = p->next;
    if (p->val == val) {
        head = p->next;
        free(p);
        return head;
    }
    else {
        while (q != NULL && q->val != val) {
            p = q;
            q = q->next;
        }
        if (!p) {
            return head;
        }
        else {
            p->next = q->next;
            free(q);
            return head;
        }
    }
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>          图论          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 
                                                              //模板，拓扑排序
#if 0

#include <stdio.h>
#include<stdlib.h>


typedef struct EDGE {
    int adjvex;
    int weight;
    struct EDGE* next;
}EDGE;
typedef struct VEX {
    int in;
    struct EDGE* first_edge;
}VEX;
typedef struct GRAPH {
    struct VEX vex[200];
    int vex_cnt;
    int edge_cnt;
}GRAPH;

int order[200];
int g = -1;
void init(GRAPH* m) {
    scanf("%d %d", &m->vex_cnt, &m->edge_cnt);
    for (int i = 0; i <= m->vex_cnt; i++) {
        m->vex[i].in = 0;
        m->vex[i].first_edge = NULL;
    }
    for (int i = 0; i < m->edge_cnt; i++) {
        int v, w;
        scanf("%d %d", &v, &w);
        m->vex[w].in++;
        if (!m->vex[v].first_edge) {
            EDGE* last = m->vex[v].first_edge = (EDGE*)malloc(sizeof(EDGE));
            last->adjvex = w; last->next = NULL; last->weight = 1;
        }
        else {
            EDGE* last = m->vex[v].first_edge;
            while (last->next) {
                last = last->next;
            }
            last->next = (EDGE*)malloc(sizeof(EDGE)); last = last->next;
            last->adjvex = w; last->next = NULL; last->weight = 1;
        }
    }
}

int topologicalsort(GRAPH* m) {
    int cnt = 0;
    int stack[200001];
    //int list[200001];
    int head = 0, rear = 0;
    int top = -1;
    for (int i = 1; i <= m->vex_cnt; i++) {
        if (!m->vex[i].in) {
            stack[++top] = i;
            //list[rear++]=i;
        }
    }
    while (top != -1) {
        int cur = stack[top--];
        //int cur=list[head++];
        cnt++;
        order[++g] = cur;
        for (EDGE* p = m->vex[cur].first_edge; p; p = p->next) {
            int start = cur, end = p->adjvex, time = p->weight;
            if (!--m->vex[end].in) {
                stack[++top] = end;
                //list[rear++]=end;
            }
        }
    }
    return cnt == m->vex_cnt ? 1 : 0;
}

int main()
{
    GRAPH m;
    init(&m);

    if (!topologicalsort(&m)) {
        printf("-1");
    }
    else {
        for (int i = 0; i < m.vex_cnt; i++) {
            printf("%d ", order[i]);
        }
    }


    return 0;
}

#endif

                                                              //最小生成树
#if 0
//void swap1(int* a, int* b);
//int getmid(int* arr[], int key, int low, int high, int col);
//void sort(int* arr[], int key, int low, int high, int col);
//void quick_sort1(int* arr[], int row, int key, int col);
//int find1(int* parent, int num);
//int gettotal(int* cost[], int n, int m);
//
//int miniSpanningTree(int n, int m, int** cost, int costRowLen, int* costColLen) {
//    // write code here
//    quick_sort1(cost, m, 2, *costColLen);//超时，
//
//
//
//
//    int total = 0;
//    total = gettotal(cost, n, m);//发生段错误
//    //printf("%d",total);
//
//
//    return total;
//}
//
//
//void swap1(int* a, int* b) {
//    int temp = *a;
//    *a = *b;
//    *b = temp;
//}
//int getmid(int* arr[], int key, int low, int high, int col) {
//    int mid = arr[low][key];
//    int l = low;
//    int r = high;
//    while (r > l) {
//        while (r > l && arr[r][key] >= mid) {
//            r--;
//        }
//        for (int i = 0; i < col; i++) {
//            swap1(&arr[l][key] - key + i, &arr[r][key] - key + i);
//        }
//        while (r > l && arr[l][key] <= mid) {
//            l++;//出循环时l为大于mid的数的下标
//        }
//        for (int i = 0; i < col; i++) {
//            swap1(&arr[l][key] - key + i, &arr[r][key] - key + i);
//        }
//    }
//    return l;
//}
//void sort(int* arr[], int key, int low, int high, int col) {
//    int mid;
//    if (low < high) {
//        mid = getmid(arr, key, low, high, col);
//        sort(arr, key, 0, mid - 1, col);
//        sort(arr, key, mid + 1, high, col);
//    }
//}
//void quick_sort1(int* arr[], int row, int key, int col) {//key是关键字所在的列数，row是前row个要排序的总行数
//    sort(arr, key, 0, row - 1, col);
//}
//int find1(int* parent, int num) {
//    while (parent[num] != 0) {
//        num = parent[num];
//    }
//    return num;
//}
//
//int gettotal(int* cost[], int n, int m) {
//    int x, y;
//    int parent[n + 1];
//    for (int i = 0; i <= n; i++) {
//        parent[i] = 0;
//    }
//    int total = 0;
//    int cnt = 0;
//    for (int i = 0; i < m; i++) {
//        x = find1(parent, cost[i][0]);
//        y = find1(parent, cost[i][1]);
//        if (x != y) {
//            total += cost[i][2];
//            parent[n] = m;
//            cnt++;
//            if (cnt == n - 1) {
//                return total;
//            }
//        }
//    }
//    return total;
//}                                                                   //一版
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                      //二版
int getpivot(int** cost, int low, int high, int col, int key);
void quick_sort(int** cost, int row, int col, int key);
void sort(int** cost, int low, int high, int col, int key);
int depart(int** cost, int low, int high, int col, int key);
void sort(int** cost, int low, int high, int col, int key);
void memcpy2(void* dst, void* src, int size) {
    char* p1 = (char*)dst;
    char* p2 = (char*)src;
    for (int i = 0; i < size; i++) {
        *p1 = *p2;
        p1++;
        p2++;
    }
}
void swap(void* p1, void* p2, int size) {
    int temp[3];
    memcpy2(temp, p1, size);
    memcpy2(p1, p2, size);
    memcpy2(p2, temp, size);
}

int depart(int** cost, int low, int high, int col, int key) {
    if (high == low) {
        return low;
    }
    int temp[3];
    memcpy2(temp, cost[low], 12);
    //int pivot=(low+high)/2;
    //swap(cost[high],cost[low],12);
    int pivotkey = cost[low][key];
    while (high > low) {
        while (cost[high][key] >= pivotkey && high > low) {
            high--;
        }
        memcpy2(cost[low], cost[high], 12);
        //swap(cost[low],cost[high],12);
        while (cost[low][key] <= pivotkey && high > low) {
            low++;
        }
        memcpy2(cost[high], cost[low], 12);
        //swap(cost[low],cost[high],12);
    }
    memcpy2(cost[low], temp, 12);
    return low;
}
void insert_sort(int** cost, int low, int high, int col, int key) {
    int i, j;
    for (int k = (high - low) / 2; k >= 1; k /= 2) {
        for (i = low + k; i < high; i++) {
            int temp[3];
            memcpy(temp, cost[i], 12);
            for (j = i; j >= low + k && cost[j - k][key] > temp[key]; j -= k) {

                memcpy(cost[j], cost[j - k], 12);

            }
            memcpy(cost[j], temp, 12);
        }
    }
}
void quick_sort(int** cost, int row, int col, int key) {
    sort(cost, 0, row - 1, col, key);
}
void sort(int** cost, int low, int high, int col, int key) {
    if (high - low > 100867) {
        while (high > low) {
            int mid = depart(cost, low, high, col, key);
            sort(cost, low, mid - 1, col, key);
            //sort(cost, mid + 1, high, col, key);
            low = mid + 1;
        }
    }
    else {
        insert_sort(cost, low, high + 1, col, key);//high+1是最后一个元素的下一个下标
    }
}
int find(int* parent, int a) {
    while (parent[a] >= 0) {
        a = parent[a];
    }
    return a;
}
int gettotal(int** cost, int row, int col, int key, int p_cnt) {
    int size = p_cnt + 1;
    int cnt = 0;
    int* parent = (int*)malloc(sizeof(int) * size);
    int ret = 0;
    for (int i = 0; i <= size; i++) {
        parent[i] = -1;
    }
    for (int i = 0; i < row; i++) {
        int a = find(parent, cost[i][0]);
        int b = find(parent, cost[i][1]);
        if (a != b) {

            if (parent[a] < parent[b]) {
                parent[a] += parent[b];
                parent[b] = a;
            }
            else {
                parent[b] += parent[a];
                parent[a] = b;
            }
            ret += cost[i][key];
            cnt++;
            if (cnt == p_cnt - 1) {
                return ret;
            }
        }
    }
    return ret;
}



int main()
{
    //int arr[10][3] = { { 1,2,3 },{3,5,2},{4,5,6},{6,2,1},{4,9,8},{5,7,7},{2,8,4},{6,1,5},{7,8,9} };
    //int arr[10][3] = { { 1,2,3 },{3,5,6},{4,5,6},{6,2,1},{4,9,8},{5,7,8},{2,8,4},{6,1,8},{7,8,9} };

    int arr[10][3] = { {5,3,8},{1,3,6},{2,5,4},{2,3,5},{4,5,6},{3,4,3},{2,4,8},{1,2,2},{1,4,5},{1,6,2} };
    int row = 10, col = 3;
    miniSpanningTree(9, 9, arr, row, &col);
    //insert_sort(arr, 0, row,col , 2);
    swap(arr[4], arr[1], 12);

    return 0;
}
#endif

                                                              //模板，单源最短路
#if 0
#include <stdio.h>
#include<stdlib.h>
#define INFINITY 655355555
#define MAX 5000
typedef struct GRAPH {
    int edge[5001][5001];
    int vex_cnt;
    int edge_cnt;
}GRAPH;


void init(GRAPH* m) {
    scanf("%d %d", &m->vex_cnt, &m->edge_cnt);
    for (int i = 1; i <= MAX; i++) {
        for (int j = 1; j <= MAX; j++) {
            if (i == j) {
                m->edge[i][j] = 0;
            }
            else {
                m->edge[i][j] = INFINITY;
            }
        }
    }
    for (int i = 0; i < m->edge_cnt; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        m->edge[x][y] = m->edge[y][x] = z;
    }
}

void shorest_path(GRAPH* m, int src, int* dist, int* path) {
    int final[5001] = { 0 };
    for (int i = 1; i <= MAX; i++) {
        dist[i] = INFINITY;
        path[i] = -1;
    }
    dist[src] = 0;
    for (int x = 1; x <= MAX; x++) {
        int min = INFINITY, k = 1;
        for (int y = 1; y <= MAX; y++) {
            if (!final[y] && dist[y] < min) {
                min = dist[y];
                k = y;
            }
        }
        final[k] = 1;
        for (int i = 1; i <= MAX; i++) {
            if (!final[i] && min + m->edge[k][i] < dist[i]) {
                dist[i] = min + m->edge[k][i];
                path[i] = k;
            }
        }
    }

    if (dist[m->vex_cnt] != INFINITY) {
        printf("%d", dist[m->vex_cnt]);
    }
    else {
        printf("-1");
    }
}


int main()
{
    GRAPH m;
    init(&m);

    int dist[5001];
    int path[5001];
    shorest_path(&m, 1, dist, path);

    return 0;
}
#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>          堆           >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#if 0
#include <stdio.h>
#include<string.h>

void insert(int* heap, int* size, int x) {
    if (!*size) {
        heap[++(*size)] = x;
        return;
    }
    int i;
    heap[++(*size)]= x;
    for (i = *size; i > 1 && heap[i / 2] <x; i /= 2) {
        heap[i] = heap[i / 2];
    }
    heap[i] = x;
}

int delete(int* heap, int* size) {
    if (!(*size)) {
        return -1;
    }
    int root = heap[1];
    heap[1] = heap[(*size)--];

    int parent = 1;
    int last = heap[1];
    for (int child = 2 * parent; child <= *size; child *= 2) {
        if (child<*size && heap[child + 1]>heap[child]) {
            child += 1;
        }
        if (heap[child] < last) {
            break;
        }
        heap[parent] = heap[child];
        parent = child;
    }
    heap[parent] = last;

    return root;
}


int main() {

    int heap[100001];
    int size = 0;

    char opt[5];
    int dta;
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", opt);
        if (!strcmp("push", opt)) {
            scanf("%d", &dta);
            insert(heap, &size, dta);
        }
        else if (!strcmp("pop", opt)) {
            getchar();
            int ret = delete(heap, &size);
            if (ret != -1) {
                printf("%d\n", ret);
            }
            else {
                printf("empty\n");
            }
        }
        else {
            getchar();
            if (!size) {
                printf("empty\n");
            }
            else {
                printf("%d\n", heap[1]);
            }
        }
    }

    return 0;
}
#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>          bfs           >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                   //单源最短路

#if 0
#include <stdio.h>
#include<stdlib.h>
#define INFINITY 65535
#define MAX 5000
typedef struct GRAPH {
    int edge[5001][5001];
    int vex_cnt;
    int edge_cnt;
}GRAPH;

void init(GRAPH* m) {
    scanf("%d %d", &m->vex_cnt, &m->edge_cnt);
    for (int i = 0; i <= MAX; i++) {
        for (int j = 0; j <= MAX; j++) {
            if (i == j) {
                m->edge[i][j] = 0;
            }
            else {
                m->edge[i][j] = INFINITY;
            }
        }
    }
    for (int i = 0; i < m->edge_cnt; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        m->edge[u][v] = m->edge[v][u] = 1;
    }
}

int  shorest_path(GRAPH* m, int src, int dst) {
    int dist[5001]; int path[5001] = { 0 }; int final[5001] = { 0 };
    for (int i = 1; i <= MAX; i++) {
        dist[i] = INFINITY;
    }
    dist[src] = 0;
    for (int i = 1; i <= MAX; i++) {
        int min = INFINITY, k = 1;
        for (int j = 1; j <= MAX; j++) {
            if (!final[j] && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }

        final[k] = 1;
        for (int j = 1; j <= MAX; j++) {
            if (!final[j] && min + m->edge[k][j] < dist[j]) {
                dist[j] = min + m->edge[k][j];
                path[j] = k;
            }
        }
    }
    if (dist[dst] != INFINITY) {
        printf("%d", dist[dst]);
    }
    else {
        printf("-1");
    }
    return dist[dst];
}


int main() {
    GRAPH m;
    init(&m);

    int ret = shorest_path(&m, 1, m.vex_cnt);


    return 0;
}
#endif

                                                                   //走迷宫
#if 0
#include <stdio.h>
#include<stdlib.h>

typedef  struct COORD {
    int x;
    int y;
}COORD;

int n, m;
COORD src, dst;
int visited[11][11] = { 0 };
int dist[11][11] = { 0 };


int judge(char** matrix,int x, int y) {
    if (x >= 1 && x <= n && y >= 1 && y <= m) {
        if (!visited[x][y] && matrix[x][y]=='.') {
            return 1;
        }
    }
    return 0;
}

void in_list(char** matrix ,COORD* list, int head, int* rear, COORD cur,COORD* tail,int step) {
    COORD p;
    if (judge(matrix,cur.x, cur.y + 1)) {
        p.x = cur.x; p.y = cur.y + 1;
        list[(*rear)++] = p;
        visited[p.x][p.y] = 1; dist[p.x][p.y] = step;
        tail->x = p.x; tail->y = p.y;
    }
    if (judge(matrix,cur.x, cur.y - 1)) {
        p.x = cur.x; p.y = cur.y - 1;
        list[(*rear)++] = p;
        visited[p.x][p.y] = 1; dist[p.x][p.y] = step;
        tail->x = p.x; tail->y = p.y;
    }
    if (judge(matrix,cur.x-1, cur.y )) {
        p.x = cur.x-1; p.y = cur.y;
        list[(*rear)++] = p;
        visited[p.x][p.y] = 1; dist[p.x][p.y] = step;
        tail->x = p.x; tail->y = p.y;
    }
    if (judge(matrix,cur.x+1, cur.y )) {
        p.x = cur.x+1; p.y = cur.y;
        list[(*rear)++] = p;
        visited[p.x][p.y] = 1; dist[p.x][p.y] = step;
        tail->x = p.x; tail->y = p.y;
    }
}


int get_cnt(char** matrix, int row, int col, COORD src, COORD dst) {
    if (matrix[dst.x][dst.y] == '*')return -1;
    COORD list[1000];
    int head = 0, rear = 0;
    list[rear++] = src;
    visited[src.x][src.y] = 1;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            dist[i][j] = -1;
        }
    }
    int step = 1;
    COORD last=src, tail;
    while (head != rear) {
        COORD cur = list[head++];
        //if (cur.x == dst.x && cur.y == dst.y)break;
        in_list(matrix,list, head, &rear, cur,&tail,step);
        if (cur.x == last.x && cur.y == last.y) {
            last = tail;
            step++;
        }
    }

    return dist[dst.x][dst.y];
}

int main() {
    scanf("%d %d", &n, &m);
    char** matrix;
    matrix = (char**)malloc(sizeof(char*) * (n + 1));
    for (int i = 0; i <= n; i++) {
        matrix[i] = (char*)malloc(sizeof(char) * (m + 1));
    }

    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    src.x = x1; src.y = y1; dst.x = x2; dst.y = y2;

    for (int i =0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (!i || !j) {
                matrix[i][j] = '*';
            }
            else {
                scanf(" %c", &matrix[i][j]);
            }
        }
    }

    int step = get_cnt(matrix, n, m, src, dst);
    printf("%d", step);

    return 0;
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>          dfs           >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                               //数岛的个数(数连通集)
#if 0
#include<stdio.h>
#include<stdlib.h>
typedef  struct COORD {
    int x;
    int y;
}COORD;
visited[10][10] = { 0 };

int judge(char** matrix, int row,int col,int x, int y) {
    if (x >= 0 && x < row && y >= 0 && y < col) {
        if (!visited[x][y] && matrix[x][y] == '1') {
            return 1;
        }
    }
    return 0;
}

void dfs(char** matrix,int row,int col,COORD cur) {
    visited[cur.x][cur.y] = 1;

    COORD p;
    if (judge(matrix,row,col ,cur.x, cur.y + 1)) {
        p.x = cur.x; p.y = cur.y + 1;
        dfs(matrix, row, col, p);
    }
    if (judge(matrix, row, col, cur.x, cur.y - 1)) {
        p.x = cur.x; p.y = cur.y - 1;
        dfs(matrix, row, col, p);
    }
    if (judge(matrix, row, col, cur.x - 1, cur.y)) {
        p.x = cur.x - 1; p.y = cur.y;
        dfs(matrix, row, col, p);
    }
    if (judge(matrix, row, col, cur.x + 1, cur.y)) {
        p.x = cur.x + 1; p.y = cur.y;
        dfs(matrix, row, col, p);
    }

}

int get_cnt(char** matrix, int row, int col) {
    int cnt = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (!visited[i][j] && matrix[i][j] == '1') {
                COORD src; src.x = i; src.y = j;
                dfs(matrix, row, col,src);
                cnt++;
            }
        }
    }
    return cnt;
}

int main()
{
    int row = 5, col = 5;
    char** matrix = (char**)malloc(sizeof(char*) * row);
    for (int i = 0; i < row; i++) {
        matrix[i] = (char*)malloc(sizeof(char) * col);
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf(" %c", &matrix[i][j]);
        }
    }

    int ret;
    printf("%d", (ret = get_cnt(matrix, row, col)));



    return 0;
}

#endif

                                                         //kotori和素因子,给定n个正整数的各一个素因子最小和

#if 0
#include<stdio.h>
#include<math.h>
int SUM[20];
int top = 0;
int visited[30] = { 0 };
int sum = 0;

int is_prime(int n) {
    if (n == 2) {
        return 1;
    }
    for (int i = 2; i < sqrt(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void get_prime(int* prime, int N) {
    prime[0] = prime[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!prime[i] ) {
            if (is_prime(i)) {
                for (int j = 2 * i; j <= N; j += i) {
                    prime[j] = 1;
                }
            }
            else {
                prime[i] = 1;
            }
        }
    }
}

void dfs(int arr[11][10], int level, int sum,int n) {
    if (level == n + 1) {
        SUM[top++] = sum;
        return;
    }
    int sign = 0;
    int x;
    for (int i = 1; i <= arr[level][0]; i++) {
        x = arr[level][i];
        if (!visited[x]) {
            visited[x] = 1;
            sign = 1;
            if (sign) {
                sum += x;
                dfs(arr, level + 1, sum, n);
                sum -= x;
                visited[x] = 0;
            }
        }
    }
    return;
}

void get_cnt(int arr[11][10],int n, int* prime, int N) {
    for (int i = 1; i <= arr[1][0]; i++) {
        int x = arr[1][i];
        sum = 0;
        if (!visited[x]) {
            visited[x] = 1;
            sum = x;
            dfs(arr, 2, sum, n);
        }
        for (int j = 1; j <= 30; j++) {
            visited[j] = 0;
        }
    }
}

int main()
{
    //初始化数组
    int n = 0;
    scanf("%d", &n);
    int arr[11][10] = { 0 };
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[0][i]);//0行存正整数，0列存对应的素因子个数。
    }
    //拿到1000内的素数表
    int prime[1001] = { 0 };//0为素数，1不是
    get_prime(prime, 1000);
    //得到各个数的素因子
    for (int i = 1; i <= n; i++) {
        int x = arr[0][i];
        for (int j = 2; j <= x; j++) {
            if (x%j==0 && !prime[j]) {
                int top = ++arr[i][0];
                arr[i][top] = j;
            }
        }
    }
    //拿到所有和
    get_cnt(arr, n, prime, 1000);

    int min = 65535;
    for (int i = 0; i < top; i++) {
        if (SUM[i] < min) {
            min = SUM[i];
        }
    }
    if (min != 65535)printf("%d", min);
    else printf("-1");

    return 0;
}
#endif 



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>          递归          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                  //汉诺塔

#if 0
#include<stdio.h>
#include<stdlib.h>
int cnt = 0;

void move(char** str, char* src, char* dst) {
    sprintf(str[cnt++], "move from %s to %s", src, dst);
    printf("%s\n", str[cnt - 1]);
}

void hanno(char** str, int n, char* src, char* temp, char* dst) {
    if (n == 1) {
        move(str, src, dst);
    }
    else {
        hanno(str, n - 1, src, dst, temp);
        move(str, src, dst);
        hanno(str, n - 1, temp, src, dst);
    }
}


char** getSolution(int n, int* returnSize) {
    // write code here
    char** str = (char**)malloc(sizeof(char*) * 100);
    for (int i = 0; i < 100; i++) {
        str[i] = (char*)malloc(sizeof(char) * 25);
    }
    hanno(str, n, "left", "mid", "right");

    *returnSize = cnt;
    return str;
}

int main()
{
    int size = 0;
    char** ret = getSolution(2, &size);

    /*char arr[10];
    sprintf(arr, "%s %s", "hello", "bit");
    printf("%s", arr);*/
    double a = 5.0;
    printf("%d", (int)a);

    return 0;
}
#endif 




//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>          分治          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                    //快速幂
#if 0
#include <stdio.h>
#include<math.h>

int main() {
    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        long long a, b, p;
        scanf("%lld %lld %lld", &a, &b, &p);
        int ans = 1; a %= p;
        while (b > 0) {
            if (b % 2 == 1) {
                ans = (ans * a) % p;
                b -= 1;
            }
            b /= 2;
            if (b == 1) {
                a = (a * a) % p;
                ans = (ans * a) % p;
                break;
            }
            a = (a * a) % p;
        }
        printf("%d\n", ans);
    }

    return 0;
}
#endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>          排序          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#if 0
#include<stdio.h>
#include<stdlib.h>
void merge(int* src, int* dst, int L, int M, int R) {
    int p1 = L, p2 = M + 1;
    int p0 = L;
    while (p1 <= M && p2 <= R) {
        if (src[p1] >= src[p2]) {
            dst[p0++] = src[p2++];
        }
        else if (src[p1] <= src[p2]) {
            dst[p0++] = src[p1++];
        }
    }
    while (p1 <= M) {
        dst[p0++] = src[p1++];
    }
    while (p2 <= R) {
        dst[p0++] = src[p2++];
    }

}

void sort(int* arr, int* temp, int L, int R) {
    if (R == L) {
        temp[L] = arr[L];
        return;
    }
    else {
        int M = (R + L) / 2;
        sort(arr, temp, L, M);
        sort(arr, temp, M + 1, R);
        merge(temp, arr, L, M, R);
        for (int i = L; i <= R; i++) {
            temp[i] = arr[i];
        }
    }
}

int* MySort(int* arr, int arrLen, int* returnSize) {
    // write code here
    int* temp = (int*)malloc(sizeof(int) * arrLen);
    sort(arr, temp, 0, arrLen - 1);

    *returnSize = arrLen;
    return arr;
}

int main()
{
    int arr[10] = { 4,3,6,8,1,2,5,9,7,0 };
    int size = 10;

    int* ret = MySort(arr, size, &size);



    return 0;
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>           双指针         >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#if 0
#include <stdio.h>
#include<stdlib.h>


void merge(int* src, int* dst, int L, int M, int R) {
    int p1 = L, p2 = M + 1;
    int p0 = L;
    while (p1 <= M && p2 <= R) {
        if (src[p1] >= src[p2]) {
            dst[p0++] = src[p2++];
        }
        else if (src[p1] <= src[p2]) {
            dst[p0++] = src[p1++];
        }
    }
    while (p1 <= M) {
        dst[p0++] = src[p1++];
    }
    while (p2 <= R) {
        dst[p0++] = src[p2++];
    }

}

void sort(int* arr, int* temp, int L, int R) {
    if (R == L) {
        temp[L] = arr[L];
        return;
    }
    else {
        int M = (R + L) / 2;
        sort(arr, temp, L, M);
        sort(arr, temp, M + 1, R);
        merge(temp, arr, L, M, R);
        for (int i = L; i <= R; i++) {
            temp[i] = arr[i];
        }
    }
}

int* MySort(int* arr, int arrLen, int* returnSize) {
    // write code here
    int* temp = (int*)malloc(sizeof(int) * arrLen);
    sort(arr, temp, 0, arrLen - 1);

    *returnSize = arrLen;
    return arr;
}

int compare(const void* p1, const void* p2) {
    return *(int*)p1 - *(int*)p2;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    //int* ret = MySort(arr, n, &n);
    qsort(arr, n, sizeof(int), compare);

    int cnt = 0, max = 0;
    for (int i = 0; i < n; i++) {
        cnt = 0;
        for (int j = n - 1; j >= i; j--) {
            if (arr[j] - arr[i] > k) {
                cnt++;
            }
            else {
                break;
            }
        }
        cnt = n - cnt-i;
        if (cnt > max)max = cnt;
    }
    printf("%d", max);

    return 0;
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>           贪心           >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                  //活动安排
#if 0
#include <stdio.h>
#include<stdlib.h>

typedef struct NODE {
    int end;
    struct NODE* next;
}NODE;

void insert(NODE** arr, int size, int x, int y) {
    NODE* p = arr[x];
    if (!arr[x]) {
        arr[x] = (NODE*)malloc(sizeof(NODE));
        arr[x]->end = y;
        arr[x]->next = NULL;
        return;
    }
    while (!p->next && y > p->next->end) {
        p = p->next;
    }
    NODE* new = (NODE*)malloc(sizeof(NODE));
    new->end = y;
    new->next = p->next;
    p->next = new;
}


int main() {
    int n;
    scanf("%d", &n);

    NODE* arr[20] = { 0 };
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        insert(arr, n, x, y);//用数组下标代表活动起始时间不好，还是用结构体存然后按活动结束时间来排序最好
    }


    return 0;
}
#endif 

                                                                  //哈夫曼编码


//#include <stdio.h>
//#include<stdlib.h>
//
//typedef struct NODE {
//    int index;
//    int weight;
//    struct NODE* left;
//    struct NODE* right;
//}NODE;
//
//void insert(NODE** heap, int* N, NODE* x) {
//    heap[++(*N)] = x;
//    if (*N == 1)return;
//
//    int i;
//    for (i = *N; i > 1 && x->weight < heap[i / 2]->weight; i /= 2) {
//        heap[i] = heap[i / 2];
//    }
//    heap[i] = x;
//}
//
//NODE* delete(NODE** heap, int* N) {
//    NODE* ret = heap[1];
//    heap[1] = heap[(*N)--];
//
//    int parent = 1;
//    NODE* new = heap[1];
//    for (int child = parent * 2; child <= *N; child *= 2) {
//        if (child < *N && heap[child + 1]->weight < heap[child]->weight) {
//            child++;
//        }
//        if (heap[child]->weight > new->weight) {
//            break;
//        }
//        heap[parent] = heap[child];
//        parent = child;
//    }
//    heap[parent] = new;
//
//    return ret;
//}
//
//NODE* build_tree(NODE** heap, int* size, int type) {
//    NODE* p1, *p2;
//    while (*size != 1) {
//        p1 = delete(heap, size);
//        p2 = delete(heap, size);
//        NODE* mix = (NODE*)malloc(sizeof(NODE));
//        mix->left = p1; mix->right = p2;
//        mix->index = 0;
//        mix->weight = p1->weight + p2->weight;
//        insert(heap, size, mix);
//    }
//    return heap[*size];
//}
//
//int get_codelen(NODE* root,int depth, int index) {
//    if (!root) {
//        return 0;
//    }
//    if (root->index == index) {
//        return depth;
//    }
//    int ret1= get_codelen(root->left, depth + 1, index);
//    int ret2 = get_codelen(root->right, depth + 1, index);
//    return ret2 > ret1 ? ret2 : ret1;
//}
//
//int get_min(NODE* root, int* time, int type) {
//    int sum = 0;
//
//    for (int i = 1; i <= type; i++) {
//        int times = time[i];
//        int length = get_codelen(root, 1, i) - 1;//得到对应节点的层数，len为层数减一
//        sum += times * length;
//    }
//    return sum;
//}
//
//int main() {
//    int type;
//    scanf("%d", &type);
//
//    int* time = (int*)malloc(sizeof(int) * (type + 1));
//    for (int i = 1; i <= type; i++) {
//        scanf("%d", &time[i]);
//    }
//
//    NODE** heap = (NODE**)malloc(sizeof(NODE*));
//    int size = 0;
//    for (int i = 1; i <= type; i++) {
//        NODE* new = (NODE*)malloc(sizeof(NODE));
//        new->right = new->left = NULL;
//        new->index = i;
//        new->weight = time[i];
//        insert(heap, &size, new);
//    }
//
//    NODE* root = build_tree(heap, &size, type);
//    
//    int min = get_min(root, time, type);
//    
//
//    return 0;
//}

#if 0
#include <stdio.h>
#include<stdlib.h>


typedef struct NODE {
    int index;
    int weight;
    struct NODE* left;
    struct NODE* right;
}NODE;

void insert(NODE** heap, int* N, NODE* x) {
    heap[++(*N)] = x;
    if (*N == 1)return;

    int i;
    for (i = *N; i > 1 && x->weight < heap[i / 2]->weight; i /= 2) {
        heap[i] = heap[i / 2];
    }
    heap[i] = x;
}

NODE* delete(NODE** heap, int* N) {
    NODE* ret = heap[1];
    heap[1] = heap[(*N)--];

    int parent = 1;
    NODE* new = heap[1];
    for (int child = parent * 2; child <= *N; child *= 2) {
        if (child < *N && heap[child + 1]->weight < heap[child]->weight) {
            child++;
        }
        if (heap[child]->weight > new->weight) {
            break;
        }
        heap[parent] = heap[child];
        parent = child;
    }
    heap[parent] = new;

    return ret;
}

NODE* build_tree(NODE** heap, int* size, int type) {
    NODE* p1, * p2;
    while (*size != 1) {
        p1 = delete(heap, size);
        p2 = delete(heap, size);
        NODE* mix = (NODE*)malloc(sizeof(NODE));
        mix->left = p1; mix->right = p2;
        mix->index = 0;
        mix->weight = p1->weight + p2->weight;
        insert(heap, size, mix);
    }
    return heap[*size];
}

int get_codelen(NODE* root, int depth, int index) {
    if (!root) {
        return 0;
    }
    if (root->index == index) {
        return depth;
    }
    int ret1 = get_codelen(root->left, depth + 1, index);
    int ret2 = get_codelen(root->right, depth + 1, index);
    return ret2 > ret1 ? ret2 : ret1;
}

int get_min(NODE* root, int* time, int type) {
    int sum = 0;

    for (int i = 1; i <= type; i++) {
        int times = time[i];
        int length = get_codelen(root, 1, i) - 1;//得到对应节点的层数，len为层数减一
        sum += times * length;
    }
    return sum;
}

int main() {
    int type;
    scanf("%d", &type);

    int* time = (int*)malloc(sizeof(int) * (type + 1));
    for (int i = 1; i <= type; i++) {
        scanf("%d", &time[i]);
    }

    NODE** heap = (NODE**)malloc(sizeof(NODE*));
    int size = 0;
    for (int i = 1; i <= type; i++) {
        NODE* new = (NODE*)malloc(sizeof(NODE));
        new->right = new->left = NULL;
        new->index = i;
        new->weight = time[i];
        insert(heap, &size, new);
    }

    NODE* root = build_tree(heap, &size, type);

    int min = get_min(root, time, type);
    printf("%d\n", min);

    

    return 0;
}
#endif



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>         动态规划         >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                     //线性DP
                                                                     //跳台阶
#if 0
int jumpFloor(int number) {
    // write code here
    int DP[41] = { 0 };
    DP[1] = 1;
    DP[2] = 2;
    for (int i = 3; i <= number; i++) {
        int step1 = DP[i - 1];
        int step2 = DP[i - 2];
        DP[i] = step1 + step2;
    }

    return DP[number];
}
#endif

                                                                //三角形最小路径和
#if 0
#define INFINITY 65535
int MIN(int a, int b) {
    return a < b ? a : b;
}

int minTrace(int triangle[5][5], int triangleRowLen, int* triangleColLen) {
    // write code here
    int n = triangleRowLen;

    int DP[10][10];
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            DP[i][j] = INFINITY;
        }
    }
    DP[1][1] = triangle[1][1];
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            DP[i][j] = MIN(DP[i - 1][j] + triangle[i][j], DP[i - 1][j - 1] + triangle[i][j]);
        }
    }

    int min = INFINITY;
    for (int i = 1; i <= n; i++) {
        if (DP[n][i] <min) {
            min = DP[n][i];
        }
    }
    return min;
}


int main()
{
    int arr[5][5] = { {0}, {0, 2 },{0,3,4},{0,6,5,7},{0,4,1,8,3} };
    int row = 4;
    int col = 4;
    int ret = minTrace(arr, row, &col);


    return 0;
}
#endif


                                                                //连续子数组最大和
#if 0
#include <stdio.h>

int MAX(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[20];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }

    int DP[20] = { -999 };//状态————以i为最后一个结束的最大子数组和
    DP[1] = arr[1];
    for (int i = 2; i <= n; i++) {
        DP[i] = MAX(DP[i - 1] + arr[i], arr[i]);
    }
    printf("%d", DP[n]);


    return 0;
}
#endif


                                                               //最长上升子序列
#if 0
#include <stdio.h>

int main() {
    int arr[1001] = { 0 };
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }

    int DP[1001] = { 0 };
    int max = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] || j == 0) {
                if (DP[j] + 1 > DP[i]) {
                    DP[i] = DP[j] + 1;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (DP[i] > max) {
            max = DP[i];
        }
    }
    printf("%d", max);

    return 0;
}
#endif

                                                               //最长公共子序列
#if 0
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

int MAX(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char str1[10];
    char str2[10];
    scanf("%s", &str1[1]); str1[0] = ' ';
    scanf("%s", &str2[1]); str2[0] = ' ';


    int DP[10][10] = { 0 };
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (str1[i] == str2[j]) {
                DP[i][j] = DP[i - 1][j - 1] + 1;//如果最后一个相等，那么这个字符就是公共的一个字符。
            }
            else {
                DP[i][j] = MAX(DP[i - 1][j], DP[i][j - 1]);//如果最后一个不相等，那么考虑如何将规模缩小。
            }//考虑DP[i-1][j]时，因为最后一个不相等所以即使在DP[i-1][j]的基础上i+1变成DP[i][j]，也不可能让结果变大，因为i增加的那一个字符要和最后一个比。又
        }//因为最后一个不相等，所以DP[i][j]!=DP[i-1][j]+1。
    }//同理也可能将DP[i][j]的规模缩小成DP[i][j-1].所以就在两个中间取max

    printf("%d", DP[n][m]);

    return 0;
}
#endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                   //背包问题
                                                                   //装箱问题
#if 0
#include <stdio.h>

int MAX(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, v;
    scanf("%d %d", &v, &n);
    int V[10];
    int top = 1;
    for (int i = 0; i < n; i++) {
        scanf("%d", &V[top++]);
    }

    int DP[20001] = { 0 };//状态————DP[i]表示容量为i时能装下的最大体积
    for (int i = 1; i <= n; i++) {
        for (int j = v; j >= V[i]; j--) {
            DP[j] = MAX(DP[j], V[i] + DP[j - V[i]]);
        }
    }
    printf("%d", v - DP[v]);

    return 0;
}
#endif



                                                                    //01背包
#if 0
#include <stdio.h>
#include<stdlib.h>


int MAX(int a, int b) {
    return a > b ? a : b;
}

int main() {

    int n, v;
    scanf("%d %d", &n, &v);
    int V[10] = { 0 };
    int W[10] = { 0 };
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int Vi, Wi;
        scanf("%d %d", &Vi, &Wi);
        V[++cnt] = Vi;
        W[cnt] = Wi;
    }


    int DP1[10][10] = { 0 };
    int DP2[10][10];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= v; j++) {
            if (V[i] > j) {
                DP1[i][j] = DP1[i - 1][j];
            }
            else {
                int last = j - V[i];
                int may = W[i] + DP1[i - 1][last];
                DP1[i][j] = MAX(may, DP1[i - 1][j]);
            }
        }
    }
    printf("%d\n", DP1[n][v]);

    for (int i = 1; i <= v; i++) {
        DP2[0][i] = -1;
    }
    for (int i = 0; i <= n; i++) {
        DP2[i][0] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= v; j++) {
            if (V[i] > j || DP2[i - 1][j - V[i]] == -1) {
                DP2[i][j] = DP2[i - 1][j];
            }
            else {
                int last = j - V[i];
                int may1 = W[i] + DP2[i - 1][last];
                int may2 = DP2[i - 1][j];
                DP2[i][j] = MAX(may1,may2 );
            }
        }
    }
    if (DP2[n][v] == -1) {
        printf("0");
    }
    else {
        printf("%d", DP2[n][v]);
    }

    return 0;
}
#endif


                                                                    //完全背包
#if 0
#include <stdio.h>
#include<stdlib.h>


int MAX(int a, int b) {
    return a > b ? a : b;
}

int main() {

    int n, v;
    scanf("%d %d", &n, &v);
    int V[15] = { 0 };
    int W[15] = { 0 };
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int Vi, Wi;
        scanf("%d %d", &Vi, &Wi);
        V[++cnt] = Vi;
        W[cnt] = Wi;
    }


    int DP1[15] = { 0 };
    int DP2[15];
    for (int i = 1; i <= n; i++) {
        for (int j = V[i]; j <= v; j++) {
            int last = j - V[i];
            DP1[j] = MAX(DP1[j], W[i] + DP1[last]);
        }
    }
    printf("%d\n", DP1[v]);



    for (int i = 1; i <= v; i++) {
        DP2[i] = -1;
    }
    DP2[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = V[i]; j <= v; j++) {
            int last = j - V[i];
            if (DP2[last] == -1) {
                continue;//如果装不满就保持上一次的最优解
            }
            else {
                DP2[j] = MAX(DP2[j], W[i] + DP2[last]);
            }
        }
    }
    if (DP2[v] == -1) {
        printf("0");
    }
    else {
        printf("%d", DP2[v]);
    }

    return 0;
}
#endif














