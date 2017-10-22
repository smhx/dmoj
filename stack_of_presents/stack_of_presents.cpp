#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/* PROBLEM 
The CS Nerd is dreaming about giving Christmas presents to the girl. Unfortunately, he does not have enough courage to do this in real life.

In the dream, there are NN presents that he could possibly give to the girl. 
The ithith present has a weight of wiwi. 
The CS Nerd wants to impress the girl by building a large stack of presents – that is, presents stacked one on top of each other – and giving it to her.

However, the CS Nerd needs to ensure that the sum of the weights of the presents above any present does not exceed that present's weight. 
What is the maximum number of presents that can be in the stack?

The first line of input will contain a single integer N (1≤N≤100000)(1≤N≤100000).

NN lines of input follow. The ithith line will consist of a single integer, wiwi (1≤wi≤109)(1≤wi≤109).

For 20% of the points, N≤10N≤10.

For an additional 30% of the points, N≤1000N≤1000.

Start at the right. 
5
7
8
2
5
10
*/



int main () {
	int N;
	cin >> N;
	vector<int> w = vector<int>(N);
	for (int i = 0; i < N; i++) {
		cin >> w[i];
	}
	sort( w.begin(), w.end());
	int sum = 0;
	int count = 0;
	for (int i = 0; i < N; i++) {
		if (w[i] >= sum) {
			sum += w[i];
			count++;
		}
	}
	cout << count << endl;
}