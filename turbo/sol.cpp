#include <iostream>

#define MAXN 100001

using namespace std;

int N, bit[MAXN], pos[MAXN];

void add(int idx, int val){
    printf("update %d by %d\n", idx, val);
    while(idx <= MAXN){
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int n){
    int ans = 0;
    while(n > 0){
        ans += bit[n];
        n -= (n & -n);
    }
    return ans;
}

int sum(int a, int b){
    printf("sum(%d, %d) = ", a, b);
    if (a == 1) {
        int ans = query(b);
        printf("%d\n", ans);
        return ans;
    }
    int ans= query(b) - query(a - 1);
    printf("%d\n", ans);
    return ans;
}

int main(){
    freopen("data.txt", "r", stdin);
    cin.sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N;
    for (int i = 1, x; i <= N; i++){
        cin >> x;
        add(i, 1);
        pos[x] = i;
    }

    for (int i = 1; i <= N; i++){
        if (i % 2 == 1){
            int num = (i + 1) / 2;
            add(pos[num], -1);
            printf("i = %d, num = %d, pos[num] = %d\n", i, num, pos[num]);

            cout << sum(1, pos[num]) << "\n";
        } else {
            int num = N - i / 2 + 1;
            add(pos[num], -1);
            cout << sum(pos[num], N) << "\n";
        }
    }
}
