#include <cstdio>
#include <cstdlib>
typedef long long ll;
ll own, friends[2];
int S[2];
int T, N, Q;
void input(ll& x) {
    x = 0;
    char c;
    for (int j = 0; j < Q; ++j) {
        scanf(" %c", &c);
        if (c=='T') x |= (1LL << j);
    }
}
int main() {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d%d", &N, &Q);
        for (int i = 0; i < N; ++i) {
            input(friends[i]);
        }
        input(own);
        for (int i = 0; i < N; ++i) scanf("%d", S+i);
        if (N==1) {
            int a = 0;
            for (int i = 0; i < Q; i++) {
                a += ( (own & (1LL << i) ) == (friends[0] & (1LL << i)) ) ? 1 : 0;
            } 
            printf("Case #%d: %d\n", t, Q-std::abs(S[0]-a));
        } else {
            printf("N==2. own=%lld, f1=%lld, f2=%lld\n", own, friends[0], friends[1]);
            int b[4];
            b[0]=b[1]=b[2]=b[3]=0;
            for (int i = 0; i < Q; i++) {
                ll mine = own & (1LL << i);
                ll one = friends[0] & (1LL << i);
                ll two = friends[1] & (1LL << i);
                if (mine==one) {
                    if ( one==two) {
                        ++b[0];
                    } else {
                        ++b[2];
                    }
                } else {
                    if (mine==two) {
                        ++b[3];
                    } else {
                        ++b[1];
                    }
                }
            }
            for (int i = 0; i < 4; ++i) printf("b[%d]=%d\n", i, b[i]);
            int sum[2];
            sum[0]=S[0]-b[1]-b[3];
            sum[1]=S[1]-b[1]-b[2];
            int max = -1;
            for (int x0 = 0; x0 <= b[0]; ++x0) {
                for (int x1 = 0; x1 <= b[1]; ++x1) {
                    for (int x2 = 0; x2 <= b[2]; ++x2) {
                        for (int x3 = 0; x3 <= b[3]; ++x3) {
                            if (sum[1]==(x0-x1-x2+x3) && sum[0]==(x0-x1+x2-x3) && max < (x0+x1+x2+x3) ) {
                                max = x0+x1+x2+x3;
                                printf("x0=%d, x1=%d, x2=%d, x3=%d\n", x0, x1, x2, x3);
                            }
                        }
                    }
                }
            }
            printf("Case #%d: %d\n", t, max);
        }
    }
}