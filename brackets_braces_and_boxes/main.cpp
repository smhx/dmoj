#include <cstdio>
#include <stack>
#include <unordered_map>
#include <string>

using namespace std;

bool closing(char c) {
	return c==')' || c==']' || c=='}';
}

bool matches(char o, char c) {
	return (o=='(' && c==')' ) || (o=='{' && c=='}') || (o=='[' && c==']');
}

string input;

void same(int i, int j) {
	if (input[i]=='(') {
		input[j]=')';
		return;
	}
	if (input[i]=='[') {
		input[j]=']';
		return;
	}
	input[j]='}';
}


void other(int a, int b) {
	string o = "([{";
	string c = ")]}";
	int i, j;
	for (i = 0; i <3; i++) {
		if (o[i]==input[a]) break;
	}
	for (j = 0; j < 3; j++) {
		if (c[j]==input[b]) break;
	}
	int k;
	for (k = 0; k <3; k++) {
		if (k!=i && k!=j) break;
	}
	input[a]=o[k];
	input[b]=c[k];
	return;
}

void next(int i, int j) {
	if (input[i]=='(') {
		input[i]='[';
		input[j]=']';
		return;
	}
	if (input[i]=='[') {
		input[i]='(';
		input[j]=')';
		return;
	}
	input[i]='(';
	input[j]=')';
}


int main() {
	int N, K;
	scanf("%d %d", &N, &K);

	getchar();

	unordered_map<int, int> bad = unordered_map<int, int>();
	unordered_map<int, int> good = unordered_map<int, int>();

	input = "";

	stack<int> stack;

	for (int i = 0; i < N; i++) {
		scanf("%c", &input[i]);
		if (closing(input[i])) {
			if (stack.empty()) {
				printf("impossible\n");
				return 0;
			}
			int top = stack.top();
			stack.pop();
			if (!matches(input[top], input[i])) {
				bad.insert(make_pair(top, i));
			} else {
				good.insert(make_pair(top, i));
			}
		} else {
			stack.push(i);
		}
	}
	if (!stack.empty()) {
		printf("impossible\n");
		return 0;
	}

	int numBad = (int) bad.size();
	int numGood = (int) good.size();

	if (numBad > K) {
		printf("impossible\n");
		return 0;
	}

	if (2*numBad >= K) {
		int n = K-numBad;

		for (int i = 0; i < N; i++) {
			if (closing(input[i])) continue;
			if (good.find(i) != good.end() ) continue;
			if (n) {
				other(i, bad[i]);
				--n;
			}
			else same(i, bad[i]);
		}
		for (int i = 0; i < N; i++) {
			printf("%c", input[i]);
		}
		printf("\n");
		return 0;
	}

	if ( (2*numBad + 2*numGood ) < K) {
		printf("impossible\n");
		return 0;
	}

	for (auto badP : bad) {
		if (K%2==1) {
			same(badP.first, badP.second);
			--K;
			continue;
		}
		other(badP.first, badP.second);
		K -= 2;
	}


	if (K%2==1) {
		printf("impossible\n");
		return 0;
	}

	for (auto goodP : good) {
		if (K) {
			next(goodP.first, goodP.second);
			K -= 2;
		} 
		else break;
	}

	for (int i = 0; i < N; i++) {
		printf("%c", input[i]);
	}
	printf("\n");
	return 0;
}