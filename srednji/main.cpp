/*input
6 3
1 2 4 5 6 3
*/
#include <cstdio>
#include <algorithm>
#define MAXN 100005
typedef long long ll;
int N, k, B, A[MAXN], l[MAXN], r[MAXN], freql[2*MAXN], freqr[2*MAXN];
ll cnt = 0;
int main() {
    
    scanf("%d%d", &N, &B);
    for (int i = 1; i <= N; ++i) {
    	scanf("%d", A+i);
    	if (A[i]==B) k=i;
    }

    for (int i = k+1; i <= N; ++i) {
    	if (A[i] > B) l[i]=l[i-1], r[i]=1+r[i-1];
    	else l[i]=l[i-1]+1, r[i]=r[i-1];

    	++freqr[r[i]-l[i]+N];
    }

    for (int i = k-1; i; --i) {
    	if (A[i] > B) l[i]=l[i+1], r[i]=1+r[i+1];
    	else l[i]=1+l[i+1], r[i]=r[i+1];

    	++freql[r[i]-l[i]+N];
    }

    ++freqr[N], ++freql[N];

    for (int i = 0; i < 2*N; ++i) 
    	cnt += (ll)freql[i] * (ll)freqr[2*N-i];
    

    printf("%lld\n", cnt);

}