#include <cstdio>
#define MAXN 100005
typedef long long ll;
int N, K, D, q[MAXN], t[MAXN], qn=0, tn=0;
ll res[MAXN], prod = 1;
char op;
int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d%d%d", &N, &K, &D);
	q[0] = 1;
	for (int i = 0; i < N; ++i) {
		scanf(" %c", &op);
		if (op=='T') t[tn++] = qn;
		else scanf("%d", &q[++qn]);
	}
	
	for (int i = tn-1; i >= 0; --i) {
		for(;qn>t[i];--qn) 
			if (prod <= ll(D) ) 
				prod *= ll(q[qn]);
		res[i] = prod;
	}	

	for (int i = 0; i < tn; ++i) {
		if (res[i] > ll(D) ) printf("dust\n");
		else printf("%lld\n", res[i]);
	}
}
