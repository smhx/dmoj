/*input
2
5
13
*/
#include <iostream>
#include <vector>
// #define ull unsigned long long
// typedef unsigned long long ull;
using namespace std;

size_t x;
int N, n;

int main() {
    scanf("%d", &N);
    while (N--) {
    	x = 1;
    	scanf("%d", &n);
    	for (size_t i = 1; i <= (size_t)n; ++i) {

    	    x *= i;
    	    // cout << "x==" << x << endl;
    	    x %= (1LL << 32);
    	}
    	cout << x << endl;
    }
    
}