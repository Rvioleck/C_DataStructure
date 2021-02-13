//
// Created by Rvioleck on 2021/2/11.
//

#include "SelectSort.h"


void SelectSort(ElemType A[], int n){
    for (int i = 0; i < n - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < n; ++j) {
            if (A[j] < A[min])
                min = j;
        }
        if (min != i){
            swap(A[i], A[min]);
        }
    }
}

void swap(LNode *p, LNode *q){
    char temp = p->data;
    p->data = q->data;
    q->data = temp;
}

void SelectSort(LinkList &L){
    LNode *cur;
    LNode *done = L;
    while (done->next){
        cur = done->next;
        char min;
        if (cur)
            min = cur->data;
        LNode *minN = cur;
        while (cur){
            if (min > cur->data){
                min = cur->data;
                minN = cur;
            }
            cur = cur->next;
        }
        swap(minN, done->next);
        done = done->next;
    }
}



void HeadMaxAdjust(ElemType A[], int k, int len){
    /// kΪ���������±꣬lenΪ��������
    A[0] = A[k];
    for (int i = 2 * k; i <= len; i *= 2) { // ��ֵ�ϴ���ӽ������ɸѡ
        if (i < len && A[i] < A[i + 1]){    // �����������i���±���Ϊ������
            i++;
        }
        if (A[i] > A[0]){  // ��������±���ڸ��ڵ��±�
            A[k] = A[i];   // ��������ֵ��ֵ�����ڵ�
            k = i;         // ��������������ԭ�����ֵ
        } else break;
    }
    A[k] = A[0];   // ��ɸѡ����ֵ��������λ��
}

void BuildMaxHeap(ElemType A[], int len){
    /// ����ѣ���һ��Ԫ��A[0]����Ԫ��
    for (int i = len/2; i > 0; --i) {
        HeadMaxAdjust(A, i, len);
    }
}

void HeapMaxSort(ElemType A[], int len){
    BuildMaxHeap(A, len);  // ��ʼ����
    for (int i = len; i > 1; --i) {
        swap(A[i], A[1]);
        HeadMaxAdjust(A, 1, i - 1);
    }
}

void HeadMinAdjust(ElemType A[], int k, int len){
    A[0] = A[k];
    for (int i = 2 * k; i <= len; i *= 2) {
        if (i < len && A[i] > A[i + 1]){
            i++;
        }
        if (A[0] > A[i]){
            A[k] = A[i];
            k = i;
        } else break;
    }
    A[k] = A[0];
}

void BuildMinSort(ElemType A[], int len){
    for (int i = len / 2; i >= 1; --i) {
        HeadMinAdjust(A, i, len);
    }
}

void HeapMinSort(ElemType A[], int len){
    BuildMinSort(A, len);
    for (int i = len; i >= 2; --i) {
        swap(A[1], A[i]);
        HeadMinAdjust(A, 1, i - 1);
    }
}

ElemType *B = (ElemType*)malloc(sizeof(ElemType) * MaxSize);
void Merge(ElemType A[], int low, int high, int mid){
    for (int i = low; i <= high; ++i) {
        B[i] = A[i];
    }
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high){
        if (B[i] <= B[j]){
            A[k] = B[i++];
        } else {
            A[k] = B[j++];
        }
        k++;
    }
    while (i <= mid)
        A[k++] = B[i++];
    while (j <= high)
        A[k++] = B[j++];
}

void MergeSort(ElemType A[], int low, int high){
    if (low < high){
        int mid = (low + high) / 2;
        MergeSort(A, low, mid);
        MergeSort(A, mid + 1, high);
        Merge(A, low, high, mid);
    }
}

int main(){
    ElemType A[] = {3, 2, 5, 6, 4, 9, 0, 8};
    MergeSort(A, 0, 7);
    for (int i = 0; i < 8; ++i) {
        cout<<A[i]<<" ";
    }
    cout<<endl;
    SelectSort(A, 8);
    for (int i = 0; i < 8; ++i) {
        cout<<A[i]<<" ";
    }
    cout<<endl;
    HeapMinSort(A, 7);
    for (int i = 1; i <= 7; ++i) {
        cout<<A[i]<<" ";
    }
    cout<<endl;
//    LinkList L;
//    InitList(L);
//    TailInsert(L);
//    ShowList(L);
//    SelectSort(L);
//    ShowList(L);
}