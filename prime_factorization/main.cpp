#include <cstdio>
#include <unordered_set>
#include <vector>
using namespace std;

const int SQRT = 4000;

bool prime[SQRT];

vector<int> primes;
int main() {
	freopen("data.txt", "r", stdin);
	for (int i = 0; i < SQRT; ++i) prime[i] = true;
	for (int i = 2; i*i < SQRT; ++i) {
		if (prime[i]) {
			for (int j = i*i; j < SQRT; j += i) {
				prime[j] = false;
			}
		}
	}
	for (int i = 2; i < SQRT; ++i) if (prime[i]) primes.push_back(i);
	int N; 
	scanf("%d", &N);
	while (N--) {
		int M; scanf("%d", &M);
		for (int p : primes) {
			if (p*p > M) break;
			if (M%p==0){
				while (M%p==0) {
					printf("%d ", p);
					M/=p;
				}
			}
		}
		if (M>1) printf("%d\n", M);
		else printf("\n");
	}
}