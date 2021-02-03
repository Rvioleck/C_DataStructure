//
// Created by Rvioleck on 2021/2/2.
//

#include "Graph.h"

int FirstNeighbor(MGraph G, int v){
    for (int i = 0; i < G.vexNum; ++i) {
        if (G.Edge[v][i] == true){
            return i;
        }
    }
    return -1;
}

int NextNeighbor(MGraph G, int v, int w){
    // ���±�v��Ӧ�Ľ����w֮��ĵ�һ�����ڱߵĶ�Ӧ���
    for (int i = w + 1; i < G.vexNum; ++i) {
        if (G.Edge[v][i] == true){
            return i;
        }
    }
    return -1;
}

//<editor-fold desc="BFS������ȱ���">
void BFS(MGraph G, int v, bool visited[]){
    /// ���±�Ϊv�Ķ��������������ȱ���ͼG
    cout<<G.Vex[v]<<" ";     // ���ʳ�ʼ����v
    visited[v] = true;
    CQueue Q;
    InitQueue(Q);
    EnQueue(Q, v);
    while (!IsEmpty(Q)){
        DeQueue(Q, v);
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
            if (!visited[w]){
                cout<<G.Vex[w]<<" ";
                visited[w] = true;
                EnQueue(Q, w);
            }
        }
    }
}

void BFSTraverse(MGraph G){
    bool visited[G.vexNum];
    for (int i = 0; i < G.vexNum; ++i) {
        visited[i] = false;
    }
    cout<<"BFS: ";
    for (int i = 0; i < G.vexNum; ++i) {
        if (!visited[i]){
            BFS(G, i, visited);
        }
    }
    cout<<endl;
}
//</editor-fold>

//<editor-fold desc="DFS������ȱ���">
void DFS(MGraph G, int v, bool visited[]){
    /// ���±�Ϊv�Ķ��������������ȱ���ͼG(�ڽӾ���)
    cout<<G.Vex[v]<<" ";     // ���ʳ�ʼ����v
    visited[v] = true;
    for (int w = FirstNeighbor(G, v); w >= 0 ; w = NextNeighbor(G, v, w)) {
        if (!visited[w]){
            DFS(G, w, visited);
        }
    }
}

void DFS_iterate(MGraph G, int v, bool visited[]){
    /// �ǵݹ�������ȱ����ڽӾ���G
    LinkStack S;
    InitStack(S);
    while (!visited[v] || !IsEmpty(S)){
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
            if (!visited[w])
                Push(S, w);
        }
        if (!visited[v]){
            cout<<G.Vex[v]<<" ";     // ���ʳ�ʼ����v
            visited[v] = true;
            if (!IsEmpty(S))
                Pop(S, v);
        }
    }
}

void DFSTraverse(MGraph G){
    bool visited[G.vexNum];
    for (int i = 0; i < G.vexNum; ++i) {
        visited[i] = false;
    }
    cout<<"DFS: ";
    for (int i = 0; i < G.vexNum; ++i) {
        if (!visited[i]){
            DFS_iterate(G, i, visited);
        }
    }
    cout<<endl;
}
//</editor-fold>

//<editor-fold desc="�ж�ͼ�Ƿ�Ϊ��">
void isTreeDFS(MGraph G, int v, bool visited[], int &vNum, int &aNum){
    visited[v] = true;  // ���ʸö���
    vNum++;  // �������һ
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        if (!visited[w]){
            isTreeDFS(G, w, visited, vNum, aNum); // �����������
            aNum++;  // ������һ
        }
    }
}

bool isTree(MGraph G){
    /// �ж�ͼG�Ƿ���һ����
    bool *visited = new bool[G.vexNum];
    for (int i = 0; i < G.vexNum; ++i) {
        visited[i] = false;
    }
    int vNum = 0, aNum = 0;  // ��¼һ��������ȱ��������ʵĽ��ͱߵĸ���
    isTreeDFS(G, 0, visited, vNum, aNum);  // ����һ��������ȱ���
    if (aNum == G.vexNum - 1 && vNum == G.vexNum)  // һ�����ѵĽ��Ϊ�ܽ����������Ϊ�������һ����Ϊ��
        return true;
    else
        return false;
}
//</editor-fold>

int main(){
//    MGraph G;
//    CreateGraph(G, false);
//    BFSTraverse(G);
//    DFSTraverse(G);
//    isTree(G) ? cout<<"G is tree\n" : cout<<"G is not tree\n";

    ALGraph G1;
    CreateGraph(G1, false);

}