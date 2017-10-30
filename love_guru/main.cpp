#include <cstdio>
#include <cstring>
#include <string>
#define MAXL 1000006

char A[MAXL], B[MAXL];

int qpow(int b, int e) {
    if (e==0) return 1;
    int half = qpow(b, e/2);
    return (half*half*(e&1 ? b : 1) )%10;
}

int main() {
    freopen("data.txt", "r", stdin);
    scanf(" %s %s", A, B);
    int amod = 0,bmod=0;
    for (int i = 0; i < strlen(A); ++i) {
        if (isupper(A[i])) A[i] = tolower(A[i]);
        amod = (amod + qpow((A[i]-'a'+1)%10, i+1)) % 10;
    }
    if (amod==0) amod = 10;
    for (int i = 0; i < strlen(B); ++i) {
        if (isupper(B[i])) B[i] = tolower(B[i]);
        bmod = (bmod + qpow((B[i]-'a'+1)%10, i+1)) % 10;
    }
    if (bmod==0) bmod = 10;
    printf("%d\n", amod+bmod);
}