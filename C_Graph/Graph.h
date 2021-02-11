//
// Created by Rvioleck on 2021/2/2.
//

#ifndef C_GRAPH_GRAPH_H
#define C_GRAPH_GRAPH_H

#include <iostream>
using namespace std;

#define MaxVertexNum 100
#define MaxInt 0x7fffffff
typedef char VertexType;
typedef int EdgeType;
typedef int QueueType;
typedef int StackType;


//<editor-fold desc="邻接矩阵表示图">
typedef struct {
    /// 邻接矩阵表示图
    VertexType Vex[MaxVertexNum]; // 结点表
    EdgeType Edge[MaxVertexNum][MaxVertexNum]; // 边表
    int vexNum, arcNum; // 记录结点个数和边数
}MGraph;

void InitGraph(MGraph &G){
    for (int i = 0; i < MaxVertexNum; ++i) {
        G.Vex[i] = '#';
        for (int j = 0; j < MaxVertexNum; ++j) {
            G.Edge[i][j] = MaxInt;
        }
    }
    G.vexNum = 0, G.arcNum = 0;
}

int getVertexIndex(MGraph G, VertexType vex){
    /// 求得邻接矩阵G中结点vex对应的结点下标
    for (int i = 0; i < G.vexNum; ++i) {
        if (G.Vex[i] == vex){
            return i;
        }
    }
    return -1;
}

void CreateGraph(MGraph &G, bool isDG){
    /// 邻接矩阵法构造带权图(isDG=1为有向图，isDG=0为无向图)
    InitGraph(G);
    // 输入结点
    cout<<"Vertex: "<<endl;
    VertexType vex;
    cin>>vex;
    int i = 0;
    while (vex != '#'){
        G.Vex[i++] = vex;
        G.vexNum++;
        cin>>vex;
    }
    // 输入边(弧)
    cout<<"Arc: "<<endl;
    VertexType head, tail;
    int headIndex, tailIndex, weight;
    cin>>head>>tail>>weight; // weight为边权
    headIndex = getVertexIndex(G, head);
    tailIndex = getVertexIndex(G, tail);
    while (headIndex != -1 && tailIndex != -1){
        G.Edge[headIndex][tailIndex] = weight;
        if (isDG == 0){
            G.Edge[tailIndex][headIndex] = weight;  // 无向图
        }
        G.arcNum++;
        cin>>head>>tail>>weight;
        headIndex = getVertexIndex(G, head);
        tailIndex = getVertexIndex(G, tail);
    }
}
//</editor-fold>


//<editor-fold desc="邻接表表示图">
typedef struct ArcNode{
    // 边表结点
    int adjVex; // 该弧所指向的结点位置
    struct ArcNode *next; // 指向下一个弧的指针
    EdgeType info; // 弧的权值
}ArcNode;

typedef struct VNode{
    // 顶点表结点
    VertexType data; // 顶点的信息
    ArcNode *first;  // 指向第一个依附于该顶点的弧指针
}VNode, AdjList[MaxVertexNum];

typedef struct{
    /// 邻接表表示图
    AdjList vertexes;
    int vexNum, arcNum;
} ALGraph;

void InitGraph(ALGraph &G){
    G.vexNum = 0;
    G.arcNum = 0;
}

int createArc(ALGraph &G, VertexType head, VertexType tail, int weight, bool isDG){
    int headIndex = -1, tailIndex = -1;
    for (int i = 0; i < G.vexNum; ++i) {
        if (G.vertexes[i].data == head){
            headIndex = i;
        }
        if (G.vertexes[i].data == tail){
            tailIndex = i;
        }
    }
    if (tailIndex == -1 || headIndex == -1){
        // 其中一个结点不存在结点集合中
        return 0;
    }
    // 添加head到tail的结点
    auto* arc = (ArcNode*)malloc(sizeof(ArcNode));
    arc->adjVex = tailIndex;
    arc->info = weight;  // 权值
    arc->next = nullptr;
    if (G.vertexes[headIndex].first == nullptr){
        G.vertexes[headIndex].first = arc;
    } else {
        arc->next = G.vertexes[headIndex].first->next;
        G.vertexes[headIndex].first->next = arc;
    }
    G.arcNum++;

    if (!isDG){
        // 如果是无向图，还要添加tail到head的结点
        auto* arc = (ArcNode*)malloc(sizeof(ArcNode));
        arc->adjVex = headIndex;
        arc->info = weight;
        arc->next = nullptr;
        if (G.vertexes[tailIndex].first == nullptr){
            G.vertexes[tailIndex].first = arc;
        } else {
            arc->next = G.vertexes[tailIndex].first->next;
            G.vertexes[tailIndex].first->next = arc;
        }
    }
    return true;
}

void CreateGraph(ALGraph &G, bool isDG){
    InitGraph(G);
    cout<<"Vertex: "<<endl;
    VertexType vex;
    cin>>vex;
    int i = 0;
    while (vex != '#'){
        G.vertexes[i].data = vex;
        G.vertexes[i].first = nullptr;
        G.vexNum++;
        i++;
        cin>>vex;
    }
    cout<<"Arc: "<<endl;
    VertexType head, tail;
    int weight;
    cin>>head>>tail>>weight;
    while (head != '#' && tail != '#'){
        int tag = createArc(G, head, tail, weight, isDG);
        if (tag == 0){
            cout<<"Existence arc invalid: "<<head<<" and "<<tail<<endl;
        }
        cin>>head>>tail>>weight;
    }
    cout<<"Successfully!"<<endl;
}

//</editor-fold>


//<editor-fold desc="结点队列">
typedef struct{
    QueueType data[MaxVertexNum];
    int tag;
    int front;
    int rear;
} CQueue;

void InitQueue(CQueue &Q){
    Q.tag = 0;
    Q.front = 0;
    Q.rear = 0;
}

bool EnQueue(CQueue &Q, QueueType x){
    if (Q.tag == 1 && Q.front == Q.rear)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear+1)%MaxVertexNum;
    Q.tag = 1; // 可能满，tag置1
    return true;
}

bool DeQueue(CQueue &Q, QueueType &x){
    if (Q.tag == 0 && Q.front == Q.rear)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front+1)%MaxVertexNum;
    Q.tag = 0;  // 可能空，tag置0
    return true;
}

bool IsEmpty(CQueue Q){
    return Q.front == Q.rear && Q.tag == 0;
}
//</editor-fold>


//<editor-fold desc="结点栈">
typedef struct LNode{
    StackType data;
    struct LNode *next;
} *LinkStack;

bool InitStack(LinkStack &S){
    S = (LNode*)malloc(sizeof(LNode));
    if (S == nullptr) // 分配内存失败
        return false;
    S->next = nullptr;
    return true;
}

bool Push(LinkStack &S, StackType x){
    LNode *e = (LNode*)malloc(sizeof(LNode));
    e->data = x;
    e->next = S->next;
    S->next = e;
    return true;
}

bool Pop(LinkStack &S, StackType &x){
    if (!S->next)
        return false;
    x = S->next->data;
    S->next = S->next->next;
    return true;
}

bool IsEmpty(LinkStack S){
    return S->next == nullptr;
}
//</editor-fold>

#endif //C_GRAPH_GRAPH_H
