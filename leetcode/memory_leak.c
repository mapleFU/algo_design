//
// Created by 付旭炜 on 2019/3/19.
//
#include <stdlib.h>
#include <stdio.h>

int **m_value_no_return(int size) {
    int **darr = (int**) malloc(sizeof(int**) * size);
    for (int i = 0; i < size; ++i) {
        darr[i] = malloc(sizeof(int*));
    }
    return darr;
}

int main() {
    // memory leak
    int *p = (int *)malloc(sizeof(int));
    *p = 32;
    printf("%d\n", *p);
    free(p);

    // chkeck size
    int a[10];
//    a[10] = 123;

    // different types
    a[5] = 'a';

    int ** mlc = m_value_no_return(5);
//    free(mlc);

    return 0;
}