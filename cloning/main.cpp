#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX = 1e5+5, LVL = 70;
char s[2][MAX];

int freq[2][2], Q;
// freq[id][0 or 1]

ll sz[LVL][2];

pair<ll,int> a[MAX];

int main() {
	scanf(" %s %s %d", s[0], s[1], &Q);
	for (int id = 0; id < 2; ++id) {
		for (int i = 0; i < (int)strlen(s[id]); ++i) {
			++freq[id][s[id][i]-'0'];
		}
	}
	for (int q = 0; q < Q; ++q) {
		scanf("%lld", &a[q].first);
		a[q].second = q;
	}
	sort(a, a+Q);
	sz[0][0]=sz[0][1]=1;
	ll end = 1;
	for (int lvl = 1; end < a[Q-1].first; ++lvl) {
		for (int id = 0; id < 2; ++id) {
			sz[lvl][id] = sz[lvl-1][0]*freq[id][0]+sz[lvl-1][1]*freq[id][1];
		}
		end += sz[lvl][0];
	}
}