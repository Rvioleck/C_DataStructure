//
// Created by Rvioleck on 2021/2/6.
//

#include "SequenceSearch.h"

int SeqSearch(SSTable ST, ElemType key){
    ST.elem[0] = key;
    int i;
    for (i = ST.TableLen; ST.elem[i] != key; --i);
    return i;
}