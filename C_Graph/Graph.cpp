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
    // 求下标v对应的结点在w之后的第一个存在边的对应结点
    for (int i = w + 1; i < G.vexNum; ++i) {
        if (G.Edge[v][i] == true){
            return i;
        }
    }
    return -1;
}

//<editor-fold desc="BFS广度优先遍历">
void BFS(MGraph G, int v, bool visited[]){
    /// 从下标为v的顶点出发，广度优先遍历图G
    cout<<G.Vex[v]<<" ";     // 访问初始顶点v
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

//<editor-fold desc="DFS深度优先遍历">
void DFS(MGraph G, int v, bool visited[]){
    /// 从下标为v的顶点出发，深度优先遍历图G(邻接矩阵)
    cout<<G.Vex[v]<<" ";     // 访问初始顶点v
    visited[v] = true;
    for (int w = FirstNeighbor(G, v); w >= 0 ; w = NextNeighbor(G, v, w)) {
        if (!visited[w]){
            DFS(G, w, visited);
        }
    }
}

void DFS_iterate(MGraph G, int v, bool visited[]){
    /// 非递归深度优先遍历邻接矩阵G
    LinkStack S;
    InitStack(S);
    while (!visited[v] || !IsEmpty(S)){
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
            if (!visited[w])
                Push(S, w);
        }
        if (!visited[v]){
            cout<<G.Vex[v]<<" ";     // 访问初始顶点v
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

//<editor-fold desc="判断图是否为树">
void isTreeDFS(MGraph G, int v, bool visited[], int &vNum, int &aNum){
    visited[v] = true;  // 访问该顶点
    vNum++;  // 结点数加一
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        if (!visited[w]){
            isTreeDFS(G, w, visited, vNum, aNum); // 深度优先搜索
            aNum++;  // 弧数加一
        }
    }
}

bool isTree(MGraph G){
    /// 判断图G是否是一棵树
    bool *visited = new bool[G.vexNum];
    for (int i = 0; i < G.vexNum; ++i) {
        visited[i] = false;
    }
    int vNum = 0, aNum = 0;  // 记录一次深度优先遍历，访问的结点和边的个数
    isTreeDFS(G, 0, visited, vNum, aNum);  // 进行一次深度优先遍历
    if (aNum == G.vexNum - 1 && vNum == G.vexNum)  // 一次深搜的结点为总结点数，弧数为结点数减一，则为树
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