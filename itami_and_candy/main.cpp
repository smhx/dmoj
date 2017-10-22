#include <cstdio>
#include <vector>
#define MAXN 148734
using namespace std;
int N, X, cnt=0;
vector<int> primes;
int main() {
    scanf("%d%d", &N, &X);
    for (int x = 2; x <= MAXN; ++x) {
        bool prime = true;
        for (int f = 2; f*f <= x && prime; ++f) 
            if (x%f==0) prime = false;
        if (prime) primes.push_back(x);
    }

    for (int p : primes) {
        if (p > N) break;
        int rem = N-p;
        cnt += (rem / X)*2 + ( (rem%X==0) ? 1 : 2 );
    }
    printf("%d\n", cnt);
}