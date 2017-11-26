#include <cstdio>
#include <vector>
#include <functional>
#include <deque>
#include <algorithm>
#include <cmath>
using namespace std;

typedef pair<int, int> ii;
typedef long long ll;

const int MAXN = 2005, MAXQ = 900000; ll INF = 10000000000000LL;
const double EPS = 1e-6;
int N, Q; ll X, K, A[MAXN], B[MAXN], C[MAXN];
double m[MAXN];

vector<pair<double, int> > plane1[MAXN]; 
vector<pair<double, vector<int> > > plane2[MAXN];
vector<pair<double, ll> > plane[MAXN];

vector<ii> q_for_plane[MAXN]; // second is id
ll ans[MAXQ];

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%lld%lld%d%d", &X, &K, &N, &Q);
	for (int i = 1; i<=N; ++i) {
		scanf("%lld%lld%lld", A+i, B+i, C+i);
		m[i] = double(B[i]-A[i]) / double(X);
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = i+1; j <= N; ++j) {

			if (m[i] != m[j]) {
				double meetx = double(A[i]-A[j]) / (m[j]-m[i]);
				if (0.0 <= meetx && meetx <= (double)X){
					plane1[i].push_back({meetx, j});
					plane1[j].push_back({meetx, i});
				}

			}
		}
	}
	
	for (int p = 1; p <= N; ++p) {
		plane2[p].push_back({0.0, {0}});
		sort(plane1[p].begin(), plane1[p].end());
		for (int i = 0; i < plane1[p].size(); ++i) {
			if (fabs(plane1[p][i].first-plane2[p].back().first) > EPS) {
				plane2[p].push_back({plane1[p][i].first, {}});
			}	
			plane2[p].back().second.push_back(plane1[p][i].second);
		}
	}

	vector<ii> start;
	for (int i = 1; i <= N; ++i) {
		start.push_back({A[i], i});
	}
	sort(start.begin(), start.end(), greater<ii>());

	for (int p = 1; p <= N; ++p) plane[p] = vector<pair<double,ll> >(plane2[p].size());

	for (ll i = 0, sum=0; i < start.size(); ++i) {
		plane[start[i].second][0].second = sum;
		sum += C[start[i].second];
	}

	for (int p = 1; p <= N; ++p) {
		ll above = plane[p][0].second;

		for (int i = 1; i < plane2[p].size(); ++i) {
			for (int q : plane2[p][i].second) {
				if (m[q] > m[p]) {
					above += C[q];
				} else {
					above -= C[q];
				}
			}
			plane[p][i].second = above;
			plane[p][i].first = plane2[p][i].first;
		}
	}
	for (int id = 0; id < Q; ++id) {
		int p, s; scanf("%d%d", &p, &s);
		q_for_plane[p].push_back({s, id});
	}

	for (int p = 1; p <= N; ++p) {
		vector<ii> bounds(plane[p].size());

		sort(q_for_plane[p].begin(), q_for_plane[p].end());

		for (int i = 0; i < q_for_plane[p].size(); ++i) {
			int s = q_for_plane[p][i].first;
			bounds[i].first = (lower_bound(plane[p].begin(), plane[p].end(), pair<double, ll>(double(s), INF) ) - plane[p].begin() ) - 1;
			bounds[i].second = (lower_bound(plane[p].begin(), plane[p].end(), pair<double,ll>(double(s+K), INF)) - plane[p].begin() ) - 1;
		}	

		deque<pair<ll,int> > dq;
		for (int idx=0, qidx = 0; qidx < q_for_plane[p].size(); ++qidx) {
			while (idx <= bounds[qidx].second) {
				while (!dq.empty() && dq.back().first < plane[p][idx].second) dq.pop_back();
				dq.push_back({plane[p][idx].second, idx});
				++idx;
			}
			while (dq.front().second < bounds[qidx].first) dq.pop_front();
			ans[q_for_plane[p][qidx].second] = dq.front().first;
		}
	}
	for (int q = 0; q < Q; ++q) printf("%lld\n", ans[q]);
	
}