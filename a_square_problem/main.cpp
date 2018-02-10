#include <bits/stdc++.h>
using namespace std;

int N, freq[257];
char A[50][50], o[257];

bool islatin() {
	for (int r = 0; r < N; ++r){
		memset(freq, 0, sizeof freq);
		for (int c = 0; c < N; ++c) {
			freq[(int)A[r][c]]++;
		}
		for (int i = 0; i < N; ++i) {
			if (freq[(int)o[i]]!=1) {
				return false;
			}
		}
	}
	// r is now column, c is now row
	for (int r = 0; r < N; ++r){
		memset(freq, 0, sizeof freq);
		for (int c = 0; c < N; ++c) {
			freq[(int)A[c][r]]++;
		}
		for (int i = 0; i < N; ++i) if (freq[(int)o[i]]!=1) return false;
	}
	return true;
}

bool isreduced() {
	for (int c = 0; c < N; ++c) if (A[0][c]!=o[c]) return false;
	for (int r = 0; r < N; ++r) if (A[r][0]!=o[r]) return false;
	return true;
}

void init() {
	for (int i = 0; i < 10; ++i) o[i] = '0'+i;
	for (int i = 0; i < 26; ++i) o[i+10]='A'+i;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < N; ++c) {
			scanf(" %c", &A[r][c]);
		}
	}
	init();
	if (!islatin()) return !printf("No\n");
	if (!isreduced()) return !printf("Latin\n");
	printf("Reduced\n");
}