//
// Created by Rvioleck on 2021/1/25.
//

#ifndef C_LINEAR_LIST_KMP_H
#define C_LINEAR_LIST_KMP_H
#include <string.h>
#include <cstdlib>
#include <iostream>

using namespace std;

class kmp {
public:
    void get_next(int next[], string needle){
        int i = 0, j = -1;
        next[0] = -1;
        while(i < needle.length()){
            if (j == -1 || needle[i] == needle[j]){
                i++;
                j++;
                next[i] = j;
            }else{
                j = next[j];
            }
        }
    }

    void get_nextVal(int next[], string needle){
        int i = 0, j = -1;
        while (i < needle.length()){
            if (j == -1 || needle[i] == needle[j]){
                i++;
                j++;
                if (needle[i] != needle[j]){
                    next[i] = j;
                }else
                    next[i] = next[j];
            }else
                j = next[j];
        }
    }

    int strStr(string haystack, string needle) {
        int i = 0, j = 0;
        int n = haystack.length(), m = needle.length();
        int *next = new int[m];
        this->get_next(next, needle);
        this->get_nextVal(next, needle);
        while(i < n && j < m){
            if (j == -1 || haystack[i] == needle[j]){
                i++;
                j++;
            }else{
                j = next[j];
            }
        }
        delete []next;
        if (j >= m){
            return i - m;
        }
        else
            return -1;
    }
};


#endif //C_LINEAR_LIST_KMP_H
