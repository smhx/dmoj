#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
typedef long long ll;
using namespace std;
int t,scores[100001],bit[100001],tmp[100001],cur=0; ll ans=0; 
inline bool cmp(const int &a,const int &b) {return scores[a] < scores[b];}
inline int sum(int x) {
    int s=0;
    for (;x;x-=x&-x) s+=bit[x];
    return s;
}
inline void update(int x){
    for (;x<=t;x+=x&-x) ++bit[x];
}

int solve() {
    int s=0;
    for (int i=1;i<=t;i++){
        for(int j=1;j<i;j++){
            if(scores[j]>scores[i]) ++s;
        }
        ++s;
    }
    return s;
}
int main() {
    int num;
    scan(num);
    scan(t);
    
    srand(time(NULL));
    while (num--) {
        ans=0;
        for (int i=1;i<=t;i++){
            // scan(scores[i]);
            scores[i]=rand()%1000000000+1;
            tmp[i]=i;
            bit[i]=0;
        }
        sort(tmp+1,tmp+t+1,cmp);
        for(int i=1;i<=t;i++) {
            int x;
            if (i==1) {
                x=1;
            } else if (scores[tmp[i]]!=cur) {
                x=scores[tmp[i-1]]+1;
            } else{
                x=scores[tmp[i-1]];
            }
            cur=scores[tmp[i]];
            scores[tmp[i]]=x;
        }
        for(int i=1;i<=t;i++){
            ans+=i-sum(scores[i]);
            update(scores[i]);
        }
        int k=solve();
        if (k!=ans){
            printf("WRONG!!\n");
            for (int i=1;i<=t;i++){
                printf("%d ", scores[i]);
            }
            printf("\n");
            return 0;
        } 
    }
    printf("All good\n");
    return 0;
}