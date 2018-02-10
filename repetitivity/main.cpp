// CCO '13 Day 2 Problem 3- Repetitivity
// https://dmoj.ca/problem/cco13p6

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int maxn = 10001;
string s;
int len,dp[maxn][maxn],m;
bool same[maxn][maxn];
int main() {
    freopen("data.txt", "r", stdin);
    getline(cin,s);
    scanf("%d",&m);
    len = (int) s.length();
    for (int i = 0;i<len;i++)
        for (int j = 0;j<len;j++) {
            if (s[i] == s[j]) { same[i][j] = 1;}
        }
    for (int i = 0;i<=len;i++) {
        dp[i][0] = dp[0][i] = 1;
    }
    for (int i = 1;i<=len;i++) {
        printf("i = %d\n", i);
        for (int j = 1;j<=len;j++) {
            printf("    j = %d\n", j);
            if (same[i-1][j-1]) {
                dp[i][j] = (dp[i-1][j] + dp[i][j-1])%m;
            }
            else {
                dp[i][j] = ((dp[i-1][j] + dp[i][j-1])%m - dp[i-1][j-1]+m)%m;
            }
            printf("        dp[%d][%d] = %d\n", i, j, dp[i][j]);

        }
    }
    
    for (int i = 0;i<=len;i++) {
        for (int j = 0;j<=len;j++)
            cout << dp[i][j] << " " ;
        cout << endl;
    }
    
    printf("%d\n",dp[len][len]);
}