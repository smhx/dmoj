
#include <cstdio>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <map>

using namespace std;

int main () {
	int N, p=0, k=0, b=0, m=0, _1, _2;
	scanf("%d", &N);

	map<int, vector<int> > A = map<int, vector<int> >();

	for (int i = 0; i < N; i++) {
		scanf("%d %d", &_1, &_2);
		if (_1==N) {
			k++;
			p += _2;
			continue;
		}
		if (_1 > m) m = _1;
		if (A.find(_1) != A.end() ) {
			A[_1].push_back(_2);
		} else {
			A.insert(make_pair(_1, vector<int>(1, _2) ) );
		}
	}


	for (auto vp : A) {
		sort (vp.second.begin(), vp.second.end(), greater<int>() );
	}
	
	for (auto it = A.begin(); it != --A.end(); ++it) {

		b += it->second.size()-1;
		int r = it->first;
		++it;
		int s = it->second;
		--it;
		int n = r-s+1;
		// printf("n is %d\n", n);
		while (n--) {
			// printf("n is %d\n", n);
			if (b) {
				// printf("b is not zero. Continuing\n");
				b--;
				continue;
			}

			if (k) {
				// printf("k is not zero. Continuiing\n");
				k--;
				continue;
			}

			// You have to buy the minimum...
			int min = 1 << 31;
			auto minit = A.end();
			auto jit = ++it;
			--it;
			for (; jit != A.end(); jit++) {
				if (jit->second.back() < min && jit->second.size() > 1) {
					min = jit->second.back();
					minit = jit;
					continue;
				}
				if (jit == --A.end() && jit->second.size()==1) {
					min = jit->second.back();
					minit = jit;
				}
			}

			minit->second.pop_back();
			p += min;
		}
	}
	
	printf("%d\n", p);
	return 0;
}