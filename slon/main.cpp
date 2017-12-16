#include <iostream>
#include <string>
#include <stack>
using namespace std;

typedef long long ll;

struct expr {ll m,b;};

int prec[256]; 
const char NUM_DELIM = '|';
ll P, M;


string postfix(const string& infix) {
	prec[(int)'*'] = 3;
	prec[(int)'+'] = 2;
	prec[(int)'-'] = 2;
	prec[(int)'('] = 1;
	string post;
	stack<char> opstack;
	for (size_t i = 0; i < infix.size(); ++i) {
		char tok = infix[i];
		if (tok == 'x') {
			post += tok;
		} else if ('0' <= tok && tok <= '9') {
			post += tok;
			int j = i+1;
			for (; j < infix.size(); ++j) {
				char c = infix[j];
				if ('0' <= c && c <= '9') post += c;
				else break;
			}
			post += NUM_DELIM;
			i = j-1;
		} else if (tok == '(') {
			opstack.push(tok);
		} else if (tok == ')') {
			while (!opstack.empty() && opstack.top() != '(') {
				post += opstack.top();
				opstack.pop();
			}
			opstack.pop();
		} else {
			while (!opstack.empty() && prec[(int)opstack.top()]>=prec[(int)tok]){
				post += opstack.top();
				opstack.pop();
			}
			opstack.push(tok);
		}
	}
	while (!opstack.empty()) {
		post += opstack.top();
		opstack.pop();
	}
	return post;
}

expr evalexpr(expr l, expr r, char tok) {
	if (tok == '+') return {(l.m + r.m)%M, (l.b+r.b)%M};
	if (tok == '-') return {(l.m - r.m)%M, (l.b - r.b)%M};
	if (l.m == 0) return {(r.m * l.b)%M, (r.b*l.b)%M};
	return {(r.b * l.m)%M, (r.b * l.b)%M};
}

expr evalpostfix(const string& postfix) {
	stack<expr> vstack;
	for (size_t i = 0; i < postfix.size(); ++i) {
		char tok = postfix[i];
		if (tok == '+' || tok == '-' || tok == '*') {
			expr right = vstack.top();
			vstack.pop();
			expr left = vstack.top();
			vstack.pop();
			vstack.push(evalexpr(left, right, tok));
		} else if (tok == 'x') {
			vstack.push({1LL, 0LL});
		} else {
			ll n = tok - '0';
			for (++i; i < postfix.size() && postfix[i] != NUM_DELIM; ++i) {
				n = 10LL*n + ll(postfix[i]-'0');
				n %= M;
			}
			vstack.push({0LL, n});
		}
	}
	return vstack.top();
}
int main() {
	freopen("data.txt", "r", stdin);
	string infix;
	cin >> infix;
	cin >> P >> M;

	string post = postfix(infix);
	expr res = evalpostfix(post);
	cout << post << "\n";
	cout << res.m << " * x + " << res.b << "\n";
	
	for (ll x = 0; x < M; ++x) {
		ll ans = res.m * x + res.b;
		ans %= M;
		ans = (ans + M) % M;
		if (ans == P) {
			// cout << "ans = " << ans << " P = " << P << endl;
			cout << x << "\n";
			return 0;
		}
	}
	cout << "-1\n";
}