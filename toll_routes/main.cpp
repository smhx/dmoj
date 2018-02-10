#include <cstdio>
#include <vector>
#include <algorithm>
typedef std::pair<int,int> ii;
typedef long long ll;
typedef std::pair<ll, ll> pll;
const int MAXN = 3005;
const ll INF = 1000000000000LL;

ll ans[MAXN];
bool reachable[MAXN];

struct static_hull_optimizer {
	typedef std::pair<ll,int> query; // (x, id)
	bool bad(pll l1, pll l2, pll l3) {
		return (l3.second-l1.second)*(l1.first-l2.first) < (l2.second-l1.second)*(l1.first-l3.first);
	}
	// add with non increasing slope
	void addLine(ll m, ll b){
		pll toadd = {m,b};
		while (l.size() >= 2 && bad(l[l.size()-2], l.back(), toadd)) l.pop_back();
		l.push_back(toadd);
	}
	void addQuery(ll x, int id)  {q.push_back({x,id});}
	ll eval(ll x, int idx) {return l[idx].first*x+l[idx].second;}
	void answerQueries() {
		for (int i = 0; i < q.size(); ++i) reachable[q[i].second] = !l.empty();
		if (l.empty()) return;
		sort(q.begin(), q.end());
		int idx=0;
		for (int i = 0; i < q.size(); ++i) {
			if (idx >= l.size()) idx = l.size()-1;
			while (idx < l.size()-1 && eval(q[i].first, idx+1) < eval(q[i].first, idx)) ++idx;
			ans[q[i].second] = eval(q[i].first, idx); 
		}
	}
	std::vector<pll> l;
	std::vector<query> q;
};

int N, M, D, tidx[MAXN];
std::vector<ii> adj[MAXN];
std::vector<int> topo;

static_hull_optimizer hull[MAXN];

bool visit[MAXN];
void dfs(int u) {
	visit[u]=true;
	for (ii e : adj[u]) if (!visit[e.second]) dfs(e.second);
	topo.push_back(u);
}

ll mind[MAXN][MAXN]; // mind[u][n]
void computeHull() {
	for (int i = 0; i < N; ++i)
		for (int n = 0; n < N; ++n) mind[i][n] = INF;
	mind[tidx[1]][0] = 0;
	for (int n = 1; n < N; ++n) {
		for (int i = N-1; i >= 0; --i) {
			int u = topo[i];
			for (ii e : adj[u]) {
				if (tidx[e.second] <= i) {printf("ERROR\n");}
				mind[i][n] = std::min(mind[i][n], e.first+mind[tidx[e.second]][n-1]);
			}
		}
	}
	for (int i = 0; i < N; ++i) 
		for (int n = N-1; n >= 0; --n) 
			if (mind[i][n] != INF) hull[i].addLine(1LL*n, mind[i][n]);
}

void solve() {
	ll sumC=0;
	for (int i = 1; i <= D; ++i) {
		int c, d; scanf("%d%d", &c, &d);
		sumC += 1LL*c;
		hull[tidx[d]].addQuery(sumC, i);
	}
	for (int i = 0; i < N; ++i) hull[i].answerQueries();
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d%d", &N, &M, &D);
	for (int i=0,u,v,t; i < M; ++i) {
		scanf("%d%d%d", &u, &v, &t);
		adj[v].push_back({t,u});
	}
	for (int u = 1; u <= N; ++u) if (!visit[u]) dfs(u);
	std::reverse(topo.begin(), topo.end());
	for (int i = 0; i < topo.size(); ++i) tidx[topo[i]]=i;
	computeHull();
	solve();
	for (int i = 1; i <= D; ++i) {
		if (!reachable[i]) printf("Cannot Deliver\n");
		else printf("%lld\n", ans[i]);
	}
}