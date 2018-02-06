/*input
9084194700940903797191718247801197019268
*/

#include <bits/stdc++.h>
using namespace std;
const int INF = 1e7;
int N, S[50], dp[50][2][2];

void input() {
	char c;
	while ((c=getchar()) >= '0') S[N++]=c-'0';
}

inline int dist(int a, int b) {
	if (a>b) swap(a, b);
	return min(b-a, 10-b+a);
}

int f(int i, int iscarry, int shouldcarry);

// no carry and no should carry
int case2(int a, int b, int i) {
	int x = INF;
	x = min(x, max(a,b)-min(a,b)+f(i+1, 0, 0) ); // get a to b and recurse
	if (a!=9) x = min(x, max(b, (a+1)%10 )-min(b, (a+1)%10 ) + f(i+1, 0, 1)); // get (a+1)%10 to b and recurse
	x = min(x, 10-b+   min( (10-a)%10, a)    +f(i+1, 1, 0)); // get b to 10 and a to 0 and recurse
	if (a!=9) x = min(x, 10-b+   min( (10-(a+1)%10 )%10, (a+1)%10) +    f(i+1, 1, 1)); // get b to 10 and (a+1)%10 to zero and recurse
	return x;
}

// no carry and should carry
int case1(int a, int b, int i) {
	int x = INF;
	x = min(x, 10-a+b+f(i+1, 0, 0) );
	x = min(x, 10-(a+1)+b+f(i+1, 0, 1));
	x = min(x, 10-b+10-a+f(i+1, 1, 0));
	x = min(x, 10-b+(10-(a+1)%10)%10+f(i+1, 1, 1));
	return x;
}

int f(int i, int iscarry, int shouldcarry) {

	int &x = dp[i][iscarry][shouldcarry];
	if (x != -1) return x;

	x = INF;
	// base case.
	if (i > N-i-1) {
		if (shouldcarry ^ iscarry) x = INF;
		else x = 0;
	} else if (i == N-i-1) {
		if (iscarry) {
			if (S[i]==9) {
				if (shouldcarry) x = 0;
				else x = INF;
			} else {
				if (shouldcarry) x = 10-S[i]-1;
				else x=0;
			}
		} else {
			if (shouldcarry) x = 10-S[i];
			else x=0;
		}
	} else {
		int a = S[i], b = S[N-i-1];

		if (iscarry) {
			if (shouldcarry) {
				if (b==9) {
					x = min(x, 10-a+f(i+1, 1, 0)); // b goes to 0. Then get a to 0
					x = min(x, 10-(a+1)+f(i+1, 1, 1)); // a goes to a+1
				} else {
					x = case1(a, b+1, i); // same as below
				}
			} else {
				if (b == 9) {
					x = min(x, a+f(i+1, 1, 0)); // b goes to 0 no carry so then b has to go to a.
					if (a!=9) x = min(x, a+1  +f(i+1, 1, 1)); // a goes to (a+1)%10 and b has to match
				} else {
					x = case2(a, b+1, i); // same as below
				}
			}
		} else {
			if (shouldcarry){
				x = case1(a, b, i);
			} else {
				x = case2(a, b, i);
			}
		}
	}

	return x;
}

int main() {
	input();
	memset(dp, -1, sizeof dp);
	printf("%d\n", min( f(0, 0, 0), f(0, 0, 1)) );
}