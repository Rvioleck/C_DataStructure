#include <cstdlib>
#include <cstring>
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

void reverse_p17q8(SeqList &L, int x1, int x2){
    // 交换顺序表L中前x1个元素和x1到x2个元素之间的顺序
    reverse(L, 0, L.length - 1);
    reverse(L, 0, x2 - 1);
    reverse(L, x2, x1 + x2 - 1);
}

bool findElemOfX_p17q9(SeqList &L, int x){
    int low = 0, high = L.length - 1;
    int mid;
    while (low < high - 1){
        mid = (low + high)/2;
        if (L.data[mid] < x){
            low = mid;
        }else if (L.data[mid] > x){
            high = mid;
        }else{
            int temp = L.data[mid];
            L.data[mid] = L.data[mid + 1];
            L.data[mid + 1] = temp;
            return true;
        }
    }
    for (int i = L.length - 1; i >= high; --i) {
        L.data[i+1] = L.data[i];
    }
    L.data[high] = x;
    L.length++;
    return false;
}

void moveAllLeftP_p17q10(SeqList &L, int x){
    reverse(L, 0, L.length - 1);
    reverse(L, 0, L.length - 1 - x);
    reverse(L, L.length - x, L.length - 1);
}

int findMidOfTwoSeqList_p17q11(SeqList &L1, SeqList &L2){
    /// 找到等长顺序表L1和L2合并后的中位数，坐标为⌈L/2⌉，L = L1+L2
    // 时间复杂度O(logn)，空间复杂度O(1)
    int h1 = 0, t1 = L1.length - 1, h2 = 0, t2 = L2.length - 1; // 分别是数组L1和L2的头和尾的下标
    int m1, m2;   // 分别是数组L1和数组L2的中位数下标
    while (h1 != t1 || h2 != t2){
        m1 = (h1+t1)/2;
        m2 = (h2+t2)/2;
        if (L1.data[m1] == L2.data[m2]){
            return L1.data[m1];
        }
        else if (L1.data[m1] < L2.data[m2]){ // L1的中位数小于L2的中位数
            if ((h1+t1)%2){ // 若元素个数为奇数
                h1 = m1;    // 删除L1中间点以前的部分
                t2 = m2;    // 删除L2中间点以后的部分
            }
            else{           // 若元素个数为偶数
                h1 = m1 + 1;// 删除L1中间点(包括)以前的部分
                t2 = m2;    // 删除L2中间点(不包括)以后的部分
            }
        }else{
            if ((h1+t1)%2){
                h2 = m2;
                t1 = m1;
            } else{
                h2 = m2 + 1;
                t1 = m1;
            }
        }
    }
    return L1.data[m1] < L2.data[m2] ? L1.data[m1] : L2.data[m2];

    // 时间复杂度为O(n)，空间复杂度为O(1)
//    int len = L1.length + L2.length;
//    int mid = (len)%2 ? len/2 + 1 : len/2;
//    int i = 0, j = 0;
//    while (mid--){
//        if (L1.data[i] <= L2.data[j]){
//            i++;  // 因为数组等长，所以不用考虑溢出的情况
//        }else{
//            j++;
//        }
//    }
//    if (L1.data[i-1] >= L2.data[j-1]){
//        return L1.data[i-1];
//    }else
//        return L2.data[j-1];
}

int findMainElem_p17q12(SeqList &L){
    if (L.length == 0){
        return -1;
    }
    int c = L.data[0], num = 1;
    for (int i = 1; i < L.length; ++i) {
        if (L.data[i] == c){
            num++;
        }else{
            if (num > 0){
                num--;
            }else{
                num = 1;
                c = L.data[i];
            }
        }
    }
    if (num > 0)/*{
        num = 0;
        for (int i = 0; i < L.length; ++i) {
            if (L.data[i] == c)
                num++;
        }
    }
    if (num > L.length / 2) */return c;
    else return -1;
}

int findMinNumNotInSeqList_p17q13(SeqList &L){
    int n = L.length, i;
    ElemType *a = (ElemType*)malloc(sizeof(ElemType)*n);
    memset(a, 0, sizeof(ElemType) * n);
    for (i = 0; i < n; ++i) {
        if (L.data[i] > 0 && L.data[i] <= n){
            a[L.data[i] - 1] = 1;
        }
    }
    for (i = 0; i < n; ++i) {
        if (a[i] != 1){
            break;   // 注意边界条件，当i = n时，返回的是n+1
        }
    }
    return i+1;
}

bool isMin(int a, int b, int c){
    if (a <= b && a <= c){
        return true;
    }
    return false;
}

int minValueOfThreeGroups_p17q14(SeqList &L1, SeqList &L2, SeqList &L3){
    int i = 0, j = 0, k = 0;
    int min = 0x7fffffff;
    while (i < L1.length && j < L2.length && k < L3.length){
        int distance = abs(L1.data[i] - L2.data[j]) + abs(L2.data[j] - L3.data[k]) + abs(L3.data[k] - L1.data[i]);
        if (distance < min){
            min = distance;
        }
        if (isMin(L1.data[i], L2.data[j], L3.data[k])){
            i++;
        } else if (isMin(L2.data[j], L1.data[i], L3.data[k])){
            j++;
        } else{
            k++;
        }
    }
    return min;
}

int main() {
    SeqList L1;
    InitList(L1);
    ListInsert(L1, 1, 3);
    ListInsert(L1, 1, 2);
    ListInsert(L1, 1, 1);

    SeqList L2;
    InitList(L2);
    ListInsert(L2, 1, 6);
    ListInsert(L2, 1, 5);
    ListInsert(L2, 1, 4);
    SeqList L3;
    InitList(L3);
    ListInsert(L3, 1, 9);
    ListInsert(L3, 1, 8);
    ListInsert(L3, 1, 7);
//    ShowList(L1);

    /// minValueOfThreeGroups 调试
//    printf("%d", minValueOfThreeGroups_p17q14(L1, L2, L3));

    /// findminNumNotInSeqList 调试
//    printf("%d", findMinNumNotInSeqList_p17q13(L1));

    /// findMainElem 调试
//    printf("%d", findMainElem_p17q12(L1));

    /// findMidOfTwoSeqList 调试
//    SeqList L2;
//    InitList(L2);
//    ListInsert(L2, 1, 10);
//    ListInsert(L2, 1, 8);
//    ListInsert(L2, 1, 6);
//    ListInsert(L2, 1, 4);
//    ListInsert(L2, 1, 2);
//    ShowList(L2);
//    printf("%d", findMidOfTwoSeqList_p17q11(L1, L2));

    /// findElemOfX 调试
//    if (findElemOfX_p17q9(L1, 3)){
//        printf("find it!\n");
//    }else{
//        printf("doesn't find it!\n");
//    }
//    ShowList(L1);

    /// reverse 调试，x1和x2分别是两个顺序表的大小
//    reverse_p17q8(L1, 2, 5);
//    ShowList(L1);

    /// mergeOrderlyTwoSeqListToOne调试
//    SeqList L2;
//    InitList(L2);
//    ListInsert(L2, 1, 6);
//    ListInsert(L2, 1, 4);
//    ListInsert(L2, 1, 2);
//    ShowList(L2);
//    SeqList L3 = mergeOrderlyTwoSeqListToOne_p17q7(L1, L2);
//    ShowList(L3);

    /// deleteRepeatedElem 调试
//    deleteRepeatedElem(L);
//    ShowList(L);

    /// deleteAllElemFromSToT 调试
//    if (!deleteAllElemFromSToT_p17q4(L, 2, 5)){
//        printf("The SeqList is empty, or the input numbers is valid!");
//    }else{
//        ShowList(L);
//    }

    /// deleteAllElemBetweenSAndT 调试
//    if (!deleteAllElemBetweenSAndT_p17q3(L, 2, 5)){
//        printf("The SeqList is empty, or the input numbers is valid!")
//    }else{
//        ShowList(L);
//    }

    ///deleteAllElemIsX 调试
//    ElemType x = 3;
//    deleteAllElemIsX_p17q3(L, x);
//    ShowList(L);

    ///reverseSeqList 调试
//    reverseSeqList_p17q2(L);
//    ShowList(L);

    /// deleteMinOne 调试
//    ElemType a;
//    if (!deleteMinElem_p17q1(L, a)){
//        printf("The SeqList is empty!");
//    }else{
//        printf("The min value is %d\n", a);
//    }
//    ShowList(L);

    return 0;
}
