#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <array>
using namespace std;

vector<pair<array<int, 6>, int> > s;

void add(const array<int,6>& snow, int id) {
	for (int rot = 0; rot < 6; ++rot) {
		pair<array<int, 6>, int> toadd;
		toadd.second = id;
		for (int j = 0; j < 6; ++j) {
			toadd.first[(j+rot)%6] = snow[j];
		}
		s.push_back(toadd);
	}
}

int main() {
	freopen("data.txt", "r", stdin);
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		array<int, 6> snow1, snow2;
		for (int j = 0; j < 6; ++j) {
			scanf("%d", &snow1[j]);
			snow2[5-j]=snow1[j];
		}
		add(snow1, i);
		add(snow2, i);
	}
	sort(s.begin(), s.end());
	for (auto x : s) {
		for (int i = 0; i < 6; ++i) printf("%d ", x.first[i]);
		printf(", %d\n", x.second);
	}
	for (int i = 0; i + 1 < s.size(); ++i) {
		if (s[i].first==s[i+1].first && s[i].second != s[i+1].second) {
			printf("Twin snowflakes found.\n");
			return 0;
		}
	}
	printf("No two snowflakes are alike.\n");
}