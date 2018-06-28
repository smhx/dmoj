#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> f[100];
int main() {
	f[1].push_back({0});
	for (int n = 2; n <= 4; ++n) {
		for (int k = 1; k <= n-k; ++k) {

			for (auto s1 : f[k]) {
				for (auto s2 : f[n-k]){
					vector<int> s;
					for (auto x : s1) s.push_back(x+1);
					for (auto x : s2) s.push_back(x+1);
					sort(s.begin(), s.end());
					f[n].push_back(s);
				}
			}
			
		}
		sort(f[n].begin(), f[n].end());
		f[n].erase(unique(f[n].begin(), f[n].end()), f[n].end());
		printf("f[%d]: cnt = %lu\n", n, f[n].size());
		for (auto v : f[n]) {
			for (auto x : v) printf("%d ", x);
			printf("\n");
		}
	}
}