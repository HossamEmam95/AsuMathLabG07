#include <iostream>
#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>
#include<curses.h>
#include <ncurses.h>

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
  Matrix(int num_rows, int num_col, int initialization= MI_ZEROS, double initializationValue = 0.0 );
  Matrix(int num_rows, int num_col, double first, ...);
  Matrix(Matrix& m);
  Matrix(double d);
  Matrix(std::string s);


//rawan
  void copy(Matrix& m);
  void copy(double d);
  //void copy(string s);
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
  Matrix operator++();//Pre Increment
  Matrix operator++(int);//Post Increment ,int is not used
  Matrix operator--();//Pre Increment
  Matrix operator--(int);//Post Increment ,int is not used

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
//end of Matrix Class


Matrix::Matrix()
{
  num_rows = num_col = 0;
  values = NULL;
}

Matrix::~Matrix()
{
reset();
}

Matrix::Matrix(int num_rows, int num_col, int initialization, double initializationValue)
{
    this->num_rows = num_rows;
    this->num_col = num_col;
    if((num_col*num_rows) == 0){values = NULL; return;}

    values = new double* [num_rows];
    for(int iR = 0; iR<num_rows; iR++ )
    {
      values[iR] = new double[num_col];
      for(int iC = 0; iC<num_col; iC++)
      {
        switch (initialization)
        {
          case MI_ZEROS: values[iR][iC];
          case MI_ONES: values[iR][iC] = 1; break;
          case MI_EYE: values[iR][iC] = (iR==iC)?1:0; break;
          case MI_RAND: values[iR][iC] = (rand()%1000000)/1000000.0; break;
          case MI_VALUE: values[iR][iC] = initializationValue; break;
        }
      }
    }
}


Matrix::Matrix(int num_rows,int num_col, double first, ...)
{
  this-> num_rows = num_rows;
  this-> num_col = num_col;
  if ((num_col*num_rows) == 0 ){values = NULL; return;}

  values = new double* [num_rows];
  va_list va;
  va_start(va, first);

  for(int iR=0; iR<num_rows; iR++ )
  {
    values[iR] = new double[num_col];

    for(int iC=0; iC<num_col; iC++)
    {
      values[iR][iC] = (iC==0 && iR==0)?first : va_arg(va, double);
    }
  }
  va_end(va);
}

Matrix::Matrix(Matrix& m)
{
  num_rows = num_rows = 0;
  values = NULL;
  copy(m);
}


void Matrix::copy(Matrix& m)
{
  reset();

  this-> num_rows = m.num_rows;
  this-> num_col = m.num_col;
  if ((num_col*num_rows) == 0 ){values = NULL; return;}

  values = new double*[num_rows];
  for(int iR=0;iR<num_rows;iR++)
  {
    values[iR] = new double[num_col];
    for(int iC=0;iC<num_col;iC++)
    {
    values[iR][iC] = m.values[iR][iC];
    }
  }
}

Matrix::Matrix(double d)
{
  num_rows = num_rows = 0;
  values = NULL;
  copy(d);
}


void Matrix::copy(double d)
{
  reset();

  this->num_rows = 1;
  this->num_col = 1;
  values = new double*[1];
  values[0] = new double[1];
  values[0][0] = d;
}



void Matrix::reset()
{
  if (values)
  {
    for(int i=0; i<num_rows; i++){delete[] values[i];}
    delete[] values;
  }
  num_rows = num_col = 0;
  values = NULL;
}


Matrix Matrix::operator=(Matrix& m)
{
  copy(m);
  return *this;
}

Matrix Matrix::operator=(double d)
{
  copy(d);
  return *this;
}

void Matrix::add(Matrix& m)
{
  if(num_rows!=m.num_rows||num_col!=m.num_col)
    throw("Invalid Matrix dimensions for add operation");

  for(int iR=0; iR<num_rows; iR++ )
    for(int iC=0; iC<num_col; iC++)
      values[iR][iC] += m.values[iR][iC];
}

void Matrix::operator+=(Matrix& m)
{
  add(m);
}

/*
void Matrix::operator+=(double d)
{
  add(Matrix(num_rows, num_col, MI_VALUE, d));
}
*/

Matrix Matrix::operator+(Matrix& m)
{
  Matrix r = *this;
  r += m;
  return r;
}

/*
Matrix Matrix::operator+(double d)
{
  Matrix r = *this;
  r += d;
  return r;
}
*/

void Matrix::sub(Matrix& m)
{
  if(num_rows!=m.num_rows||num_col!=m.num_col)
    throw("Invalid Matrix dimensions for sub operation");

  for(int iR=0; iR<num_rows; iR++ )
    for(int iC=0; iC<num_col; iC++)
      values[iR][iC] -= m.values[iR][iC];
}

void Matrix::operator-=(Matrix& m)
{
  sub(m);
}

/*
void Matrix::operator-=(double d)
{
  sub(Matrix(num_rows, num_col, MI_VALUE, d));
}
*/

Matrix Matrix::operator-(Matrix& m)
{
  Matrix r = *this;
  r -= m;
  return r;
}

/*
Matrix Matrix::operator-(double d)
{
  Matrix r = *this;
  r -= d;
  return r;
}
*/

void Matrix::mul(Matrix& m)
{
    if(num_rows!=m.num_rows||num_col!=m.num_col)
      throw("Invalid dimensions for mul operation");

    Matrix r(num_rows, m.num_col);

    for(int iR=0; iR<num_rows; iR++)
      for(int iC=0; iC<num_col; iC++)
      {
        r.values[iR][iC] = 0;
        for(int k=0; k<m.num_col; k++)
          r.values[iR][iC] += values[iR][iC] * m.values[k][iC];
      }
      copy(r);
}

void Matrix::operator*=(Matrix& m)
{
  mul(m);
}

void Matrix::operator*=(double d)
{
    for(int iR=0;iR<num_rows;iR++)
      for(int iC=0;iC<num_col;iC++)
        values[iR][iC] *= 9;
}


Matrix Matrix::operator*(Matrix& m)
{
  Matrix r = *this;
  r*=m;
  return r;
}


Matrix Matrix::operator*(double d)
{
  Matrix r = *this;
  r*=d;
  return r;
}

Matrix Matrix::operator++()
{
  const double d = 1.0;
  add(Matrix(num_rows, num_col, MI_VALUE, d));
  return  *this;
}






int main()
{

  return 0;
}
