#include <cstdio>
#include <unordered_map>
using namespace std;
typedef pair<int,int> ii;
typedef unordered_map<int,int> hashmap;
const int MAXN = 53;
int N, cnt=0, A[MAXN][MAXN], sum[MAXN][MAXN];
inline int recsum(int i1, int j1, int i2, int j2){ 
	return sum[max(i1,i2)][max(j1,j2)]+sum[min(i1,i2)-1][min(j1,j2)-1]-sum[max(i1,i2)][min(j1,j2)-1]- sum[min(i1,i2)-1][max(j1,j2)];
}
void generate(int a, int b, int dira, int dirb, hashmap& mp) {
	mp.clear();
	for (int i = a; 0 < i && i <= N; i += dira) 
		for (int j = b; 0 < j && j <= N; j += dirb) mp[recsum(a,b,i,j)]++;
}
int common(hashmap& a, hashmap& b) {
	int ans = 0;
	for (ii p : a) ans += p.second * b[p.first];
	return ans;
}
int main() {
	freopen("data.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) 
		for (int j = 1; j <= N; ++j) scanf("%d", &A[i][j]);
		
	for (int i = 1; i <= N; ++i) 
		for (int j = 1; j <= N; ++j) 
			sum[i][j] = sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+A[i][j];
	hashmap mpa, mpb;
	for (int i = 1; i < N; ++i) {
		for (int j = 1; j < N; ++j) {
			generate(i,j, -1, -1, mpa);
			generate(i+1,j+1,1,1,mpb);
			cnt += common(mpa,mpb);
		}
	}
	for (int i = 2; i <= N; ++i) {
		for (int j = 1; j < N; ++j) {
			generate(i,j, 1, -1, mpa);
			generate(i-1, j+1, -1, 1, mpb);
			cnt +=  common(mpa, mpb);
		}
	}
	printf("%d\n", cnt);
}