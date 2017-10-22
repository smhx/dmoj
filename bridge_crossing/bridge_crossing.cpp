#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main () {
	int M, Q;
	cin >> M >> Q;
	vector<string> names = vector<string>(Q);
	vector<int> times = vector<int> (Q);
	for (int i = 0; i < Q; i++) {
		cin >> names[i] >> times[i];
	}	
	vector<int> c = vector<int>(Q);
	
	vector<int> ends = vector<int>(Q);

	
	int max = -1;
	for (int i = 1; i <= M; i++) {
		if (times[Q-i] > max) max = times[Q-i];
		c[Q-i] = max;
		ends[Q-i] = Q-1;
	}
	for (int i = Q-M-1; i>=0; i--) {
		int min = 1 << 30;
		int cMaxTime = -1;
		int index = -1;
		for (int j = 0; j < M; j++) {
			if (times[i+j]>cMaxTime) cMaxTime = times[i+j];
			if (c[i+j+1]+cMaxTime < min) {
				min = c[i+j+1]+cMaxTime;
				index = i+j;
			}
		}
		c[i] = min;
		ends[i] = index;
	}
	
	cout << "Total Time: " << c[0] << endl;
	
	int next = ends[0];
	for (int i = 0; i < Q; i++) {
		cout << names[i] << " ";
		if (i==next) {
			cout << endl;
			if (i==Q-1) break;
			next = ends[i+1];
		}	

	}
	
	return 0;
}

