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
    //SHOW(&list);
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
*/
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
                                                                 //线性表的顺序存储
#define MAXSIZE 100//顺序表有最大长度，数组的大小是不可变的。
#define OK 1
#define Error 0
typedef int ElementType;
typedef int status;
typedef struct list {
    ElementType arr[MAXSIZE];
    int len;//MAXSIZE是最大能容纳数据的长度，而这里length表示的是链表实际使用的长度
} LIST;


status  search_place(LIST* list, ElementType num, int* place);//找一个数字,用指针返回找到的位置
status search_num(LIST* list, int place, int* num);//根据位置找数据,并用指针把给的num值赋值成找到的值。函数返回值为状态
status insert(LIST* list, int place, int num);
status delete(LIST* list, int place, int* num);
status tail_add(LIST* list, int num);
int main()
{
    LIST* list = (LIST*)malloc(sizeof(LIST));//创建一个指向LIST的指针，并用malloc让它指向一个申请来的LIST
    list->len = 0;
    if (tail_add(list, 9)) {
        printf("%d\n", list->arr[0]);
    }
    else {
        printf("hello");
    }

    int place = 2;
    search_place(list, 9, &place);
    printf("%d", place);


    return 0;
}
status search_place(LIST* list, ElementType num, int* place) {
    int i = 0;
    ElementType a = num;
    while (i < list->len) {
        if (list->arr[i] == a) {
            *place = i + 1;
            return OK;
        }
        else {
            i++;
        }
    }
    return NULL;
}

status search_num(LIST* list, int place, int* num) {
    if (list->len == 0 || place <0 || place>list->len + 1) {
        return Error;//下标很容易弄混淆，注意分清是下标还是元素位置。分清后，同类进行比较，不要混着比较
    }//下标与元素位置的关系是加一。
    *num = list->arr[place - 1];
    return OK;
}
status insert(LIST* list, int place, int num) {
    if (list->len >= MAXSIZE) {
        return Error;
    }
    if (place<1 || place>list->len + 1) {
        return Error;//至少需要一个元素才能插，如果是一个空表，那么这里就直接返回了
    }

    for (int i = list->len - 1; i >= place - 1; i--) {
        list->arr[i + 1] = list->arr[i];
    }

    list->arr[place - 1] = num;
    list->len++;
    return OK;
}
status delete(LIST* list, int place, int* num) {
    if (list->len == 0) {
        return Error;
    }
    if (place<1 || place>list->len) {
        return Error;
    }
    *num = list->arr[place - 1];
    for (int i = place - 1; i < list->len; i++) {
        list->arr[i] = list->arr[i + 1];
    }
    list->len--;
    return OK;
}
status tail_add(LIST* list, int num) {
    int last = list->len;
    if (list->len == 0) {
        list->arr[0] = num;
        list->len++;
    }
    else {
        list->arr[last] = num;
        list->len++;
    }
    return OK;
}
