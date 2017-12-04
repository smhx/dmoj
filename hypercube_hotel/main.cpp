#include <cstdio>
#include <cstring>
typedef long long ll;
const int MAXN=10, SIZE = 2000000;
int N, sz=1, a[MAXN];
ll x[SIZE], sum[2][SIZE];
int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i){
		scanf("%d", a+i);
		sz*=a[i];
	}
	for (int i = 0; i < sz; ++i) {
		scanf("%lld", x+i);
		sum[(N+1)&1][i]=x[i];
	}
	int d = 1, dimSize = 1;
	for (int dim = N; dim; --dim) {
		dimSize *= a[dim];
		memset(sum[dim&1], 0, sizeof sum[dim&1]);
		for (int n = 0; n < sz; ++n) {
			sum[dim&1][n] += sum[(dim&1)^1][n];
			if (n-d>=0 && (n-d)/dimSize==n/dimSize) sum[dim&1][n] += sum[(dim&1)^1][n-d];
			if (n+d < sz && (n+d)/dimSize==n/dimSize) sum[dim&1][n] += sum[(dim&1)^1][n+d];
		}
		d *= a[dim];
	}
	for (int n = 0; n < sz; ++n) printf("%lld\n", sum[1][n] - x[n]);
}