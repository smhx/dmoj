#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

string in;

int N, C;

map<string, string> combos;

string input() {
	vector<string> things;
	cin >> in;
	while (in != ")") {
		if (in != "+") {
			if (in=="(") {
				string x = input();
				things.push_back(x);
			} else {
				things.push_back(in);
			}
		}
		cin >> in;
	}
	sort(things.begin(), things.end());
	string x;
	for (auto s : things) x  += s;
	return combos[x];
}


int main() {
	// freopen("data.txt", "r", stdin);
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) {
		vector<string> things;
		while (1) {
			cin >> in;
			if (in=="+" || in=="(" || in==")") continue;
			else if (in=="=") break;
			else things.push_back(in);
		}
		cin >> in;
		sort(things.begin(), things.end());
		string x;
		for (auto s : things) x  += s;
		combos[x]=in;
	}
	cin >> C;
	while (C--) {
		cin >> in;
		string x = input();
		cout << x << endl;
	}
}