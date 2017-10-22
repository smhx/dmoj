/* **************************************
   File: bareiss.cc
   Purpose: Implementation of the Bareiss algorithm for
	computing determinants of matrices.  
	This version performs pivoting
	(cf. Gaussian.cc in ${CORE}/progs/gaussian)
	The book "Fundamental Problems of Algorithmic Algebra",
	by C.Yap (Oxford U.Press, 2000) treats this algorithm.
	The input matrix is hard-coded.
   Usage:
	% bareiss
   CORE Library, $Id: bareiss.cpp,v 1.1.1.1 2002/02/28 07:55:44 exact Exp $
 ************************************** */

#ifndef Level
#   define Level 3
#endif

#include <iostream>
#include <cassert>
#include <cstdlib>
using namespace std;
// #include "CORE.h"

class Matrix {
private:
  int     n;
  double* _rep;

public:
   Matrix(int d) : n(d) { _rep   = new double [n*n]; }
   Matrix(int d, double M[]);
   Matrix(int d, int M[]);
   Matrix(const Matrix&);
   const Matrix& operator=(const Matrix&);
   ~Matrix() { delete [] _rep; }
   const double& operator()(int r, int c) const { return _rep[r * n + c]; }
   double& operator()(int r, int c) { return _rep[r * n + c]; }
   double determinant() const;
   friend ostream& operator<<(ostream&, const Matrix&);
};

Matrix::Matrix(int d, double M[]) : n(d) {
   int i, j;
   _rep   = new double [n*n];
   for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
         _rep[i * n + j] = M[i * n + j];
}
Matrix::Matrix(int d, int M[]) : n(d) {
   int i, j;
   _rep   = new double [n*n];
   for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
         _rep[i * n + j] = M[i * n + j];
}

Matrix::Matrix(const Matrix& M) : n(M.n) {
   int i, j;
   _rep   = new double [n*n];
   for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
         _rep[i * n + j] = M._rep[i * n + j];
}

const Matrix& Matrix::operator=(const Matrix& M) {
   int i, j;
   if (n != M.n) {
      delete [] _rep;
      n = M.n;
      _rep = new double [n*n];
   }
   for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
         _rep[i * n + j] = M._rep[i * n + j];
   return *this;
}

double Matrix::determinant() const {
   Matrix A = *this;
   double det;
   int i, j, k;

   for (i = 0; i < n-1; i++) {
      // assert(a(i, i) == 0);
      for (j = i + 1; j < n; j++)
         for (k = i + 1; k < n; k++) {
            A(j,k) = (A(j,k)*A(i,i)-A(j,i)*A(i,k));
	    if (i) A(j, k) /= A(i-1,i-1);
         }
   }

   return A(n-1,n-1);
}


int main( int argc, char *argv[] ) {
  int n;
  cin >> n;
  double A[500];
  for (int i = 0; i < n*n;++i) cin >> A[i];
  Matrix m(n, A);
  cout << m.determinant() << endl;
  return 0;

}