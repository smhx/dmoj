#include <cstdio>
#define MAX 200005
int N, Q;  // 1 <= N, Q <= MAX

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 0; i < N; ++i) {
        int x, y, v;
        scanf("%d%d%d", &x, &y, &v);
    }
}

/*
    Look at all the prefixes.
    You have a TRIE of binary vals.

    Each node is either an endpoint or not.

    You can test if (x, y) matches a painting (a, b)

    if x matches a and y matches b.

    You can test x matches a in 64 max calls, using a trie.

    But let's say you


*/