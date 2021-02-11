//
// Created by Rvioleck on 2021/2/9.
//

#include "SwapSort.h"

void BubbleSort(SeqList a){
    int count = 0;
    for (int i = 0; i < a.len - 1; ++i) {
        for (int j = a.len - 1; j > i; --j) {
            count++;
            if (a.data[j] < a.data[j - 1]){
                int temp = a.data[j];
                a.data[j] = a.data[j - 1];
                a.data[j - 1] = temp;
            }
        }
    }
    cout<<"Bubble sorting:\n\t";
    for (int k = 0; k < a.len; ++k) {
        cout<<a.data[k]<<" ";
    }
    cout<<"Comparison times: "<<count<<endl;

}

int Partition(SeqList &a, int low, int high, int &count){
    int pivot = a.data[low];
    while (low < high) {
        while (low < high && a.data[high] > pivot) {
            count++;
            high--;
        }
        a.data[low] = a.data[high];
        while (low < high && a.data[low] < pivot){
            count++;
            low++;
        }
        a.data[high] = a.data[low];
    }
    a.data[low] = pivot;
    return low;
}

void QuickSort(SeqList &a, int low, int high, int &count){
    int pivotPos = Partition(a, low, high, count);
    if (low < high){
        QuickSort(a, low, pivotPos - 1, count);
        QuickSort(a, pivotPos + 1, high, count);
    }
}

int main(){
    SeqList a;
//    int data[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
//    int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int data[10] = {1, 3, 2, 5, 7, 0, 4, 9, 8, 6};
    CreateSeqList(a, data, 10);
    showSeqList(a);
    BubbleSort(a);

    int count = 0;
    cout<<"Quick sorting:\n\t";
    QuickSort(a, 0, 9, count);
    for (int k = 0; k < a.len; ++k) {
        cout<<a.data[k]<<" ";
    }
    cout<<"Comparison times: "<<count<<endl;
}