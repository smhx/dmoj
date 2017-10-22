// #include <cstdio>
#define BIGN 2005
#define SMALLN 101
#define INF (1LL<<62)-1
typedef long long ll;

int N, A, B, Y[BIGN]; 
ll sum[BIGN], beauty=INF;
bool dp[SMALLN][SMALLN];
int groupcnt[BIGN];

inline bool inside(ll a, ll b) { // a inside b
    return (a|b)==b;
}

bool doable(ll beau) {
    // printf("IN DOABLE %lld\n", beau);
    if (A!=1) {
        for (int i = 0; i < SMALLN; ++i) 
            for (int j = 0; j < SMALLN; ++j) 
                dp[i][j] = 0;
            
        for (int l = 1; l <= N; ++l) {
            for (int g = 1; g <= l; ++g) {
                // printf("Looking at (l=%d, g=%d)\n", l, g);
                if (g==1) {
                    dp[l][g] = inside(sum[l], beau);
                    // printf("g==1. Returnign %d\n", dp[l][g]);
                } else {
                    for (int lo = g; lo <= l; ++lo) {
                        if (dp[lo-1][g-1] && inside(sum[l]-sum[lo-1], beau)) {
                            dp[l][g] = 1; break;
                        }
                    }
                    // printf("returning %d\n", dp[l][g]);
                }
            }
        }
        for (int g = A; g <= B; ++g) {
            if (dp[N][g]) {return true;}
        }
        // printf("RETURNING FALSE\n");
        return false;
    } else {
        // printf("A==1\n");
        // have to be more efficient here...
        // cuz N=2000 here and N^3 wont work...
        // but N^2 can work...............::::
        #define XXX 10000000
        for (int i = 0; i < BIGN; ++i) groupcnt[i]=XXX;
        groupcnt[0] = 0;
        for (int l = 1; l <= N; ++l) {
            // printf("l==%d\n", l);
            // printf("groupcnt[%d]=%d\n", l, groupcnt[l]);
            // first check alone
            if (1+groupcnt[l-1] <= B && inside(Y[l], beau)) {
                // printf("self: setting to %d\n", 1+groupcnt[l-1]);
                groupcnt[l] = 1+groupcnt[l-1];
            }
            for (int lo = 1; lo < l; ++lo) {
                if (groupcnt[lo-1] < B && groupcnt[lo-1]+1 < groupcnt[l] && inside(sum[l]-sum[lo-1], beau)) {
                    // printf("  setting groupcnt[%d] to %d\n", l, groupcnt[lo]+1);
                    groupcnt[l] = groupcnt[lo-1]+1;
                }
            }
        }
        // printf("returning %d\n", groupcnt[N] <= B);
        return groupcnt[N] <= B;
    }
}

int main() {
   
    // freopen("data.txt","r", stdin);
    scanf("%d%d%d", &N, &A, &B);
    for (int i = 1; i <= N; ++i) scanf("%d", Y+i);
    sum[0] = 0;
    for (int i = 1; i <= N; ++i) sum[i] = Y[i]+sum[i-1];
    // printf("doable(13)=%d\n", doable(13));
    for (int i = 61; i >= 0; --i) 
        if (doable(beauty-(1LL << i))) beauty -= (1LL << i);
    printf("%lld\n", beauty);
}