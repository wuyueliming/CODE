#define _CRT_SECURE_NO_WARNINGS  1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                                              //最大子列和
#if 0
int main()
{
    int K = 0;
    scanf("%d", &K);
    int* arr = (int*)malloc(sizeof(int) * K);

    for (int i = 0; i < K; i++) {
        scanf("%d", &arr[i]);
    }
    int max = 0;
    int cur = 0;
    for (int i = 0; i < K; i++) {
        cur = 0;
        for (int j = i; j < K; j++) {
            cur += arr[j];
            if (cur >= max) {
                max = cur;
            }
        }
    }

    printf("%d", max);

    return 0;
}

#endif



//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                                                     //每k个结点翻转
#if 0
#include<stdio.h>
#define maxsize 100001//数字头太大存不下
int main()
{
    int head, N, K;
    scanf("%d %d %d", &head, &N, &K);
    int data[maxsize];
    int link[maxsize];

    int add, dta, nxt;
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &add, &dta, &nxt);
        data[add] = dta;
        link[add] = nxt;
    }

    int sortList[maxsize];
    int count = 0;// 必须用count重新数一遍有多少个结点，因为有独立结点
    while (head != -1) {
        sortList[count] = head;
        head = link[head];
        count++;
    }

    for (int i = 0; i < count - count % K; i += K) {
        //反转链表
        for (int j = 0; j < K / 2; j++) {
            int t = sortList[i + j];
            // 当K = 4, 0要和3交换，1要和2交换，算一下可知相当于 i+j索引元素与i+K -j-1 进行交换
            sortList[i + j] = sortList[i + K - j - 1];
            sortList[i + K - j - 1] = t;
        }
    }
    for (int i = 0; i < count - 1; i++) {
        printf("%05d %d %05d\n", sortList[i], data[sortList[i]], sortList[i + 1]);
    }
    printf("%05d %d -1\n", sortList[count - 1], data[sortList[count - 1]]);//必须用count，因为输入数据有可能有独立结点
    return 0;
}
#endif





//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                                              //判断栈的弹出序列
#if 0

#include<stdio.h>

int is_order(const int* push, const int* pop, int N, int M) {
    int x = 0, y = 0;
    int stack[M];
    int top = -1;
    for (int i = 0; i < N && top < M; i++) {//注意栈的大小为M，序列大小为N。可能M是小于N的。
        stack[++top] = push[x++];
        while (top != -1 && y < N && top < M && stack[top] == pop[y]) {//防止越界
            top--;
            y++;
        }
    }

    if (y == N) {
        return 1;
    }
    else {
        return 0;
    }

}

int main()
{
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);
    int stack[N];
    for (int i = 0; i < N; i++) {
        stack[i] = i + 1;
    }

    int arr[N];

    for (int i = 0; i < K; i++) {
        for (int i = 0; i < N; i++) {
            scanf("%d", &arr[i]);
        }
        if (is_order(stack, arr, N, M)) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }

    return 0;
}
#endif

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                                               //KMP
#if 0
void get_next(char* ptn, int* next) {
    next[0] = -1;
    int len = strlen(ptn);

    for (int i = 1; i < len; i++) {
        int t = next[i - 1];

        while (ptn[t + 1] != ptn[i] && t >= 0) {
            t = next[t];
        }
        if (ptn[t + 1] == ptn[i]) {
            next[i] = t + 1;
        }
        else {
            next[i] = -1;
        }

    }

}

int is_son(char* str, char* ptn) {
    int len1 = strlen(str);
    int len2 = strlen(ptn);
    int p1 = 0, p2 = 0;
    if (len1 < len2) {
        return -1;
    }
    int* next = (int*)malloc(sizeof(int) * len2);
    get_next(ptn, next);
    while (p1 < len1 && p2 < len2) {
        if (str[p1] == ptn[p2]) {
            p1++;
            p2++;
        }
        else if (!p2) {
            p1++;
        }
        else if (p2 > 0) {
            p2 = next[p2 - 1] + 1;
        }
    }
    return p2 == len2 ? p1 - len2 : -1;

}

int main()
{
    char string[1001];//注意大小
    char pattern[1001];
    int n = 0;
    int ret = 0;
    scanf("%s", string);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", pattern);
        if ((ret = is_son(string, pattern)) != -1) {
            printf("%s\n", &string[ret]);
        }
        else {
            printf("Not Found\n");
        }
    }

    return 0;
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                       //树的同构

#if 0
typedef struct NODE {
    char data;
    int left;
    int right;
}NODE;
NODE M[10];
NODE N[10];
int m, n;

int hehe(int x1, int x2, int y1, int y2) {
    int retm1 = -1, retm2 = -1;
    int retn1 = -1, retn2 = -1;
    int ret1 = 0, ret2 = 0;

    if (x1 >= m && x2 >= m && y1 >= n && y2 >= n) {
        return 1;
    }
    else if (x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0) {
        return 1;
    }

    if (M[x1].data == N[y1].data && M[x2].data == N[y2].data) {
        retm1 = hehe(M[x1].left, M[x1].right, N[y1].left, N[y1].right);
        retn1 = hehe(M[x2].left, M[x2].right, N[y2].left, N[y2].right);
        ret1 = retm1 && retn1;
    }
    else if ((M[x1].data == N[y2].data && M[x2].data == N[y1].data)) {
        retm2 = hehe(M[x1].left, M[x1].right, N[y2].left, N[y2].right);
        retn2 = hehe(M[x2].left, M[x2].right, N[y1].left, N[y1].right);
        ret2 = retm2 && retn2;
    }
    else {
        return 0;
    }
    return ret1 || ret2;
}
void get_first(NODE* M, int m, int* f1, NODE* N, int n, int* f2) {//找到数组的根节点的下标，这里是根据测试用例假装做出来的
    for (int i = 0; i < m; i++) {  //正确做法是遍历所有结点的left和right，看哪一个节点的下标是没出现过的，因为没有节点的left和right是指向根节点的。
        if (M[i].data == 'A') {
            *f1 = i;
        }
    }
    for (int j = 0; j < n; j++) {
        if (N[j].data == 'A') {
            *f2 = j;
        }
    }

}
int judge(NODE* M, int m, NODE* N, int n) {
    if (m != n) {
        return 0;
    }
    else if (m == 0 || n == 0) {
        return 1;
    }
    int f1 = 0, f2 = 0;
    get_first(M, m, &f1, N, n, &f2);
    if (M[f1].data != N[f2].data) {
        return 0;
    }
    if (f1 > m || f2 > n) {
        return 1;
    }

    int m1 = M[f1].left, m2 = M[f1].right, n1 = N[f2].left, n2 = N[f2].right;

    return hehe(m1, m2, n1, n2);
}


int main()
{
    char data = 0;
    char l = 0, r = 0;


    scanf("%d", &m);
    getchar();
    for (int i = 0; i < m; i++) {
        scanf(" %c %c %c", &data, &l, &r);
        M[i].data = data;
        if (l >= '0' && l <= '9') {
            M[i].left = l - '0';
        }
        else {
            M[i].left = '-';
        }
        if (r >= '0' && r <= '9') {
            M[i].right = r - '0';
        }
        else {
            M[i].right = '-';
        }
    }


    scanf("%d", &n);
    getchar();
    for (int j = 0; j < n; j++) {
        scanf(" %c %c %c", &data, &l, &r);
        N[j].data = data;
        if (l >= '0' && l <= '9') {
            N[j].left = l - '0';
        }
        else {
            N[j].left = '-';
        }
        if (r >= '0' && r <= '9') {
            N[j].right = r - '0';
        }
        else {
            N[j].right = '-';
        }
    }

    if (!judge(M, m, N, n)) {
        printf("No");
    }
    else {
        printf("Yes");
    }

    return 0;
}
#endif 



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                              //层序遍历
#if 0
typedef struct NODE {
    int left;
    int right;
}NODE;
NODE T[10];
int cnt;
int t;



void Traverse(NODE* T, int cnt, int t) {
    int* list = (int*)malloc(sizeof(int) * cnt);
    int head = 0, rear = 0;//因为数组大小等于节点数，所以不用循环数组，大小刚刚好。
    list[rear++] = t;

    int* order = (int*)malloc(sizeof(int) * cnt);
    int top = -1;
    for (int i = 0; i < cnt; i++) {
        order[i] = -1;
    }


    while (head != rear) {
        int temp = list[head++];
        order[++top] = temp;
        if (T[temp].left >= 0 && T[temp].left <= 9) {
            list[rear++] = T[temp].left;
        }
        if (T[temp].right >= 0 && T[temp].right <= 9) {
            list[rear++] = T[temp].right;
        }
    }

    /*for (int i = 0; i < top; i++) {
        printf("%d ", order[i]);
    }
    printf("%d", order[top]);*/

    for (int i = 0; i < top; i++) {
        int x = order[i];
        if (T[x].left > cnt && T[x].right > cnt)
            printf("%d ", order[i]);
    }
    if (T[order[top]].left > cnt && T[order[top]].right > cnt)
        printf("%d", order[top]);

}


int main()
{
    char l = 0, r = 0;

    int check[10] = { 0 };
    scanf("%d", &cnt);
    getchar();
    for (int i = 0; i < cnt; i++) {
        scanf(" %c %c", &l, &r);
        if (l >= '0' && l <= '9') {
            l = T[i].left = l - '0';
            check[l] = 1;
        }
        else {
            T[i].left = '-';
        }
        if (r >= '0' && r <= '9') {
            r = T[i].right = r - '0';
            check[r] = 1;
        }
        else {
            T[i].right = '-';
        }
    }
    for (int i = 0; i < cnt; i++) {
        if (!check[i]) {
            t = i;
            break;
        }
    }

    Traverse(T, cnt, t);


    return 0;
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                             //根据非递归中序遍历的栈操作来获得树及其后序遍历
#if 0
typedef struct NODE {
    int data;
    struct NODE* left;
    struct NODE* right;
}NODE;

#define max 31
void in_pre_build(int* inorder, int* preorder, int N, NODE** root) {
    if (N == 0) {
        return 0;
    }

    *root = (NODE*)malloc(sizeof(NODE));
    (*root)->data = preorder[0];
    (*root)->left = NULL;
    (*root)->right = NULL;
    //左子树的中序和先序
    int L_len = 0;
    int* inorder_L = (int*)malloc(sizeof(int) * max);
    int* preorder_L = (int*)malloc(sizeof(int) * max);
    //右子树的中序和先序
    int R_len = 0;
    int* inorder_R = (int*)malloc(sizeof(int) * max);
    int* preorder_R = (int*)malloc(sizeof(int) * max);

    int sign = 1;
    for (int i = 0; i < N; i++) {
        if (inorder[i] == preorder[0]) {
            sign = 0;
        }
        else {
            if (sign) {
                inorder_L[L_len++] = inorder[i];
            }
            else {
                inorder_R[R_len++] = inorder[i];
            }
        }
    }

    for (int i = 1; i < N; i++) {
        if (i <= L_len) {
            preorder_L[i - 1] = preorder[i];
        }
        else {
            preorder_R[i - 1 - L_len] = preorder[i];
        }
    }

    in_pre_build(inorder_L, preorder_L, L_len, &(*root)->left);
    in_pre_build(inorder_R, preorder_R, R_len, &(*root)->right);

}

void get_order(int* inorder, int* preorder, int N)
{
    int top_in = -1, top_pre = -1;
    char opt[5];
    int dta = 0;
    int stack[max];
    int top = -1;
    for (int i = 0; i < 2 * N; i++) {
        scanf("%s", opt);
        if (!strcmp(opt, "Push")) {
            scanf("%d", &dta);
            preorder[++top_pre] = dta;
            stack[++top] = dta;
        }
        else {
            inorder[++top_in] = stack[top--];
        }
    }

}
void post_traverse(NODE* head) {
    if (head) {
        post_traverse(head->left);
        post_traverse(head->right);
        printf("%d ", head->data);
    }
}

int main()
{
    int N = 0;
    scanf("%d", &N);
    getchar();

    int inorder[max];
    int preorder[max];
    get_order(inorder, preorder, N);

    NODE* head = NULL;
    in_pre_build(inorder, preorder, N, &head);

    post_traverse(head);

    return 0;
}
#endif 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                         //判断多种插入序列构成的二叉搜索树是否一样
#if 0
typedef struct NODE {
    int data;
    struct NODE* left;
    struct NODE* right;
}NODE;


NODE* build_tree(int* arr, int N) {
    NODE* head = NULL;
    NODE* cur = head;
    NODE* pre = head;
    int sign = 0;
    for (int i = 0; i < N; i++) {
        if (head == NULL) {
            head = (NODE*)malloc(sizeof(NODE));
            head->data = arr[0];
            head->left = head->right = NULL;
            cur = head;
            pre = head;
            continue;
        }
        else {
            while (cur) {
                if (arr[i] > cur->data) {
                    pre = cur;
                    sign = 0;
                    cur = cur->right;
                }
                else if (arr[i] < cur->data) {
                    pre = cur;
                    sign = 1;
                    cur = cur->left;
                }
            }
            if (!sign) {
                NODE* t = pre->right = (NODE*)malloc(sizeof(NODE));
                t->left = t->right = NULL;
                t->data = arr[i];
            }
            else {
                NODE* t = pre->left = (NODE*)malloc(sizeof(NODE));
                t->left = t->right = NULL;
                t->data = arr[i];
            }
            cur = head;//一定要重置。
        }
    }
    return head;
}

void    get_inorder(NODE* head, int* order, int N) {
    int top = -1;
    int i = 0;
    NODE* p = head;
    NODE* q;
    NODE* stack[10] = { 0 };
    while (top != -1 || p) {
        while (p) {
            stack[++top] = p;
            p = p->left;
        }
        if (!p) {
            q = stack[top--];
            order[i++] = q->data;
            p = q->right;
        }
    }
}
void    get_preorder(NODE* head, int* order, int N) {
    int top = -1;
    int i = 0;
    NODE* p = head;
    NODE* stack[10] = { 0 };
    while (top != -1 || p) {
        while (p) {
            stack[++top] = p;
            order[i++] = p->data;
            p = p->left;
        }
        if (!p) {

            p = stack[top--]->right;

        }
    }
}
void get_postorder1(NODE* head, int* arr, int N) {
    static int i = 0;//static，对于多组数据没有进行重置，最终导致数组越界
    if (head) {
        get_postorder1(head->left, arr, N);
        get_postorder1(head->right, arr, N);
        arr[i++] = head->data;
    }
}
void get_postorder2(NODE* head, int* arr, int N) {
    static int j = 0;
    if (head) {
        get_postorder2(head->left, arr, N);
        get_postorder2(head->right, arr, N);
        arr[j++] = head->data;
    }
}

int is_same(int* src, int* ptn, int N) {
    NODE* A = build_tree(src, N);
    int src_in[10] = { 0 };
    int src_pre[10] = { 0 };
    int src_post[200] = { 0 };

    NODE* B = build_tree(ptn, N);
    int ptn_in[10] = { 0 };
    int ptn_pre[10] = { 0 };
    int ptn_post[200] = { 0 };

    get_inorder(A, src_in, N);
    get_inorder(B, ptn_in, N);
    get_preorder(A, src_pre, N);
    get_preorder(B, ptn_pre, N);
    get_postorder1(A, src_post, N);
    get_postorder2(B, ptn_post, N);

    int sign1 = 1;
    int sign2 = 1;
    int sign3 = 1;
    for (int i = 0; i < N; i++) {
        if (src_in[i] != ptn_in[i])
            sign1 = 0;
    }
    for (int i = 0; i < N; i++) {
        if (src_pre[i] != ptn_pre[i])
            sign2 = 0;
    }
    for (int i = 0; i < N; i++) {
        if (src_post[i] != ptn_post[i])
            sign3 = 0;
    }
    return sign1 && sign2 && sign3;
}

int main()
{
    int N, L;
    int src[10] = { 0 };
    int ptn[10] = { 0 };
    while (scanf("%d %d", &N, &L) != EOF) {
        if (!N) {
            break;
        }
        for (int i = 0; i < N; i++) {
            scanf("%d", &src[i]);
        }
        for (int j = 0; j < L; j++) {
            for (int i = 0; i < N; i++) {
                scanf("%d", &ptn[i]);
            }
            if (is_same(src, ptn, N)) {
                printf("Yes\n");
            }
            else {
                printf("No\n");
            }
        }
    }


    return 0;
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                             //二叉树的操作集
#if 0
typedef int ElementType;
typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal(BinTree BT) {
    if (BT) {
        printf("%d ", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}
void InorderTraversal(BinTree BT) {
    if (BT) {
        PreorderTraversal(BT->Left);
        printf("%d ", BT->Data);
        PreorderTraversal(BT->Right);
    }
}

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp == MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp == MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}

BinTree Insert(BinTree BST, ElementType X) {
    if (!BST) {
        BST = (struct TNode*)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }
    if (X > BST->Data) {
        BST->Right = Insert(BST->Right, X);
    }
    else if (X < BST->Data) {
        BST->Left = Insert(BST->Left, X);
    }
    return BST;
}
BinTree Delete(BinTree BST, ElementType X) {
    if (!BST) {
        printf("Not Found\n");
        return NULL;
    }
    if (X > BST->Data) {
        BST->Right = Delete(BST->Right, X);
    }
    else if (X < BST->Data) {
        BST->Left = Delete(BST->Left, X);
    }
    else {
        if (BST->Left && BST->Right) {
            struct TNode* t = FindMin(BST->Right);
            BST->Data = t->Data;
            BST->Right = Delete(BST->Right, BST->Data);
        }
        else {

            if (!BST->Right) {
                return BST->Left;
            }
            else if (!BST->Left) {
                return  BST->Right;
            }
        }
    }
    return BST;
}
Position Find(BinTree BST, ElementType X) {
    while (BST) {
        if (X > BST->Data) {
            BST = BST->Right;
        }
        else if (X < BST->Data) {
            BST = BST->Left;
        }
        else {
            return BST;
        }
    }
    return NULL;
}




Position FindMin(BinTree BST) {
    if (!BST) {
        return NULL;
    }
    while (BST->Left) {
        BST = BST->Left;
    }
    return BST;
}
Position FindMax(BinTree BST) {
    if (!BST) {
        return NULL;
    }
    while (BST->Right) {
        BST = BST->Right;
    }
    return BST;
}
#endif 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 
                                                                    //AVL树插入
#if 0
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
enum BF { LH = 1, EH = 0, RH = -1 };//  bf为左子树高度减去右子树高度
typedef struct NODE {
    int data;
    struct NODE* left;
    struct NODE* right;
    enum BF bf;
}NODE;
typedef int status;


void L_rotate(NODE** T) {
    NODE* R = (*T)->right;
    (*T)->right = R->left;
    R->left = *T;
    *T = R;
}

void R_rotate(NODE** T) {
    NODE* L = (*T)->left;
    (*T)->left = L->right;
    L->right = *T;
    *T = L;
}

void left_balance(NODE** T) {//在insert中T的左子树比右子树高度超过2时才会调用当前函数，所以T的bf默认为2
    NODE* L = (*T)->left;
    NODE* LR = L->right;
    switch (L->bf) {
    case LH://T本来是左子树高，如果L也是左高就直接右旋
        (*T)->bf = L->bf = EH;//右旋后会平衡
        R_rotate(T);
        break;
    case RH://如果L是右高，就先左旋(以L为根节点的左旋)，让L变成左高，然后再右旋(以T为根节点)
        switch (LR->bf) {
        case LH:
            (*T)->bf = RH;
            L->bf = EH;
            break;
        case EH:
            (*T)->bf = L->bf = EH;//先左旋后右旋后，各个节点的bf值。
            break;
        case RH:
            (*T)->bf = EH;
            L->bf = LH;
            break;
        }
        LR->bf = EH;
        L_rotate(&(*T)->left);
        R_rotate(T);
    }
}

void right_balance(NODE** T) {//bf默认为-2
    NODE* R = (*T)->right;
    NODE* RL = R->left;
    switch (R->bf) {
    case RH:
        (*T)->bf = R->bf = EH;
        L_rotate(T);
        break;
    case LH:
        switch (RL->bf) {
        case RH:
            (*T)->bf = LH;
            R->bf = EH;
            break;
        case EH:
            (*T)->bf = R->bf = EH;
            break;
        case LH:
            (*T)->bf = EH;
            R->bf = RH;
            break;
        }
        RL->bf = EH;
        R_rotate(&(*T)->right);
        L_rotate(T);
    }
}

status insert_AVL(NODE** T, int x, status* taller) {
    if (!(*T)) {
        *T = (NODE*)malloc(sizeof(NODE));
        (*T)->left = (*T)->right = NULL;
        (*T)->data = x;
        (*T)->bf = EH;
        *taller = true;
    }
    else
    {
        if (x == (*T)->data) {
            *taller = false;
            return false;
        }
        else if (x < (*T)->data) {
            if (!insert_AVL(&(*T)->left, x, taller)) {//递归的进入左子树插入
                return false;
            }
            if (*taller) {//插入完了节点后，从递归栈中一层一层的返回，如果树变高了就进入switch
                switch ((*T)->bf) {
                case LH:
                    *taller = false;//在这层递归中，如果进入switch说明T的左子树的根节点一定是EH，才能使taller为true，在这一层进入switch，所以*T->left的bf从EH增高
                    left_balance(T);//后要么是LH，要么是RH。             如果插入前左高，那么现在bf就会超过2，进入left_balance处理
                    break;
                case EH:
                    *taller = true;//如果在左子树中插入之前是等高的，那么插入后树就变高
                    (*T)->bf = LH;//只有插入前是等高的，插入后树才会变高。
                    break;
                case RH:
                    *taller = false;//如果插入前右边高，那么现在等高。
                    (*T)->bf = EH;
                    break;
                }
            }
        }
        else if (x > (*T)->data) {
            if (!insert_AVL(&(*T)->right, x, taller)) {//每一层递归都是比过大小进入不同的if分支语句，知道节点是在
                return false;                    //当前节点的左子树还是右子树中插入的。
            }
            if (*taller) {
                switch ((*T)->bf) {
                case LH:
                    *taller = false;
                    (*T)->bf = EH;
                    break;
                case EH:
                    *taller = true;
                    (*T)->bf = RH;
                    break;
                case RH:
                    *taller = false;
                    right_balance(T);
                    break;
                }
            }
        }
    }
    return true;
}

void in_T(NODE* head)
{
    if (head) {
        in_T(head->left);
        printf("%d ", head->data);
        in_T(head->right);
    }
}

int main()
{
    NODE* head = NULL;
    status taller;
    int t, cnt;
    scanf("%d", &cnt);
    for (int i = 0; i < cnt; i++) {
        scanf("%d", &t);
        insert_AVL(&head, t, &taller);
    }
    printf("%d", head->data);

    return 0;
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 
                                                               //根据序列建立完全二叉搜索树
#if 0
typedef struct NODE {
    int data;
    struct NODE* left;
    struct NODE* right;
}NODE;

void sort(int* arr, int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

int get_root(int* inorder, int L, int R) {
    if (R == L) {
        return L;
    }
    int cnt = R - L + 1;//节点数
    int level = 0;//cnt个节点构成完全二叉树后的层数
    for (int i = 0; ; i++) {
        if (cnt <= pow(2, i) - 1) {
            level = i;
            break;
        }
    }
    int L_cnt, R_cnt;//不要最后一层的节点个数
    L_cnt = pow(2, level - 2) - 1;
    R_cnt = pow(2, level - 2) - 1;

    int last_cnt = cnt - L_cnt - R_cnt - 1;//最后一层的节点数
    int sign = last_cnt / (int)pow(2, level - 2);//判断最后一层的节点只在根节点的左子树上，还是即在左子树上也在右子树上。


    L_cnt += sign ? pow(2, level - 2) : last_cnt;

    return L + L_cnt;//根节点下标
}


void build_tree(NODE** head, int* inorder, int L, int R) {
    if (R < L) {
        return;
    }
    int index = get_root(inorder, L, R);
    int root = inorder[index];
    (*head) = (NODE*)malloc(sizeof(NODE));
    (*head)->data = root;
    (*head)->left = (*head)->right = NULL;

    build_tree(&(*head)->left, inorder, L, index - 1);
    build_tree(&(*head)->right, inorder, index + 1, R);
}

void level_traverse(int* level, int N, NODE* T) {
    NODE** list = (NODE**)malloc(sizeof(NODE*) * N);
    int head = 0, rear = 0;
    int top = -1;
    list[rear++] = T;
    NODE* p;
    while (head != rear) {
        p = list[head++];

        if (!p) {
            return;
        }
        if (p->left) {
            list[rear++] = p->left;
        }
        if (p->right) {
            list[rear++] = p->right;
        }
        if (head == rear) {
            printf("%d", p->data);
        }
        else {
            printf("%d ", p->data);
        }
    }
}

int main()
{
    int N = 0;
    scanf("%d", &N);
    int* token = (int*)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &token[i]);
    }

    sort(token, N);
    NODE* head = NULL;
    build_tree(&head, token, 0, N - 1);

    int* level = (int*)malloc(sizeof(int) * N);
    level_traverse(level, N, head);

    //printf("%d", level[0]); 
    //for (int i = 0; i < N - 1; i++) {
    //    printf("%d ", level[i]);
    //}
    //printf("%d", level[N - 1]);

    return  0;
}

#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                      //建立堆，打印从某节点到根节点的路径
#if 0
void insert(int* data, int* N, int x) {
    data[++*N] = x;
    if (*N == 1)return;

    int i;
    for (i = *N; i > 1 && x < data[i / 2]; i /= 2) {//大于1的时候进入，等于1说明已经是根节点了，不需要继续比较了
        data[i] = data[i / 2];
    }
    data[i] = x;
}

int delete(int* data, int* N) {//本质上是一个根节点，和它的左右子树(已经是两个堆)。将一个节点和两个堆合成一个堆的过程。
    int min = data[1];
    data[1] = data[(*N)--];//把根节点和最后一个元素交换，最后一个元素退出堆中。

    int parent = 1;
    int temp = data[parent];
    for (int child = parent * 2; child <= *N; child *= 2) {
        if (child < *N && data[child + 1] < data[child]) {//找到左右子树中较小的那一个
            child++;
        }
        if (temp <= data[child]) {//最小堆，从上往下值是递增的，找到左右子树中较小的那一个之后。如果比进入该循环时的夫节点更大就不用交换
            break;    //将这一个节点的值向上移，然后往下一层去寻找。如果找到比它更小的就break，将开始的parent的值插入到这里。
        }                      //简单来说就是在一个递增的序列向后遍历，找到自己的位置然后插入，思路和直接插入排序几乎一样

        data[parent] = data[child];
        parent = child;
    }
    data[parent] = temp;//退出循环后，parent指向原本的parent现在应该插入的位置


    return min;
}

void  build_heap(int* data, int N) {
    for (int i = N / 2; i > 0; i--) {
        int parent = i;
        int temp = data[parent];
        for (int child = parent * 2; child <= N; child *= 2) {
            if (child < N && data[child + 1] < data[child]) {//找到左右子树中较小的那一个
                child++;
            }
            if (temp <= data[child]) {//最小堆，从上往下值是递增的，找到左右子树中较小的那一个之后。如果比进入该循环时的夫节点更大就不用交换
                break;    //将这一个节点的值向上移，然后往下一层去寻找。如果找到比它更小的就break，将开始的parent的值插入到这里。
            }                      //简单来说就是在一个递增的序列向后遍历，找到自己的位置然后插入，思路和直接插入排序几乎一样

            data[parent] = data[child];
            parent = child;
        }
        data[parent] = temp;//退出循环后，parent指向原本的parent现在应该插入的位置
    }
}


int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int* data = (int*)malloc(sizeof(int) * (n + 1));
    int x = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        insert(data, &cnt, x);
    }




    int index = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d", &index);
        while (index) {
            if (index / 2 == 0) {
                printf("%d\n", data[index]);
                break;
            }
            else {
                printf("%d ", data[index]);
                index /= 2;
            }
        }
    }


    return 0;
}
#endif 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                   //并查集
#if 0
#define max 10001
int cmp[max], cnt, size;


int find(int p1) {
#if 0
    while (cmp[p1] > 0) {
        p1 = cmp[p1];
    }
    return p1;
#endif
    if (cmp[p1] < 0) {//——————做路径压缩和不做的区别其实就是在大O(N)的N前面乘一个logN还是乘一个常数，所以当N足够大的时候才能体现路径压缩的优势 
        return p1;
    }
    else {
        return cmp[p1] = find(cmp[p1]);//路径压缩————————和kmp算法中next数组的优化一样
    }

}
void uni(int p1, int p2) {
    static int i = 1;
    int r1 = find(p1);
    int r2 = find(p2);
#if 1
    if (r1 != r2) {
        if (cmp[r1] > cmp[r2]) {//将个数小的树并入个数大的树中，保证树的高度最小
            cmp[r2] += cmp[r1];
            cmp[r1] = r2;
        }
        else {
            cmp[r1] += cmp[r2];                
            cmp[r2] = r1;
        }
    }
#endif                            //<<<<<<<——————两种合并树的方式都是按秩归并，上面是按节点数，下面是按树高
#if 0
    if (r1 != r2) {
        if (cmp[r1] > cmp[r2]) {
            cmp[r1] = r2;
        }
        else if(cmp[r1] < cmp[r2]){
            cmp[r2] = r1;
        }else{//按树的高度合并，如果高度相等则合并后高度+1
            cmp[r2] = r1;
            cmp[r1] -= 1;
        }
#endif
}

int main()
{
    for (int i = 0; i < max; i++) {
        cmp[i] = -1;
    }
    scanf("%d", &size);
    cnt = 0;

    char a;
    int p1, p2;
    while (scanf(" %c", &a) && a != 'S') {
        scanf("%d %d", &p1, &p2);
        if (a == 'I') {
            uni(p1, p2);
        }
        else if (a == 'C') {
            if (find(p1) == find(p2)) {
                printf("yes\n");
            }
            else {
                printf("no\n");
            }
        }
    }

    for (int i = 1; i <= size; i++) {
        if (cmp[i] < 0) {
            cnt++;
        }
    }
    if (cmp[find(p1)] + size == 0) {
        printf("The network is connected.\n");
    }
    else {
        printf("There are %d components.\n", cnt);
    }

    return 0;
}

#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                    //哈夫曼树
#if 0
typedef struct NODE {
    char data;
    struct NODE* left;
    struct NODE* right;
}NODE;

typedef struct DATA {
    char data;
    int frequency;
}DATA;

DATA heap[64];
int cnt = 0;


void insert(DATA* data, int* N, DATA x) {
    data[++*N] = x;
    if (*N == 1)return;

    int i;
    for (i = *N; i > 1 && x.frequency < data[i / 2].frequency; i /= 2) {//大于1的时候进入，等于1说明已经是根节点了，不需要继续比较了
        data[i] = data[i / 2];
    }
    data[i] = x;
}

DATA delete(DATA* data, int* N) {//本质上是一个根节点，和它的左右子树(已经是两个堆)。将一个节点和两个堆合成一个堆的过程。
    DATA min = data[1];
    data[1] = data[(*N)--];//把根节点和最后一个元素交换，最后一个元素退出堆中。

    int parent = 1;
    DATA temp = data[parent];
    for (int child = parent * 2; child <= *N; child *= 2) {
        if (child < *N && data[child + 1].frequency < data[child].frequency) {//找到左右子树中较小的那一个
            child++;
        }
        if (temp.frequency <= data[child].frequency) {//最小堆，从上往下值是递增的，找到左右子树中较小的那一个之后。如果比进入该循环时的夫节点更大就不用交换
            break;    //将这一个节点的值向上移，然后往下一层去寻找。如果找到比它更小的就break，将开始的parent的值插入到这里。
        }                      //简单来说就是在一个递增的序列向后遍历，找到自己的位置然后插入，思路和直接插入排序几乎一样

        data[parent] = data[child];
        parent = child;
    }
    data[parent] = temp;//退出循环后，parent指向原本的parent现在应该插入的位置

    return min;
}

NODE* huffman() {
    NODE* unleaf[100] = { 0 };
    int top = -1;
    for (int i = 0; i < cnt - 1; i++) {//一共N个数据，进行N-1次就能合成一颗树。
        DATA min1 = delete(heap, &cnt);
        DATA min2 = delete(heap, &cnt);//每次找两个最小的，如果是叶子节点就创建一个，如果不是就在非叶指针数组里面找与之对应的节点指针

        NODE* L = (NODE*)malloc(sizeof(NODE));
        NODE* R = (NODE*)malloc(sizeof(NODE));//要判断是否为叶节点，这个已经废了，懒得改了
        L->data = min1.data;
        L->left = L->right = NULL;
        R->data = min2.data;
        R->left = R->right = NULL;

        NODE* head = (NODE*)malloc(sizeof(NODE));//创建一个非叶节点指向最小的两个。
        head->data = '#';
        head->left = L;
        head->right = R;
        unleaf[++top] = head;//放入非叶数组中

        DATA newhead = { '#',min1.frequency + min2.frequency };//将新的数据放入堆中重新排序。
        insaert(heap, &cnt, newhead);
    }
    
    //我这个做法在建树的时候很麻烦，真正的做法是读入数据的时候就创建节点（堆存指向节点的指针），然后在huffman函数里面直接创一个新节点，然后从堆里拿两个
    //最小节点的指针，让left和right等于指针，把新节点放入堆中重排
}

int main()
{
    int N = 0;
    scanf("%d", &N);
    getchar();
    DATA dta = { 0 };
    for (int i = 0; i < N; i++) {
        scanf(" %c %d", &dta.data, &dta.frequency);
        insert(heap, &cnt, dta);
    }

    huffman();
    int M = 0;
    scanf("%d", &M);



    return 0;
}

#endif 


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                   //DFS、BFS
#if 0
#include<stdio.h>

typedef struct GRAPH {
    int edge[10][10];
    int num_e;
    int num_v;
}GRAPH;

int visited[10];
int cnt_D;
int cnt_B;

void DFS(GRAPH* m, int x) {
    visited[x] = 1;
    cnt_D++;
    printf("%d ", x);
    for (int i = 0; i < m->num_v; i++) {
        if (!visited[i] && m->edge[x][i]) {
            DFS(m, i);
        }
    }

}

void BFS(GRAPH* m, int x) {
    visited[x] = 1;
    int list[10] = { 0 };
    int head = 0;
    int rear = 0;
    list[rear++] = x;
    while (head != rear) {
        int y = list[head++];
        printf("%d ", y);
        // visited[i] = 1; 因为比如1连了4，也连了2。所以2弹出时，4还没visit，4会重复进队列。所以对每个进队列的，认为在进入队列时就已经被visit
        for (int i = 0; i < m->num_v; i++) {
            if (!visited[i] && m->edge[y][i]) {
                list[rear++] = i;
                visited[i] = 1;

            }
        }

    }

}

int main()
{
    GRAPH m = { 0 };
    scanf("%d %d", &m.num_v, &m.num_e);

    int v, w;

    //for (int i = 0; i < m.num_v; i++) {
    //    for (int j = 0; i < m.num_v; j++) {
    //        //m.edge[i][j] = 0;
    //    }
    //}
    for (int i = 0; i < m.num_e; i++) {
        scanf("%d %d", &v, &w);
        m.edge[v][w] = m.edge[w][v] = 1;
    }


    for (int i = 0; i < m.num_v; i++) {
        if (!visited[i]) {
            printf("{ ");
            DFS(&m, i);
            printf("}");
            if (cnt_D != m.num_v) {
                printf("\n");
            }
        }
    }
    printf("\n");
    for (int i = 0; i < m.num_v; i++) {
        visited[i] = 0;
    }
    for (int i = 0; i < m.num_v; i++) {
        if (!visited[i]) {
            printf("{ ");
            BFS(&m, i);
            printf("}");
            if (cnt_B != m.num_v) {
                printf("\n");
            }
        }
    }



    return 0;
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                 //六度空间
#if 0
#include<stdio.h>

typedef struct GRAPH {
    int edge[330][330];
    int num_e;
    int num_v;
}GRAPH;

int visited[100];


void DFS(GRAPH* m, int x, int level, int* cnt) {//有可能第一层的第一个节点的第一个节点是第0层的第二个节点，将这个第一层的节点看作第二层的了。
    visited[x] = 1;
    if (level >= 0 && level <= 6) {
        (*cnt)++;
    }
    for (int i = 1; i <= m->num_v; i++) {
        if (!visited[i] && m->edge[x][i]) {
            DFS(m, i, level + 1, cnt);
        }
    }
}


int BFS(GRAPH* m, int x) {
    int cnt = 1;
    int list[20] = { 0 };
    int head = 0, rear = 0;
    int last = x;//当前这一层最后一个节点
    int tail=1;//下一层的最后一个节点
    int level = 0;
    visited[x] = 1;

    list[rear++] = x;
    while (head != rear) {
        int y = list[head++];
        
        for (int i = 1; i <= m->num_v; i++) {
            if (!visited[i] && m->edge[y][i]) {
                list[rear++] = i;
                visited[i] = 1;
                tail = i;
                cnt++;
            }
        }
        if (y == last) {
            last = tail;
            level++;//当走到这一层最后一个节点的时候才会更新到当前这一层
        }
        if (level == 6) {
            break;
        }
    }
    return cnt;
}



int main()
{
    GRAPH m = { 0 };
    scanf("%d %d", &m.num_v, &m.num_e);

    int v, w;
    for (int i = 0; i < m.num_e; i++) {
        scanf("%d %d", &v, &w);
        m.edge[v][w] = m.edge[w][v] = 1;
    }
    

    int cnt = 0;
    for (int i = 1; i <= m.num_v; i++) {
        for (int j = 0; j <= m.num_v; j++) {
            visited[j] = 0;
        }
        int ret = BFS(&m, i);
        printf("%d: %.2f%%\n", i, 100 * (ret * 1.0) / m.num_v);
        ret = 0;
    }


    return 0;
}
#endif 
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                  //拯救007(跳鳄鱼)
#if 0
#include<stdio.h>
#include<math.h>
typedef struct COORD {
    int x;
    int y;
}COORD;
typedef struct GRAPH {
    struct COORD vertex[101];
    int edge[101][101];
    int step;
    int n_edeg;
    int n_vex;
}GRAPH;
int visited[101];
int sign = 0;


int  judge(COORD A, COORD B, int step) {
    int dx = A.x - B.x > 0 ? A.x - B.x : B.x - A.x;
    int dy = A.x - B.y > 0 ? A.y - B.y : B.y - A.y;
    float distance = sqrt(dx * dx + dy * dy);

    if (A.x == B.x && A.y == B.y) {
        int min_x = A.x > 0 ? 50 - A.x : A.x + 50;
        int min_y = A.y > 0 ? 50 - A.y : A.y + 50;
        distance = min_x > min_y ? min_y : min_x;
        return distance <= step ? 1 : 0;
    }
    else if ((A.x == 0 && A.y == 0) || (B.x == 0 && B.y == 0)) {
        return distance - 7.5 <= step ? 1 : 0;
    }
    else {
        return distance <= step ? 1 : 0;
    }
}

void init(GRAPH* m) {
    for (int i = 0; i < m->n_vex; i++) {
        for (int j = 0; j < m->n_vex; j++) {
            if (judge(m->vertex[i], m->vertex[j], m->step)) {
                m->edge[i][j] = 1;
                m->n_edeg++;
            }
            else {
                m->edge[i][j] = 0;
            }
        }
    }
}

void DFS(GRAPH* m, int x) {
    if (!visited[x]) {
        visited[x] = 1;
    }
    if (m->edge[x][x] || sign) {
        sign = 1;
        return;
    }
    for (int i = 0; i < m->n_vex; i++) {
        if (!visited[i] && m->edge[x][i]) {
            DFS(m, i);
        }
    }
}

int main()
{
    GRAPH m;
    scanf("%d %d", &m.n_vex, &m.step);
    for (int i = 1; i <= m.n_vex; i++) {
        scanf("%d %d", &m.vertex[i].x, &m.vertex[i].y);//其实这题的图不需要这么麻烦，可以只用一个顶点表来存顶点信息
    }
    m.vertex[0].x = m.vertex[0].y = 0;//主函数内对每个鳄鱼判断是否可以从岛上跳过去，进入DFS内每一次跳之前用judge函数判断这是否为图的边
    m.n_vex++;                     //当然在进DFS中首先判断能否从这个鳄鱼跳上岸。
    init(&m);                      //这种实现方法其实是每次都先判断这是不是边再跳，这样就可以不用edge数组这么多的空间来存储边的信息。


    DFS(&m, 0);
    if (sign) {
        printf("Yes");
    }
    else {
        printf("No");
    }

    return 0;
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                              //拯救007 pro max plus
#if 0
#include<stdio.h>
#include<math.h>
#define  INFINITY 65535
typedef struct COORD {
    int x;
    int y;
}COORD;
typedef struct GRAPH {
    struct COORD vertex[101];
    int edge[101][101];
    int step;
    int n_vex;
}GRAPH;
int visited[101];
int sign = 0;
int dst[8];
int dst_top = 0;

float  judge(COORD A, COORD B, int step) {
    int dx = A.x - B.x > 0 ? A.x - B.x : B.x - A.x;
    int dy = A.x - B.y > 0 ? A.y - B.y : B.y - A.y;
    float distance = sqrt(dx * dx + dy * dy);
    float ret = 0;
    if (A.x == B.x && A.y == B.y) {
        int min_x = A.x > 0 ? 50 - A.x : A.x + 50;
        int min_y = A.y > 0 ? 50 - A.y : A.y + 50;
        distance = min_x > min_y ? min_y : min_x;
        ret = distance <= step ? 0 : INFINITY;
    }
    else if ((A.x == 0 && A.y == 0) || (B.x == 0 && B.y == 0)) {
        ret = distance - 7.5 <= step ? distance - 7.5 : INFINITY;
    }
    else {
        ret = distance <= step ? distance : INFINITY;
    }
    return ret;
}

void init(GRAPH* m) {
    int ret = 0;
    for (int i = 0; i < m->n_vex; i++) {
        for (int j = 0; j < m->n_vex; j++) {
            ret = judge(m->vertex[i], m->vertex[j], m->step);
            m->edge[i][j] = ret;
        }
    }
}

void DFS(GRAPH* m, int x) {
    if (!visited[x]) {
        visited[x] = 1;
    }
    if (!m->edge[x][x]) {
        sign = 1;
        dst[dst_top++] = x;
    }
    for (int i = 0; i < m->n_vex; i++) {
        if (!visited[i] && m->edge[x][i] > 0 && m->edge[x][i] < INFINITY) {
            DFS(m, i);
        }
    }
}

void shortest_path(GRAPH* m, int src, int* dist, int* path) {
    int final[101] = { 0 };
    for (int i = 0; i < m->n_vex; i++) {
        path[i] = -1;
        dist[i] = INFINITY;
    }
    dist[src] = 0;
    for (int i = 0; i < m->n_vex; i++) {
        int min = INFINITY, k = 0;
        for (int i = 0; i < m->n_vex; i++) {
            if (dist[i] < min && !final[i]) {
                min = dist[i];
                k = i;
            }
        }
        final[k] = 1;
        for (int i = 0; i < m->n_vex; i++) {
            if (!final[i] && m->edge[k][i] < INFINITY) {
                if (min + m->edge[k][i] < dist[i]) {
                    dist[i] = min + m->edge[k][i];
                    path[i] = k;
                }
            }
        }
    }
}
//
//void shortest_path(GRAPH* m, int src, int* dist, int* path) {
//    int final[5001] = { 0 };
//    for (int i = 0;i < m->n_vex; i++) {
//        dist[i] = INFINITY;
//        path[i] = -1;
//    }
//    dist[src] = 0;
//    for (int x = 0; x < m->n_vex; x++) {
//        int min = INFINITY, k = 0;
//        for (int y = 0; y < m->n_vex; y++) {
//            if (!final[y] && dist[y] < min) {
//                min = dist[y];
//                k = y;
//            }
//        }
//        final[k] = 1;
//        for (int i = 0; i < m->n_vex; i++) {
//            if (!final[i] && min + m->edge[k][i] < dist[i]) {
//                dist[i] = min + m->edge[k][i];
//                path[i] = k;
//            }
//        }
//    }
//
//    
//}


void get_road(int* path, int* road, int* cnt, int dst) {
    int stack[101];
    int top = -1;

    stack[++top] = dst;
    (*cnt)++;
    while (path[dst] != -1) {
        dst = stack[++top] = path[dst];
        (*cnt)++;
    }
    int t = 0;
    while (top != -1) {
        road[t++] = stack[top--];
    }

}

void get_anwser(GRAPH* m, int* road, int time) {
    printf("%d", time);

    for (int i = 1; i <= time - 1; i++) {
        int vettex_index = road[i];
        printf("\n%d %d", m->vertex[vettex_index].x, m->vertex[vettex_index].y);
    }

}

int main()
{
    GRAPH m;
    scanf("%d %d", &m.n_vex, &m.step);
    for (int i = 1; i <= m.n_vex; i++) {
        scanf("%d %d", &m.vertex[i].x, &m.vertex[i].y);
    }
    m.vertex[0].x = m.vertex[0].y = 0;
    m.n_vex++;
    init(&m);

    DFS(&m, 0);
    if (!sign) {
        printf("0");
    }
    else {
        int dist[101];
        int path[101];
        shortest_path(&m, 0, dist, path);

        int(*road)[101];
        road = (int(*)[101])malloc(sizeof(int[101]) * dst_top);
        int* road_step = (int*)calloc(dst_top, sizeof(int));
        for (int i = 0; i < dst_top; i++) {
            get_road(path, road[i], &road_step[i], dst[i]);
        }

        int min_time = INFINITY, min_index = 0, first_index = INFINITY;
        for (int i = 0; i < dst_top; i++) {
            if (road_step[i] < min_time) {
                min_time = road_step[i];
            }
        }
        for (int i = dst_top-1; i >=0 ; i--) {
            if (road_step[i]==min_time) {
                if (road[i][1] < first_index) {
                    min_index = i;//更新路径的代号
                    first_index = road[i][1];//更新当前在所有次数最少的路径中找到的第一跳对应节点编号
                }
            }
        }
        get_anwser(&m, road[min_index], min_time);
        printf("hello");
    }
    return 0;
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                    //哈利波特的考试
#if 0
#include<stdio.h>
#include<stdlib.h>
#define INFINITY 65535
typedef struct GRAPH {
    int vex_cnt;
    int edge_cnt;
    int edge[10][10];
    int vertex[10];
}GRAPH;

void init(GRAPH* m) {
    int i, j, weight;
    for (i = 1; i <= m->vex_cnt; i++) {
        for (j = 1; j <= m->vex_cnt; j++) {
            if (i == j) {
                m->edge[i][j] = 0;
            }
            else {
                m->edge[i][j] = INFINITY;
            }
        }
    }
    for (int k = 0; k < m->edge_cnt; k++) {
        scanf("%d %d %d", &i, &j, &weight);
        m->edge[i][j] = m->edge[j][i] = weight;
    }

}

void shorest_path_floyd(GRAPH* m, int (*path)[10], int (*dist)[10]) {
    for (int i = 1; i <= m->vex_cnt; i++) {
        for (int j = 1; j <= m->vex_cnt; j++) {
            path[i][j] = -1;
            dist[i][j] = m->edge[i][j];
        }
    }
    for (int k = 1; k <= m->vex_cnt; k++) {
        for (int i = 1; i <= m->vex_cnt; i++) {
            for (int j = 1; j <= m->vex_cnt; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
}

//int get_cost(int src, int dst, int path[101][101]) {
//    int sum = 0;
//    while (src != dst) {
//        src = path[src][dst];
//        sum+=
//    }
//
//
//}
int no_anwser(int vex_cnt, int dist[101][101]) {
    int ret = 0;
    for (int i = 1; i <= vex_cnt; i++) {
        for (int j = 1; j <= vex_cnt; j++) {
            if (dist[i][j] == INFINITY) {
                return 1;
            }
        }
    }
    return ret;
}

int main()
{
    GRAPH m;
    scanf("%d %d", &m.vex_cnt, &m.edge_cnt);

    init(&m);

    int path[10][10];
    int dist[10][10];

    shorest_path_floyd(&m, path, dist);

    if (no_anwser(m.vex_cnt, dist)) {
        printf("0");
    }
    else {
        int hardest[10] = { 0 };
        int top = 0, min = INFINITY, max = 0;
        for (int i = 1; i <= m.vex_cnt; i++) {
            max = 0;
            for (int j = 1; j <= m.vex_cnt; j++) {
                if (dist[i][j] > max) {
                    max = dist[i][j];
                }
            }
            hardest[++top] = max;
        }

        min = m.vex_cnt;
        for (int i = m.vex_cnt; i >= 1; i--) {
            if (hardest[i] <= hardest[min]) {
                min = i;
            }
        }
        printf("%d %d", min, hardest[min]);
    }

    return 0;
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                     //旅游路线
#if 0
#include<stdio.h>
#include<stdlib.h>
#define INFINITY 65535
typedef struct GRAPH {
    int vex_cnt;
    int edge_cnt;
    int edge_length[521][521];
    int edge_cost[521][521];
    int vertex[1];
}GRAPH;

void init(GRAPH* m, int* src, int* dst) {
    scanf("%d %d %d %d", &m->vex_cnt, &m->edge_cnt, &(*src), &(*dst));

    for (int i = 0; i < m->vex_cnt; i++) {
        for (int j = 0; j < m->vex_cnt; j++) {
            if (i == j) {
                m->edge_length[i][j] = m->edge_cost[i][j] = 0;
            }
            else {
                m->edge_length[i][j] = m->edge_cost[j][i] = INFINITY;
            }
        }
    }

    int cost, length, p1, p2;
    for (int i = 0; i < m->edge_cnt; i++) {
        scanf("%d %d %d %d", &p1, &p2, &length, &cost);
        m->edge_cost[p1][p2] = m->edge_cost[p2][p1] = cost;
        m->edge_length[p1][p2] = m->edge_length[p2][p1] = length;
    }

}

void shorest_length(GRAPH* m, int* dist, int* path, int* cost, int src) {
    int final[521] = { 0 };
    for (int i = 0; i < m->vex_cnt; i++) {
        path[i] = -1;
        dist[i] = INFINITY;
        cost[i] = INFINITY;
    }
    dist[src] = 0; cost[src] = 0;
    int k = 0, min = INFINITY;
    for (int x = 0; x < m->vex_cnt; x++) {
        min = INFINITY;
        for (int y = 0; y < m->vex_cnt; y++) {
            if (dist[y] < min && !final[y]) {
                min = dist[y];
                k = y;
            }
        }
        final[k] = 1;
        for (int i = 0; i < m->vex_cnt; i++) {
            if (!final[i] && m->edge_length[k][i] < INFINITY) {
                if (min + m->edge_length[k][i] < dist[i]) {
                    dist[i] = min + m->edge_length[k][i];
                    cost[i] = cost[k] + m->edge_cost[k][i];//如果路径更短就更新路径
                    path[i] = k;
                }
                else if (min + m->edge_length[k][i] == dist[i] && cost[k] + m->edge_cost[k][i] < cost[i]) {
                    cost[i] = cost[k] + m->edge_cost[k][i];//如果路径相等但是更便宜也要更新路径
                    path[i] = k;
                }

            }
        }
    }
}


int get_cost(int src, int dst, int* path_length, GRAPH* m) {
    int p1 = path_length[dst], p2 = dst;
    int sum = 0;
    while (p2 != src) {
        sum += m->edge_cost[p1][p2];
        p2 = path_length[p2];
        p1 = path_length[p1];
    }
    return sum;
}

int main()
{
    GRAPH m;
    int src, dst;
    init(&m, &src, &dst);

    int path_length[521]; int dist_length[521]; int cost_length[521];
    shorest_length(&m, dist_length, path_length, cost_length, src);
   
    int  cost= get_cost(src, dst, path_length, &m);
    printf("%d %d", dist_length[dst], cost);

    return 0;
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                 //村庄修路

#if 0
#include<stdio.h>
#include<stdlib.h>
#define INFINITY 65535
typedef struct GRAPH {
    int vex_cnt;
    int edge_cnt;
    int edge[10][10];
}GRAPH;

void init(GRAPH* m) {
    scanf("%d %d", &m->vex_cnt, &m->edge_cnt);
    int i, j, cost;
    for (int i = 1; i <= m->vex_cnt; i++) {
        for (int j = 1; j < m->vex_cnt; j++) {
            if (i == j) {
                m->edge[i][j] = 0;
            }
            else {
                m->edge[i][j] = INFINITY;
            }
        }
    }
    for (int k = 0; k < m->edge_cnt; k++) {
        scanf("%d %d %d", &i, &j, &cost);
        m->edge[i][j] = m->edge[j][i] = cost;
    }
}

int minimum_spanning_tree(GRAPH* m) {
    int sum = 0;//dist是存到树的距离，adjvex[i]表示是谁让对应的dist[i]更新
    int dist[10]; int parent[10]; int adjvex[10];
    for (int i = 1; i <= m->vex_cnt; i++) {
        dist[i] = m->edge[1][i];
        parent[i] = -1;
        adjvex[i] = 1;
    }
    dist[1] = 0;
    for (int j = 1; j < m->vex_cnt; j++) {//找cnt-1条边
        int k = 1, min = INFINITY;
        for (int i = 1; i <= m->vex_cnt; i++) {
            if (dist[i] && dist[i] < min) {
                min = dist[i];
                k = i;
            }
        }
        if (min == INFINITY) {//有独立点，无法建成树
            break;
        }
        sum += dist[k];//dist存的是到adjvex[i]的距离,也是到树的距离
        dist[k] = 0;
        parent[k] = adjvex[k];
        for (int i = 1; i <= m->vex_cnt; i++) {
            if (dist[i] && m->edge[k][i] < dist[i]) {
                dist[i] = m->edge[k][i];
                adjvex[i] = k;
            }
        }
    }
    for (int i = 1; i <= m->vex_cnt; i++) {
        if (parent[i] == -1 && i != 1) {
            return 0;
        }
    }
    return sum;
}


int main()
{
    GRAPH m;
    init(&m);

    int ret = minimum_spanning_tree(&m);

    if (!ret) {
        printf("-1");
    }
    else {
        printf("%d", ret);
    }

    return 0;
}

#endif 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                 //求活动最早完成时间          
#if 0
//#include<stdio.h>
//#include<stdlib.h>
//#define INFINITY 65535
//typedef struct VERTEX {
//    int earliest;
//    int latest;
//}VERTEX;
//
//typedef struct GRAPH {
//    int vex_cnt;
//    int edge_cnt;
//    int edge[100][100];
//    VERTEX vertex[100];
//}GRAPH;
//
//void init(GRAPH* m) {
//    scanf("%d %d", &m->vex_cnt, &m->edge_cnt);
//    for (int i = 0; i < m->vex_cnt;i++) {
//        for (int j = 0; j < m->vex_cnt;i++) {
//            if (i == j) {
//                m->edge[i][j] = 0;
//            }
//            else {
//                m->edge[i][j] = INFINITY;
//            }
//        }
//    }
//    for (int i = 0; i < m->edge_cnt; i++) {
//        int start, end, time;
//        scanf("%d %d %d", &start, &end, &time);
//        m->edge[start][end] = time;
//    }
//}
//
//int main()
//{
//    GRAPH m;
//    init(&m);
//
//
//
//
//
//    return 0;
//}

#include<stdio.h>
#include<stdlib.h>
#define INFINITY 65535

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
    struct VEX vex[10];
    int vex_cnt;
    int edge_cnt;
}GRAPH;
int* etv;
int* ltv;//这两个数组可以被拆分成每个vex[i]的etv和ltv，不过这样更方便。
int stack_negative[10];
int top2 = -1;

void init(GRAPH* m) {
    scanf("%d %d", &m->vex_cnt, &m->edge_cnt);
    etv = (int*)malloc(sizeof(int) * m->vex_cnt);
    ltv = (int*)malloc(sizeof(int) * m->vex_cnt);
    for (int i = 0; i <= m->vex_cnt; i++) {
        m->vex[i].in = 0;
        m->vex[i].first_edge = NULL;
    }
    for (int i = 0; i < m->edge_cnt; i++) {
        int start, end, time;
        scanf("%d %d %d", &start, &end, &time);
        m->vex[end].in += 1;
        if (!m->vex[start].first_edge) {
            EDGE* last=m->vex[start].first_edge= (EDGE*)malloc(sizeof(EDGE));
            last->adjvex = end; last->next = NULL; last->weight = time;
        }
        else {
            EDGE* last = m->vex[start].first_edge;
            while (last->next) {
                last = last->next;
            }
            last->next = (EDGE*)malloc(sizeof(EDGE)); last = last->next;
            last->adjvex = end; last->next = NULL; last->weight = time;
        }
    }
}

int get_final(GRAPH* m) {
    int ret = 0;
    for (int i = 0; i < m->vex_cnt; i++) {
        if (etv[i] > etv[ret]) {
            ret = i;
        }
    }
    return ret;
}

int topological_sort(GRAPH* m) {
    int cnt = 0;
    int stack_positive[10];
    int top1 = -1;
    int indegree[10];
    for (int i = 0; i < m->vex_cnt; i++) {
        etv[i] = 0;
        indegree[i] = m->vex[i].in;
        if (!indegree[i]) {
            stack_positive[++top1] = i;
        }
    }
    while (top1 != -1) {
        int cur = stack_positive[top1--];
        stack_negative[++top2] = cur;
        cnt++;
        for (EDGE* p = m->vex[cur].first_edge; p; p = p->next) {
            int end = p->adjvex, time = p->weight;
            if (!--indegree[end]) {
                stack_positive[++top1] = end;
            }
            if (etv[cur] + time > etv[end]) {
                etv[end] = etv[cur] + time;
            }
        }
    }
    if (cnt == m->vex_cnt) {
        return 1;
    }
    else {
        return 0;
    }
}




int main()
{
    GRAPH m;
    init(&m);

    int ret, final;
    if (!(ret = topological_sort(&m))) {
        printf("Impossible");
    }
    else {
        final = get_final(&m);
        printf("%d", etv[final]);
    }

    return 0;
}

#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                  //求最早时间及关键路径
#if 0
#include<stdio.h>
#include<stdlib.h>
#define INFINITY 65535

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
    struct VEX vex[101];
    int vex_cnt;
    int edge_cnt;
}GRAPH;
int* etv;
int* ltv;//这两个数组可以被拆分成每个vex[i]的etv和ltv，不过这样更方便。
int stack_negative[101];
int top2 = -1;

int parent[101] = { 0 };

void init(GRAPH* m) {
    scanf("%d %d", &m->vex_cnt, &m->edge_cnt);
    etv = (int*)malloc(sizeof(int) * m->vex_cnt);
    ltv = (int*)malloc(sizeof(int) * m->vex_cnt);
    for (int i = 0; i <= m->vex_cnt; i++) {
        m->vex[i].in = 0;
        m->vex[i].first_edge = NULL;
    }
    for (int i = 0; i < m->edge_cnt; i++) {
        int start, end, time;
        scanf("%d %d %d", &start, &end, &time);
        m->vex[end].in += 1;
        if (!m->vex[start].first_edge) {
            EDGE* last = m->vex[start].first_edge = (EDGE*)malloc(sizeof(EDGE));
            last->adjvex = end; last->next = NULL; last->weight = time;
        }
        else {
            EDGE* last = m->vex[start].first_edge;
            while (last->next) {
                last = last->next;
            }
            last->next = (EDGE*)malloc(sizeof(EDGE)); last = last->next;
            last->adjvex = end; last->next = NULL; last->weight = time;
        }
    }
}

int get_final(GRAPH* m) {
    int ret = 0;
    for (int i = 1; i <= m->vex_cnt; i++) {
        if (etv[i] > etv[ret]) {
            ret = i;
        }
    }
    return ret;
}

int topological_sort(GRAPH* m) {
    int cnt = 0;
    int stack_positive[101];
    int top1 = -1;
    int indegree[101];
    for (int i = 1; i <= m->vex_cnt; i++) {
        etv[i] = 0;
        indegree[i] = m->vex[i].in;
        if (!indegree[i]) {
            stack_positive[++top1] = i;
        }
    }
    while (top1 != -1) {
        int cur = stack_positive[top1--];
        stack_negative[++top2] = cur;
        cnt++;
        for (EDGE* p = m->vex[cur].first_edge; p; p = p->next) {
            int end = p->adjvex, time = p->weight;
            if (!--indegree[end]) {
                stack_positive[++top1] = end;
            }
            if (etv[cur] + time > etv[end]) {
                etv[end] = etv[cur] + time;
            }
        }
    }
    if (cnt == m->vex_cnt) {
        return 1;
    }
    else {
        return 0;
    }
}

void critical_path(GRAPH* m, int final) {
    for (int i = 1; i <= m->vex_cnt; i++) {
        ltv[i] = etv[final];
    }
    while (top2 != -1) {
        int cur = stack_negative[top2--];
        for (EDGE* p = m->vex[cur].first_edge; p; p = p->next) {
            int end = p->adjvex, time = p->weight;
            if (ltv[end] - time < ltv[cur]) {
                ltv[cur] = ltv[end] - time;
            }
        }
    }
    for (int i = 1; i <= m->vex_cnt; i++) {
        for (EDGE* p = m->vex[i].first_edge; p; p = p->next) {
            int j = p->adjvex, time = p->weight;
            int ete = etv[i], lte = etv[j] - time;
            if (ete == lte) {
                //printf("%d->%d\n", i, j);
                parent[j] = i;//这么多关键路径可能有多起点多终点，同一起点终点可能有多条路径。我不知道怎么输出了。
            }
        }
    }

}

void get_path(int last) {
    int stack[101];
    int top = -1;
    while (last != 1) {
        stack[++top] = last;
        last = parent[last];
    }
    stack[++top] = 1;

    for (int i = top, j = i - 1; i != 0; i--, j--) {
        printf("%d->%d\n", stack[i], stack[j]);
    }
}

int main()
{
    GRAPH m;
    init(&m);

    int ret, final;
    if (!(ret = topological_sort(&m))) {
        printf("0");
    }
    else {
        final = get_final(&m);
        printf("%d\n", etv[final]);
        critical_path(&m, final);
        get_path(m.vex_cnt);
    }

    return 0;
}

#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 
                                                                //表排序后的物理排序
#if 0
void get_index(int* data,int* index, int N) {
    for (int i = 0; i < N; i++) {//对data数组遍历，对于a[2]=7来说，代表了7存在了2这个位置，让index[d7]=2;d7代表了7在所有序列的位置，由于数据特殊
        index[data[i]] = i;                                                                                     //7的位置就是7
    }
}

void sort(int* data, int* index, int N) {
    for (int i = 0; i < N; i++) {
        if (index[i] == i) {
            continue;
        }
        else {
            int j = i;//i是这个环的起点
            int temp = data[j];
            while (index[j] != i) {
                data[j] = data[index[j]];
                int t = j;
                j = index[j];
                index[t] = t;
            }
            data[j] = temp;
            index[j] = j;
        }
    }
}

int main()
{
    int data[10] = { 3,5,7,2,6,4,9,0,8,1 };
    int index[10] = { 0 };//正常来说，得到index需要用排序算法对index中的指针进行排序
    get_index(data,index, 10);//但是这里的数据是特殊的从0到9顺序的，所以由数字本身就能得出该数字在序列中的位置。
    sort(data, index, 10);

    for (int i = 0; i < 10; i++) {
        printf("%d ", data[i]);
    }
    printf("\nhello\n");
    return 0;
}

#endif












































































