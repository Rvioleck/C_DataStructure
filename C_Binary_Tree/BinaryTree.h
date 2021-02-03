//
// Created by Rvioleck on 2021/1/28.
//

#ifndef C_BINARY_TREE_BINARYTREE_H
#define C_BINARY_TREE_BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>

#define ElemType char
#define MaxSize 20

//<editor-fold desc="BinaryTree">
typedef struct BiTNode {
    ElemType data;    // 数据域
    struct BiTNode *lchild, *rchild;   // 左右孩子
} BiTNode, *BiTree;

//<editor-fold desc="stack and queue implementation">
typedef struct {
    BiTree data[MaxSize];
    int tag;
    int front;
    int rear;
} CQueue;

void InitQueue(CQueue &Q) {
    Q.tag = 0;
    Q.front = 0;
    Q.rear = 0;
}

bool EnQueue(CQueue &Q, BiTree x) {
    if (Q.tag == 1 && Q.front == Q.rear)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    Q.tag = 1; // 可能满，tag置1
    return true;
}

bool DeQueue(CQueue &Q, BiTree &x) {
    if (Q.tag == 0 && Q.front == Q.rear)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    Q.tag = 0;  // 可能空，tag置0
    return true;
}

bool IsEmpty(CQueue Q) {
    return Q.front == Q.rear && Q.tag == 0;
}

typedef struct LNode {
    BiTree data;
    struct LNode *next;
} *LinkStack;

bool InitStack(LinkStack &S) {
    S = (LNode *) malloc(sizeof(LNode));
    if (S == nullptr) // 分配内存失败
        return false;
    S->next = nullptr;
    return true;
}

bool Push(LinkStack &S, BiTree x) {
    LNode *e = (LNode *) malloc(sizeof(LNode));
    e->data = x;
    e->next = S->next;
    S->next = e;
    return true;
}

bool Pop(LinkStack &S, BiTree &x) {
    if (!S->next)
        return false;
    x = S->next->data;
    S->next = S->next->next;
    return true;
}

bool Peek(LinkStack &S, BiTree &x) {
    if (!S->next)
        return false;
    x = S->next->data;
    return true;
}

void Show(LinkStack S) {
    if (S && S->next) {
        Show(S->next);
    }
    if (S) {
        printf("%c->", S->data);
    }
}

void ShowStack(LinkStack S) {
    S = S->next;
    printf("From the bottom to the top: ");
    Show(S);
    printf("nullptr\n");
}

bool IsEmpty(LinkStack S) {
    return S->next == nullptr;
}
//</editor-fold>

void InitTree(BiTree &tree) {
    tree = (BiTree) malloc(sizeof(BiTNode));
    tree->lchild = nullptr;
    tree->rchild = nullptr;
}

//<editor-fold desc="Tree traversal">
void visit(BiTree tree) {
    if (tree) {
        printf("%c->", tree->data);
    }
}

void PreOrder(BiTree tree) {
    if (tree != nullptr) {
        visit(tree);             // 访问根节点
        PreOrder(tree->lchild);  // 遍历左子树
        PreOrder(tree->rchild);  // 遍历右子树
    }
}

void PreOrder2(BiTree tree) {
    LinkStack s;
    InitStack(s);
    BiTree p = tree;
    while (p || !IsEmpty(s)) {
        if (p) {
            visit(p);
            Push(s, p);
            p = p->lchild;
        } else {
            Pop(s, p);
            p = p->rchild;
        }
    }
}

void InOrder(BiTree tree) {
    if (tree != nullptr) {
        InOrder(tree->lchild);
        visit(tree);
        InOrder(tree->rchild);
    }
}

void InOrder2(BiTree tree) {
    LinkStack s;
    InitStack(s);
    BiTree p = tree;
    while (p || !IsEmpty(s)) {
        if (p) {
            Push(s, p);
            p = p->lchild;
        } else {
            Pop(s, p);
            visit(p);
            p = p->rchild;
        }
    }
}

void PostOrder(BiTree tree) {
    if (tree != nullptr) {
        PostOrder(tree->lchild);
        PostOrder(tree->rchild);
        visit(tree);
    }
}

void PostOrder2(BiTree tree) {
    BiTree p = tree;
    LinkStack s;
    InitStack(s);
    BiTNode *r = nullptr;
    while (p || !IsEmpty(s)) {
        if (p) {   // 左树
            Push(s, p); // 左子树入栈，保留根节点
            p = p->lchild;
        } else {   // 右树
            Peek(s, p); // 取栈顶元素(取(子树)根)
            if (p->rchild && p->rchild != r) {
                p = p->rchild; // 右子树直接遍历
            } else {
                Pop(s, p);
                visit(p);
                r = p;
                p = nullptr;
            }
        }
    }
}

void LevelOrder(BiTree tree) {
    /// 从上到下，从左到右
    CQueue q;
    InitQueue(q);
    BiTree p;
    EnQueue(q, tree);  // 根节点入队
    while (!IsEmpty(q)) {
        DeQueue(q, p);
        visit(p);
        if (p->lchild) {
            EnQueue(q, p->lchild);
        }
        if (p->rchild) {
            EnQueue(q, p->rchild);
        }
    }
}
//</editor-fold>

void CreateTree(BiTree &tree) {
    /// 前序构造二叉树，以字符'#'为空
    char data;
    scanf("%c", &data);
    if (data == '#') {
        tree = nullptr;
    } else {
        tree = (BiTNode *) malloc(sizeof(BiTNode));
        tree->data = data;
        CreateTree(tree->lchild);
        CreateTree(tree->rchild);
    }
}
//</editor-fold>


//<editor-fold desc="ThreadBinaryTree">
typedef struct ThreadNode {
    ElemType data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;  // tag = 1 则指向前驱或后继; tag = 0 则指向左孩子或右孩子
} ThreadNode, *ThreadTree;

void CreateThreadTree(ThreadTree &tree) {
    /// 前序构造线索二叉树，以字符'#'为空
    char data;
    scanf("%c", &data);
    if (data == '#')
        tree = nullptr;
    else {
        tree = (ThreadNode *) malloc(sizeof(ThreadNode));
        tree->data = data;
        tree->ltag = 0;                     // 左线索初始化为0
        tree->rtag = 0;                     // 右线索初始化为0
        CreateThreadTree(tree->lchild); // 递归构造左子树
        CreateThreadTree(tree->rchild); // 递归构造右子树
    }
}

//<editor-fold desc="InThread">
void InThread(ThreadTree &p, ThreadTree &pre) {
    /// 中序遍历实现二叉树线索化
    if (p != nullptr) {
        InThread(p->lchild, pre);  // 递归，线索化左子树
        //region 处理根节点
        if (p->lchild == nullptr) { // 左子树为空，建立前驱线索
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != nullptr && pre->rchild == nullptr) {
            pre->rchild = p;  // 建立后继线索
            pre->rtag = 1;
        }
        pre = p;
        //endregion
        InThread(p->rchild, pre);  // 递归，线索化右子树
    }
}

void CreateInThread(ThreadTree &T) {
    ThreadTree pre = nullptr;
    if (T != nullptr) {
        InThread(T, pre);  // 线索化二叉树
        if (pre->rchild == nullptr)   // 处理最后一个结点
            pre->rtag = 1;
    }
}

ThreadNode *FirstNode(ThreadNode *p) {
    /// 求中序搜索下二叉树中序序列的第一个结点(最左侧的结点)
    while (p->ltag == 0) {
        p = p->lchild;
    }
    return p;
}

ThreadNode *LastNode(ThreadNode *p) {
    /// 求中序搜索下二叉树中序序列的最后一个结点(最右侧的结点)
    while (p->rtag == 0) {
        p = p->rchild;
    }
    return p;
}

ThreadNode *InNextNode(ThreadNode *p) {
    /// 求中序搜索下二叉树中序序列中p的后继
    if (p->rtag == 0)
        return FirstNode(p->rchild); // 右孩子的第一个结点，是该结点的下一个结点
    else
        return p->rchild;
}

ThreadNode *InPriorNode(ThreadNode *p) {
    /// 求中序搜索下二叉树中序序列中p的前驱
    if (p->ltag == 0)
        return LastNode(p->lchild); // 左孩子的最后一个结点，是该结点的上一个结点
    else
        return p->lchild;
}

void PrintInThread(ThreadTree tree) {
    /// 可以中序遍历打印二叉树，同时因为每个结点都包含前驱，所以也可以逆中序打印二叉树
    for (ThreadNode *p = FirstNode(tree); p != nullptr; p = InNextNode(p)) {
        printf("%c ", p->data);
    }
    printf("\n");
}

void RevPrintInThread(ThreadTree tree) {
    /// 逆中序打印二叉树
    for (ThreadNode *p = LastNode(tree); p != nullptr; p = InPriorNode(p)) {
        printf("%c ", p->data);
    }
    printf("\n");
}

//</editor-fold>

//<editor-fold desc="PreThread">
void PreThread(ThreadTree &p, ThreadTree &pre) {
    /// 前序遍历实现二叉树线索化
    if (p != nullptr) {
        //region 处理根节点
        if (p->lchild == nullptr) {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != nullptr && pre->rchild == nullptr) {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
        //endregion
        if (p->ltag != 1)
            PreThread(p->lchild, pre); // 在左子树无线索时，处理左子树
        PreThread(p->rchild, pre);     // 递归处理右子树
    }
}

void CreatePreThread(ThreadTree &T) {
    ThreadTree pre = nullptr;
    if (T != nullptr) {
        PreThread(T, pre);
        if (pre->rchild == nullptr)
            pre->rtag = 1;
    }
}

ThreadNode *PreNextNode(ThreadNode *p) {
    /// 求先序搜索下二叉树先序序列中p的后继
    if (p->rtag == 1) { // 如果存在后继线索，直接为右孩子
        return p->rchild;
    } else if (p->lchild && p->ltag == 0) { // 不存在后继线索和前驱线索，优先左子树根
        return p->lchild;
    } else {            // 不存在左子树根，再是右子树根
        return p->rchild;
    }
}

void PrintPreThread(ThreadTree tree) {
    for (ThreadNode *p = tree; p != nullptr; p = PreNextNode(p)) {
        printf("%c ", p->data);
    }
    printf("\n");
}
//</editor-fold>

//<editor-fold desc="PostThread">
void PostThread(ThreadTree &p, ThreadTree &pre) {
    if (p) {
        PostThread(p->lchild, pre);
        PostThread(p->rchild, pre);
        if (p->lchild == nullptr) {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != nullptr && pre->rchild == p) {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
    }
}

void CreatePostThread(ThreadTree &T) {
    ThreadNode *pre = nullptr;
    if (T) {
        PostThread(T, pre);
        if (pre->rchild == nullptr)
            pre->rtag = 1;
    }
}

ThreadNode *PostPriorNode(ThreadNode *p) {
    /// 求后序搜索下二叉树后序序列中p的前驱
    if (p->ltag == 1) {
        return p->lchild;
    } else if (p->rchild) {
        return p->rchild;
    } else
        return p->lchild;
}

void RevPrintPostThread(ThreadTree tree) {
    for (ThreadNode *p = tree; p != nullptr; p = PostPriorNode(p)) {
        printf("%c ", p->data);
    }
    printf("\n");
}

//</editor-fold>


//</editor-fold>

//<editor-fold desc="BinarySearchTree">
BiTNode *BST_Search(BiTree T, ElemType key){
    /// 非递归实现二叉排序树的查找
    while (T != nullptr && key != T->data){
        if (key < T->data){
            T = T->lchild;
        }else T = T->rchild;
    }
    return T;
}

BiTNode *BSTSearch(BiTree T, ElemType key){
    /// 递归实现二叉排序树的查找
    if (T == nullptr)
        return nullptr;
    if (T->data < key){
        return BSTSearch(T->rchild, key);
    }else if (T->data > key){
        return BSTSearch(T->lchild, key);
    }else
        return T;
}

int BST_Insert(BiTree &T, ElemType key){
    /// 非递归实现二叉排序树的插入
    while (T != nullptr && key != T->data){
        if (key < T->data){
            T = T->lchild;
        }else
            T = T->rchild;
    }
    if (key == T->data)
        return 0;
    if (T == nullptr){
        T = (BiTNode*)malloc(sizeof(BiTNode));
        T->data = key;
        T->lchild = T->rchild = nullptr;
        return 1;
    }
}

int BSTInsert(BiTree &T, ElemType key){
    /// 递归实现二叉排序树的插入
    if (T->data == key)
        return 0;
    else if (T == nullptr){
        T = (BiTNode*)malloc(sizeof(BiTNode));
        T->data = key;
        T->lchild = T->rchild = nullptr;
        return 1;
    }
    else if (key < T->data){
        return BSTInsert(T->lchild, key);
    }
    else
        return BSTInsert(T->rchild, key);
}

void BST_Create(BiTree &T, ElemType str[], int n){
    T = nullptr;
    int i = 0;
    while (i < n){
        BST_Insert(T, str[i]);
        i++;
    }
}


//</editor-fold>


#endif //C_BINARY_TREE_BINARYTREE_H
