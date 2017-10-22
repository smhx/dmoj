#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstdint>
typedef long long ll;
ll own, friends[2];
int S[2];
int T, N, Q;

int bruteForce() {
    int max = -1;
    for (ll test = 0; test < (1LL <<Q); ++test) {
        int sumOwn=0, sumZero=0, sumOne=0;
        for (int i = 0; i < Q; ++i) {
            ll o, z, one;
            o = own&(1LL<<i);
            z = friends[0]&(1LL<<i);
            one = friends[1]&(1LL<<i);
            ll tester = test & (1LL<<i);
            if ((o^tester)==0) ++sumOwn;
            if ((z^tester)==0) ++sumZero;
            if ((one^tester)==0) ++sumOne;
        }
        if (sumZero==S[0] && sumOne==S[1] && max < sumOwn) {
            max = sumOwn;
        }
    }
    return max;
}

int bf() {
    int max = -1;
    for (ll test = 0; test < (1LL<<Q); ++test) {
        int sumFriend=0, sumOwn=0;
        for (int i = 0; i < Q; ++i) {
            ll tester = test&(1LL<<i);
            if ( (own&(1LL<<i)) == tester) ++sumOwn;
            if ( (friends[0]&(1LL<<i))==tester )++sumFriend;
        }
        if (sumFriend==S[0] && max < sumOwn) max = sumOwn;
    }
    return max;
}

void input(ll& x) {
    for (int j = 0; j < Q; ++j) {
        // char c;
        // scanf(" %c", &c);
        if (rand()%2) x |= 1LL << j;
    }
    printf("x=%lld\n", x);
}

int main() {
    srand(time(NULL));
    scanf("%d%d", &T, &Q);
    N=1;
    for (int t = 1; t <= T; ++t) {
        // scanf("%d%d", &N, &Q);
        for (int i = 0; i < N; ++i) {
            input(friends[i]);
        }
        input(own);
        // for (int i = 0; i < N; ++i) scanf("%d", S+i);
        S[0] = rand()%Q;
        if (N==1) {
            int a = 0;
            for (int i = 0; i < Q; i++) {
                a += ( (own & (1LL << i)) == (friends[0] & (1LL << i)) ) ? 1 : 0;
            } 
            printf("Case #%d: own=%lld, friend=%lld, S=%d, norm=%d. bruteForce=%d\n", t, own, friends[0], S[0], Q-std::abs(S[0]-a), bf());
        } else {
            int b[4];
            for (int i = 0; i < Q; i++) {
                ll mine = own & (1LL << i);
                ll one = friends[0] & (1LL << i);
                ll two = friends[1] & (1LL << i);
                if ( (mine^one) ==0) {
                    if ( (one^two) ==0) {
                        ++b[0];
                    } else {
                        ++b[2];
                    }
                } else {
                    if ((mine^two)==0) {
                        ++b[3];
                    } else {
                        ++b[1];
                    }
                }
            }
            for (int i = 0; i < 4; ++i) printf("b[%d]=%d\n", i, b[i]);
            int sum[2];
            sum[0]=S[0]-b[1]-b[3];
            sum[1]=S[1]-b[1]-b[2];
            int max = -1;
            for (int x0 = 0; x0 <= b[0]; ++x0) {
                for (int x1 = 0; x1 <= b[1]; ++x1) {
                    for (int x2 = 0; x2 <= b[2]; ++x2) {
                        for (int x3 = 0; x3 <= b[3]; ++x3) {
                            if (sum[1]==(x0-x1-x2+x3) && sum[0]==(x0-x1+x2-x3) && max < (x0+x1+x2+x3) ) {
                                max = x0+x1+x2+x3;
                                printf("x0=%d, x1=%d, x2=%d, x3=%d\n", x0, x1, x2, x3);
                            }
                        }
                    }
                }
            }
            printf("Case #%d: %d. Brute force is %d\n", t, max, bruteForce());
            // printf("Case #%d: %d\n", t, bruteForce());
        }
    }
}
/*

int main() {
    srand(time(NULL));
    scanf("%d%d", &T, &Q);
    for (int t = 1; t <= T; ++t) {
        ll test = rand()%(1LL<<Q);
        own = rand()%(1LL<<Q);
        friends[0]=rand()%(1LL<<Q);
        S[0] = rand()%Q;
        int a = 0;
        for (int i = 0; i < Q; i++) {
            a += (((own & (1LL << i))^(friends[0] & (1LL << i)))==0) ? 1 : 0;
        } 
        int n = Q-std::abs(S[0]-a);
        int b = bf();
        if (n!=b) {
            printf("MISTAKE on t=%d\n", t);
            printf("test=%lld, own=%lld, friend=%lld, S=%d\n", test, own, friends[0], S[0]);
            printf("normal = %d, b = %d\n", n, b);
            return 0;
        }
        // printf("Normal=%d. bruteForce=%d\n", Q-std::abs(S[0]-a), bf());
    }
    printf("ok\n");
}
*/