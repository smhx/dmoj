#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int maxn = 1e5+5, inf = 1e9;
int n, k, m, ecover[maxn], mp[maxn];
int _a[maxn], _b[maxn], _c[maxn];
vector<ii> I, skel;
bool cmp1(const ii& a, const ii& b) {
	return a.second != b.second ? a.second > b.second : a.first < b.first;
}
int idxof[maxn];
int bound[maxn];


bool bad[100005];
void skeleton(vector<ii>& I, vector<ii>& ans) {
	sort(I.begin(), I.end());
	// printf("in skeleton with: ");
	// for (ii x : I) printf("[%d, %d]\n", x.first, x.second);
	// printf("\n");
	ans.clear();
	vector<ii> cpy(I);
	sort(cpy.begin(), cpy.end(), cmp1);
	// printf("cpy: ");
	// for (ii x : cpy) printf("[%d, %d]\n", x.first, x.second);
	// printf("\n");
	int i = 0;
	while (i < (int)I.size()) {
		if (I[i].first < cpy.back().first) {
			bad[I[i].first] = true;
			++i;
		} else {
			ans.push_back(I[i]);
			cpy.pop_back();
			while (bad[cpy.back().first]) cpy.pop_back();

			++i;
		}
	}
	for (size_t i = 0; i < ans.size(); ++i) idxof[ans[i].first] = i;

	// check correctness

	for (size_t i = 0; i + 1 < ans.size(); ++i) {
		if (ans[i].first < ans[i+1].first && ans[i].second < ans[i+1].second) {

		} else {
			// printf("%d.%d.%d:", n, k, m);
			// for (int i = 0; i < m; ++i) printf("%d,%d,%d.", _a[i], _b[i], _c[i]);
			while (1) {}
			// printf("error\n");
		}
	}
	// printf("returning: ");
	// for (ii x : ans) printf("[%d, %d]\n", x.first, x.second);
	// printf("\n");
}


void renumber() {
	for (int i = 1; i <= n; ++i) {
		if (ecover[i] == 0) mp[i] = mp[i-1]+1; 
		else mp[i] = mp[i-1];
	}
	// printf("after renumbering\n");
	for (ii& v : I) {
		if (ecover[v.first]) v.first = mp[v.first]+1;
		else v.first = mp[v.first];
		v.second = mp[v.second];
		// printf("[%d, %d]\n", v.first, v.second);
	}
}

bool alone[maxn], single[maxn];
int minreq, maxreq;
int greedy[maxn];
void findloners(const vector<ii>& skel) {
	int i, j;
	memset(greedy, -1, sizeof greedy);
	for (i = 0; i < (int)skel.size();) {
		// for (j = i+1; j < skel.size() && skel[j].first <= skel[i].second; ++j);
		// if (j < skel.size()) {
			// assert((int)j == bound[skel[i].second]);
		// }
		j = bound[skel[i].second];
		if (j == -1) {
			j = skel.size();
		}
		if (skel[j-1].first == skel[i].second) {
			alone[skel[i].second] = true;
			// printf("setting alone %d = true\n", skel[i].second);
		}
		++minreq;
		greedy[skel[i].second] = minreq;
		i = j;
	}
}
void findsingle(const vector<ii>& skel) {
	for (size_t i = 0; i < skel.size(); ++i) {
		if (skel[i].first == skel[i].second) {
			single[skel[i].first] = true;
			// printf("single[%d] = true\n", skel[i].first);
		}
	}
}

void clean(vector<ii>& a) {
	sort(a.begin(), a.end());
	// printf("cleaning: ");
	// for (ii x : a) printf("[%d, %d] ", x.first, x.second);
	// printf("\n");
	vector<ii> b;
	size_t i, j;
	for (i = 0; i < a.size();) {
		j = i+1;
		while (j < a.size() && a[j].first == a[i].first) ++j;
		b.push_back(a[i]);
		i = j;
	}
	a = b;
	// printf("result: ");
	// for (ii x : a) printf("[%d, %d] ", x.first, x.second);
	// printf("\n");
}


void compute_bound() {
	// printf("computebound\n");
	int at = 0;
	size_t i = 0;
	for (i = 0; i < skel.size(); ++i) {
		while (at < skel[i].first) {
			// printf("i = %d, at = %d\n", i, at);
			bound[at++] = i;
		}
	} 
	for (; at < maxn; ++at) bound[at] = -1;
	// printf("end of compute bound\n");
	// for (int i = 1; i <= n; ++i) {
	// 	printf("%d ", bound[i]);
	// }
	// printf("\n");
}
int dp[maxn];
void compute_dp() {
	// printf("compute_dp\n");
	for (int i = skel.size()-1; i >= 0; --i) {
		// printf("i = %d, bound = %d\n", i, bound[skel[i].second]);
		if (bound[skel[i].second] == -1) dp[i] = 1;
		else {
			// printf(" i = %d, bound[skel[i].second] = %d\n", i, bound[skel[i].second]);
			dp[i] = 1 + dp[bound[skel[i].second]];
		}
		// printf("dp[%d]= %d\n", i, dp[i]);
	}
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%d%d", &n, &k, &m);
	maxreq = n;
	for (int i = 1, a, b, c; i <= m; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		_a[i] = a; _b[i] = b; _c[i] = c;
		if (c) {
			I.emplace_back(a, b);
		} else {
			++ecover[a];
			--ecover[b+1];
		}
	}
	// for (ii i : I) {
		// printf("[%d, %d]\n", i.first, i.second);
	// }
	for (int i = 1; i <= n + 1; ++i) {
		ecover[i] += ecover[i-1];
		if (ecover[i]) --maxreq;
		// printf("ecover[%d] = %d\n", i, ecover[i]);
	}
	renumber();
	clean(I);
	skeleton(I, skel);
	compute_bound();
	findloners(skel);
	findsingle(skel);
	compute_dp();
	bool added = false;
	// printf("mineeq = %d, maxreq = %d\n", minreq, maxreq);
	for (int q = 1; q <= n; ++q) {
		if (!ecover[q]) {
			int p = mp[q];
			if (!alone[p]) {
				if (!(minreq <= k && k <= maxreq - 1)) {

					printf("%d\n", q);
					added = true;
				} 
			} else if (!single[p]) {
				if (greedy[p] == -1) {
					printf("ERROR\n");
				}
				// printf("p = %d, greedy[p] = %d, idxof[p] = %d, dp[*] = %d\n", p, greedy[p], idxof[p], dp[idxof[p]]);
				int lo = greedy[p] + dp[idxof[p]];
				// printf("lo = %d\n", lo);
				if (lo != minreq && lo != minreq+1) {
					// while (1){}
					printf("p = %d, greedy[p] = %d, idxof[p] = %d, dp[*] = %d, minreq = %d\n", p, greedy[p], idxof[p], dp[idxof[p]], minreq);
				}
				if (!(lo <= k && k <= maxreq - 1 )) {
					printf("%d\n", q);
					added = true;
				}
			} else {
				// printf("q = %d is single and alonge\n", q);
				printf("%d\n", q);
				added = true;
			}
		}
	}
	if (!added) printf("-1\n");
}