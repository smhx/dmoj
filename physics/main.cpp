#include <cstdio>
using namespace std;
typedef long long ll;
int N, odd;
ll sum=0;

ll round(double x) {
    // printf("x = %lf\n", x);
    ll X = (ll)x;
    // printf("X = %d\n", X);
	if (x-X < 0.5) return X;
	else if (x-X > 0.5) return X+1;
	else return (X%2==0) ? X : X+1;
}
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		int r; scanf("%d", &r);
		if (r&1) ++odd;
		sum += (ll)r;
	}	
	ll hi = round(double(sum)-(odd ? 0.1 : 0)+ 0.5 * double(N) );
	ll lo = round(double(sum) - 0.5 * double(N)+(odd ? 0.1 : 0) );
	printf("%lld\n%lld\n", lo, hi);
}
