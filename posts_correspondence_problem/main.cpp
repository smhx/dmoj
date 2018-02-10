#include <bits/stdc++.h>
using namespace std;

string s[2][50];
int n, m, mem[50][2][50][30];

stack<int> moves;


bool f(int k, int u, int idx, int st) {
	if (k > m) return false;
	int &x = mem[k][u][idx][st];
	if (x!=-1) return x;

	x = 0;	
	for (int i = 1; i <= n; ++i) {
		bool works = true;
		for (int l = 0; l < s[u][i].size() && l+st < s[u^1][idx].size() && works; ++l) {
			if (s[u][i][l] != s[u^1][idx][l+st]) works = false;
		}
		int d = s[u^1][idx].size()-st;
		for (int l = s[u^1][idx].size()-st; works && l < s[u][i].size() && l-d < s[u^1][i].size(); ++l) {
			if (s[u][i][l] != s[u^1][i][l-d]) works = false;
		}

		if (!works) continue;


		if (s[u^1][i].size()+d == s[u][i].size()) {
			moves.push(i);
			return x = 1;
		} else if (s[u^1][i].size()+d > s[u][i].size()) {
			x = f(k+1, u, i, s[u][i].size()-d);
			if (x) {
				moves.push(i);
				return x = 1;
			}
		} else {
			x = f(k+1, u^1, i, s[u^1][i].size()+d);
			if (x) {
				moves.push(i);
				return x = 1;
			}
		}
	}

	return x=0;
}

int main() {
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= n; ++i) cin >> s[0][i];
	for (int i = 1; i <= n; ++i) cin >> s[1][i];
	memset(mem, -1, sizeof mem);
	bool possible = f(0, 0, 0, 0);
	if (!possible){
		printf("No solution.\n");
	} else {
		printf("%lu\n", moves.size());
		while (!moves.empty()){
			printf("%d\n", moves.top());
			moves.pop();
		}
	}
}