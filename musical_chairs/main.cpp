/*input
7 3
1 2 3
1 2 3 4
*/
#include <bits/stdc++.h>
using namespace std;
int N, K, stu[1000005];
bool empty[1000005];
stack<int> s;
int main() {
	scanf("%d%d", &N, &K);
	int start;
	for (int i = 0; i < K; ++i) {
		scanf("%d", &start);
		empty[start]=true;
	}
	for (int i = 1; i <= K+1; ++i) {
		int c; scanf("%d", &c);
		stu[c] = i;
	}
	int at = start+1;
	if (at == N+1) at = 1;
	for (int i = 0; i < N; ++i) {
		if (stu[at]) {
			s.push(stu[at]);
			stu[at] = 0;
		}
		if (empty[at] && !s.empty()) {
			s.pop();
			empty[at] = 0;
		}
		++at;
		if (at==N+1) at = 1;
	}
	while (!s.empty()) {
		printf("%d\n", s.top());
		s.pop();
	}
}