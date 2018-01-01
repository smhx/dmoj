#include <cstdio>
#include <map>
#include <set>
using namespace std;
const int MAXN = 100005;
int N, K;
char moves[MAXN];
map<int, set<int> > aset[2],bset[2];
int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &K);
	scanf(" %s", moves);
	int a, b;
	for (int i = 0; i < N; ++i) {
		int x,y; scanf("%d%d", &x, &y);
		if (!i) a=x+y, b=x-y;
		int A = x+y, B = x-y;
		aset[B&1][A].insert(B);
		bset[A&1][B].insert(A);
	}
	for (int k = 0; k < K; ++k) {
		if (moves[k]=='A' || moves[k]=='D') {
			auto it = bset[a&1][b].find(a);
			if ( (moves[k]=='A' && it == --bset[a&1][b].end() ) || (moves[k]=='D' && it==bset[a&1][b].begin()) ) continue;
			if (moves[k]=='A')++it;
			else --it;
			int newa = *it;
			bset[a&1][b].erase(a);
			aset[b&1][a].erase(b);
			a = newa;
		} else {
			auto it = aset[b&1][a].find(b);
			if ( (moves[k]=='B' && it == --aset[b&1][a].end()) || (moves[k]=='C' && it == aset[b&1][a].begin())) continue;
			
			if (moves[k]=='B') ++it;
			else --it;
			int newb = *it;
			aset[b&1][a].erase(b);
			bset[a&1][b].erase(a);
			b = newb;
		}
	}
	printf("%d %d\n", (a+b)/2, (a-b)/2);
}
