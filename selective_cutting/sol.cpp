/*
    This is the best solution. It is not yours.
    First sort each of the trees in descending height.
    
    The key idea is that you know all the queries beforehand.
    So you can simply answer them in the order you want!

    So each query has a property height, which is q. 
    Sort it in decreasing height because for every q,
    you only need to look at all h >= q

    Keep a pointer t to the current highest tree. So initially
    t just points to the first tree.
    For every query, update tree.
    Then get the answer by doing a standard sum!
*/
#include <iostream>
#include <algorithm>

#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

const int MAXN = 1e5 + 5;

struct tree{
	int mass;
	int id;
	tree() {
		mass = 0;
	}
	bool operator <(const tree& t) const {
		return mass > t.mass;
	}
};

struct query{
	int l, r, height, order;
	bool operator <(const query& q) const {
		return height > q.height;
	}
};

long long data[MAXN];
long long ans[MAXN];
query q[MAXN];
tree trees[MAXN];
int n, o, t = 0;

void update(int pos, int val){
	for(int i = pos; i <= MAXN; i += i & -i){
		data[i] += val;
	}
}

long long sum(int at){
	long long s = 0;
	for(int i = at; i; i -= i & -i){
		s += data[i];
	}
	return s;
}

int main(){
	scan(n);
	for(int i = 0; i < n; i++){
		scan(trees[i].mass);
		trees[i].id = i + 1;
	}
	std::sort(trees, trees + n);
	scan(o);
	for(int i = 0; i < o; i++){
		scan(q[i].l);
		scan(q[i].r);
		scan(q[i].height);
		q[i].order = i;
	}
	std::sort(q, q + o);
	for(int ii = 0; ii < o; ii++){
		int i = q[ii].order;
		int height = q[ii].height;
		while(trees[t].mass >= height && t < n){
			update(trees[t].id, trees[t].mass);
			t++;
		}
		ans[i] = sum(q[ii].r + 1) - sum(q[ii].l);
	}
	for(int i = 0; i < o; i++){
		printf("%lld\n", ans[i]);
	}
}