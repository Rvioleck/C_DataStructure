//
// Created by Rvioleck on 2021/2/2.
//

#include "Graph.h"

//<editor-fold desc="�ڽӾ�����ڽӱ��ұ����ڽӵ��㷨">
int FirstNeighbor(MGraph G, int v){
    for (int i = 0; i < G.vexNum; ++i) {
        if (G.Edge[v][i] != MaxInt){
            return i;
        }
    }
    return -1;
}

int NextNeighbor(MGraph G, int v, int w){
    // ���±�v��Ӧ�Ľ����w֮��ĵ�һ�����ڱߵĶ�Ӧ���
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

//<editor-fold desc="BFS������ȱ���(�ڽӾ�����ڽӱ�ʵ��)">
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

//<editor-fold desc="DFS������ȱ���(�ڽӾ�����ڽӱ�ʵ��)">
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
    Push(S, v);
    while (!IsEmpty(S)){
        Pop(S, v);
        if (!visited[v]){
            cout<<G.Vex[v]<<" ";     // ���ʳ�ʼ����v
            visited[v] = true;       // ����ʱ�ñ�־λΪtrue��������ջ��ʱ���ñ�־λΪtrue
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
    /// �ǵݹ�������ȱ����ڽӱ�G
    LinkStack S;
    InitStack(S);
    Push(S, v);
    while (!IsEmpty(S)){
        Pop(S, v);
        if (!visited[v]){
            visited[v] = true;     // ����ʱ�ñ�־λΪtrue��������ջ��ʱ���ñ�־λΪtrue
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
    if (aNum == G.arcNum && vNum == G.vexNum)  // һ�����ѵĽ��Ϊ�ܽ����������Ϊ�������һ����Ϊ��
        return true;
    else
        return false;
}
//</editor-fold>

//<editor-fold desc="���ҽ��vi�����vj֮���Ƿ���·��">
bool betweenIandJ_DFS(ALGraph G, VertexType vi, VertexType vj){
    /// ��������ȱ��������ҽ��vi�ͽ��vj֮���Ƿ����·��
    bool visited[G.vexNum];
    LinkStack S;
    InitStack(S);
    int i, j;  // ��¼���vi��vj���±�ֵ
    for (int k = 0; k < G.vexNum; ++k) { // ��ʼ������������
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
                Push(S, w);  // �����i�����ڽ��������ջ
            }
        }
        if (i == j){   // ��ʱ����±�i�����±�j���ʱ������������ʵ����j
            return true;
        }else
            visited[i] = true;
    }
    return false;
}

bool betweenIandJ_BFS(ALGraph G, VertexType vi, VertexType vj){
    /// �ù�����ȱ��������ҽ��vi�ͽ��vj֮���Ƿ����·��
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

//<editor-fold desc="���ҽ��vi�����vj������·��">
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

//<editor-fold desc="����С������(�ڽӾ���Prim�㷨)">
bool isComplete(const bool isJoin[], int n){
    for (int i = 0; i < n; ++i) {
        if (!isJoin[i]){
            return false;
        }
    }
    return true;
}

int Prim(MGraph G, MGraph &T){
    /// Prim�㷨����С������
    // isJoinΪ�жϽ���Ƿ����ı�־, lowCastΪ��T��ʣ��ÿ�����ĳ���
    bool isJoin[G.vexNum], lowCast[G.vexNum];
    // isJoin��lowCast��ʼ��
    for (int i = 0; i < G.vexNum; ++i) {
        isJoin[i] = false;
        lowCast[i] = G.Edge[0][i];
    }
    lowCast[0] = false;
    isJoin[0] = true;
    // ��ʼ��T�����н��
    // (T��ʼ���Ǿ���G�����н�㣬���ǽ��е����Ĺ�����ͨ��isJoin�������ж��Ƿ���ɼ���)
    for (int i = 0; i < G.vexNum; ++i) {
        T.Vex[i] = G.Vex[i];
    }
    T.vexNum = G.vexNum;
    // ��ʼ����
    while (!isComplete(isJoin, G.vexNum)){ // ��isJoin���鲻ȫΪ1ʱ����δ���
        // �ҵ�lowCast��������Сֵ
        int min = MaxInt, index = -1;
        for (int i = 0; i < G.vexNum; ++i) {
            if (isJoin[i] == 0){  // �ҵ���һ����Сֵ����T��
                if (min > lowCast[i]){
                    min = lowCast[i];
                    index = i;
                }
            }
        }
        // ���߸�ֵ
        for (int i = 0; i < G.vexNum; ++i) {
            if (G.Edge[index][i] == min && isJoin[i] == 1){  // ��һ����Сֵ����һ�����Ӧ����T��
                T.Edge[index][i] = min;
                T.Edge[i][index] = min;
                T.arcNum++;
                break;
            }
        }
        // ����isJoin����
        isJoin[index] = true;
        // ����lowCast����
        for (int i = 0; i < G.vexNum; ++i) {
            if (isJoin[i] == 0){
                if (G.Edge[index][i] < lowCast[i]){
                    lowCast[i] = G.Edge[index][i];
                }
            }
        }
    }
    int low = 0;   // ��¼��С�������Ĵ���
    for (int i = 0; i < G.vexNum; ++i) {
        low += lowCast[i];
    }
    return low;    // ���ش���
}
//</editor-fold>

//<editor-fold desc="��Դ���·��(��ȨͼBFS����ȨͼDijkstra�㷨)">

void BFSMinDistance(MGraph G, VertexType vi){
    /// BFS����Ȩͼ(Ȩ��ͬ)��Դ���·��
    int d[G.vexNum], path[G.vexNum];
    bool visited[G.vexNum];
    int u = -1;   // uΪ���vi���±�
    for (int i = 0; i < G.vexNum; ++i) {
        if (G.Vex[i] == vi){
            u = i;
        }
        path[i] = -1;
        d[i] = MaxInt;
        visited[i] = false;
    }
    int u0 = u;   // ��¼u�ı���
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
    // �õ�d[]��path[]����
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
    /// Dijkstra�㷨���Ȩ��Դ���·��
    //<editor-fold desc="��final[], path[], d[]��ʼ��">
    int d[G.vexNum], path[G.vexNum];
    bool final[G.vexNum];
    int u = -1; // uΪ���vi���±�
    for (int i = 0; i < G.vexNum; ++i) {
        // �ҵ����vi���±�u����ʼ�����ҵ�����final
        if (G.Vex[i] == vi){
            u = i;
        }
        path[i] = -1;
        final[i] = false;
    }
    int u0 = u; // ��¼u�ı���
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
        // ��ÿ��������ѭ������
        int min = MaxInt, index = -1;
        for (int i = 0; i < G.vexNum; ++i) {
            // �ҵ�δ��������d��̵Ľ������±�
            if (!final[i]){
                if (min > d[i]){
                    min = d[i];
                    index = i;
                }
            }
        }
        final[index] = true;
        for (int j = 0; j < G.vexNum; ++j) {
            // ������index���ڵ�����δ������Ľ�����d�Ĵ���
            if (!final[j] && G.Edge[index][j] != MaxInt && d[index] + G.Edge[index][j] < d[j]){
                d[j] = d[index] + G.Edge[index][j];
                path[j] = index;
            }
        }
    }
    // �õ�d[]��path[]����
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
    /// Floyd�㷨��ͼ�ĸ�������·��
    // �����ʼ��
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
    // ��̬�滮����
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
    // ��ӡ���
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

//<editor-fold desc="�������������������">
void TopologicalSort(ALGraph G){
    /// ���ڽӱ�洢��ͼG������������
    // ��ʼ��inDegree[]���ڴ洢�߼��ϵĽ����Ⱥ�print[]���Լ�¼��ӡ����
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
    // ��ʼ������ʼ�����Ϊ0�Ľ����ջ
    LinkStack S;
    InitStack(S);
    for (int i = 0; i < G.vexNum; ++i) {
        if (inDegree[i] == 0){
            Push(S, i);
        }
    }
    int v, count = 0;
    // �����Ϊ0�Ľ�������ջ
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
    /// �Խ��v����������ȱ���
    visited[v] = true;
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        if (!visited[w]){
            DFSTopologicalRecurse(G, w, visited, res);
        }
    }
    Push(res, v);
}

void DFSTopologicalTraversal(ALGraph G){
    /// �ڸ������ջ�İ��������õݹ�ʵ�ֵ�DFS�㷨ʵ����������
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