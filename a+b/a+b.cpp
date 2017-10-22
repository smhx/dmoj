#include <cstdio>
#include <string>
#include <cstdint>
#include <cstdlib>


using namespace std;

int N;

// i8 sum[100000];
char in;


int sum[50][100000];
int start[50];
int pre[50];
bool isPos[50];
bool isZero[50];

int main () {
	scanf("%d", &N);
	scanf("%c", &in);
	for ( int _ = 0; _ < N; _++ ) {
		int carry=0;

		int nums[2][100000];
		int lengths[2];
		for (int i = 0; i < 2; i++) {
			int factor=1;
			int index = 0;
			while (true) {
				scanf("%c", &in);
				if (in==' ' || in=='\n') {
					lengths[i] = index;
					break;
				}
				if (in=='-') {
					factor = -1;
					continue;
				}
				nums[i][index] =  (int)(in-'0')*factor;
				++index;
			}
		}
		
		int ai=lengths[0]-1;
		int bi=lengths[1]-1;
		bool pos = true;
		
		if (nums[0][0] >= 0 && nums[1][0] >= 0) {
			pos = true;
		} 
		else if (nums[0][0] <= 0 && nums[1][0] <= 0) {
			pos = false;
		}
		else {
			if (lengths[0] == lengths[1]) {
				int l = 0;
				while(true) {
					
					if (nums[0][l] + nums[1][l]==0){
						if (l==lengths[0]){
							isZero[_] = true;
						}
						++l;
						continue;
					}
					pos = nums[0][l]+nums[1][l] > 0;
					int tmp = lengths[0];
					lengths[0] = tmp-l;
					lengths[1] = tmp-l;
					break;
				}
			} 
			else {
				int k = (lengths[1] > lengths[0]) ? 1 : 0;
				pos = nums[k][0] > 0;
			}
		}
		isPos[_] = pos;
		
		for (int dp=0; dp >= 0; dp++) {
			if (ai >=0 && bi >= 0) {
				int tmp = nums[0][ai]+nums[1][bi]+carry;

				carry = (int) tmp / 10;
				sum[_][dp] = (int) (tmp-10*carry);
				if (pos) {
					if (sum[_][dp] < 0) {
						sum[_][dp]+=10;
						--carry;
					}
					
				} else {
					if (sum[_][dp] > 0) {
						sum[_][dp]-=10;
						++carry;
					}
				}
				--ai;
				--bi;
			}
			else if (ai < 0 && bi >= 0) {
				int tmp = nums[1][bi]+carry;
				carry = (int) tmp / 10;

				sum[_][dp] = (int) (tmp-10*carry);
				if (pos) {
					if (sum[_][dp] < 0) {
						sum[_][dp]+=10;
						--carry;
					}
					
				} else {
					if (sum[_][dp] > 0) {
						sum[_][dp]-=10;
						++carry;
					}
				}
				--ai;
				--bi;
			}
			else if (bi < 0 && ai >= 0) {
				int tmp = nums[0][ai]+carry;
				carry = (int) tmp / 10;

				sum[_][dp] = (int) (tmp-10*carry);
				if (pos) {
					if (sum[_][dp] < 0) {
						sum[_][dp]+=10;
						--carry;
					}
					
				} else {
					if (sum[_][dp] > 0) {
						sum[_][dp]-=10;
						++carry;
					}
				}
				--ai;
				--bi;
			}
			else {
				pre[_] = abs(carry);
				break;
			}
		}
		start[_] = max(lengths[0], lengths[1])-1;
		if (pre[_] != 0) continue;
		while (true) {
			if (sum[_][start[_]] != 0) {
				break;
			}
			if (start[_]==0) {
				isZero[_] = true;
				goto NNN;
			}
			--start[_];
		}
		NNN:
		continue;
	}
	for (int _ = 0; _<N; _++) {
		if (isZero[_]){
			printf("%d\n", 0);
			continue;
		}
		if (isPos[_]==false)
			printf("-");
		if (pre[_] != 0)
			printf("%d", pre[_]);
		for (int i = start[_]; i>=0; i--) {
			printf("%d", abs(sum[_][i]));
		}
		printf("\n");
	}
	return 0;
}
