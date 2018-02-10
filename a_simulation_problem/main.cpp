/*input
10
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, lo;

bool isint(double x) {
	double floor = double(int(x));
	return x-floor < 1e-6;
}

int main() {
	ll N;
	scanf("%lld\n", &N);
	double l = 0.5*(double(2*N-1)-sqrt(2*N*N-2*N+1) );

	if (isint(l)) lo = int(l);
	else lo = (int)l+1;

	printf("%lld\n", min(lo, N));
}