#include <cstdio>
#include <vector>
using namespace std;

int tryCombination(int S[]);
void answer(int S[], int D[]);
const int MAXN = 5005;
int v[MAXN], d[MAXN], c[MAXN];
vector<int> U;
void exploreCave(int N) {
	int bound = tryCombination(v);
	for (int i = 0; i < N; ++i) U.push_back(i);
	while (!U.empty()) {
		int lo = 0, hi = U.size()-1;
		int newBound;
		while (lo<hi){
			int mid = (lo+hi)/2;
			for (int i = lo; i <= mid; ++i) v[U[i]]^=1;
			newBound = tryCombination(v);
			for (int i = lo; i <= mid; ++i) v[U[i]]^=1;
			if (newBound != bound) hi = mid;
			else lo = mid+1;
		}
		v[U[lo]]^=1;
		newBound = tryCombination(v);
		if (bound==-1 || (newBound != -1 && newBound < bound) ) {
			d[U[lo]]=newBound;
			v[U[lo]]^=1;
			c[U[lo]]=v[U[lo]];
		} else {
			d[U[lo]]=bound;
			c[U[lo]]=v[U[lo]];
			bound = newBound;
		}
		U.erase(U.begin()+lo);
	}
	answer(c, d);
}

/* Testing */

int testN, testC[MAXN], testD[MAXN], testDoorRev[MAXN];

int tryCombination(int S[]) {
	for (int door = 0; door < testN; ++door) {
		int swt = testDoorRev[door];
		if (S[swt]!=testC[swt]) return door; // door is closed
	}
	return -1;
}

void answer(int S[], int D[]) {
	printf("\nSubmitting answer\n");
	printf("switches are:\n");
	for (int i = 0; i < testN; ++i) printf("%d ", S[i]);
	printf("\nexpected:\n");
	for (int i = 0; i < testN; ++i) printf("%d ", testC[i]);

	printf("\n\ndoors are:\n");
	for (int i = 0; i < testN; ++i) printf("%d ", D[i]);
	printf("\nexpected:\n");
	for (int i = 0; i < testN; ++i) printf("%d ", testD[i]);
	printf("\n");
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &testN);
	for (int i = 0; i < testN; ++i) {
		scanf("%d", testD+i); // The i'th switch is for door testD[i]
		testDoorRev[testD[i]]=i;
	}
	for (int i = 0; i < testN; ++i) scanf("%d", testC+i);
	exploreCave(testN);
}