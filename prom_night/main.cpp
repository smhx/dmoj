#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_set>
#define MAXN 100

using namespace std;

int N, M, csgirls=0;


bool fstar[MAXN], bstar[MAXN];

typedef bitset<MAXN> gs;
unordered_set<gs> f, tmp;
vector<int> adj[MAXN];

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &M);


	for (int i = 0, t, g; i < N; ++i) {
		scanf("%d", &t);
		if (i==0) csgirls += t;
		while (t--) {
			scanf("%d", &g);
			if (i==0) fstar[g] = true;
			if (fstar[g]) {
				bstar[i] = true;
				adj[i].push_back(g-1);
			}
		}
	}

	f.insert(gs());

	for (int b = 1; b < N; ++b) {
		if (!bstar[b]) continue;
		for (auto set : f) {
			for (int g : adj[b]) {
				if (!set[g]) {
					gs nset = set;
					nset[g] = 1;
					tmp.insert(nset);
				} 
			}
		} 
		
		if (!tmp.empty()) {
			f = tmp;
			tmp.clear();
		}
	}

	int lonely = csgirls;
	for (auto set : f) 
		lonely = min(lonely, csgirls-(int)set.count());
	printf("%d\n", lonely);
}