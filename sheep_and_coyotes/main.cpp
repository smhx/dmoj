#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;

double x[100];
double y[100];
bool reachable[100];

inline double distance(double x1, double y1, double x2, double y2) {
	return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

inline double round(double x) {
	x *= 100.0
	if (x-(int)x >= 0.5) ++x;
	return 0.01 * x;
}

int main () {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++){
		cin >> x[i] >> y[i];
	}
	for (double p=0.0f; p<=1000.0f; p+=0.1f) {
		
		int min = 1 << 30;
		vector<int> minIndices;
		for (int i = 0; i<N; i++) {
			double d=distance(p, 0.0f, x[i], y[i]);
			if (d<min){
				min=d;
				minIndices = vector<int>(1);
				minIndices[0] = i;
			}
			else if (d==min){
				minIndices.push_back(i);
			}
		}
		for (int i = 0; i < (int)minIndices.size(); i++) {
			
			reachable[minIndices[i]] = true;
		}
	}
	for (int i =0; i < N; i++) {
		if (reachable[i]) {
			cout << fixed << setprecision(2) << "The sheep at (" <<  round(x[i])  << ", " << round(y[i]) << ") might be eaten.\n";
		}
	}
	return 0;
}
