#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;


int main () {
	string A, B;
	cin >> A >> B;
	int N = (int)A.size();
	int M = (int)B.size();
	for (int overlap = min(N, M); overlap >= 0; overlap--) {
		if (overlap==0) {
			cout << A << B << endl;
			return 0;
		}
		if (B[overlap-1] != A[N-1])
			continue;
		if (B[overlap-2] != A[N-2])
			continue;
		for (int i =0; i < overlap; i++) {
			if (B[i] != A[N-overlap+i]) {
				goto NEXT_WORD;
			}
		}
		cout << A;
		for (int j=overlap; j<M; j++){
			cout << B[j];
		}
		cout << endl;
		return 0;
		NEXT_WORD:
		continue;
	}
	return 0;
}