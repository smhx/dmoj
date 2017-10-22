#include <cstdio>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

int A[500001], N, t; long long inv=0;

inline int sum(int t) {
    int s = 0;
    for (;t;t-=t&-t) s+= A[t];
    return s;
}

inline void update(int t) {
    for (;t<=N;t+=t&-t) ++A[t];
}

int main() {
    scan(N);
    for (int i = 0; i < N; i++) {
        scan(t);
        int less = sum(t);
        inv += less < i-less ? less : i-less;
        update(t);
    }
    printf("%lld\n", inv);
    return 0;
}