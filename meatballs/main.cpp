#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
const int MAXN = 1005;
int K, idx; long long N;
double p[2][MAXN];

double pre1[MAXN], pre2[MAXN];

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%lld%d%d", &N, &K, &idx);
	
	if (K==0) {	
		cout << scientific << 1.0 / double(N) << "\n";
	} else if (K==1) {
		cout << scientific << double(2*idx) / double(N*(N+1));
	} else if (K==2) {
		long long denom = 6LL + 1LL*3*(N-2) + 1LL*(N-1)*(N-2)/2LL;
        int num = 1 + idx;
        if (idx==1) num = 3;
        cout << scientific << double(num)/double(denom) << "\n";
	} else {
		p[1][1] = 1.0;
		for (int i = 0; i < MAXN; ++i) p[1][i] = 1.0;
		for (int n = 2; n <= N; ++n) {
			printf("n = %d\n", n);
			for (int i = 0; i <= n; ++i) pre1[i] = pre2[i] = 0.0;

			for (int b = 1; b <= n; ++b) {
				int na = (n+K-b)/n + 1;
				pre1[b] = pre1[b-1]+ double(na)/double(n+K) ;
				pre2[b] = pre2[b-1] + double(na)/double(n+K) ;
			}

			for (int f = 1; f <= n; ++f) {
				p[n&1][f] = pre2[f-1]*p[(n-1)&1][f-1] + (pre1[n] - pre1[f])*p[(n-1)&1][f];
			}
		}
		cout << scientific << p[N&1][idx] << "\n";
	}
}