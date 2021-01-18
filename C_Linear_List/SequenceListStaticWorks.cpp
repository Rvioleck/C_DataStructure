#include "SequenceListStaticAlloc.h"

bool deleteMinElem_p17q1(SeqList &L, ElemType &value){
    // 删除L中最小的元素，并且将最后一个元素填充到最小元素的位置
    if (L.length == 0){
        return false;
    }
    value = L.data[0];
    int index = 0;
    for (int i = 1; i < L.length; ++i) {
        if (L.data[i] < value){
            value = L.data[i];
            index = i;
        }
    }
    L.data[index] = L.data[L.length - 1];
    L.length--;
    return true;
}

void reverseSeqList_p17q2(SeqList &L){
    // 以空间复杂度O(1)逆序顺序表
    int len = L.length;
    int low = 0;
    int high = len - 1;
    while (low < high){
        ElemType temp = L.data[low];
        L.data[low] = L.data[high];
        L.data[high] = temp;
        low++;
        high--;
    }
}

void deleteAllElemIsX_p17q3(SeqList &L, ElemType x){
    /// 删除顺序表中所有值为x的元素
    // 未打乱L的先后次序
    int k = 0;
    for (int i = 0; i < L.length; ++i) {
        if (L.data[i] != x){
            L.data[k] = L.data[i];
            k++;
        }
    }
    L.length = k;

    // 打乱了L的先后次序
//    for (int i = 0; i < L.length; ++i) {
//        if (x == L.data[i]){
//            L.data[i] = L.data[L.length - 1];
//            L.length--;
//            i--;
//        }
//    }
}

bool deleteAllElemBetweenSAndT_p17q4(SeqList &L, ElemType s, ElemType t){
    // 删除所有值在S和T之间的元素，必须保持有序
    if (s >= t || L.length == 0){
        return false;
    }
    int k = 0;
    for (int i = 0; i < L.length; ++i) {
        if (L.data[i] <= s || L.data[i] >= t){
            L.data[k] = L.data[i];
            k++;
        }
    }
    L.length = k;
    return true;
}

bool deleteAllElemFromSToT_p17q5(SeqList &L, ElemType s, ElemType t){
    // 删除所有值从S到T的元素
    if (s >= t || L.length == 0){
        return false;
    }
    int k = 0;
    for (int i = 0; i < L.length; ++i) {
        if (L.data[i] < s || L.data[i] > t){
            L.data[k] = L.data[i];
            k++;
        }
    }
    L.length = k;
    return true;
}

void deleteRepeatedElem_p17q6(SeqList &L){
    // 删除有序顺序表中重复的元素
    int k = 0, i;
    for (i = 0; i < L.length - 1; ++i) {
        if (L.data[i] != L.data[i + 1]){
            L.data[k++] = L.data[i];
        }
    }
    L.data[k++] = L.data[i]; // 最后一个值未进行判断，直接加入
    L.length = k;
}

SeqList mergeOrderlyTwoSeqListToOne_p17q7(SeqList L1, SeqList L2){
    SeqList L3;
    L3.length = L1.length + L2.length;
    int k = 0, i = 0, j = 0;
    while (i < L1.length && j < L2.length){ // L1和L2将小者加入L3
        if (L1.data[i] <= L2.data[j]){
            L3.data[k++] = L1.data[i++];
        }else
            L3.data[k++] = L2.data[j++];
    }
    while (i < L1.length){ // L1比较的剩余部分加入L3
        L3.data[k++] = L1.data[i++];
    }
    while (j < L2.length){ // L2比较的剩余部分加入L3
        L3.data[k++] = L2.data[j++];
    }
    return L3;
}

int main() {
    SeqList L1;
    InitList(L1);
    ListInsert(L1, 1, 5);
    ListInsert(L1, 1, 3);
    ListInsert(L1, 1, 1);
    ShowList(L1);

//    // mergeOrderlyTwoSeqListToOne调试
//    SeqList L2;
//    InitList(L2);
//    ListInsert(L2, 1, 6);
//    ListInsert(L2, 1, 4);
//    ListInsert(L2, 1, 2);
//    ShowList(L2);
//    SeqList L3 = mergeOrderlyTwoSeqListToOne_p17q7(L1, L2);
//    ShowList(L3);

//    // deleteRepeatedElem 调试
//    deleteRepeatedElem(L);
//    ShowList(L);

//    // deleteAllElemFromSToT 调试
//    if (!deleteAllElemFromSToT_p17q4(L, 2, 5)){
//        printf("The Seqlist is empty, or the input numbers is valid!");
//    }else{
//        ShowList(L);
//    }

//    // deleteAllElemBetweenSAndT 调试
//    if (!deleteAllElemBetweenSAndT_p17q3(L, 2, 5)){
//        printf("The Seqlist is empty, or the input numbers is valid!")
//    }else{
//        ShowList(L);
//    }

//    // deleteAllElemIsX 调试
//    ElemType x = 3;
//    deleteAllElemIsX_p17q3(L, x);
//    ShowList(L);

//    //reverseSeqList 调试
//    reverseSeqList_p17q2(L);
//    ShowList(L);

//    // deleteMinOne 调试
//    ElemType a;
//    if (!deleteMinElem_p17q1(L, a)){
//        printf("The SeqList is empty!");
//    }else{
//        printf("The min value is %d\n", a);
//    }
//    ShowList(L);

    return 0;
}
