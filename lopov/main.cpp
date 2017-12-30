#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
const int MAXN = 300005;
int N, K;
ii jewel[MAXN];
ll liberated=0;
map<int,int> sizes;
int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d%d",&N, &K);
	for (int i = 0; i < N; ++i) scanf("%d%d", &jewel[i].second, &jewel[i].first);
	for (int i = 0, c; i < K; ++i) {
		scanf("%d", &c);
		sizes[c]++;
	}
	sort(jewel, jewel+N, [](ii a, ii b) {return a.first != b.first ? a.first > b.first : a.second < b.second;});
	for (int i = 0; i < N; ++i) {
		if (sizes.empty())break;
		auto it = sizes.lower_bound(jewel[i].second);
		if (it==sizes.end()) continue;
		if (it->second==1) sizes.erase(it);
		else it->second--;
		liberated += 1LL * jewel[i].first;
	}
	printf("%lld\n", liberated);
}
