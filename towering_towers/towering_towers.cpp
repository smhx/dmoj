#include <iostream>
#include <vector>
using namespace std;

int main () {
	int N;
	cin >> N;
	vector<int> H = vector<int>(N);
	for (int i = 0; i < N; i++) {
		cin >> H[i];
	}

	vector<int> V = vector<int>(N);

	V[0] = 0;
	for (int i = 1; i < N; i++) {
		int j = i-1;

		while (j >= 0) {

			if (H[j] > H[i] || j==0) {
				V[i] = i-j;
				break;
			}
	
			j -= V[j];
		}
	
	}

	for (int i = 0; i < N; i++) {
		cout << V[i] << " ";
	}
	cout << endl;
	return 0;
}