#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int cmpfunc (const void * a, const void * b){return ( *(int*)b - *(int*)a );}
int N, c[6]; char s[10];
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf(" %s", s);
        if (strcmp(s, "red")==0) ++c[0];
        else if (strcmp(s, "orange")==0) ++c[1];
        else if (strcmp(s, "yellow")==0) ++c[2];
        else if (strcmp(s, "green")==0) ++c[3];
        else if (strcmp(s, "blue")==0) ++c[4];
        else ++c[5];
    }
    qsort(c, 6, sizeof(int), cmpfunc);
    int leftOver = c[0]-1;
    for (int i = 1; i < 6; ++i) {
        if (leftOver > c[i]) leftOver -= c[i];
        else {
            leftOver = 0;
            break;
        }
    }
    printf("%d\n", N-leftOver);
}