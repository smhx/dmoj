/*input
3 100 120
*/
#include <cstdio>

double vin, rf, rg;

int main() {
	scanf("%lf%lf%lf", &vin, &rf, &rg);

	printf("%lf\n", vin * (1.0+rf/rg));
}