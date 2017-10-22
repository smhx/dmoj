#include <iostream>
#include <unordered_map>

using namespace std;

int N, G, g[12][12], ans;
unordered_map<int, int> mp;
char ch;

int main () {
	cin >> N >> G;
	for (int i = 0; i < G; i++) {
		for (int r = 1; r <= N; r++) {
		
			for (int c = 1; c <= N; c++) {
				
				cin >> ch;
			
				g[r][c] = ch=='R';
			}
		}
		
		for (int r = 1; r < N; r++) {
			for (int c = 1; c < N; c++) {
				if (g[r][c]) {
					g[r][c] ^= 1;
					g[r+1][c] ^= 1;
					g[r+1][c+1] ^= 1;
					g[r][c+1] ^= 1;
				}
			}
		}

		
		int mask = 0;
		
		for (int c=1; c <= N; c++) {
			mask = mask << 1 | g[N][c];
		}

		for (int r=N-1; r >= 1; r--) {
			mask = mask << 1 | g[r][N];
		}
		
		mp[mask]++;

		
	}
	for (auto mask: mp) {
			
			ans += mask.second*(mask.second-1) / 2;
		}
	
	
	cout << ans << endl;
}