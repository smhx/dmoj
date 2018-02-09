#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX = 1e5+5, LVL = 100;
char s[2][MAX];

int len[2], Q;

ll sz[LVL][2], maxa=0, a[MAX];

vector<ll> breaks, endpnts[2][LVL];

void precomp() {
	sz[0][0]=sz[0][1]=1;
	ll end = 1;
	endpnts[0][0].push_back(1);
	endpnts[1][0].push_back(1);

	breaks.push_back(1);

	for (int lvl = 1; end < maxa; ++lvl) {
		for (int id = 0; id < 2; ++id) {
			endpnts[id][lvl].push_back(0);
			for (int i = 0; i < len[id]; ++i) {
				sz[lvl][id] += sz[lvl-1][s[id][i]-'0'];
				endpnts[id][lvl].push_back(endpnts[id][lvl].back() + sz[lvl-1][s[id][i]-'0']);
			}
		}
		end += sz[lvl][0];
		breaks.push_back(end);
	}
}

int solve(ll x) {
	int lvl = lower_bound(breaks.begin(), breaks.end(), x) - breaks.begin();
	int state = 0;
	x = x - breaks[lvl-1];
	while (lvl > 0) {
		int i = lower_bound(endpnts[state][lvl].begin(), endpnts[state][lvl].end(), x) - endpnts[state][lvl].begin();
		x -= endpnts[state][lvl][i-1];
		state = s[state][i-1]-'0';
		--lvl;
	}
	return state;
}	

int main() {
	// freopen("data.txt", "r", stdin);
	scanf(" %s %s %d", s[0], s[1], &Q);
	len[0] = strlen(s[0]); len[1] = strlen(s[1]);
	for (int q = 0; q < Q; ++q) {
		scanf("%lld", &a[q]);
		maxa = max(maxa, a[q]);
	}
	precomp();
	for (int q = 0; q < Q; ++q) {
		int state = solve(a[q]);
		printf("%d\n", state);
	}
}