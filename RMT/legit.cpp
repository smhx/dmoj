#include <cstdio>
#define MAX 100001
int N, M, Q, lag[MAX], line[MAX], fix[MAX], ppl[MAX];

inline void run(int l) {
    ++lag[l];
}

void update(int x) {
    // what should x be?
}

int sum(int x) {
    int s=0;
    for (; x > 0; x -= x&-x) {
        if (lag[line[x]]-fix[x]) {
            update(x);
        }
        s += ppl[x];
    }
    return s;
}

int main() {
    scanf("%d%d%d", &N, &M, &Q);
    for (int i = 1; i <= N; ++i) scanf("%d", line+i);
    for (int i = 1; i <= N; ++i) scanf("%d", ppl+i);
    while (Q--) {
        int q;
        scanf("%d", &q);
		if (q==1) {
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%d", sum(l)-sum(r-1));
		} else {
			int l;
			scanf("%d", &l);
			run(l);
		}
    }
}