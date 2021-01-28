//
// Created by Rvioleck on 2021/1/25.
//

#ifndef C_LINEAR_LIST_SSTRING_H
#define C_LINEAR_LIST_SSTRING_H

#include <cstdio>
#include <cstring>
#include <cstdlib>

#define MAXLEN 15

typedef struct{
    // 定长顺序存储表示
    char ch[MAXLEN]; // 从1~MAXLEN-1
    int length;
}SString;

void InitString(SString &s){
    s.length = 0;
}


bool StrAssign(SString &s, char chars[]){
    int len = strlen(chars);
    if (len > MAXLEN - 1){
        return false;
    }
    s.length = len;
    for (int i = 1; i <= s.length; ++i) {
        *(s.ch + i) = *(chars + i - 1);
    }
    return true;
}

void StrCopy(SString &s, SString t){
    s.length = t.length;
    for (int i = 1; i <= t.length; ++i) {
        s.ch[i] = t.ch[i];
    }
}

bool StrEmpty(SString s){
    return s.length == 0;
}

int StrCompare(SString s, SString t){
    for (int i = 1; i <= s.length && i<=t.length; ++i) {
        if (s.ch[i] != t.ch[i])
            return s.ch[i] - t.ch[i];
    }
    return s.length - t.length;
}

int StrLength(SString s){
    return s.length;
}

SString concat(SString s1, SString s2){
    SString s;
    InitString(s);
    int len = s1.length + s2.length;
    if (len > MAXLEN - 1){
        len = MAXLEN - 1;
    }
    s.length = len;
    for (int i = 1; i <= s1.length ; ++i) {
        s.ch[i] = s1.ch[i];
    }
    for (int i = s1.length + 1; i <= s.length; ++i) {
        s.ch[i] = s2.ch[i - s1.length];
    }
    return s;
}

SString SubString(SString s, int pos, int len){
    SString res;
    InitString(res);
    for (int i = pos; i < pos + len && i < MAXLEN; ++i) {
        res.ch[i - pos + 1] = s.ch[i];
        res.length++;
    }
    return res;
}

int Index(SString s, SString t){
    SString sub;
    InitString(sub);
    for (int i = 1; i <= s.length - t.length + 1; ++i) {
        sub = SubString(s, i, t.length);
        if (StrCompare(sub, t) != 0)
            i++;
        else
            return i;
    }
    return 0;
}

void get_next(SString t, int next[]){
    int i = 1, j = 0;
    next[1] = 0;
    while (i < t.length){
        if (j == 0 || t.ch[i] == t.ch[j]){
            i++;
            j++;
            next[i] = j;
        }else{
            j = next[j];
        }
    }
}

void get_nextval(SString t, int next[]){
    int i = 1, j = 0;
    while (i <= t.length){
        if (j == 0 || t.ch[i] == t.ch[j]){
            i++;
            j++;
            if (t.ch[i] != t.ch[j])
                next[i] = j;
            else
                next[i] = next[j];
        }else
            j = next[j];
    }
}

int Index_KMP(SString s, SString t){
    int i = 1, j = 1;
    int next[t.length + 1];
    get_next(t, next);
    get_nextval(t, next);
    while (i <= s.length && j <= t.length){
        if (j == 0 || s.ch[i] == t.ch[j]){
            i++;
            j++;
        }else{
            j = next[j];
        }
    }
    if (j > t.length)
        return i-t.length;
    return 0;
}


void ShowString(SString s){
    printf("String is: \"");
    for (int i = 1; i <= s.length; ++i) {
        printf("%c", s.ch[i]);
    }
    printf("\", the length is %d\n", StrLength(s));
}

void ClearString(SString &s){
    s.length = 0;
}

void DestroyString(SString &s){
    free(s.ch);
    s.length = 0;
}


typedef struct{
    // 堆分配存储表示
    char *ch;
    int length;
}HString;


#endif //C_LINEAR_LIST_SSTRING_H
