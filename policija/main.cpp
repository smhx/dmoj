#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 300005, LOG = 23;

int N, M;
vector<int> adj[MAXN];

int dfst=0, rootdeg=0, disc[MAXN], low[MAXN], p[MAXN];
void tarjan(int u) {
	low[u]=disc[u]=++dfst;
	for (int v : adj[u]) {
		if (!disc[v]) {
			if (u==1) ++rootdeg;
			p[v]=u;
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (v!=p[u]) {
			low[u] = min(low[u], disc[v]);
		}
	}
}

int btsize=1, btnode[MAXN];
vector<int> btree[MAXN];

void buildBT(int u, int block) {
	btnode[u] = block;
	for (int v : adj[u]) {
		if (!btnode[v]) {
			if (disc[u] < low[v]) {
				++btsize;
				btree[block].push_back(btsize);
				btree[btsize].push_back(block);
				buildBT(v, btsize);
			} else {
				buildBT(v, block);
			}
		}
	}
}

vector<int> bctree[MAXN];
int bctsize=1, artnode[MAXN], blocknode[MAXN];
void buildBCT(int u, int block) {
	blocknode[u]=block;
	for (int v : adj[u]) {
		if (!blocknode[v]) {
			if ( (u!= 1 && disc[u] <= low[v]) || (u==1 && rootdeg > 1) ) {
				if (!artnode[u]) {
					artnode[u] = ++bctsize;
					bctree[block].push_back(bctsize);
					bctree[bctsize].push_back(block);
				} 
				++bctsize;
				bctree[artnode[u]].push_back(bctsize);
				bctree[bctsize].push_back(artnode[u]);
				buildBCT(v, bctsize);
			} else {
				buildBCT(v, block);
			}
		}
	}
}

int btp[MAXN], bth[MAXN], bctp[MAXN], bcth[MAXN];

void dfs(int u, int p[], int h[], const vector<int> tree[]) {
	for (int v : tree[u]) {
		if (v!=p[u]) {
			p[v] = u;
			h[v] = 1+h[u];
			dfs(v, p, h, tree);
		}
	}
}

int btst[MAXN][LOG], bctst[MAXN][LOG];
void buildLCA(int p[], int (&st)[MAXN][LOG], int sz) {
	for (int u = 1; u <= sz; ++u) st[u][0] = p[u];
	for (int k = 1; k < LOG; ++k) {
		for (int u = 1; u <= sz; ++u){
			st[u][k] = st[st[u][k-1]][k-1];
		}
	}
}

int anc(int u, int d, const int (&st)[MAXN][LOG]) {
	for (int k = LOG-1; k >= 0; --k) if (d&(1<<k)) u = st[u][k];
	return u;
}

int lca(int u, int v, const int h[], const int (&st)[MAXN][LOG]) {
	if (h[u] < h[v]) {v = anc(v, h[v]-h[u], st);} 
	else if (h[v] < h[u]) {u = anc(u, h[u]-h[v], st);}
	if (u==v) return u; // or v
	for (int k = LOG-1; k >= 0; --k) {
		if (st[u][k]!=st[v][k]) {
			u = st[u][k];
			v = st[v][k];
		}
	}
	return st[u][0]; // or st[v][0]
}

bool onpath(int x, int u, int v, const int (&st)[MAXN][LOG], const int h[]) {
	int xu = lca(x, u, h, st);
	int xv = lca(x, v, h, st);
	int uv = lca(u, v, h, st);
	if ( (x==xu || x==xv) && h[x]>=h[uv]) return true;
	return false;
}

int main() {
// 	freopen("data.txt", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 0, u, v; i < M; ++i) {
		scanf("%d%d", &u, &v);	
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	tarjan(1);
	buildBT(1, 1);
	buildBCT(1, 1);
	dfs(1, btp, bth, btree);
	dfs(1, bctp, bcth, bctree);
	buildLCA(btp, btst, btsize);
	buildLCA(bctp, bctst, bctsize);
	int Q; 
	scanf("%d", &Q);
	while (Q--) {
		int type; scanf("%d", &type);
		if (type==1) {
			int A, B, G1, G2; scanf("%d%d%d%d", &A, &B, &G1, &G2);
			if (btnode[G1]==btnode[G2]) {
				// not a bridge
				printf("yes\n");
			} else if (btnode[A]==btnode[B]) {
				printf("yes\n");
			} else {
				int g1 = btnode[G1], g2 = btnode[G2];
				int a = btnode[A], b = btnode[B];

				if (onpath(g1, a, b, btst, bth) && onpath(g2, a, b, btst, bth) && (btp[g1]==g2 || btp[g2]==g1)) {
					printf("no\n");
				} else {
					printf("yes\n");
				}
			}
		} else {
			int A, B, C; scanf("%d%d%d", &A, &B, &C);
			if (!artnode[C]) {
				printf("yes\n");
			} else {
				int a, b, c;
				c = artnode[C];
				if (artnode[A]) a = artnode[A];
				else a = blocknode[A];

				if (artnode[B]) b=artnode[B];
				else b = blocknode[B];

				if (onpath(c, a, b, bctst, bcth)) {
					printf("no\n");
				} else {
					printf("yes\n");
				}
			}
		}
	}
}