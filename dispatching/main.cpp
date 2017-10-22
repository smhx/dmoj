#include <cstdio>
#define MAXN 100005
typedef long long ll;

int N, M, B[MAXN], C[MAXN], L[MAXN], root;

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; ++i ) {
        scanf("%d%d%d", B+i, C+i, L+i);
        if (B[i]==0) root = i;
    }

}

/*
    Node u has children v1, v2, ..., vk

    f(u):
    case 1: Dispatch manager f(u) = u.L
    case 2: Don't dispatch manager
        Don't dispatch subset w.
        so f(u) = (sum over w g(w) + |v|-|w|) * u.L

    
    g(u) is the number of children you can
    
    

*/