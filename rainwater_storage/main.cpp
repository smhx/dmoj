#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

int A[51];
int N;
vector<int> l;
vector<int> c;
int secondLargest;

unordered_set<int> rain(int k) {
	unordered_set<int> s = unordered_set<int>();

	if (  k == N-1  ) {
		s.insert(0);
		return s;
	}
	int j;

	for (j = 0; j < (int) c.size(); j++) {
		if (c[j]==l[k])
			break;
	}



	unordered_set<int> rec = rain(k+1);

	for (int m = j; m < (int) c.size(); m++) {
		if (c[m] > secondLargest) continue;
		for (auto a : rec) {
			s.insert(c[m]-l[k]+a);
		}
	}

	return s;
}


int main() {
	scanf("%d", &N);
	l = vector<int>(N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &l[i]);
		A[l[i]]++;
	}

	sort(l.begin(), l.end());

	secondLargest = l[(int)l.size()-2];

	for (int i = 1; i <= 50; i++) {
		if (A[i]) {
			c.push_back(i);
		}
	}

	auto s = rain(0);

	vector<int> v = vector<int>();

	for (auto a : s) {
		v.push_back(a);
	}

	sort(v.begin(), v.end());

	for (int i = 0; i < v.size(); i++) {
		printf("%d ", v[i]);
	}

	printf("\n");
	return 0;
}	



