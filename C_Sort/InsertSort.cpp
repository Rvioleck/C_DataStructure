//
// Created by Rvioleck on 2021/2/9.
//

#include "InsertSort.h"

void DirectlyInsertSort(SeqList a){
    /// No guard, directly insert sorting.
    int i, j, temp, count = 0;
    for (i = 1; i < a.len; ++i) {
        temp = a.data[i];
        for (j = i - 1; j >= 0; --j) {
            count++;
            if (a.data[j] > temp){
                a.data[j + 1] = a.data[j];
            } else {
                break;
            }
        }
        a.data[j + 1] = temp;
    }
    cout<<"Directly insert sorting:\n\t";
    for (int k = 0; k < a.len; ++k) {
        cout<<a.data[k]<<" ";
    }
    cout<<"Comparison times: "<<count<<endl;
}

void HalfInsertSort(SeqList a){
    /// No guard, half insert sorting
    int i, j, temp, count = 0;
    for (i = 1; i < a.len; ++i) {
        temp = a.data[i];
        int low = 0, high = i - 1;
        while (low <= high){
            int mid = (low + high) / 2;
            if (a.data[mid] <= temp){
                low = mid + 1;
            } else {
                high = mid - 1;
            }
            count++;
        }
        for (j = i - 1; j >= low; --j) {
            a.data[j + 1] = a.data[j];
        }
        a.data[j + 1] = temp;
    }
    cout<<"Half insert sorting:\n\t";
    for (int k = 0; k < a.len; ++k) {
        cout<<a.data[k]<<" ";
    }
    cout<<"Comparison times: "<<count<<endl;

}

void ShellSort(SeqList a){
    int i, j, temp, count = 0;
    for (int d = a.len/2; d >= 1; d /= 2) {
        for (i = d ; i < a.len; i += d) {
            temp = a.data[i];
            for (j = i - d; j >= 0; j -= d) {
                count++; // 记录比较次数
                if (a.data[j] > temp){
                    a.data[j + d] = a.data[j];
                } else {
                    break;
                }
            }
            a.data[j + d] = temp;
        }
    }
    cout<<"Shell sorting:\n\t";
    for (int k = 0; k < a.len; ++k) {
        cout<<a.data[k]<<" ";
    }
    cout<<"Comparison times: "<<count<<endl;

}

int main(){
    SeqList a;
    int data[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
//    int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//    int data[10] = {1, 3, 2, 5, 7, 0, 4, 9, 8, 6};
    CreateSeqList(a, data, 10);
    showSeqList(a);

    DirectlyInsertSort(a);
    HalfInsertSort(a);
    ShellSort(a);

}