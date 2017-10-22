#include <iostream>
using namespace std;
int n; double A[500][500];
double det() {
    int i, j, k;
    for (i=0;i<n-1;++i){
        for(j=i+1;j<n;++j){
            for(k=i+1;k<n;++k){
                A[j][k]=A[k][k]*A[i][i]-A[j][i]*A[i][k];
                if (i) A[j][k] /= A[i-1][i-1];
            }
        }
    }
    return A[n-1][n-1];
}

int main() {
    cin >> n;
    for (int i=0;i<n;++i){
        for (int j=0;j<n;++j){
            cin >> A[i][j];
        }
    }
    cout << det() << endl;
    return 0;
}