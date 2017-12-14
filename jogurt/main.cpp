#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_NODES = 70000;

int N, tree[MAX_NODES];

void build(int u, vector<int>& v) {

	if (v.size()==1) {
		tree[u] = v[0];
		return;
	}

	sort(v.begin(), v.end());
	tree[u] = v.back();
	v.pop_back();

	int l = 0, r = v.size()-1;
	vector<int> w[2];
	while (l + 1 != r) {
		w[l&1].push_back(v[l]);
		w[l&1].push_back(v[r]);
		++l, --r;
	}
	w[0].push_back(v[l]);
	w[1].push_back(v[r]);
	build(u<<1, w[0]);
	build(u<<1|1, w[1]);
}

void display(int u) {
	printf("%d ", tree[u]);
	if (tree[u<<1] && tree[u<<1|1]) {
		display(u<<1);
		display(u<<1|1);
	}
}

int main() {
	scanf("%d", &N);
	vector<int> v;
	for (int i = 1; i < (1<<N); ++i) v.push_back(i);
	build(1, v);
	display(1);
}