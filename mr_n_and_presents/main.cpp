/*input
5
F 1
F 2
R 1
E 3
E 1
*/
#include <cstdio>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

int Q, x;
char op;
typedef pair<int, int> ii;

unordered_map<int, int> pos;
vector<ii> v;


int main() {
	scanf("%d", &Q);

	int front = 0, end = 0;
	while (Q--) {
		scanf(" %c%d", &op, &x);
		if (op=='F') {

			pos[x] = front;
			--front;
			
		} else if (op=='E') {
			pos[x] = end;
			++end;
			
		} else {
			pos.erase(x);
		}
	}

	for (auto p : pos)
		v.push_back(ii(p.second, p.first));
	sort(v.begin(), v.end());
	for (auto p : v) {
		printf("%d\n", p.second);
	}
}