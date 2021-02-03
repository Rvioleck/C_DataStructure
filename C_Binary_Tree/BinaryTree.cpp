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
    /// 判断是否为完全二叉树
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

int NodesWith2Degree(BiTree tree){
    /// 统计二叉树中的二度结点
    if (!tree)
        return 0;
    else if (tree->lchild && tree->rchild){
        return NodesWith2Degree(tree->lchild) + NodesWith2Degree(tree->rchild) + 1;
    }else
        return NodesWith2Degree(tree->lchild) + NodesWith2Degree(tree->rchild);
}

BiTree SwapLeftAndRight(BiTree &tree){
    /// 交换二叉树中所有的左右子树
    if (!tree)
        return NULL;
    else {
        SwapLeftAndRight(tree->lchild);
        SwapLeftAndRight(tree->rchild);
        BiTNode *temp = tree->lchild;
        tree->lchild = tree->rchild;
        tree->rchild = temp;
    }
    return tree;
}

int i = 1;
ElemType KthNodesInPreOrder(BiTree tree, int k){
    if (!tree){
        return '#';
    }
    if (i == k){ // 根
        return tree->data;
    }
    ++i;
    ElemType ch;
    ch = KthNodesInPreOrder(tree->lchild, k); // 左
    if (ch != '#')
        return ch;
    else{
        ch = KthNodesInPreOrder(tree->rchild, k); // 右
        return ch;
    }
}

void Delete(BiTree &bt){
    // 删除以bt为根的子树
    if (bt){
        Delete(bt->lchild);
        Delete(bt->rchild);
        free(bt);
    }
}

void DeleteTheValueOfX(BiTree &tree, ElemType x){
    /// 删除所有值为x的子树
    if (tree->data == x){
        Delete(tree);
        return;
    }
    CQueue q;
    InitQueue(q);
    EnQueue(q, tree);
    BiTNode *p;
    while (!IsEmpty(q)){
        DeQueue(q, p);
        if (p){
            if (p->lchild){
                if (p->lchild->data == x){
                    Delete(p->lchild);
                    p->lchild = NULL;
                }else {
                    EnQueue(q, p->lchild);
                }
            }
            if (p->rchild){
                if (p->rchild->data == x){
                    Delete(p->rchild);
                    p->rchild = NULL;
                }else {
                    EnQueue(q, p->rchild);
                }
            }
        }
    }
}

//<editor-fold desc="非递归实现打印所有x结点的祖先">
//typedef struct {
//    BiTree t;
//    int tag;
//}stack; // tag=0表示左子女被访问，tag=1表示右子女被访问

//void printAncestorsOfNodesX(BiTree tree, ElemType x){
//    stack s[MaxSize];
//    int top = 0;
//    while (tree || top > 0){
//        while (tree && tree->data != x){
//            s[++top].t = tree;
//            s[top].tag = 0;
//            tree = tree->lchild; // 沿着左分支向下
//        }
//        if (tree->data == x){
//            printf("All ancestors of current node are: \n");
//            for (int j = 1; j <= top; ++j) {
//                printf("%d",s[j].t->data);
//            }
//            return;
//        }
//        while (top != 0 && s[top].tag == 1) // 退栈
//            top--;
//        if (top != 0){
//            s[top].tag = 1;
//            tree = s[top].t->rchild;
//        }
//    }
//}
//</editor-fold>

bool printAncestorsOfNodesX(BiTree tree, ElemType x){
    /// 递归实现打印值为x的结点的所有祖先
    if (!tree)
        return false;
    if (tree->data == x)
        return true;
    if (printAncestorsOfNodesX(tree->lchild, x) ||
        printAncestorsOfNodesX(tree->rchild, x)){
        printf("%c ", tree->data);
        return true;
    }
}

BiTNode *LowestCommonAncestor(BiTree root, BiTNode *p, BiTNode *q){
    /// 用后序遍历查找p和q的最近公共祖先
    if (root == NULL || root == p || root == q)  // 查找到p或q结点，直接级联返回(出栈)
        return root;

    BiTNode *left = LowestCommonAncestor(root->lchild, p, q); // 遍历左右子树找到p或q
    BiTNode *right = LowestCommonAncestor(root->rchild, p, q);

    if (root->lchild != NULL && root->rchild != NULL)  // 如果左右子树同时找到了p或q，则当前子树根为LCA
        return root;
    // 如果有一个子树为NULL，则正常返回p或q结点(以便后面的继续找寻)，或返回p和q的LCA结点(直到结束)
    return left == NULL ? right : left;
}

BiTNode* GetLeafLinkListInOrder(BiTree bt){
    /// 得到所有叶子结点由rchild指针构成的链表
    static BiTNode *head, *pre = NULL;
    if (bt){
        GetLeafLinkListInOrder(bt->lchild);
        if (pre == NULL){
            pre = bt;
            head = bt;
        } else{
            pre->rchild = bt;
            pre = bt;
        }
        GetLeafLinkListInOrder(bt->rchild);
        pre->rchild = NULL;
    }
    return head;
}

int GetWidth(BiTree root){
    int width = 1;
    BiTree Q[MaxSize];
    int front = -1, rear = -1;
    int last = 0;
    BiTNode *p;
    Q[++rear] = root;
    while (front < rear){
        p = Q[++front];
        if (p->lchild){
            Q[++rear] = p->lchild;
        }
        if (p->rchild){
            Q[++rear] = p->rchild;
        }
        if (front == last){
            last = rear;
            if (width < rear - front)
                width = rear - front;
        }
    }
    return width;
}

int WeightProcessLength(BiTree root){
    /// 非递归求叶子结点(带权)路径长度
    int level = 0;
    int result = 0;
    BiTNode *Q[MaxSize];
    BiTNode *p;
    int front = -1, rear = -1, last = 0;
    Q[++rear] = root;
    while (front < rear){
        p = Q[++front];
        if (p->lchild == NULL && p->rchild == NULL){
            result += level;
        }
        if (p->lchild)
            Q[++rear] = p->lchild;
        if (p->rchild)
            Q[++rear] = p->rchild;
        if (last == front){
            level++;
            last = rear;
        }
    }
    return result;
}

int ProcessLength(BiTree root, int deep){
    /// 递归求叶子结点路径长度
    static int wpl = 0;
    if (root->lchild == NULL && root->rchild == NULL)
        wpl += deep;
    if (root->lchild){
        ProcessLength(root->lchild, deep+1);
    }
    if (root->rchild){
        ProcessLength(root->rchild, deep+1);
    }
    return wpl;
}

//<editor-fold desc="根据二叉树构造中序表达式">
typedef struct node{
    char data;
    struct node *left, *right;
}BTree;
void BtreeToExp(BTree *root, int deep){
    /// 通过二叉树得到中序表达式
    if (root == NULL) return;
    else if (root->left == NULL && root->right == NULL)
        printf("%c", root->data);
    else{
        if (deep > 1) printf("(");
        BtreeToExp(root->left, deep + 1);
        printf("%c", root->data);
        BtreeToExp(root->right, deep + 1);
        if (deep > 1) printf(")");
    }
}
//</editor-fold>

int IsBST(BiTree root){
    /// 判断是否为二叉排序树
    static int pre = -32767;
    int b1, b2;
    if (!root)
        return 1;
    if (root){
        // 中序遍历
        b1 = IsBST(root->lchild);
        if (b1 == 0 || pre >= root->data){
            return 0;
        }
        pre = root->data;
        b2 = IsBST(root->rchild);
        return b2;
    }
}

int getBSTLevel(BiTree root, ElemType x){
    /// 获取二叉排序树中给定结点的层次
    if (!root)
        return 0;
    int level = 0;
    while (root != NULL){
        level++;
        if (root->data < x){
            root = root->rchild;
        }else if (root->data > x){
            root = root->lchild;
        }else {
            return level;
        }
    }
    return 0;
}

void JudgeAVL(BiTree root, int &balance, int &h){
    /// 判断是否为平衡二叉树, balance为root是否平衡的标志，h为root的高度
    int lb, lh, rb, rh; // 左子树平衡标志，左子树高度，右子树平衡标志，右子树高度
    if (root == nullptr){
        h = 0;
        balance = 1;
    } else if (root->lchild == nullptr && root->rchild == nullptr){
        h = 1;
        balance = 1;
    } else {
        // 后序遍历
        JudgeAVL(root->lchild, lb, lh); // 遍历左子树求得平衡标志和高度
        JudgeAVL(root->rchild, rb, rh); // 遍历右子树求得平衡标志和高度
        // 求该结点的平衡标志和高度
        h = lh > rh ? lh + 1 : rh + 1;
        if (abs(lh - rh) < 2){
            balance = lb&&rb;
        } else {
            balance = 0;
        }


    }
}

void GreaterThanK(BiTree root, ElemType k){
    if (root){
        GreaterThanK(root->rchild, k);
        if (root->data >= k){
            printf("%c", root->data);
        }
        GreaterThanK(root->lchild, k);
    }
}

int main(){
    BiTree root;
    InitTree(root);
    CreateTree(root);  // 以先序构造二叉树(abd##e#g##c#f##) (abc##d##ef##g##)

    /// GreaterThanK
    GreaterThanK(root, 'd');

    /// IsBST 调试
//    printf("%d", IsBST(root));

    /// JudgeAVL
//    int balance, h;
//    JudgeAVL(root, balance, h);
//    printf("%d, %d", balance, h);


    /// 叶节点(带权)路径长度调试
//    printf("%d\n", WeightProcessLength(root));
//    printf("%d\n", ProcessLength(root, 0));

    /// InThreadTree调试
//    ThreadTree InTree;
//    CreateThreadTree(InTree);   // 以先序构造二叉树(abd##e#g##c#f##)
//    CreateInThread(InTree);     // 二叉树中序线索化
//    PrintInThread(InTree);         // 中序打印二叉树
//    RevPrintInThread(InTree);      // 逆中序打印二叉树

    /// PreThreadTree 调试
//    ThreadTree PreTree;
//    CreateThreadTree(PreTree);   // 以先序构造二叉树(abd##e#g##c#f##)
//    CreatePreThread(PreTree);    // 二叉树先序线索化
//    PrintPreThread(PreTree);        // 先序打印二叉树

    /// PostThreadTree 调试
//    ThreadTree PostTree;
//    CreateThreadTree(PostTree);
//    CreatePostThread(PostTree);
//    RevPrintPostThread(PostTree);

    /// GetHeight 调试
//    printf("%d, %d", GetHeight(root), GetHeight2(root));
    /// PreInCreate 调试
//    char a[] = "0abdecfg";
//    char b[] = "0dbeafcg";
//    BiTree tree = PreInCreate(a, b, 1, 7, 1, 7);
//    LevelOrder(tree);
//    printf("\n");
//    printAncestorsOfNodesX(tree, 'e');
    /// IsCompleteBinaryTree 调试
//    printf("%d\n", IsCompleteBinaryTree(tree));
    /// NodesWith2Degree 调试
//    printf("The number of the Nodes with 2 sons: %d\n", NodesWith2Degree(tree));
    /// SwapLeftAndRight 调试
//    SwapLeftAndRight(tree);
//    LevelOrder(tree);
    /// DeleteTheValueOfX 调试
//    DeleteTheValueOfX(tree, 'c');
//    LevelOrder(tree);
    /// KthNodesInPreOrder 调试
//    printf("\n%c", KthNodesInPreOrder(tree, 11));

}