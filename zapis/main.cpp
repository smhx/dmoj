#include <bits/stdc++.h>
using namespace std;
const int MAXN = 205, MOD = 1e5;
int N;
char str[MAXN];

typedef long long ll;

ll mem[MAXN][MAXN];

inline bool isclosed(char c) {return c==')' || c==']' || c=='}';}
inline bool matches(char a, char b) {
	return a=='?' || b=='?' || ( (a=='(' && b==')' ) || (a=='[' && b==']') || (a=='{' && b=='}') );
}

inline ll modp(ll x) {return x >= MOD ? MOD+x%MOD : x;}

ll f(int l, int r) {
	if (mem[l][r] != -1) return mem[l][r];
	mem[l][r] = 0;
	if (l>r) return mem[l][r]=1;
	else if (l==r) return mem[l][r] = 0;
	else if (isclosed(str[l])) return mem[l][r];
	else if (str[l]=='?') {
		for (int k = l+1; k <= r; ++k) {
			if (isclosed(str[k])) 
				mem[l][r] = modp(mem[l][r]+ f(l+1, k-1) * f(k+1, r) );
			else if (str[k]=='?') 
				mem[l][r] = modp(mem[l][r]+ 3*f(l+1, k-1) * f(k+1, r) );
		}
	} else {
		for (int k = l+1; k <= r; ++k) 
			if (matches(str[l],str[k])) mem[l][r] = modp(mem[l][r]+ f(l+1, k-1) * f(k+1, r) );
	}
	return mem[l][r];
}

int main() {
	freopen("data.txt", "r", stdin);
	memset(mem, -1, sizeof mem);
	scanf("%d %s", &N, str);
	if (f(0,N-1) >= MOD) printf("%05lld\n", f(0,N-1)-MOD);
	else printf("%lld\n", f(0, N-1));
}