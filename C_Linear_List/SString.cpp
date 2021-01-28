//
// Created by Rvioleck on 2021/1/25.
//

#include "SString.h"

int main(){
    char a[] = {'n', 'o', 't', 'y', 'o', 'u', 'r', 'k', 'e', 'i', '\0'};
    SString s, s2;
    InitString(s);
    InitString(s2);
    ShowString(s);

    StrAssign(s, a);
    ShowString(s);

    StrEmpty(s2) ? printf("Empty!\n") : printf("Not empty!\n");
    StrCopy(s2, s);
    ShowString(s2);

    int x = StrCompare(s, s2);
    if (x > 0){
        printf("The former is larger");
    }else if (x == 0){
        printf("The Strings equal");
    }else{
        printf("The former is smaller");
    }

    s = concat(s, s2);
    ShowString(s);

    s2 = SubString(s, 5, 6);
    ShowString(s2);

    printf("%d, %d", Index(s, s2), Index_KMP(s, s2));

}