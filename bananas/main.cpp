#include <iostream>
#include <string>
using namespace std;

bool monkey(string& word) {
	int bs = 0;
	int simpleIndex = 0;
	char options[] = "AN";
	for (size_t i = 0; i < word.size(); i++) {
		if (bs < 0) return false;
		if (word[i]=='B') {
			if (i > 0) {
				if (word[i-1] == 'A' || word[i-1] == 'S'){
					return false;
				}
			}
			++bs;
			continue;
		}

		if (word[i]=='S') {
			if (i+1 < word.size() && (word[i+1]=='A' || word[i+1]=='B') )
				return false;
			--bs;
			continue;
		}
		if (word[i]=='A' || word[i]=='N') {
			if (word[i] != options[simpleIndex%2]) return false;
			++simpleIndex;
			continue;
		}
		return false;
	}
	if (bs !=0) return false;
	if (simpleIndex%2==0) return false;
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string word;
	cin >> word;
	while (true) {
		if (monkey(word) ) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
		cin >> word;
		if (word=="X")
			break;
	}
	
	return 0;
}