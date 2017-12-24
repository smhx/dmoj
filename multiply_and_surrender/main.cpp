/*input
5
2 2 2 2 2
*/
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int N;
    scanf("%d", &N);
    double logsum=0.0;
    while (N--) {
        double a; cin >> a;
        logsum += log2(a);
    }
    int flr = (int)logsum;
    printf("%d\n", flr+1);
}