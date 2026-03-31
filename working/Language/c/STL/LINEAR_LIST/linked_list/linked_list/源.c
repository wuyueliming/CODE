#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>线性表<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*
typedef struct {
    int* array;
    int  size;
} Array;
Array array_creat(int size);
void array_free(Array* a);
int* array_at(Array* a, int index);
int array_size(Array* a);
void array_inflate(Array* a, int moreSpace);
int main()
{
    Array a = array_creat(100);

    int num = 0;
    while (num != -1) {
        scanf("%d", &num);
        if (num != -1) {
            a.array = num;
        }
    }

    return 0;
}
Array array_creat(int size) {
    Array a;
    a.size = size;
    a.array = (int*)malloc(sizeof(int) * size);
    return a;
}
void array_free(Array* a) {
    free(a->array);
    a->array = NULL;
    a->size = 0;
}
int* array_at(Array* a, int index) {//既然是自动增长数组，那就得在访问时发现空间够了就增加空间嘛
    int* add = &(a->array[index]);
    int block = 20;
    int moreSpace = (index / block + 1) * block - (a->size);
    if (index >= a->size) {
        array_inflate(a, moreSpace);
    }
    return add;

}
int array_size(Array* a) {

    return a->size;
}
void array_inflate(Array* a, int moreSpace) {
    int* p = (int*)malloc(sizeof(int) * (array_size(a) + moreSpace));
    for (int i = 0; i < a->size; i++) {
        p[i] = a->array[i];
    }
    array_free(a);
    a->array = p;
    a->size += moreSpace;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>翁恺讲的自动变长数组和链表pro>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


typedef struct _NODE {
    struct _NODE* last;
    int num;
    struct _NODE* next;
} NODE;
typedef struct _LIST {
    NODE* head;
    NODE* tail;
} LIST;
void add(LIST* Plist, int number);
void SHOW(LIST* Plist);
void release(LIST* Plist);
void antidromicSHOW(LIST* Plist);
int main()
{
    //做一个双向链表(add,release,search
    LIST list;
    list.head = NULL;
    list.tail = NULL;
    //正向输入数字，读到-1就停止
    int number = 0;
    while (number != -1) {
        scanf("%d", &number);
        if (number != -1) {
            add(&list, number);
        }
    }
    //逆向输出链表
    SHOW(&list);
    antidromicSHOW(&list);
    //释放空间
    release(&list);

    return 0;
}
void add(LIST* Plist, int number) {
    NODE* p = (NODE*)malloc(sizeof(NODE));//p是指向一个节点的指针(新建一个节点)
    p->num = number;
    p->next = NULL;//对节点进行初始化
    NODE* final = Plist->head;//final是已有链表的末尾

    if (final) {//如果已有链表中已经有节点了，就把新节点接到final上
        while (final->next) {
            final = final->next;//如果final的next还有节点的话，就指向next。循环结束后final就是链表的末尾
        }
        final->next = p;//把新节点接到链表的末尾上
    }
    else {//如果已有的链表一个节点都没有，就把新节点接到head上。
        Plist->head = p;
    }
    p->last = final;//双向链表，把新节点的向上的指针接到final上。
    Plist->tail = p;
}
void release(LIST* Plist) {
    NODE* q = Plist->head;
    for (NODE* p = q->next; p; q = p, p = p->next) {
        free(q);
    }
    free(q);
}
void SHOW(LIST* Plist) {
    NODE* p;
    for (p = Plist->head; p; p = p->next) {
        printf("%d ", p->num);
    }
}
void antidromicSHOW(LIST* Plist) {
    NODE* p;

    for (p = Plist->tail; p; p = p->last) {
        printf("%d ", p->num);
    }

}
*//*
void add(LIST* Plist, int number);

void SHOW(LIST* Plist);

void release(LIST* Plist);

void antidromicSHOW(LIST* Plist);

int main()
{
    //做一个双向链表(add,release,search
    LIST list;
    list.head = NULL;
    list.tail = NULL;

    int number = 0;
    while (scanf("%d", &number) != EOF) {
        add(&list, number);
    }
    //int arr[] = { 10,20,30,40 };
    //for (int i = 0; i < 4; i++) {
    //    add(&list, arr[i]);
    //}
    //逆向输出链表
    SHOW(&list);

    antidromicSHOW(&list);

    //释放空间
    release(&list);

    return 0;
}
void add(LIST* Plist, int number) {
    NODE* p = (NODE*)malloc(sizeof(NODE));//p是指向一个节点的指针(新建一个节点)
    p->num = number;//节点的值
    p->next = NULL;//节点的后继
    p->last = NULL;//节点的前驱

    NODE* final = Plist->tail;//拿到末尾节点
    NODE* head = Plist->head;//拿到头结点

    if (final) {//如果已有链表中已经有节点了，就把新节点接到final上
        //如果已有节点，把p节点挂到末尾节点的后面
        final->next = p;
        p->last = final;
        final = final->next;
        Plist->tail = final;
    }
    else {//如果已有的链表一个节点都没有，就把新节点接到head和tail上。
        Plist->head = p;
        Plist->tail = p;
    }
}

void release(LIST* Plist) {
    NODE* q = Plist->head;
    for (NODE* p = q->next; p; q = p, p = p->next) {
        free(q);
    }
    free(q);
}
void SHOW(LIST* Plist) {
    NODE* p;
    for (p = Plist->head; p; p = p->next) {
        printf("%d ", p->num);
    }
}
void antidromicSHOW(LIST* Plist) {
    NODE* p;

    for (p = Plist->tail; p; p = p->last) {
        printf("%d ", p->num);
    }

}*/
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
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                        //单向链表
#if 0
#define OK 1
#define Error 0
typedef int status;
typedef int ElementType;
typedef struct {//一般第一个节点叫做头节点，什么东西都不放，这样便于对节点进行操作，而不用将第一个节点和后面的节点分开讨论
    ElementType data;//一般从第二个节点开始数为第一节点。
    NODE* next;
} NODE;
typedef NODE* LIST;//创建头指针，指向第一个节点（头节点），以这个指针的名字为链表命名。



void initlist(LIST list);
void destroylist(LIST list);
int length_list(LIST list);
status search(LIST list, int index, ElementType* num);
status insert(LIST list, int index, ElementType num);
status search_for_place(LIST list, int* index, ElementType num);
status delete(LIST list, int index, ElementType* num);
void head_create(LIST list, int n);
void tail_create(LIST list, int n);


int main()
{
    LIST list;
    initlist(list);
    
    return 0;
}

void initlist(LIST list) {
    list = (LIST)malloc(sizeof(NODE));
    list->next = NULL;//只有一个头节点
}
void destroylist(LIST list) {
    NODE* p = list;
    NODE* q = p->next;
    while (p) {
        free(p);
        p = q;
        q = p->next;
    }
}
int length_list(LIST list) {
    int len = 0;
    NODE* p = list->next;
    while (p) {
        p = p->next;
        len++;
    }
    return len;
}

status search(LIST list, int index, ElementType* num) {
    int i = 1;//如果只用到第index个节点就从i=1，n=list开始。i和n指向的节点是对应的，如果i是0那么n就指向头节点，i是x那么n就指向第n个节点。
    NODE* n = list->next;
 /*   int i = 0;//如果需要用到第index-1个元素就从头节点开始。这样就把第一个节点包含进去了，避免了第一个节点的分类讨论。对应的循环条件是下面的<index-1
    NODE* n = list;*/
    while ( n && i < index) {//如果index是非法的说明index<1或者>len/len+1。一、如果是<1那么就会之间跳过循环，然后进入if语句判断给出错误。如果>=1，那么经过i-1次循环后
        n = n->next;//i就会等于index，就是想要找的第index个元素。二、如果是>len/len+1,那么就在i等于index之前n的地址就会为NULL跳出循环。
        i++;//总结：要么通过!n来判断index大于了范围，要么通过<index来判断小于了范围，以此来找出非法情况。正常情况就是表足够长，循环后i等于了index。
    }
    if (!n||i>index) {//循环出来后要么是非法情况：1.index>len/len+1，所以n是NULL了 2.index<=1，然后用这里的条件把等于i的筛选出来。
        return Error;//要么就是唯一的正常情况：i=index。注意while和if中的index也可以是index-1等等，那么对应的正常情况就是i=index-1.
    }
    else {
        *num = n->data;//上面while中&&的左式是以：1.i现在对应的节点是否为空来判断，说明index最大可以是表长len加1的。2.如果n换成n->next，说明index最大可以是表长len
        return OK;//1.的情况在while出来后n指向第index个节点  2.的出while的时候n指向第index+1个节点。
    }
}
status search_for_place(LIST list, int* index, ElementType num) {
    NODE* p = list->next;
    int cnt = 1;
    while (p && p->data != num) {
        p = p->next;
        cnt++;
    }
    if (!p) {
        return Error;
    }
    else {
        *index = cnt;
        return OK;
    }
}

status insert(LIST list, int index, ElementType num) {
    int i = 0;//从头节点开始，就可以避免在第一个元素插入新节点时出错。因为index为1时，需要找到第index个节点的前一个节点，这里的就是头节点
    NODE* n = list;//指向头节点
    while (n && i < index-1) {
        n = n->next;//结束后指向第index-1个节点
        i++;
    }
    if (!n||i<index-1) {//有可能第index-1个节点是一个空的。i<index-1用来判断插入位置是否合法的，index大于表长+1或者小于1时插入位置不合法。
        return Error;//index小于1是因为会直接跳过while循环，此时i=0，如果不排除就会在第一个节点插入，那么就index<=0时就都会插到第一个节点上
    }//注意：即使index为表长+100也可以用!n判断，因为index为len+1时，while循环出来就指向第len个也就是最后一个节点不为空。一旦大于len+1就会while出来后n指向一个空的
    //地址，第一个条件就能判断出问题。所以第二个条件主要是判断index小于1的非法情况。而第一个条件是用来判断index超出表长的情况。 
    else {
        NODE* q = (NODE*)malloc(sizeof(NODE));
        q->data = num;
        q->next = n->next;
        n->next = q;
        return OK;
    }
}

status delete(LIST list, int index, ElementType* num) {
    NODE* p = list;
    int cnt = 0;
    NODE* q;
    while (p->next && cnt < index-1) {//index最大只能是表长，所以用p->next来判断。
        p = p->next;
        cnt++;
    }
    if (!(p->next) || cnt > index - 1) {//就算while里面改成p忽略最后一个节点来判断，这里也是p->next
        return Error;
    }
    else {
        q = p->next;
        p->next = q->next;
        *num = q->data;
        free(q);
    }
}



void head_create(LIST list, int n) {
    list = (LIST)malloc(sizeof(NODE));
    list->next = NULL;
    for (int i = 0; i < n; i++) {
        NODE* p = (NODE*)malloc(sizeof(NODE));
        scanf(&p->data);
        p->next = list->next;
        list->next = p;
    }
}
void tail_create(LIST list, int n) {
    list = (LIST)malloc(sizeof(NODE));
    list->next = NULL;
    NODE* last = list;
    for (int i = 0; i < n; i++) {
        NODE* p = (NODE*)malloc(sizeof(NODE));
        scanf(&p->data);
        p->next = NULL;
        last->next = p;
        last = p;
    }
}
#endif








//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                    //循环链表（适用于要对首尾节点频繁操作）
#if 0
#define OK 1
#define Error 0
typedef int status;
typedef int ElementType;
typedef struct {
    ElementType data;
    NODE* next;
} NODE;
typedef NODE* LIST;


void initlist(LIST list);
void destroylist(LIST list);
int length_list(LIST list);
status search(LIST list, int index, ElementType* num);
status insert(LIST list, int index, ElementType num);
status search_for_place(LIST list, int* index, ElementType num);
status delete(LIST list, int index, ElementType* num);
void head_create(LIST list, int n);
void tail_create(LIST list, int n);


int main()
{
    LIST list;
    initlist(list);

    return 0;
}

void initlist(LIST list) {
    list = (LIST)malloc(sizeof(NODE));
    list->next = list;
}
void tail_create(LIST list, int n) {
    list = (LIST)malloc(sizeof(NODE));
    list->next = list;
    for (int i = 0; i < n; i++) {
        NODE* p = (NODE*)malloc(sizeof(NODE));
        scanf(&p->data);
        p->next = list->next;
        list->next = p;
        list = p;
    }
}
void head_create(LIST list, int n) {
    list = (LIST)malloc(sizeof(NODE));
    list->next = list;
    for (int i = 0; i < n; i++) {
        NODE* p = (NODE*)malloc(sizeof(NODE));
        scanf(&p->data);
        p->next = list->next->next;
        list->next = p;
        if (n == 0) {
            list = p;
        }
    }
}
void destroylist(LIST list) {
    NODE* p = (NODE*)malloc(sizeof(NODE));
    p = list->next;
    NODE* q = p->next;
    while (p != list) {
        free(p);
        p = q;
        q = q->next;
    }
}
int length_list(LIST list) {
    int i = 0;
    NODE* p = list->next;
    while (p->next != list) {
        i++;
        p = p->next;
    }
    return i;
}

status search(LIST list, int index, ElementType* num) {
    NODE* p = list->next;
    int cnt = 0;
    while (p->next != list && cnt<index) {
        cnt++;
        p = p->next;
    }
    if (p->next == list || cnt > index) {
        return Error;
    }
    else{
        *num = cnt;
        return OK;
    }
}
status insert(LIST list, int index, ElementType num) {
    NODE* p = list->next;
    int cnt = 0;

    while (p != list && cnt < index-1) {//应该是可以插在第一个到第len+1个
        cnt++;
        p = p->next;
    }
    if (p == list || cnt > index-1) {
        return Error;
    }
    else {
        NODE* new = (NODE*)mallic(sizeof(NODE));
        new->data = num;
        new->next = p->next;
        p->next = new;
    }
}
status search_for_place(LIST list, int* index, ElementType num) {
    NODE* p = list->next->next;
    int cnt = 1;

    while (p != list) {
        if (p->data == num) {
            *index = cnt;
            return OK;
        }
        p = p->next;
        cnt++;
    }
    return Error;
}
status delete(LIST list, int index, ElementType* num) {
    NODE* p = list->next;
    int cnt = 0;
    while (p->next != list && cnt < index - 1) {
        p = p->next;
        cnt++;
    }
    if (p->next == list || cnt > index-1) {
        return Error;
    }
    else {
        NODE* q = p->next;
        *num = q->data;
        p->next = q->next;
        free(q);
    }
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                    //循环双链表（就是把循环链表的单向链子改成双向链）
#if 0
#define OK 1
#define Error 0
typedef int status;
typedef int ElementType;
typedef struct {
    NODE* last;
    ElementType data;
    NODE* next;
} NODE;
typedef NODE* LIST;


void initlist(LIST list);
void destroylist(LIST list);
int length_list(LIST list);
status search(LIST list, int index, ElementType* num);
status insert(LIST list, int index, ElementType num);
status search_for_place(LIST list, int* index, ElementType num);
status delete(LIST list, int index, ElementType* num);
void head_create(LIST list, int n);
void tail_create(LIST list, int n);


int main()
{
    LIST list;
    initlist(list);

    return 0;
}

void initlist(LIST list) {
    list = (LIST)malloc(sizeof(NODE));
    list->next = list;
    list->last = list;
}
void tail_create(LIST list, int n) {
    list = (LIST)malloc(sizeof(NODE));
    list->next = list;
    list->last = list;
    for (int i = 0; i < n; i++) {
        NODE* p = (NODE*)malloc(sizeof(NODE));
        scanf(&p->data);
        p->next = list->next;
        p->last = list;
        list->next = p;
        list->last = p;
        list = p;
    }
}
void head_create(LIST list, int n) {
    list = (LIST)malloc(sizeof(NODE));
    list->next = list;
    list->last = list;
    for (int i = 0; i < n; i++) {
        NODE* p = (NODE*)malloc(sizeof(NODE));
        scanf(&p->data);
        p->next = list->next->next;
        p->last = list->next;
        list->next->next = p;
        list->next->next->last = p;
        if (n == 0) {
            list = p;
        }
    }
}
void destroylist(LIST list) {
    NODE* p = (NODE*)malloc(sizeof(NODE));
    p = list->next;
    NODE* q = p->next;
    while (p != list) {
        free(p);
        p = q;
        q = q->next;
    }
}
int length_list(LIST list) {
    int i = 0;
    NODE* p = list->next;
    while (p->next != list) {
        i++;
        p = p->next;
    }
    return i;
}

status search(LIST list, int index, ElementType* num) {
    NODE* p = list->next;
    int cnt = 0;
    while (p->next != list && cnt < index) {
        cnt++;
        p = p->next;
    }
    if (p->next == list || cnt > index) {
        return Error;
    }
    else {
        *num = cnt;
        return OK;
    }
}
status insert(LIST list, int index, ElementType num) {
    NODE* p = list->next;
    int cnt = 0;

    while (p != list && cnt < index - 1) {//应该是可以插在第一个到第len+1个
        cnt++;
        p = p->next;
    }
    if (p == list || cnt > index - 1) {
        return Error;
    }
    else {
        NODE* new = (NODE*)mallic(sizeof(NODE));
        new->data = num;
        new->next = p->next;
        new->last = p;
        p->next->last = new;
        p->next = new;
    }
}
status search_for_place(LIST list, int* index, ElementType num) {
    NODE* p = list->next->next;
    int cnt = 1;

    while (p != list) {
        if (p->data == num) {
            *index = cnt;
            return OK;
        }
        p = p->next;
        cnt++;
    }
    return Error;
}
status delete(LIST list, int index, ElementType* num) {
    NODE* p = list->next;
    int cnt = 0;
    while (p->next != list && cnt < index - 1) {
        p = p->next;
        cnt++;
    }
    if (p->next == list || cnt > index - 1) {
        return Error;
    }
    else {
        NODE* q = p->next;
        *num = q->data;
        p->next = q->next;
        q->last = p;
        free(q);
    }
}
#endif



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                    //首尾双链表（有一个头指针和一个尾指针）
                                                                    //看开头写的翁恺链表












//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#if 0
                                                                //(终极版)循环首尾双链表
#include<stdio.h>
#include<stdlib.h>                                       //头节点不放数据
#define OK 1
#define Error 0
typedef int status;
typedef int ElementType;


typedef struct node{
    //NODE* last;
    struct node* last;
    ElementType data;
    //NODE* next;
    struct node* next;
}NODE;
typedef struct {
    NODE* head;
    int length;
    NODE* tail;
}LIST;



void initlist(LIST* PL);
//void initlist(LIST list);
void destroylist(LIST* PL);
int length_list(LIST* PL);
status search(LIST* PL, int index, ElementType* num);
status insert(LIST* PL, int index, ElementType num);
status search_for_place(LIST* PL, int* index, ElementType num);
status delete(LIST* PL, int index, ElementType* num);
void head_create(LIST* PL, int n);
void tail_create(LIST* PL, int n);
void show(LIST* PL);
void reverse(LIST* list);

int main()
{
    LIST list;
    tail_create(&list, 5);//创建一个有五个节点的链表
    show(&list);
    int place = 6;
    int num = 0;
    printf("\n长度是：%d\n", list.length);
    
    
    insert(&list, list.length+1 , list.length+1);
    show(&list);
    printf("\n");//最后面插入一个节点
    
    
    
    delete(&list, list.length,&num);
    show(&list);
    printf("\n");//删除刚插进来的节点
    
    
    
    search(&list, 3, &num);//看看第3个位置上是多少
    printf("%d\n", num);
    
    
    search_for_place(&list, &place, 4);//看看哪一个节点的数据是4
    printf("%d\n", place);
    
    /*printf("hello\n");
    destroylist(&list);
    show(&list);
    printf("hello\n");*/

    reverse(&list);
    show(&list);


    return 0;//
}



void initlist(LIST* PL) {
    PL->head = (NODE*)malloc(sizeof(NODE));
    PL->tail = PL->head;
    PL->length = 0;
    PL->head->next = PL->head;
    PL->head->last = PL->head;
}
void destroylist(LIST* PL) {
    NODE* p = PL->head;
    NODE* q = p->next;
    do {
        free(p);
        p = q;
        q = q->next;
    } while (p != PL->head);
    PL->length = 0;
}
int length_list(LIST* PL) {
    NODE* p = PL->head;
    int cnt = 0;

    while (p->next!=PL->head) {
        cnt++;
        p = p->next;
    }
    return cnt;
}
void tail_create(LIST* PL, int n) {
    PL->head = (NODE*)malloc(sizeof(NODE));
    PL->tail = PL->head;
    PL->length = 0;
    //next是后  last也是后，命名注意
    PL->head->next = PL->head;
    PL->head->last = PL->head;
    for (int i = 0; i < n; i++) {
        NODE* p = (NODE*)malloc(sizeof(NODE));
        //scanf(&p->data);
        //0 1 
        p->data = i+1;
        p->next = PL->tail->next;
        p->last = PL->tail;
        //PL->tail = p;
        PL->tail->next = p;
        PL->head->last = p;
        PL->tail = p;
        PL->length += 1;
    }
    int m = 10;
}
void head_create(LIST* PL, int n) {
    PL->head = (NODE*)malloc(sizeof(NODE));
    PL->tail = PL->head;
    PL->length = 0;
    PL->head->next = PL->head;
    PL->head->last = PL->head;
    for (int i = 0; i < n; i++) {
        NODE* p = (NODE*)malloc(sizeof(NODE));
        //scanf(&p->data);
        p->data = i+1;
        p->next = PL->head->next;
        p->last = PL->head;
        PL->head->next = p;
        PL->head->next->last = p;
        PL->length += 1;
        if (PL->length == 0) {
            PL->tail = p;
        }
    }
}
status search(LIST* PL, int index, ElementType* num) {
    NODE* p = PL->head;
    int cnt = 0;
    while (p->next != PL->head && cnt < index) {
        p = p->next;
        cnt++;
    }
    if (p->next->data == PL->length || cnt > index) {
        return Error;
    }
    else {
        *num = p->data;
        return OK;
    }
}
status insert(LIST* PL, int index, ElementType num) {
    NODE* p = PL->head;
    int cnt = 0;

   /* while (p != PL->head && cnt < index-1) {
        cnt++;
        p = p->next;
    }*/
    do {
        cnt++;
        p = p->next;
    } while (p != PL->head && cnt < index - 1);
    if (p == PL->head || cnt > index-1) {
        return Error;
    }
    else {
        NODE* new = (NODE*)malloc(sizeof(NODE));
        new->data = num;
        new->next = p->next;
        new->last = p;
        p->next->last = new;
        p->next = new;
        PL->length += 1;
        return OK;
    }

}
status search_for_place(LIST* PL, int* index, ElementType num) {
    NODE* p = PL->head->next;
    int cnt = 1;

    while (p != PL->head && cnt < *index) {
        if (p->data == num) {
            *index = cnt;
            return OK;
        }
        else {
            cnt++;
            p = p->next;
        }
    }
    return  Error;
}
status delete(LIST* PL, int index, ElementType* num) {
    NODE* p = PL->head;
    int cnt = 0;

    while (p->next != PL->head && cnt < index - 1) {
        cnt++;
        p = p->next;
    }
    if (p->next == PL->head || cnt > index - 1) {
        return Error;
    }
    else {
        NODE* q = p->next;
        *num = q->data;
        p->next = q->next;
        PL->length -= 1;
        free(q);
        return OK;
    }
}


void show(LIST* PL){
    NODE* p = PL->head->next;
    for (int cnt = 0; cnt < PL->length; cnt++) {
        printf("%d", p->data);
        p = p->next;
    }
}


void reverse(LIST* list) {
    LIST newLIST;//创建一个新的链表
    LIST* newlist = &newLIST;//拿到新链表的指针
    
    newlist->head = (NODE*)malloc(sizeof(NODE));
    newlist->tail = newlist->head;//让头指针和尾指针指向头节点
    newlist->head->next = newlist->head;
    newlist->head->last = newlist->head;//让头节点形成双向循环

    NODE* current = list->head->next;//cur指向第一个节点
    NODE* cur_next = current->next;//cur_next指向cur的下一个节点

    while (current != newlist->head) {
        current->next = newlist->head->next;
        current->last = newlist->head;
        newlist->head->last = current;
        newlist->head->next = current;

        current = cur_next;
        cur_next = cur_next->next;

    }
    list = newlist;
}









NODE* Mergelist(NODE* pHead1, NODE* pHead2) {//两个有头节点的链表
    NODE* p1 = pHead1->next;
    NODE* p2 = pHead2->next;//亮哥链表的游标
    
    NODE* newhead = pHead1;
    NODE* final = pHead1;//先随便找表1或者表2的头节点作为新链表的头节点
    
    while (p1 != NULL && p2 != NULL) {
        if (p1->data <= p2->data) {//新链表不断蚕食表1和表2，新链表只会final的next指向比较后较小的那一个，但并不改变那个较小节点的next指向谁（每一次final指向
            final->next = p1;//较小的那一个就是在加长这个新表）
            final = p1;
            p1 = p1->next;
        }
        else {
            final->next = p2;
            final = p2;
            p2 = p2->next;
        }
    }
    /*if (p1 != NULL) {
        final->next = p1;
    }
    if (p2 != NULL) {
        final->next = p2;
    }*/
    final->next = p1 ? p1 : p2;
    
    free(pHead2);
}

NODE* Merge(NODE* pHead1, NODE* pHead2) {//牛客网上的题，给的是两个没有头节点的链表
    // write code here
    NODE* newhead = NULL;//虽然是两个没有头节点的链表，但是可以先建一个头节点，方便操作而不是像现在这样讨论是否为第一个节点。
    NODE* p1 = pHead1;//只要在两个链表合并完成后把头节点删除就可以了
    NODE* p2 = pHead2;
    NODE* final = newhead;

    int isFirst = 1;
    if (pHead1 == NULL)//就算没想到头节点来避免分类讨论，那么也没必要比较一个就把较小的那个节点单独拿出来（让这个节点接到新链表的最后一个节点上，并把这个
    {                                                                    //节点的next改成了原先的最后一个节点的next也就是NULL），这么做就切断了这个较小节点与
        return pHead2;                                                    //原来所在的链表的联系，无法直接通过较小节点的next使游标指针指向较小节点的下一个节点。
    }                                                                     //在较小节点与原来的链表的联系切断的情况下想要游标指针能遍历list1/list2就得让另一个
    else if (pHead2 == NULL)                                                //游标指针提前指向较小节点的下一个节点。
    {
        return pHead1;
    }
    while (pHead1 != NULL && pHead2 != NULL) {
        if (p1->data < p2->data) {
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
        else if (p1->data > p2->data) {
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
                p1->next = final->next;             //题目说要空间复杂度为O(1),时间复杂度为O(n)，所以我一个一个的挪这个节点。
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
//struct ListNode* Merge(struct ListNode* pHead1, struct ListNode* pHead2) {      
//    // write code here
//    struct ListNode* res = (struct ListNode*)malloc(sizeof(struct ListNode));
//    struct ListNode* dummy = res;
//    struct ListNode* l1 = pHead1;            //没想到有个华科的每次都新建一个节点，把值拿过来，代码少了这么多。
//    struct ListNode* l2 = pHead2;
//    while (l1 != NULL && l2 != NULL) {
//        struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));;
//        if (l1->val < l2->val) {
//            node->val = l1->val;
//            l1 = l1->next;
//        }
//        else {
//            node->val = l2->val;
//            l2 = l2->next;
//        }
//        res->next = node;
//        res = res->next;
//    }
//    res->next = l1 == NULL ? l2 : l1;
//    return dummy->next;
//}
#endif 
















































































































































































































