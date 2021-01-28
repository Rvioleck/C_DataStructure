//
// Created by Rvioleck on 2021/1/25.
//

#include "kmp.h"

int main(){
    string a = "hello";
    string b = "ll";
    kmp obj;
    printf("%d", obj.strStr(a, b));
}