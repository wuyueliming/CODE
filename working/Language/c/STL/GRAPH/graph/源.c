#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   图   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                   //图的存储结构
/*
一、邻接矩阵(若点很多，边很少，就会造成大量空间的浪费)
    一个一维数组存储顶点数据。一个二维数组存储边或弧的信息，用二维数组的行和列分别表示一条弧的弧尾和弧头。若不带权重，则用1表示存在该弧，0表示不存在；
    若是一个带有权重的网，可以用一个极大的数字表示不存在，用一个正常范围内的数字来表示权的值
    
二、边集数组(若要求点的度需要遍历整个数组)
    用两个一维数组，一个用来存储顶点的信息，另一个用来存储边的信息。边数组的元素是一个结构体，包含弧尾、弧头顶点在点数组中的下标，若有权重则加上weight成员

*/

/*
三、邻接表
    用数组存顶点的信息和邻接点链表的头指针，链表用来存储邻接顶点在数组中的下标和下一个邻接顶点的指针。
    若这是一个有向图，则可以用两个邻接表来表示，一个用来存储顶点和出边的信息，一个用来存储顶点和入边的信息。也可以将数组元素的结构体改成两个头指针，一个是顶点
    对应的弧头顶点链表的，另一个是顶点对应的弧尾顶点链表的头指针。(但这样将两个合并后，空间利用率比十字链表略低)
*/

/*
四、十字链表
    相对于邻接表，顶点表的元素结构体分为：data(顶点信息)、firstin(入边表头指针)、firstout(出边表头指针)
    边表的结构体分为：tailves(弧尾)、headvex(弧头)、headlink(指向headvex相同的下一个边)、taillink(指向tailvex相同的下一个边)

五、邻接多重表
    顶点表结构体分为：data、firstedge。边表的结构体分为：ivex、ilink(指向依附于ivex的下一条边)、jvex、jlink(指向依附于jvex的下一条边)

*/




//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                    //图的遍历
//邻接矩阵
#if 0
#define vex_max 9
#define edge_max 15
typedef struct GRAPH{
    char vex[vex_max];
    int edge[vex_max][vex_max];
    int vex_cnt;
    int edge_cnt;
}GRAPH;
bool visited[9];
void DFS(GRAPH m, int i);
void DFStraverse(GRAPH m);
void BFStraverse(GRAPH m);
void gethead(GRAPH m, char* queue, int* i, int* tail);
int main()
{
    GRAPH m;
    m.vex[0] = 'A';
    m.vex[1] = 'B';
    m.vex[2] = 'C';
    m.vex[3] = 'D';
    m.vex[4] = 'E';
    m.vex[5] = 'F';
    m.vex[6] = 'G';
    m.vex[7] = 'H';
    m.vex[8] = 'I';
    //m.edge[0][1] = m.edge[0][5] = m.edge[1][2] = m.edge[1][8] = m.edge[1][6] = m.edge[2][8] = m.edge[5][6] = m.edge[7][6] = m.edge[7][4] = m.edge[3][2] = m.edge[3][8] = m.edge[3][6] = m.edge[3][7] = m.edge[3][4] = 1;
    m.vex_cnt = 9;
    m.edge_cnt = 15;
    for (int i = 0; i < m.vex_cnt; i++) {
        for (int j = 0; j < m.vex_cnt; j++) {
            m.edge[i][j] = 0;
        }
    }
    m.edge[0][1] = m.edge[0][5] = m.edge[1][2] = m.edge[1][8] = m.edge[1][6] = m.edge[2][8] = m.edge[5][6] = m.edge[7][6] = m.edge[7][4] = m.edge[3][2] = m.edge[3][8] = m.edge[3][6] = m.edge[3][7] = m.edge[3][4] = m.edge[5][4] = 1;
    for (int i = 0; i < m.vex_cnt; i++) {
        for (int j = 0; j < m.vex_cnt; j++) {
            if (m.edge[i][j] == 1) {
                m.edge[j][i] = 1;
            }
        }
    }
    
    DFStraverse(m);
    printf("\n---------------------\n");
    BFStraverse(m);

    return 0;
}

//深度优先遍历
void DFS(GRAPH m, int i) {
    printf("%c", m.vex[i]);
    visited[i] = true;
    for (int j = 0; j < m.vex_cnt; j++) {
        if (m.edge[i][j] == 1 && visited[j] == false) {
            DFS(m, j);
        }
    }
}
void DFStraverse(GRAPH m) {
    for (int i = 0; i < m.vex_cnt; i++) {
        visited[i] = false;
    }
    for (int i = 0; i < m.vex_cnt; i++) {
        if (!visited[i]) {
            DFS(m, i);
        }
    }

}
//广度优先遍历
void BFStraverse(GRAPH m) {
    int i, j;
    for (i = 0; i < m.vex_cnt; i++) {
        visited[i] = false;
    }
    char* queue = (char*)malloc(sizeof(char) * (m.vex_cnt));//应该是int型，用数字代表元素，需要访问元素时通过vex数组
    int head = 0;
    int tail = 0;
    for (i = 0; i < m.vex_cnt; i++) {
        if (!visited[i]) {
            printf("%c", m.vex[i]);
            visited[i] = true;
            queue[tail++] = m.vex[i];
            while (!tail) {
                gethead(m,queue, &i,&tail);//拿到队首顶点对应在图中的位置，并将队首顶点出列
                for (j = 0; j < m.vex_cnt; j++) {
                    if (m.edge[i][j] == 1 && visited[j] == false) {
                        printf("%c", m.vex[j]);
                        visited[j] = true;
                        queue[tail++] = m.vex[j];
                    }
                }
            }
        }
    }
}

int BFS(GRAPH* m, int x) {
    int cnt = 1;
    int list[1001] = { 0 };
    int head = 0, rear = 0;
    int last = x;//当前这一层最后一个节点
    int tail = 1;//下一层的最后一个节点
    int level = 0;
    visited[x] = 1;

    list[rear++] = x;
    while (head != rear) {
        int y = list[head++];

        for (int i = 1; i <= m->num_v; i++) {
            if (!visited[i] && m->edge[y][i]) {//--------------------------------这个last，tail用来辨别当前是第几层
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

void gethead(GRAPH m,char* queue, int* i,int* tail) {
    for (int j = 0; j < m.vex_cnt; j++) {
        if (m.vex[j] == queue[0]) {//拿到队首的那个顶点在图中的位置，但如果图中有多个相同元素的话就不行。
            *i = j;//最好是让队列的元素是一个结构体，在将顶点入队的同时将该顶点在图中的位置记录下来。
        }
    }
    for (int j = 1; j < tail-1; j++) {
        queue[j - 1] = queue[j];
    }
    *tail-=1;
}
#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                            //最小生成树
//prim
#if 0
#define vex_max 9
#define edge_max 15
#define INFINITY 65535
typedef struct GRAPH {
    char vex[vex_max];
    int edge[vex_max][vex_max];
    int vex_cnt;
    int edge_cnt;
}GRAPH;
bool visited[9];
typedef struct EDGE {
    int begin;
    int end;
    int weight;
}EDGE;
EDGE edge[15];
void MiniSpanTree_prim(GRAPH m);
void MiniSpanTree_kruskal(GRAPH m);
int find(int* parent, int num);
int main()
{
    GRAPH m;
    m.vex_cnt = 9;
    m.edge_cnt = 15;
    m.vex[0] = 'A';
    m.vex[1] = 'B';
    m.vex[2] = 'C';
    m.vex[3] = 'D';
    m.vex[4] = 'E';
    m.vex[5] = 'F';
    m.vex[6] = 'G';
    m.vex[7] = 'H';
    m.vex[8] = 'I';
    for (int i = 0; i < m.vex_cnt; i++) {
        for (int j = 0; j < m.vex_cnt; j++) {
            m.edge[i][j] = INFINITY;
        }
    }
    m.edge[0][1] = 10;
    m.edge[0][5] = 11;
    m.edge[1][2] = 18;
    m.edge[1][8] = 12;
    m.edge[1][6] = 16;
    m.edge[2][8] = 8; 
    m.edge[5][6] = 17;
    m.edge[7][6] = 19; 
    m.edge[7][4] = 7;
    m.edge[3][2] = 22;
    m.edge[3][8] = 21;
    m.edge[3][6] = 24;
    m.edge[3][7] = 16;
    m.edge[3][4] = 20;
    m.edge[5][4] = 26;
    
    for (int i = 0; i < m.vex_cnt; i++) {    
        m.edge[i][i] = 0;
    }
    for (int i = 0; i < m.vex_cnt; i++) {
        for (int j = 0; j < m.vex_cnt; j++) {
            if (m.edge[i][j]!=0 && m.edge[i][j]!=INFINITY) {
                m.edge[j][i] = m.edge[i][j];
            }
        }
    }
    /*for (int i = 0; i < m.vex_cnt; i++) {
        for (int j = 0; j < m.vex_cnt; j++) {
            printf("%d\t", m.edge[i][j]);
        }
        printf("\n");
    }*/
    MiniSpanTree_prim(m);
    
    edge[0].begin = 4; edge[0].end = 7; edge[0].weight = 7;
    edge[1].begin = 2; edge[1].end = 8; edge[1].weight = 8;
    edge[2].begin = 0; edge[2].end = 1; edge[2].weight = 10;
    edge[3].begin = 0; edge[3].end = 5; edge[3].weight = 11;
    edge[4].begin = 1; edge[4].end = 8; edge[4].weight = 12;
    edge[5].begin = 3; edge[5].end = 7; edge[5].weight = 16;
    edge[6].begin = 1; edge[6].end = 6; edge[6].weight = 16;
    edge[7].begin = 5; edge[7].end = 6; edge[7].weight = 17;
    edge[8].begin = 1; edge[8].end = 2; edge[8].weight = 18;
    edge[9].begin = 6; edge[9].end = 7; edge[9].weight = 19;
    edge[10].begin = 3; edge[10].end =4; edge[10].weight = 20;
    edge[11].begin = 3; edge[11].end =8; edge[11].weight = 21;
    edge[12].begin = 2; edge[12].end =3; edge[12].weight = 22;
    edge[13].begin = 3; edge[13].end =6; edge[13].weight = 24;
    edge[14].begin = 4; edge[14].end =5; edge[14].weight = 26;
    
    printf("\n");
    MiniSpanTree_kruskal(m);




    return 0;
}
void MiniSpanTree_prim(GRAPH m) {
    int min, i, j, k;
    /*int* adjvex = (int*)malloc(sizeof(int) * (m.vex_cnt));
    int* mincost= (int*)malloc(sizeof(int) * (m.vex_cnt));*/
    int adjvex[9];
    int mincost[9];
    adjvex[0] = 0;
    mincost[0] = 0;//v0加入最小生成树
    for (i = 1; i < m.vex_cnt; i++) {
        adjvex[i] = 0;
        mincost[i] = m.edge[0][i];
    }
    for (i = 1; i < m.vex_cnt; i++) {
        min = INFINITY;
        k = 0;
        for (j = 1; j < m.vex_cnt; j++) {
            if (mincost[j] != 0 && mincost[j] < min) {
                min = mincost[j];
                k = j;
            }
        }
        printf("(%d,%d)", adjvex[k], k);
        mincost[k] = 0;
        for (j = 1; j < m.vex_cnt; j++) {
            if (mincost[j] != 0 && m.edge[k][j] < mincost[j]) {
                mincost[j] = m.edge[k][j];
                adjvex[j] = k;
            }
        }
    }

}
void MiniSpanTree_kruskal(GRAPH g) {
    int i, n, m;
    int parent[15];
    for (i = 0; i < g.edge_cnt; i++) {
        parent[i] = 0;
    }
    for (i = 0; i < g.edge_cnt; i++) {
        n = find(parent, edge[i].begin);
        m = find(parent, edge[i].end);
        if (n != m) {
            parent[n] = m;
            printf("(%d,%d)", edge[i].begin, edge[i].end);
        }
    }
}
int find(int* parent, int num) {
    while (parent[num] > 0) {
        num = parent[num];
    }
    return num;
}
#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                              //最短路径
#if 0
#define vex_max 9
#define edge_max 14
#define INFINITY 65535
typedef struct GRAPH {
    char vex[vex_max];
    int edge[vex_max][vex_max];
    int vex_cnt;
    int edge_cnt;
}GRAPH;
void get_road(int* path, int* road, int* cnt, int dst);
void shortestpath_Dijkstra(GRAPH m, int v0, int* P, int* D);
void shortestpath_floyd(GRAPH m , int** P, int** D);
void shortest_path(GRAPH* m, int src, int* dist, int* path);
int main()
{
    GRAPH m;
    m.vex_cnt = 9;
    m.edge_cnt = 14;
    
    for (int i = 0; i < m.vex_cnt; i++) {
        for (int j = 0; j < m.vex_cnt; j++) {
            if (i == j) {
                m.edge[i][j] = 0;
            }
            else {
                m.edge[i][j] = INFINITY;
            }
        }
    }
    m.edge[0][1] = 1; m.edge[1][3] = 7; m.edge[1][4] = 5; m.edge[0][2] = 5; m.edge[2][4] = 1; m.edge[2][5] = 7;
    m.edge[8][6] = 7; m.edge[6][3] = 3; m.edge[6][4] = 6; m.edge[8][7] = 4; m.edge[7][4] = 9; m.edge[7][5] = 5;
    m.edge[1][2] = 3; m.edge[3][4] = 2; m.edge[4][5] = 3; m.edge[6][7] = 2;
    for (int i = 0; i < m.vex_cnt; i++) {
        for (int j = 0; j < m.vex_cnt; j++) {
            if (m.edge[i][j] != 0 && m.edge[i][j] < INFINITY) {
                m.edge[j][i] = m.edge[i][j];
            }
        }
    }
    int P1[vex_max];
    int D1[vex_max];
    int** P2 = (int**)malloc(sizeof(int*) * m.vex_cnt);
    for (int i = 0; i < m.vex_cnt; i++) {
        P2[i] = (int*)malloc(sizeof(int) * m.vex_cnt);
    }
    int** D2 = (int**)malloc(sizeof(int*) * m.vex_cnt);
    for (int i = 0; i < m.vex_cnt; i++) {
        D2[i] = (int*)malloc(sizeof(int) * m.vex_cnt);
    }
    //shortestpath_Dijkstra(m, 0, P1, D1);
    shortest_path(&m, 0, D1, P1);
    //shortestpath_floyd(m, P2, D2);
    int arr[20];
    int cnt = 0;
    get_road(P1, arr, &cnt, 8);
    /*for (int i = 0; i < m.vex_cnt; i++) {
        for (int j = 0; j < m.vex_cnt; j++) {
            printf("%d\t", D2[i][j]);
        }
        printf("\n");
    }*/
    

    return 0;
}
void shortestpath_Dijkstra(GRAPH m, int v0, int* P, int* D) {
    int i, j, k,min;
    int final[vex_max];
    for (i = 0; i < m.vex_cnt; i++) {
        final[i] = 0;
        D[i] = m.edge[v0][i];
        P[i] = -1;
    }
    final[v0] = 1;
    P[v0] = 0;
    for (i = 1; i < m.vex_cnt; i++) {
        min = INFINITY;
        for (j = 0; j < m.vex_cnt; j++) {
            if (!final[j] && D[j] < min) {
                min = D[j];
                k = j;
            }
        }
        final[k] = 1;
        for (j = 0; j < m.vex_cnt; j++) {
            if (!final[j] && (min+m.edge[k][j]) < D[j]) {
                D[j] =min + m.edge[k][j];
                P[j] = k;
            }
        }
    }

}
void shortest_path(GRAPH* m, int src, int* dist, int* path) {
    int final[101] = { 0 };
    for (int i = 0; i < m->vex_cnt; i++) {
        path[i] = -1;
        dist[i] = INFINITY;
    }
    dist[src] = 0;
    for (int i = 0; i < m->vex_cnt; i++) {
        int min = INFINITY, k = 0;
        for (int i = 0; i < m->vex_cnt; i++) {
            if (dist[i] < min && !final[i]) {
                min = dist[i];
                k = i;
            }
        }
        final[k] = 1;
        for (int i = 0; i < m->vex_cnt; i++) {
            if (!final[i] && m->edge[k][i] < INFINITY) {
                if (min + m->edge[k][i] < dist[i]) {
                    dist[i] = min + m->edge[k][i];
                    path[i] = k;
                }
            }
        }
    }

}


void shortestpath_floyd(GRAPH m, int** P, int** D) {
    int i, j, k;
   
    for (i = 0; i < m.vex_cnt; i++) {
        for (j = 0; j < m.vex_cnt; j++) {
            D[i][j] = m.edge[i][j];
            P[i][j] = j;
        }
    }
    for (k = 0; k < m.vex_cnt; k++) {
        for (i = 0; i < m.vex_cnt; i++) {
            for (j = 0; j < m.vex_cnt; j++) {
                if (D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[i][k];
                }
            }
        }
    }
}

void get_road(int* path, int* road, int* cnt, int dst) {
    int stack[101];
    int top = -1;

    stack[++top] = dst;
    (*cnt)++;
    while (path[dst] != -1) {
        dst=stack[++top] = path[dst];
        (*cnt)++;
    }

    int t = 0;
    while (top != -1) {
        road[t++] = stack[top--];
    }

}
#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                              //拓扑排序
#if 0
#define VEX_MAX 14
#define EDGE_MAX 20
#define OK 1
#define ERROR 0
typedef int status;
typedef struct EDGE {
    int adjvex;
    struct EDGE* next;
}EDGE;

typedef struct VEX {
    int in;
    int data;
    EDGE* firstedge;
}VEX;

typedef struct GRAPH {
    VEX vex[VEX_MAX];
    int vex_cnt;
    int edge_cnt;
}GRAPH;

status TopologicalSort(GRAPH* m);
int main()
{
    GRAPH m;
    m.vex_cnt = 14;
    m.edge_cnt = 20;

    TopologicalSort(&m);

    return 0;
}

status TopologicalSort(GRAPH* m) {
    int cnt=0;
    int top=-1;
    int* stack;
    stack = (int*)malloc(sizeof(int) * m->vex_cnt);
    int cur;
    EDGE* p;
    int q;
    for (int i = 0; i < m->vex_cnt; i++) {
        if (m->vex[i].in == 0) {
            stack[++top] = i;
        }
    }
    while (top!=-1) {
        cur = stack[top--];
        printf("%d", m->vex[cur].data);
        cnt++;
        for (p = m->vex[cur].firstedge; p; p = p->next) {
            int q = p->adjvex;
            if (!(--m->vex[q].in)) {
                stack[++top] = q;
            }
        }
    }

    if (cnt == m->vex_cnt) {
        return OK;
    }
    else {
        return ERROR;
    }
}
#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                  //关键路径
#if 0
#define VEX_MAX 14
#define EDGE_MAX 20
#define OK 1
#define ERROR 0
typedef int status;
typedef struct EDGE {
    int adjvex;
    int weight;
    struct EDGE* next;
}EDGE;

typedef struct VEX {
    int in;
    int data;
    EDGE* firstedge;
}VEX;

typedef struct GRAPH {//邻接表
    VEX vex[VEX_MAX];
    int vex_cnt;
    int edge_cnt;
}GRAPH;

int* etv, * ltv;
int* stack2;
int top2;
status TopologicalSort(GRAPH* m);
void CriticalPath(GRAPH* m);
int main()
{
    GRAPH m;
    m.vex_cnt = 14;
    m.edge_cnt = 20;
    CriticalPath(&m);

    return 0;
}
void CriticalPath(GRAPH* m) {
    int ete, lte;
    int cur;
    EDGE* p;
    etv = (int*)malloc(sizeof(int) * m->vex_cnt);
    TopologicalSort(m);
    ltv = (int*)malloc(sizeof(int) * m->vex_cnt);
    for (int i = 0; i < m->vex_cnt; i++) {
        ltv[i] = etv[m->vex_cnt - 1];
    }
    while (top2 != -1) {
        cur = stack2[top2--];
        for (p = m->vex[cur].firstedge; p; p = p->next) {
            int q = p->adjvex;
            if (ltv[q] - p->weight < etv[cur]) {
                ltv[cur] = ltv[q] - p->weight;
            }
        }
    }

    for (int i = 0; i < m->vex_cnt; i++) {
        for (p = m->vex[i].firstedge; p; p = p->next) {
            int q = p->adjvex;//没有测试数据的输入，所以出现访问错误
            ete = etv[i];
            lte = ltv[i] - (p->weight);
            if (ete == lte) {
                printf("%d---%d\n", m->vex[i], m->vex[q]);
            }
        }
    }



}

status TopologicalSort(GRAPH* m) {
    int cnt = 0;
    int top = -1;
    int* stack;
    stack = (int*)malloc(sizeof(int) * m->vex_cnt);
    int cur;
    EDGE* p;
    int q;
    for (int i = 0; i < m->vex_cnt; i++) {
        if (m->vex[i].in == 0) {
            stack[++top] = i;
        }
    }
    //etv = (int*)malloc(sizeof(int) * m->vex_cnt);
    for (int i = 0; i < m->vex_cnt; i++) {
        etv[i] = 0;
    }
    stack2 = (int*)malloc(sizeof(int) * m->vex_cnt);
    top2 = -1;
    while (top != -1) {
        cur = stack[top--];
        stack2[++top2] = cur;
        cnt++;
        for (p = m->vex[cur].firstedge; p; p = p->next) {
            int q = p->adjvex;
            if (!(--m->vex[q].in)) {
                stack[++top] = q;
            }
            if (etv[cur] + p->weight > etv[q]) {//求所有能够完成事件k中最晚的那一个，比如组装汽车这个事件就受限于生产零件最慢的那个活动
                etv[q] = etv[cur] + p->weight;
            }
        }
    }
    if (cnt == m->vex_cnt) {
        return OK;
    }
    else {
        return ERROR;
    }
}
#endif

























































































