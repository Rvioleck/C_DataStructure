//
// Created by Rvioleck on 2021/1/28.
//

#include "BinaryTree.h"

void LevelOrder2(BiTree tree){
    /// ���¶��ϣ����ҵ�����в�α���
    CQueue q;
    InitQueue(q);
    LinkStack s;
    InitStack(s);
    BiTree p;
    EnQueue(q, tree);
    while (!IsEmpty(q)){
        DeQueue(q, p);   // ����
        Push(s, p);         // ��ջ
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
    /// �ݹ�ʵ��
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
    /// �ǵݹ�ʵ��
    if (tree == NULL)
        return 0;
    int front = -1, rear = -1;
    int last = 0, level = 0;
    BiTNode *Q[MaxSize];
    Q[++rear] = tree;  // ���ڵ����
    BiTree p;
    while (front < rear){
        // �Ӳ��գ���ѭ��
        p = Q[++front];  // ����Ԫ�س���
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
    /// ͨ����������a����������b�����������
    BiTree root = (BiTNode*)malloc(sizeof(BiTNode));
    root->data = a[l1];   // ���ڵ��ֵΪ���������һ������ֵ
    int i, lLen, rLen;    // lLen��rLen��¼��������������
    for (i = l2; b[i] != root->data ; ++i); // �ҵ����ڵ������������е�λ��
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
    /// �ж��Ƿ�Ϊ��ȫ������
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
    /// ͳ�ƶ������еĶ��Ƚ��
    if (!tree)
        return 0;
    else if (tree->lchild && tree->rchild){
        return NodesWith2Degree(tree->lchild) + NodesWith2Degree(tree->rchild) + 1;
    }else
        return NodesWith2Degree(tree->lchild) + NodesWith2Degree(tree->rchild);
}

BiTree SwapLeftAndRight(BiTree &tree){
    /// ���������������е���������
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
    if (i == k){ // ��
        return tree->data;
    }
    ++i;
    ElemType ch;
    ch = KthNodesInPreOrder(tree->lchild, k); // ��
    if (ch != '#')
        return ch;
    else{
        ch = KthNodesInPreOrder(tree->rchild, k); // ��
        return ch;
    }
}

void Delete(BiTree &bt){
    // ɾ����btΪ��������
    if (bt){
        Delete(bt->lchild);
        Delete(bt->rchild);
        free(bt);
    }
}

void DeleteTheValueOfX(BiTree &tree, ElemType x){
    /// ɾ������ֵΪx������
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

//<editor-fold desc="�ǵݹ�ʵ�ִ�ӡ����x��������">
//typedef struct {
//    BiTree t;
//    int tag;
//}stack; // tag=0��ʾ����Ů�����ʣ�tag=1��ʾ����Ů������

//void printAncestorsOfNodesX(BiTree tree, ElemType x){
//    stack s[MaxSize];
//    int top = 0;
//    while (tree || top > 0){
//        while (tree && tree->data != x){
//            s[++top].t = tree;
//            s[top].tag = 0;
//            tree = tree->lchild; // �������֧����
//        }
//        if (tree->data == x){
//            printf("All ancestors of current node are: \n");
//            for (int j = 1; j <= top; ++j) {
//                printf("%d",s[j].t->data);
//            }
//            return;
//        }
//        while (top != 0 && s[top].tag == 1) // ��ջ
//            top--;
//        if (top != 0){
//            s[top].tag = 1;
//            tree = s[top].t->rchild;
//        }
//    }
//}
//</editor-fold>

bool printAncestorsOfNodesX(BiTree tree, ElemType x){
    /// �ݹ�ʵ�ִ�ӡֵΪx�Ľ�����������
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
    /// �ú����������p��q�������������
    if (root == NULL || root == p || root == q)  // ���ҵ�p��q��㣬ֱ�Ӽ�������(��ջ)
        return root;

    BiTNode *left = LowestCommonAncestor(root->lchild, p, q); // �������������ҵ�p��q
    BiTNode *right = LowestCommonAncestor(root->rchild, p, q);

    if (root->lchild != NULL && root->rchild != NULL)  // �����������ͬʱ�ҵ���p��q����ǰ������ΪLCA
        return root;
    // �����һ������ΪNULL������������p��q���(�Ա����ļ�����Ѱ)���򷵻�p��q��LCA���(ֱ������)
    return left == NULL ? right : left;
}

BiTNode* GetLeafLinkListInOrder(BiTree bt){
    /// �õ�����Ҷ�ӽ����rchildָ�빹�ɵ�����
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
    /// �ǵݹ���Ҷ�ӽ��(��Ȩ)·������
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
    /// �ݹ���Ҷ�ӽ��·������
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

//<editor-fold desc="���ݶ���������������ʽ">
typedef struct node{
    char data;
    struct node *left, *right;
}BTree;
void BtreeToExp(BTree *root, int deep){
    /// ͨ���������õ�������ʽ
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
    /// �ж��Ƿ�Ϊ����������
    static int pre = -32767;
    int b1, b2;
    if (!root)
        return 1;
    if (root){
        // �������
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
    /// ��ȡ�����������и������Ĳ��
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
    /// �ж��Ƿ�Ϊƽ�������, balanceΪroot�Ƿ�ƽ��ı�־��hΪroot�ĸ߶�
    int lb, lh, rb, rh; // ������ƽ���־���������߶ȣ�������ƽ���־���������߶�
    if (root == nullptr){
        h = 0;
        balance = 1;
    } else if (root->lchild == nullptr && root->rchild == nullptr){
        h = 1;
        balance = 1;
    } else {
        // �������
        JudgeAVL(root->lchild, lb, lh); // �������������ƽ���־�͸߶�
        JudgeAVL(root->rchild, rb, rh); // �������������ƽ���־�͸߶�
        // ��ý���ƽ���־�͸߶�
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
    CreateTree(root);  // �������������(abd##e#g##c#f##) (abc##d##ef##g##)

    /// GreaterThanK
    GreaterThanK(root, 'd');

    /// IsBST ����
//    printf("%d", IsBST(root));

    /// JudgeAVL
//    int balance, h;
//    JudgeAVL(root, balance, h);
//    printf("%d, %d", balance, h);


    /// Ҷ�ڵ�(��Ȩ)·�����ȵ���
//    printf("%d\n", WeightProcessLength(root));
//    printf("%d\n", ProcessLength(root, 0));

    /// InThreadTree����
//    ThreadTree InTree;
//    CreateThreadTree(InTree);   // �������������(abd##e#g##c#f##)
//    CreateInThread(InTree);     // ����������������
//    PrintInThread(InTree);         // �����ӡ������
//    RevPrintInThread(InTree);      // �������ӡ������

    /// PreThreadTree ����
//    ThreadTree PreTree;
//    CreateThreadTree(PreTree);   // �������������(abd##e#g##c#f##)
//    CreatePreThread(PreTree);    // ����������������
//    PrintPreThread(PreTree);        // �����ӡ������

    /// PostThreadTree ����
//    ThreadTree PostTree;
//    CreateThreadTree(PostTree);
//    CreatePostThread(PostTree);
//    RevPrintPostThread(PostTree);

    /// GetHeight ����
//    printf("%d, %d", GetHeight(root), GetHeight2(root));
    /// PreInCreate ����
//    char a[] = "0abdecfg";
//    char b[] = "0dbeafcg";
//    BiTree tree = PreInCreate(a, b, 1, 7, 1, 7);
//    LevelOrder(tree);
//    printf("\n");
//    printAncestorsOfNodesX(tree, 'e');
    /// IsCompleteBinaryTree ����
//    printf("%d\n", IsCompleteBinaryTree(tree));
    /// NodesWith2Degree ����
//    printf("The number of the Nodes with 2 sons: %d\n", NodesWith2Degree(tree));
    /// SwapLeftAndRight ����
//    SwapLeftAndRight(tree);
//    LevelOrder(tree);
    /// DeleteTheValueOfX ����
//    DeleteTheValueOfX(tree, 'c');
//    LevelOrder(tree);
    /// KthNodesInPreOrder ����
//    printf("\n%c", KthNodesInPreOrder(tree, 11));

}