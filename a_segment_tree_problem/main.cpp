#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX = 2e6+6, LOG = 20;

int N;

ll numcones=0, totcost=0;	
char op[15];

struct bit {
	ll b[MAX];

	// [1, MAX-1]

	void update(int x, ll v) {
		for (; x < MAX; x += x&-x) b[x]+=v;
	}

	ll sum(int x) {
		ll res=0;
		for (; x; x -= x&-x) res += b[x];
		return res;
	}

	// returns the minimum index i such that sum(i) >= s
	int lowerbound(ll s) {
		ll cursum = 0; int x = 0;
		for (int k = LOG-1; k >= 0; --k) {
			if (x + (1<<k) < MAX) {
				if (cursum + b[x + (1<<k) ] < s) {
					x += 1<<k;
				}
			}
		}
		return x+1;
	}
};

// coster computes ax+b.

bit counter, costm, costb;


ll buylow(ll L) {
	ll end = counter.lowerbound(L);
	ll presum = counter.sum(end);
	ll rem = L-presum;

	ll cost = costm.sum(end-1)*(end-1) + costb.sum(end-1) + rem*end;
	return cost;
}

int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int q = 0; q < N; ++q) {
		scanf(" %s", op);
		if (strcmp(op, "ADD")==0) {

			printf("ADD\n");

			int K, P; scanf("%d %d", &K, &P);

			// add K more cones at price P
			counter.update(P, K);
			counter.update(P+1, -K);

			costb.update(P, K);
			costb.update(P+1, -K);

			numcones += 1LL*K;
			totcost += 1LL*K*P;

		} else if (strcmp(op, "ADDRANGE") == 0) {

			printf("ADDRANGE\n");

			int A, B; scanf("%d %d", &A, &B);

			// add 1 cone to each price P in [A, B].

			counter.update(A, 1);
			counter.update(B+1, -1);

			costm.update(A, 1);
			costb.update(A, -A+1);

			costm.update(B+1, -1);
			costb.update(B+1, 1-A);

			numcones += 1LL*(B-A+1);

			// A + A+1 + ... + B = B*(B+1)/2 - A*(A-1)/2
			totcost += 1LL*B*(B+1)/2 - 1LL*A*(A-1)/2;

		} else if (strcmp(op, "BUYAMT") == 0) {

			ll Q; scanf("%lld", &Q);

			// Do a binary search. slightly sketchy.

			ll x = 0;
			ll curm=0, curb=0;
			for (int k = LOG-1; k >= 0; --k) {
				if (x+(1<<k) < MAX) {

					ll newb = curb + costb.b[x+(1<<k)];
					ll newm = curm + costm.b[x+(1<<k)];

					ll newx = x + (1LL<<k);

					if (newm * newx + newb < Q) {
						curm = newm;
						curb = newb;
						x = newx;
					}
				}
			}

			ll cost = curm * x + curb;
			ll rem = Q-cost;
			++x;
			cost += (rem/x) * x;

			printf("%lld\n", cost);

		} else if (strcmp(op, "BUYLOW") == 0) {

			ll L; scanf("%lld", &L); 

			ll cost = buylow(L);

			printf("%lld\n", cost);

		} else if (strcmp(op, "BUYHIGH") == 0) {

			ll L; scanf("%lld", &L); 

			ll cost = totcost - buylow(numcones-L);

			printf("%lld\n", cost);

		} else if (strcmp(op, "COST") == 0) {

			int L; scanf("%d", &L);
			int cost = counter.lowerbound(L);
			if (cost == MAX) printf("-1\n");
			else printf("%d\n", cost);

		} else if (strcmp(op, "NUMCONES") == 0) {

			printf("%lld\n", numcones);
		} else {
			// total cost
			printf("%lld\n", totcost);
		}
	}
}
