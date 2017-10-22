#include <cstdio>
#include <algorithm>
#define MAXN 3000005
#define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 16384, stdin)] = 0, *_pbuf++))
char _buf[16385], *_pbuf = _buf;

int read() {
    int c, o = 0;
    while ((c = getchar()) < '0');
    do o = o*10 + c - '0';
    while ((c = getchar()) >= '0');
    return o;
}

using namespace std;
typedef long long ll;
int N, K, A[MAXN], lo[MAXN], hi[MAXN];
ll cnt = 0;
int main() {
    // freopen("data.txt", "r", stdin);
    N = read();
    K = read();
    for (int i = 0; i < N; ++i) A[i] = read();

    int i = 0, j = 0;
    while (i < N) {
        for (int M = hi[i], m = lo[i]; M-m <= K && j < N;) {
            ++j;
            M = max(M, A[j]);
            m = min(m, A[j]);
        }

        if (j < N) {
            hi[j] = lo[j] = A[j];
            for (int k = j-1; k >= i; --k) {
                hi[k] = max(hi[k+1], A[k]);
                lo[k] = min(lo[k+1], A[k]);
            }
    
            int k;
            for (k = i; k < j && hi[k]-lo[k] > K; ++k);
            cnt += ( (ll(k-i)*ll(k-i+1) )>>1) + ll(j-k)*ll(k-i);
            i=k;
        } else {
            cnt += ll(N-i)*ll(N-i+1)>>1;
            i = N;
        }
        
    }
    
    printf("%lld\n", cnt);
    
}