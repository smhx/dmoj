#include <cstdint> 
#include <iostream>
#include <ctime>
#define ui64 uint64_t
#define i128 __int128_t

using namespace std;

class MillerRabinPrime {
private:
    ui64 modFromPower(ui64 a, ui64 b, ui64 c);
    ui64 randomNumberBetween(ui64 a, ui64 b);
    int primesToTest;
    int iterations;
    const int smallPrimes[30]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
        41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 
        109, 113};
public:
    MillerRabinPrime(int it, int p) : iterations(it){
        primesToTest = (p<30) ? p : 30;
        srand(time(NULL));
    }
    bool isPrime(ui64 N);
};

ui64 MillerRabinPrime::modFromPower(ui64 a, ui64 b, ui64 c){
    ui64 r=1;

    while ( b>0 ) {
        if ( (b & 1) == 1 )
            r = (i128)a*r % c; // Use for big primes only
            // r = a*r % c;

        b >>= 1;
        a = (i128)a*a % c; // Use for big primes only
        // a = a*a % c;
     }

  return r;
}

ui64 MillerRabinPrime::randomNumberBetween(ui64 a, ui64 b) {
    ui64 r = ( (ui64)(rand())<<32 ) | rand();
    return a + (ui64)((double)(b-a+1)*r/(UINT64_MAX+1.0));
}

bool MillerRabinPrime::isPrime(ui64 N) {
    if (N<=1) return false;
    for (int i = 0; i < primesToTest; i++) {
        if (N==smallPrimes[i]) return true;
        if (N%smallPrimes[i]==0) return false;
    }
    int s=0;
    for (ui64 m=N-1; !(m&1); ++s, m >>= 1){}

    ui64 d = (N-1)/(1<<s);
    for (int i=0; i < iterations; i++) {
        ui64 a=randomNumberBetween(2, N-2);
        ui64 x=modFromPower(a, d, N);
        if ( x == 1 || x == N-1 )
            continue;
        for ( int r = 1; r <= s-1; ++r ) {
          x = modFromPower(x, 2, N);
          if ( x == 1 ) return false;
          if ( x == N - 1 ) goto LOOP;
        }
        return false;
LOOP:
        continue;
    }
    return true;

}

int main () {
    MillerRabinPrime mrp(5, 30);
    ui64 N;
    cin >> N;
    while(!mrp.isPrime(N)){
        ++N;
    }
    cout << N << endl;
    return 0;
}