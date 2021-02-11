//
// Created by Rvioleck on 2021/2/2.
//

#include "Graph.h"

//<editor-fold desc="邻接矩阵和邻接表找表相邻接点算法">
int FirstNeighbor(MGraph G, int v){
    for (int i = 0; i < G.vexNum; ++i) {
        if (G.Edge[v][i] != MaxInt){
            return i;
        }
    }
    return -1;
}

int NextNeighbor(MGraph G, int v, int w){
    // 求下标v对应的结点在w之后的第一个存在边的对应结点
    for (int i = w + 1; i < G.vexNum; ++i) {
        if (G.Edge[v][i] != MaxInt){
            return i;
        }
    }
    return -1;
}

int FirstNeighbor(ALGraph G, int v){
    if (G.vertexes[v].first){
        return G.vertexes[v].first->adjVex;
    }
    return -1;
}

int NextNeighbor(ALGraph G, int v, int w){
    ArcNode *first = G.vertexes[v].first;
    while (first->adjVex != w){
        first = first->next;
    }
    if (first->next != nullptr){
        return first->next->adjVex;
    }
    return -1;
}
//</editor-fold>

//<editor-fold desc="BFS广度优先遍历(邻接矩阵和邻接表实现)">
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
    cout<<endl<<endl;
}

void BFS(ALGraph G, int v, bool visited[]){
    cout<<G.vertexes[v].data<<" ";
    visited[v] = true;
    CQueue Q;
    InitQueue(Q);
    EnQueue(Q, v);
    while (!IsEmpty(Q)){
        DeQueue(Q, v);
        for (int w = FirstNeighbor(G, v); w >= 0 ; w = NextNeighbor(G, v, w)) {
            if (!visited[w]){
                cout<<G.vertexes[w].data<<" ";
                visited[w] = true;
                EnQueue(Q, w);
            }
        }
    }
}

void BFSTraverse(ALGraph G){
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
    cout<<endl<<endl;
}

//</editor-fold>

//<editor-fold desc="DFS深度优先遍历(邻接矩阵和邻接表实现)">
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
    Push(S, v);
    while (!IsEmpty(S)){
        Pop(S, v);
        if (!visited[v]){
            cout<<G.Vex[v]<<" ";     // 访问初始顶点v
            visited[v] = true;       // 访问时置标志位为true，而非入栈的时候置标志位为true
        }
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
            if (!visited[w]){
                Push(S, w);
            }
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
    cout<<endl<<endl;
}

void DFS(ALGraph G, int v, bool visited[]){
    cout<<G.vertexes[v].data<<" ";
    visited[v] = true;
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        if (!visited[w]){
            DFS(G, w, visited);
        }
    }
}

void DFS_iterate(ALGraph G, int v, bool visited[]){
    /// 非递归深度优先遍历邻接表G
    LinkStack S;
    InitStack(S);
    Push(S, v);
    while (!IsEmpty(S)){
        Pop(S, v);
        if (!visited[v]){
            visited[v] = true;     // 访问时置标志位为true，而非入栈的时候置标志位为true
            cout<<G.vertexes[v].data<<" ";
        }
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
            if (!visited[w]){
                Push(S, w);
            }
        }
    }
}

void DFSTraverse(ALGraph G){
    bool visited[G.vexNum];
    for (int i = 0; i < G.vexNum; ++i) {
        visited[i] = false;
    }
    cout<<"DFS: ";
    for (int i = 0; i < G.vexNum; ++i) {
        if (!visited[i]){
            DFS(G, i, visited);
        }
    }
    cout<<endl<<endl;
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
    if (aNum == G.arcNum && vNum == G.vexNum)  // 一次深搜的结点为总结点数，弧数为结点数减一，则为树
        return true;
    else
        return false;
}
//</editor-fold>

//<editor-fold desc="查找结点vi到结点vj之间是否有路径">
bool betweenIandJ_DFS(ALGraph G, VertexType vi, VertexType vj){
    /// 用深度优先遍历来查找结点vi和结点vj之间是否存在路径
    bool visited[G.vexNum];
    LinkStack S;
    InitStack(S);
    int i, j;  // 记录结点vi和vj的下标值
    for (int k = 0; k < G.vexNum; ++k) { // 初始化被访问序列
        visited[k] = false;
        if (G.vertexes[k].data == vi){
            i = k;
        }
        if (G.vertexes[k].data == vj){
            j = k;
        }
    }
    Push(S, i);
    while (!IsEmpty(S)){
        Pop(S, i);
        for (int w = FirstNeighbor(G, i); w >= 0; w = NextNeighbor(G, i, w)) {
            if (!visited[w]){
                Push(S, w);  // 将结点i的相邻结点依次入栈
            }
        }
        if (i == j){   // 此时结点下标i与结点下标j相等时则可以正常访问到结点j
            return true;
        }else
            visited[i] = true;
    }
    return false;
}

bool betweenIandJ_BFS(ALGraph G, VertexType vi, VertexType vj){
    /// 用广度优先遍历来查找结点vi和结点vj之间是否存在路径
    bool visited[G.vexNum];
    CQueue Q;
    InitQueue(Q);
    int i, j;
    for (int k = 0; k < G.vexNum; ++k) {
        visited[k] = false;
        if (G.vertexes[k].data == vi){
            i = k;
        }
        if (G.vertexes[k].data == vj){
            j = k;
        }
    }
    EnQueue(Q, i);
    while (!IsEmpty(Q)){
        DeQueue(Q, i);
        for (int w = FirstNeighbor(G, i); w >=0; w = NextNeighbor(G, i, w)) {
            if (!visited[w]){
                if (w == j)
                    return true;
                EnQueue(Q, w);
                visited[w] = true;
            }
        }
    }
    return false;
}
//</editor-fold>

//<editor-fold desc="查找结点vi到结点vj的所有路径">
void FindPath(ALGraph G, int i, int j, VertexType path[], int d, bool visited[]){
    ArcNode *p;
    d++;
    path[d] = G.vertexes[i].data;
    visited[i] = true;
    if (i == j){
        for (int k = 0; k <= d; ++k) {
            cout<<path[k];
        }
        cout<<endl;
    }
    p = G.vertexes[i].first;
    while (p != nullptr){
        int w = p->adjVex;
        if (!visited[w]){
            FindPath(G, w, j, path, d, visited);
        }
        p = p->next;
    }
    visited[i] = false;
}

void FindPathDFS(ALGraph G, VertexType vi, VertexType vj){
    bool visited[G.vexNum];
    int i = 0, j = 0;
    for (int k = 0; k < G.vexNum; ++k) {
        visited[k] = false;
        if (G.vertexes[k].data == vi){
            i = k;
        }
        if (G.vertexes[k].data == vj){
            j = k;
        }
    }
    VertexType path[G.vexNum];
    FindPath(G, i, j, path, -1, visited);
}
//</editor-fold>

//<editor-fold desc="求最小生成树(邻接矩阵Prim算法)">
bool isComplete(const bool isJoin[], int n){
    for (int i = 0; i < n; ++i) {
        if (!isJoin[i]){
            return false;
        }
    }
    return true;
}

int Prim(MGraph G, MGraph &T){
    /// Prim算法求最小生成树
    // isJoin为判断结点是否加入的标志, lowCast为树T到剩余每个结点的长度
    bool isJoin[G.vexNum], lowCast[G.vexNum];
    // isJoin和lowCast初始化
    for (int i = 0; i < G.vexNum; ++i) {
        isJoin[i] = false;
        lowCast[i] = G.Edge[0][i];
    }
    lowCast[0] = false;
    isJoin[0] = true;
    // 初始化T的所有结点
    // (T初始化是具有G的所有结点，但是进行迭代的过程中通过isJoin数组来判断是否完成加入)
    for (int i = 0; i < G.vexNum; ++i) {
        T.Vex[i] = G.Vex[i];
    }
    T.vexNum = G.vexNum;
    // 开始迭代
    while (!isComplete(isJoin, G.vexNum)){ // 当isJoin数组不全为1时，则未完成
        // 找到lowCast数组中最小值
        int min = MaxInt, index = -1;
        for (int i = 0; i < G.vexNum; ++i) {
            if (isJoin[i] == 0){  // 找到下一个最小值不在T内
                if (min > lowCast[i]){
                    min = lowCast[i];
                    index = i;
                }
            }
        }
        // 将边赋值
        for (int i = 0; i < G.vexNum; ++i) {
            if (G.Edge[index][i] == min && isJoin[i] == 1){  // 下一个最小值的另一个结点应该在T内
                T.Edge[index][i] = min;
                T.Edge[i][index] = min;
                T.arcNum++;
                break;
            }
        }
        // 更新isJoin数组
        isJoin[index] = true;
        // 更新lowCast数组
        for (int i = 0; i < G.vexNum; ++i) {
            if (isJoin[i] == 0){
                if (G.Edge[index][i] < lowCast[i]){
                    lowCast[i] = G.Edge[index][i];
                }
            }
        }
    }
    int low = 0;   // 记录最小生成树的代价
    for (int i = 0; i < G.vexNum; ++i) {
        low += lowCast[i];
    }
    return low;    // 返回代价
}
//</editor-fold>

//<editor-fold desc="求单源最短路径(无权图BFS，带权图Dijkstra算法)">

void BFSMinDistance(MGraph G, VertexType vi){
    /// BFS求无权图(权相同)单源最短路径
    int d[G.vexNum], path[G.vexNum];
    bool visited[G.vexNum];
    int u = -1;   // u为结点vi的下标
    for (int i = 0; i < G.vexNum; ++i) {
        if (G.Vex[i] == vi){
            u = i;
        }
        path[i] = -1;
        d[i] = MaxInt;
        visited[i] = false;
    }
    int u0 = u;   // 记录u的备份
    d[u] = 0;
    visited[u] = true;
    CQueue Q;
    InitQueue(Q);
    EnQueue(Q, u);
    while (!IsEmpty(Q)){
        DeQueue(Q, u);
        for (int w = FirstNeighbor(G, u); w >= 0; w = NextNeighbor(G, u, w)) {
            if (!visited[w]){
                d[w] = d[u] + 1;
                visited[w] = true;
                path[w] = u;
                EnQueue(Q, w);
            }
        }
    }
    // 得到d[]和path[]数组
    cout<<"For node "<<G.Vex[u0]<<endl;
    cout<<"Node:   ";
    for (int i = 0; i < G.vexNum; ++i) {
        if (i != u0)
            cout<<"\t"<<G.Vex[i]<<" ";
    }
    cout<<endl;
    cout<<"Distance:";
    for (int i = 0; i < G.vexNum; ++i) {
        if (i != u0)
            cout<<"\t"<<d[i]<<" ";
    }
    cout<<endl;
    cout<<"PreNode:";
    for (int i = 0; i < G.vexNum; ++i) {
        if (i != u0)
            cout<<"\t"<<G.Vex[path[i]]<<" ";
    }
    cout<<endl<<endl;
}

void Dijkstra(MGraph G, VertexType vi){
    /// Dijkstra算法求带权单源最短路径
    //<editor-fold desc="对final[], path[], d[]初始化">
    int d[G.vexNum], path[G.vexNum];
    bool final[G.vexNum];
    int u = -1; // u为结点vi的下标
    for (int i = 0; i < G.vexNum; ++i) {
        // 找到结点vi的下标u并初始化已找到数组final
        if (G.Vex[i] == vi){
            u = i;
        }
        path[i] = -1;
        final[i] = false;
    }
    int u0 = u; // 记录u的备份
    final[u] = true;
    for (int i = 0; i < G.vexNum; ++i) {
        d[i] = G.Edge[u][i];
        if (G.Edge[u][i] != MaxInt){
            path[i] = u;
        }
    }
    d[u] = 0;
    //</editor-fold>
    while (!isComplete(final, G.vexNum)){
        // 对每个结点进行循环处理
        int min = MaxInt, index = -1;
        for (int i = 0; i < G.vexNum; ++i) {
            // 找到未被处理中d最短的结点和其下标
            if (!final[i]){
                if (min > d[i]){
                    min = d[i];
                    index = i;
                }
            }
        }
        final[index] = true;
        for (int j = 0; j < G.vexNum; ++j) {
            // 对与结点index相邻的所有未被处理的结点进行d的处理
            if (!final[j] && G.Edge[index][j] != MaxInt && d[index] + G.Edge[index][j] < d[j]){
                d[j] = d[index] + G.Edge[index][j];
                path[j] = index;
            }
        }
    }
    // 得到d[]和path[]数组
    cout<<"For node "<<G.Vex[u0]<<endl;
    cout<<"Node:   ";
    for (int i = 0; i < G.vexNum; ++i) {
        if (i != u0)
            cout<<"\t"<<G.Vex[i]<<" ";
    }
    cout<<endl;
    cout<<"Distance:";
    for (int i = 0; i < G.vexNum; ++i) {
        if (i != u0)
            cout<<"\t"<<d[i]<<" ";
    }
    cout<<endl;
    cout<<"PreNode:";
    for (int i = 0; i < G.vexNum; ++i) {
        if (i != u0)
            cout<<"\t"<<G.Vex[path[i]]<<" ";
    }
    cout<<endl<<endl;
}
//</editor-fold>

void Floyd(MGraph G){
    /// Floyd算法求图的各点间最短路径
    // 数组初始化
    int a[G.vexNum][G.vexNum], path[G.vexNum][G.vexNum];
    for (int i = 0; i < G.vexNum; ++i) {
        for (int j = 0; j < G.vexNum; ++j) {
            if (i != j){
                a[i][j] = G.Edge[i][j];
            } else {
                a[i][j] = 0;
            }
            path[i][j] = -1;
        }
    }
    // 动态规划迭代
    for (int k = 0; k < G.vexNum; ++k) {
        for (int i = 0; i < G.vexNum; ++i) {
            for (int j = 0; j < G.vexNum; ++j) {
                if (a[i][k] != MaxInt && a[k][j] != MaxInt && a[i][j] > a[i][k] + a[k][j]){
                    a[i][j] = a[i][k] + a[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
    // 打印结果
    cout<<"a:"<<endl;
    for (int i = 0; i < G.vexNum; ++i) {
        for (int j = 0; j < G.vexNum; ++j) {
            cout<<a[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"\npath:"<<endl;
    for (int i = 0; i < G.vexNum; ++i) {
        for (int j = 0; j < G.vexNum; ++j) {
            cout<<path[i][j]<<"\t";
        }
        cout<<endl;
    }
}

//<editor-fold desc="拓扑排序和逆拓扑排序">
void TopologicalSort(ALGraph G){
    /// 对邻接表存储的图G进行拓扑排序
    // 初始化inDegree[]用于存储逻辑上的结点入度和print[]用以记录打印序列
    int inDegree[G.vexNum], print[G.vexNum];
    for (int i = 0; i < G.vexNum; ++i) {
        print[i] = -1;
        inDegree[i] = 0;
    }
    for (int i = 0; i < G.vexNum; ++i) {
        ArcNode *p = G.vertexes[i].first;
        while (p){
            inDegree[p->adjVex]++;
            p = p->next;
        }
    }
    // 初始化将初始的入度为0的结点入栈
    LinkStack S;
    InitStack(S);
    for (int i = 0; i < G.vexNum; ++i) {
        if (inDegree[i] == 0){
            Push(S, i);
        }
    }
    int v, count = 0;
    // 将结点为0的结点遍历入栈
    while (!IsEmpty(S)){
        Pop(S, v);
        print[count++] = v;
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
            if (!--inDegree[w]){
                Push(S, w);
            }
        }
//        for (ArcNode *p = G.vertexes[v].first; p; p = p->next) {
//            int w = p->adjVex;
//            inDegree[w]--;
//            if (!inDegree[w]){
//                Push(S, w);
//            }
//        }
    }
    if (count < G.vexNum){
        cout<<"The graph is not a DAG";
    } else {
        for (int i = 0; i < G.vexNum; ++i) {
            cout<<G.vertexes[print[i]].data<<" ";
        }
        cout<<endl;
    }
}

void DFSTopologicalRecurse(ALGraph G, int v, bool visited[], LinkStack res){
    /// 对结点v进行深度优先遍历
    visited[v] = true;
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        if (!visited[w]){
            DFSTopologicalRecurse(G, w, visited, res);
        }
    }
    Push(res, v);
}

void DFSTopologicalTraversal(ALGraph G){
    /// 在辅助输出栈的帮助下利用递归实现的DFS算法实现拓扑排序
    bool visited[G.vexNum];
    for (int i = 0; i < G.vexNum; ++i) {
        visited[i] = false;
    }
    LinkStack res;
    InitStack(res);
    for (int i = 0; i < G.vexNum; ++i) {
        if (!visited[i]){
            DFSTopologicalRecurse(G, i, visited, res);
        }
    }
    int v;
    while (!IsEmpty(res)){
        Pop(res, v);
        cout<<G.vertexes[v].data<<" ";
    }
    cout<<endl;
}

//</editor-fold>

int main(){
    ALGraph G1;
    CreateGraph(G1, true);
    TopologicalSort(G1);
    DFSTopologicalTraversal(G1);

//    MGraph G;
//    CreateGraph(G, false);

//    BFSMinDistance(G, '1');
//    Dijkstra(G, '1');
//    Floyd(G);

//    BFSTraverse(G);
//    DFSTraverse(G);
//    isTree(G) ? cout<<"G is tree\n" : cout<<"G is not tree\n";


//    MGraph T;
//    InitGraph(T);
//    Prim(G, T);
//    isTree(T) ? cout<<"T is tree\n" : cout<<"T is not tree\n";



//    FindPathDFS(G1, '1', '2');
//    BFSTraverse(G1);
//    DFSTraverse(G1);
//    betweenIandJ_DFS(G1, '1', '2') ? cout<<"yes"<<endl : cout<<"no"<<endl;
//    betweenIandJ_BFS(G1, '1', '2') ? cout<<"yes"<<endl : cout<<"no"<<endl;
}