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


//<editor-fold desc="�ڽӾ����ʾͼ">
typedef struct {
    /// �ڽӾ����ʾͼ
    VertexType Vex[MaxVertexNum]; // ����
    EdgeType Edge[MaxVertexNum][MaxVertexNum]; // �߱�
    int vexNum, arcNum; // ��¼�������ͱ���
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
    /// ����ڽӾ���G�н��vex��Ӧ�Ľ���±�
    for (int i = 0; i < G.vexNum; ++i) {
        if (G.Vex[i] == vex){
            return i;
        }
    }
    return -1;
}

void CreateGraph(MGraph &G, bool isDG){
    /// �ڽӾ��󷨹����Ȩͼ(isDG=1Ϊ����ͼ��isDG=0Ϊ����ͼ)
    InitGraph(G);
    // ������
    cout<<"Vertex: "<<endl;
    VertexType vex;
    cin>>vex;
    int i = 0;
    while (vex != '#'){
        G.Vex[i++] = vex;
        G.vexNum++;
        cin>>vex;
    }
    // �����(��)
    cout<<"Arc: "<<endl;
    VertexType head, tail;
    int headIndex, tailIndex, weight;
    cin>>head>>tail>>weight; // weightΪ��Ȩ
    headIndex = getVertexIndex(G, head);
    tailIndex = getVertexIndex(G, tail);
    while (headIndex != -1 && tailIndex != -1){
        G.Edge[headIndex][tailIndex] = weight;
        if (isDG == 0){
            G.Edge[tailIndex][headIndex] = weight;  // ����ͼ
        }
        G.arcNum++;
        cin>>head>>tail>>weight;
        headIndex = getVertexIndex(G, head);
        tailIndex = getVertexIndex(G, tail);
    }
}
//</editor-fold>


//<editor-fold desc="�ڽӱ��ʾͼ">
typedef struct ArcNode{
    // �߱���
    int adjVex; // �û���ָ��Ľ��λ��
    struct ArcNode *next; // ָ����һ������ָ��
    EdgeType info; // ����Ȩֵ
}ArcNode;

typedef struct VNode{
    // �������
    VertexType data; // �������Ϣ
    ArcNode *first;  // ָ���һ�������ڸö���Ļ�ָ��
}VNode, AdjList[MaxVertexNum];

typedef struct{
    /// �ڽӱ��ʾͼ
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
        // ����һ����㲻���ڽ�㼯����
        return 0;
    }
    // ���head��tail�Ľ��
    auto* arc = (ArcNode*)malloc(sizeof(ArcNode));
    arc->adjVex = tailIndex;
    arc->info = weight;  // Ȩֵ
    arc->next = nullptr;
    if (G.vertexes[headIndex].first == nullptr){
        G.vertexes[headIndex].first = arc;
    } else {
        arc->next = G.vertexes[headIndex].first->next;
        G.vertexes[headIndex].first->next = arc;
    }
    G.arcNum++;

    if (!isDG){
        // ���������ͼ����Ҫ���tail��head�Ľ��
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


//<editor-fold desc="������">
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
    Q.tag = 1; // ��������tag��1
    return true;
}

bool DeQueue(CQueue &Q, QueueType &x){
    if (Q.tag == 0 && Q.front == Q.rear)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front+1)%MaxVertexNum;
    Q.tag = 0;  // ���ܿգ�tag��0
    return true;
}

bool IsEmpty(CQueue Q){
    return Q.front == Q.rear && Q.tag == 0;
}
//</editor-fold>


//<editor-fold desc="���ջ">
typedef struct LNode{
    StackType data;
    struct LNode *next;
} *LinkStack;

bool InitStack(LinkStack &S){
    S = (LNode*)malloc(sizeof(LNode));
    if (S == nullptr) // �����ڴ�ʧ��
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
