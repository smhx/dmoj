#include <iostream>
#include <vector>
using namespace std;

int main () {
	int N;
	cin >> N;
	vector<int> R = vector<int>(N);
	vector<int> L = vector<int>(N);

	for (int i = 0; i < N; i++) 
		cin >> L[i] >> R[i];
	
	vector<int> r = vector<int>(N);
	vector<int> l = vector<int>(N);
	r[N-1] = N-R[N-1];
	l[N-1] = N-L[N-1];

	for (int i = N-2; i >= 0; i--) {
	
		if (R[i]>=R[i+1]) {
			r[i] = R[i]-L[i+1]+1+l[i+1];
		}
		else if (R[i] <= L[i+1]) {
			r[i] = R[i+1]-R[i]+1+r[i+1];
		}
		else {
			int rightFirst = 1+R[i+1]-L[i+1]+R[i+1]-R[i]+l[i+1];
			int leftFirst = 1+R[i+1]-L[i+1]+R[i]-L[i+1]+r[i+1];
			r[i] = min(rightFirst, leftFirst);
		}
		
		if (L[i] >= R[i+1]) {
			l[i] = 1+L[i]-L[i+1]+l[i+1];
		}
		else if (L[i] <= L[i+1]) {
			l[i] = 1+R[i+1]-L[i]+r[i+1];
		}
		else {
			int leftFirst = 1+R[i+1]-L[i+1]+L[i]-L[i+1]+r[i+1];
			int rightFirst = 1+R[i+1]-L[i+1]+R[i+1]-L[i]+l[i+1];
			l[i] = min(rightFirst, leftFirst);
		}
	}
	cout << r[0]+R[0]-1<< endl;
	return 0;
}

