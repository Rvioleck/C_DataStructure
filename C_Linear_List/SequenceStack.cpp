//
// Created by Rvioleck on 2021/1/23.
//


#include "SequenceStack.h"

bool isValid(char a[]){
    // 查看入栈的I/O序列是否合法
    int i = 0, j = 0, k = 0;
    while (a[i] != '\0'){
        switch(a[i]){
            case 'I': j++; break;
            case 'O': k++;
                if (k>j){
                    printf("序列非法\n");
                    exit(0);
                }
        }
        i++;
    }
    if (j != k){
        printf("序列非法\n");
        return false;
    }else{
        printf("序列合法\n");
        return true;
    }
}

bool bracketBalance_p90q1(char a[]){
    int i = 0;
    char x;
    SqStack S;
    InitStack(S);
    while (a[i] != '\0'){
        switch (a[i]) {
            case '[': Push(S, '['); break;
            case '{': Push(S, '{'); break;
            case '(': Push(S, '('); break;
            case ']':
                Pop(S, x);
                if (x != '[')
                    return false;
                break;
            case ')':
                Pop(S, x);
                if (x != '(')
                    return false;
                break;
            case '}':
                Pop(S, x);
                if (x != '{')
                    return false;
                break;
        }
        i++;
    }
    ShowStack(S);
    return IsEmpty(S);
}

void trainArrange_p90q2(char *train){
    char *p = train, *q = train, c;
    SqStack s;
    InitStack(s);
    while (*p){
        if (*p == 'H'){
            Push(s, *p);
        }else{
            *(q++) = *p;
        }
        p++;
    }
    while (!IsEmpty(s)){
        Pop(s, c);
        *(q++) = c;
    }
}

double p_p90q3(int n, double x){
    struct stack{
        int no;
        double val;
    }st[MaxSize];
    int top = -1, i;
    double f1 = 1, f2 = 2*x;
    for (i = n; i >= 2; i++) {
        st[++top].no = i; // 入栈
    }
    while (top >= 0){
        st[top].val = 2*x*f2 - 2*(st[top].no - 1)*f1;
        f1 = f2;
        f2 = st[top].val;
        top--;
    }
    if (n == 0)
        return f1;
    return f2;
}

int main(){

    /// trainArrange 调试
    char train[] = {'H', 'S', 'S', 'S', 'S', 'H', 'H', 'H', '\0'};
    trainArrange_p90q2(train);
    for (int i = 0; train[i] != '\0'; ++i) {
        printf("%c  ", train[i]);
    }

    /// bracketBalance 调试
//    char a[] = {'[', ']', '{', '(', ')', '{', '}', '}'};
//    printf("%d", bracketBalance_p90q1(a));

    /// isValid 调试
//    char a[8]={'I', 'I', 'I', 'O', 'O', 'O', 'I', 'O'};
//    printf("%d", isValid(a));
}