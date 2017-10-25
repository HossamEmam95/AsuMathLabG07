#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
class Matrix{

  int num_rows, num_col;

  double** values;

public:
  //hussien
  Matrix();
  ~Matrix();
//Doaa
 enum MI{MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE};

//rowan
  Matrix(int num_rows, int num_col, double first, ...);
  Matrix(Matrix& m);
  Matrix(double d);
  Matrix(std::string s);


//rawan
  void copy(Matrix& m);
  void copy(double d);
  void copy(std::string s);
  void reset();

  string getString();

  Matrix operator=(Matrix& m);
  Matrix operator=(double d);
  Matrix operator=(string s);

//hossam
  void add(Matrix& m);
  void operator+=(Matrix& m);
  void operator+=(double d);
  Matrix operator+(Matrix& m);
  Matrix operator+(double d);


  void sub(Matrix& m);
  void operator-=(Matrix& m);
  void operator-=(double d);
  Matrix operator-(Matrix& m);
  Matrix operator-(double d);

//hussien
  void mul(Matrix& m);
  void operator*=(Matrix& m);
  void operator*=(double d);
  Matrix operator*(Matrix& m);
  Matrix operator*(double d);

//Doaa & zeinab
  void div(Matrix& m);
  void operator/=(Matrix& m);
  void operator/=(double d);
  Matrix operator/(Matrix& m);
  Matrix operator/(double d);

//bahnsasay
  Matrix operator ++();//Pre Increment
  Matrix operator ++(int);//Post Increment ,int is not used
  Matrix operator --();//Pre Increment
  Matrix operator --(int);//Post Increment ,int is not used

  Matrix operator-();
  Matrix operator+();

//saber
  friend istream& operator  >> (istream &is, Matrix&m);//Stream
  friend istream& operator  << (ostream &os, Matrix&m);//Stream

//mostafa
  void setSubMatrix(int iR,int iC, Matrix& m);
  Matrix getSubMatrix(int r, int c, int nr, int nc);
  Matrix getCofactor(int r, int c);

  void addColumn(Matrix& m);
  void addRow(Matrix& m);

//samir
  double& operator[](int i){return values[i/num_col][i%num_col];}
  double& operator()(int i){return values[i/num_col][i%num_col];}
  double& operator()(int r, int c){return values[r][c];}

  int getn(){return num_rows*num_col;};
  int getnR(){return num_rows;};
  int getnC(){return num_col;};
//doaa & zienab
  double getDeteminant();
  double getTranspose();
  double getInverse();
  
};



int main()
{

  return 0;
}
