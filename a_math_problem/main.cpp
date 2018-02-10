/*input
31 41 59
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
	double K, P, X; scanf("%lf%lf%lf", &K, &P, &X);

	// X - KP/M^2 = 0. M^2 = KP/X

	int m = (int)sqrt(K*P/X);

	double v1 = X*m+K*P/m;
	double v2 = X*(m+1)+K*P/(m+1);

	double v = min(v1, v2);
	printf("%.3lf\n", v);
	// printf("%.3lf\n", X*m+K*P/m);
}