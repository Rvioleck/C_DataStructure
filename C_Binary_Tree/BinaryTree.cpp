//
// Created by Rvioleck on 2021/1/28.
//

#include "BinaryTree.h"

void LevelOrder2(BiTree tree){
    /// 自下而上，从右到左进行层次遍历
    CQueue q;
    InitQueue(q);
    LinkStack s;
    InitStack(s);
    BiTree p;
    EnQueue(q, tree);
    while (!IsEmpty(q)){
        DeQueue(q, p);   // 出队
        Push(s, p);         // 入栈
        if (p->lchild){
            EnQueue(q, p->lchild);
        }
        if (p->rchild){
            EnQueue(q, p->rchild);
        }
    }
    while (!IsEmpty(s)){
        Pop(s, p);
        visit(p);
    }
}

int GetHeight(BiTree tree){
    /// 递归实现
    if (tree == NULL){
        return 0;
    }
    int leftHeight = GetHeight(tree->lchild);
    int rightHeight = GetHeight(tree->rchild);
    if (leftHeight > rightHeight){
        return leftHeight + 1;
    }else{
        return rightHeight + 1;
    }
}

int GetHeight2(BiTree tree){
    /// 非递归实现
    if (tree == NULL)
        return 0;
    int front = -1, rear = -1;
    int last = 0, level = 0;
    BiTNode *Q[MaxSize];
    Q[++rear] = tree;  // 根节点入队
    BiTree p;
    while (front < rear){
        // 队不空，则循环
        p = Q[++front];  // 队列元素出队
        if (p->lchild){
            Q[++rear] = p->lchild;
        }
        if (p->rchild){
            Q[++rear] = p->rchild;
        }
        if (front == last){
            level++;
            last = rear;
        }
    }
    return level;
}

BiTree PreInCreate(ElemType a[], ElemType b[], int l1, int h1, int l2, int h2){
    /// 通过先序序列a和中序序列b来构造二叉树
    BiTree root = (BiTNode*)malloc(sizeof(BiTNode));
    root->data = a[l1];   // 根节点的值为先序遍历第一个结点的值
    int i, lLen, rLen;    // lLen和rLen记录左右子树结点个数
    for (i = l2; b[i] != root->data ; ++i); // 找到根节点在中序序列中的位置
    lLen = i - l2;
    rLen = h2 - i;
    if (lLen > 0){
        root->lchild = PreInCreate(a, b, l1 + 1, l1 + lLen, l2, l2 + lLen - 1);
    }else
        root->lchild = NULL;
    if (rLen > 0){
        root->rchild = PreInCreate(a, b, h1 - rLen + 1, h1, h2 - rLen + 1, h2);
    }else
        root->rchild = NULL;
    return root;
}

bool IsCompleteBinaryTree(BiTree tree){
    // 判断是否为完全二叉树
    if (!tree){
        return true;
    }
    CQueue q;
    InitQueue(q);
    EnQueue(q, tree);
    BiTree p;
    int tag = 0;
    while (!IsEmpty(q)){
        DeQueue(q, p);
        if (p){
            EnQueue(q, p->lchild);
            EnQueue(q, p->rchild);
        }else {
            while (!IsEmpty(q)){
                DeQueue(q, p);
                if (p){
                    return false;
                }
            }
        }
    }
    return true;
}



int main(){
//    BiTree root;
//    InitTree(root);

    /// PreInCreate 调试
    char a[] = "0abdecfg";
    char b[] = "0dbeafcg";
    BiTree tree = PreInCreate(a, b, 1, 7, 1, 7);
    LevelOrder(tree);
    printf("%d", IsCompleteBinaryTree(tree));
//    CreateTree(root);  // 124##5##36##7##
//    printf("%d, %d", GetHeight(root), GetHeight2(root));
}