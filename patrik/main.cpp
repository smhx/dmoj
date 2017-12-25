#include <cstdio>
#include <stack>
typedef long long ll;
typedef std::pair<int,int> ii;

int main() {
	freopen("data.txt", "r", stdin);
	int n; ll cnt=0;
	scanf("%d", &n);
	std::stack<ii> s;
	for (int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		int equal=1;
		while (!s.empty() && s.top().first <= x){
			cnt += 1LL * s.top().second;
			if (s.top().first==x) equal += s.top().second;
			s.pop();
		}
		if (!s.empty()) ++cnt;
		s.push({x,equal});
	}
	printf("%lld\n", cnt);
}