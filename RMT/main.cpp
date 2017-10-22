#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
#define mp make_pair
using namespace std;
const int MAX = 100001;
int N, M, Q, A[MAX], state[MAX], ord[MAX], line[MAX], st[2*MAX];
vector<int> lines[MAX], ogSum[MAX];
unordered_map<int, int> lazy[MAX];
typedef unordered_map<int, int>::iterator uit;

void build() {
	for (int i = N-1; i>0; i--) st[i] = st[i<<1]+st[i<<1|1];
}

int diff(int line, int lag, int left, int right) {
	return 0;
}

inline int query(int l, int r) {
	int res=0;
	for (l+=N, r+=N; l < r; l>>=1, r>>=1) {
		
	}
	return res;
}


void update(int node, int low, int high, int line) {
	auto it = lazy[node].find(line);
	if (it!=lazy[node].end()) {

	}
}

void run(int line) {
	int l = lines[line][0], r = lines[line].back();
	update(1, l, r, line);
}

int main(){
	scanf("%d%d%d", &N, &M, &Q);
	for (int i=1;i<=N;i++){
		scanf("%d", &line[i]);
		lines[line[i]].push_back(i);
	}
	for (int i=1;i<=N;i++){
		scanf("%d", st+i+N);
		A[i] = st[i+N];
	}
	for (int i = 1; i <= M; i++) {
		sort(lines[i].begin(), lines[i].end());
		for (int j = 0; j < lines[i].size(); ++j) {
			ord[lines[i][j]] = j;
		}
	}
	for (int i = 1; i <= M; ++i) {
		for (int j = 0; j < lines[i].size(); ++j) {
			int pre = 0;
			if (j) pre = ogSum[i].back();
			ogSum[i].push_back(pre+A[lines[i][j]]);
		}
	}
	build();
	for (int i=0, q; i<Q; i++) {
		scanf("%d", &q);
		if (q==1) {
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%d", query(l, r));
		} else {
			int l;
			scanf("%d", &l);
			run(l);
		}
	}
	return 0;
}

/*
	YOU SHOULD BE ABLE TO SOLVE THIS FUCKING PROBLEM!!!!

	You have N stations, numbered 1 to N. There are also M lines and each station is a part of exactly one line.
	Each line forms a loop, and when it is "run", it moves to the next state. 

	Say the stations in line l are l1, l2, ..., lk. Then plk = pl(k-1), pl(k-1) = pl(k-2), etc.

	You have Q queries (1 <= Q <= 10^5). Each is either a run, or a survey between a and b. 

	One solution is simply to use a BIT for the people in each station. Then you can perform surveys in lgN time.
	However, if a line has k people, run takes k*lgN time. This is too slow, because k can potentially be 10^5. 

	YOU KNOW THE QUERIES BEFOREHAND!

	That fact can be useful. If you have a line from x to y, then running that line does not affect and sum(a), where 
	a < x or a > y. So maybe u can be a bit lazy and mark line l as needing to run, but not running it yet.

	But let's say you run line l, and you have a query x <= b <= y. Then you still need to do a k*lgN operation.

	Do you? what if you just mark b, and all b in traversal down the BIT? That's lgN...
	But it leaves all the other stations in line l behind. hmmm... This means that each station has to have a number,
	indicating the times it has to run. (initially 0). So update once again takes O(k) time, because you need to update 
	every num. Do you? Every update is just increasing everything by 1. Yeah! Just keep a group number, and make individual negative!

	One problem... If line l has stations 1, 2, 3, ..., x, then you're going to end up updating all,
	which is again x*lgN.
	How does this work?

	run(int l) {
		// That's it!
		line[l].lag++;
	}


	sum(int x) {
		int ans=0;
		// returns the sum of all people at stations less than or equal to x.
		for (; x > 0; x -= x&-x) {
			// traverse down the tree.
			// if station x needs updating, update it
			if (lag[line[x]]-catch[x]) {
				// the problem is that in the bit, it may
				// need updating for different lines and stations!
				// 
			}
			ans += ppl[x];
		}
		return ans;
	}

	this is kind of shit...
	the obvious update is to iterate through each member in the line, and then do a lgN
	update on it...
	But that's potentially M*lgN if there's a line containing each station.
	Is there a way to improve this?

	1. Being lazy.
		This seems like the best option.
		But how would it work exactly? Every node gets a 
	2. Knowing queries beforehand
	3. 
*/