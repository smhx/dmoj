#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;

typedef long long ll;

int N, M;
ll cnt=0;

struct Block {
    int c, r;
    Block(){}
    Block(int R, int C) : c(C), r(R) {}

    ll area() const {
        ll lN  = (ll)N;
        ll lr = (ll)r;
        return (lN-lr+1)*(lN-lr+2) >> 1;
    }

    int right() const {
        return c+N-r;
    }

    int left() const {
        return c;
    }

    bool operator < (const Block& b) const {
        return c==b.c ? b.right() > right() : c < b.c;
    }
};

ll intersection(const Block& a, const Block& b) {
    Block intr = Block(a.r+b.c-a.c, b.c);
    return intr.area();
}

Block blocks[100000];

int main() {
    scanf("%d%d", &N, &M);

    for (int i = 0; i < M; i++) scanf("%d%d", &blocks[i].r, &blocks[i].c);
    
    sort(blocks, blocks+M, less<Block>() );
    Block last;
    for (int i = 0; i < M; i++) {
        Block b = blocks[i];
        if (i==0) {
            last = b;
            cnt += b.area();
            continue;
        }

        if (b.right() <= last.right() && b.left() >= last.left() ) continue;
        if (b.left() > last.right()) {
            cnt += b.area();
            last = b;
            continue;
        }
        cnt += b.area()-intersection(last, b);
        last = b;
    }
    // if (cnt==5854217913023206){
    //     printf("N=%d,M=%d (%d, %d), (%d, %d)\n", N, M, blocks[0].r, blocks[0].c, blocks[1].r, blocks[1].c);
    //     return 0;
    // }
    printf("%lld\n", cnt);
    return 0;
}
