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
    ElemType data;    // ������
    struct BiTNode *lchild, *rchild;   // ���Һ���
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
    Q.tag = 1; // ��������tag��1
    return true;
}

bool DeQueue(CQueue &Q, BiTree &x) {
    if (Q.tag == 0 && Q.front == Q.rear)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    Q.tag = 0;  // ���ܿգ�tag��0
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
    if (S == nullptr) // �����ڴ�ʧ��
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
        visit(tree);             // ���ʸ��ڵ�
        PreOrder(tree->lchild);  // ����������
        PreOrder(tree->rchild);  // ����������
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
        if (p) {   // ����
            Push(s, p); // ��������ջ���������ڵ�
            p = p->lchild;
        } else {   // ����
            Peek(s, p); // ȡջ��Ԫ��(ȡ(����)��)
            if (p->rchild && p->rchild != r) {
                p = p->rchild; // ������ֱ�ӱ���
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
    /// ���ϵ��£�������
    CQueue q;
    InitQueue(q);
    BiTree p;
    EnQueue(q, tree);  // ���ڵ����
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
    /// ǰ��������������ַ�'#'Ϊ��
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
    int ltag, rtag;  // tag = 1 ��ָ��ǰ������; tag = 0 ��ָ�����ӻ��Һ���
} ThreadNode, *ThreadTree;

void CreateThreadTree(ThreadTree &tree) {
    /// ǰ�������������������ַ�'#'Ϊ��
    char data;
    scanf("%c", &data);
    if (data == '#')
        tree = nullptr;
    else {
        tree = (ThreadNode *) malloc(sizeof(ThreadNode));
        tree->data = data;
        tree->ltag = 0;                     // ��������ʼ��Ϊ0
        tree->rtag = 0;                     // ��������ʼ��Ϊ0
        CreateThreadTree(tree->lchild); // �ݹ鹹��������
        CreateThreadTree(tree->rchild); // �ݹ鹹��������
    }
}

//<editor-fold desc="InThread">
void InThread(ThreadTree &p, ThreadTree &pre) {
    /// �������ʵ�ֶ�����������
    if (p != nullptr) {
        InThread(p->lchild, pre);  // �ݹ飬������������
        //region ������ڵ�
        if (p->lchild == nullptr) { // ������Ϊ�գ�����ǰ������
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != nullptr && pre->rchild == nullptr) {
            pre->rchild = p;  // �����������
            pre->rtag = 1;
        }
        pre = p;
        //endregion
        InThread(p->rchild, pre);  // �ݹ飬������������
    }
}

void CreateInThread(ThreadTree &T) {
    ThreadTree pre = nullptr;
    if (T != nullptr) {
        InThread(T, pre);  // ������������
        if (pre->rchild == nullptr)   // �������һ�����
            pre->rtag = 1;
    }
}

ThreadNode *FirstNode(ThreadNode *p) {
    /// �����������¶������������еĵ�һ�����(�����Ľ��)
    while (p->ltag == 0) {
        p = p->lchild;
    }
    return p;
}

ThreadNode *LastNode(ThreadNode *p) {
    /// �����������¶������������е����һ�����(���Ҳ�Ľ��)
    while (p->rtag == 0) {
        p = p->rchild;
    }
    return p;
}

ThreadNode *InNextNode(ThreadNode *p) {
    /// �����������¶���������������p�ĺ��
    if (p->rtag == 0)
        return FirstNode(p->rchild); // �Һ��ӵĵ�һ����㣬�Ǹý�����һ�����
    else
        return p->rchild;
}

ThreadNode *InPriorNode(ThreadNode *p) {
    /// �����������¶���������������p��ǰ��
    if (p->ltag == 0)
        return LastNode(p->lchild); // ���ӵ����һ����㣬�Ǹý�����һ�����
    else
        return p->lchild;
}

void PrintInThread(ThreadTree tree) {
    /// �������������ӡ��������ͬʱ��Ϊÿ����㶼����ǰ��������Ҳ�����������ӡ������
    for (ThreadNode *p = FirstNode(tree); p != nullptr; p = InNextNode(p)) {
        printf("%c ", p->data);
    }
    printf("\n");
}

void RevPrintInThread(ThreadTree tree) {
    /// �������ӡ������
    for (ThreadNode *p = LastNode(tree); p != nullptr; p = InPriorNode(p)) {
        printf("%c ", p->data);
    }
    printf("\n");
}

//</editor-fold>

//<editor-fold desc="PreThread">
void PreThread(ThreadTree &p, ThreadTree &pre) {
    /// ǰ�����ʵ�ֶ�����������
    if (p != nullptr) {
        //region ������ڵ�
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
            PreThread(p->lchild, pre); // ��������������ʱ������������
        PreThread(p->rchild, pre);     // �ݹ鴦��������
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
    /// �����������¶���������������p�ĺ��
    if (p->rtag == 1) { // ������ں��������ֱ��Ϊ�Һ���
        return p->rchild;
    } else if (p->lchild && p->ltag == 0) { // �����ں��������ǰ��������������������
        return p->lchild;
    } else {            // ����������������������������
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
    /// ����������¶���������������p��ǰ��
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
    /// �ǵݹ�ʵ�ֶ����������Ĳ���
    while (T != nullptr && key != T->data){
        if (key < T->data){
            T = T->lchild;
        }else T = T->rchild;
    }
    return T;
}

BiTNode *BSTSearch(BiTree T, ElemType key){
    /// �ݹ�ʵ�ֶ����������Ĳ���
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
    /// �ǵݹ�ʵ�ֶ����������Ĳ���
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
    /// �ݹ�ʵ�ֶ����������Ĳ���
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
