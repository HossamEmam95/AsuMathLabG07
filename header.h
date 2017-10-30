#include <iostream>
#include <ostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>
#include<curses.h>
#include <ncurses.h>
#include <algorithm>
using namespace std;


class Matrix{

  int num_rows, num_col;

public:

  double** values;


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
  Matrix(string s);


//rawan
  void copy(Matrix& m);
  void copy(double d);
  void copy(string s);
  void reset();

  string getString();



//hossam
  void add(const Matrix & m);

  void sub(const Matrix& m);

//hussien
  void mul(const Matrix& m);

//Doaa & zeinab
  void div(Matrix& m);


//bahnsasay

//saber


//mostafa
  void setSubMatrix(int iR,int iC, Matrix& m);
  Matrix getSubMatrix(int r, int c, int nr, int nc);
  Matrix getCofactor(int r, int c);

  void addColumn(Matrix& m);
  void addRow(Matrix& m);

//samir


  int getn(){return num_rows*num_col;};
  int getnR(){return num_rows;};
  int getnC(){return num_col;};
//doaa & zienab
  double getDeterminant();
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
  //  if((num_col*num_rows) == 0){values = NULL; return;}

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
//  if ((num_col*num_rows) == 0 ){values = NULL; return;}

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


void Matrix::copy(string s)
{
  reset();

  char* buffer = new char[s.length()+1];
  strcpy(buffer, s.c_str());
  char* lineContext;
  const char* lineSeparators = ";\r\n";
  char* line = strtok_r(buffer, lineSeparators, &lineContext);
  while(line)
    {
      Matrix row;
      char* context;
      const char* separators = " []";
      char* token = strtok(line, separators, &context);
        while(token)
        {
          Matrix item = atof(token);
          row.addColumn(item);
          token = strtok_r(NULL, separators, &context);
        }
        if(row.num_col>0 && (row.num_col==num_col || num_rows==0))
        addRow(row);
        line = strtok_r(NULL, lineSeparators, &lineContext);
    }
    delete[] buffer;
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

void Matrix::add(const Matrix& m)
{
  if(num_rows!=m.num_rows||num_col!=m.num_col)
    throw("Invalid Matrix dimensions for add operation");

  for(int iR=0; iR<num_rows; iR++ )
    for(int iC=0; iC<num_col; iC++)
       m.values[iR][iC]+=values[iR][iC];
}
void Matrix::mul(const Matrix& m)
{
    if(num_col!=m.num_rows)
      throw("Invalid dimensions for mul operation");

    Matrix r(num_rows, m.num_col);
	for(int i=0;i<num_rows;i++)
		for(int s=0;s<m.num_col;s++)
		{
			r.values[i][s] = 0;
		}

    for(int iC=0; iC<num_col; iC++)
      for(int iR=0; iR<num_rows; iR++)
      {
        for(int k=0; k<m.num_col; k++)
          r.values[iR][k] += values[iR][iC] * m.values[iC][k];
      }
      copy(r);
}



void Matrix::setSubMatrix(int r, int c, Matrix& m)
{
  if ((r+m.num_rows)>num_rows||(c+m.num_col)>num_col)
    throw("Invalid matrix dimensions for this operation");

    for(int iR =0; iR < num_rows; iR++)
      for(int iC=0; iC<num_col; iC++)
        values[iR+r][iC+c] = m.values[iR][iC];
}


Matrix Matrix::getSubMatrix(int r, int c, int nr, int nc)
{
  if((r+nr)>num_rows || (c+nc)>num_col  )throw("Invalid matrix dimension");

  Matrix m(nr, nc);
  for(int iR=0;iR<m.num_rows;iR++)
    for(int iC=0;iC<m.num_col;iC++)
      m.values[iR][iC] = values[r+iR][c+iC];
  return m;
}


void Matrix::addColumn(Matrix& m)
{
  Matrix n(max(num_rows, m.num_rows), num_col+m.num_col);
  n.setSubMatrix(0, 0, *this);
  n.setSubMatrix(0, num_col, m);
  *this = n;
}

void Matrix::addRow(Matrix& m)
{
  Matrix n(num_rows+n.num_rows, max(num_col,m.num_col));
  n.setSubMatrix(0, 0, *this);
  n.setSubMatrix(num_rows, 0, m);
  *this = n;
}


Matrix Matrix::getCofactor(int r, int c)
{
  if(num_rows<=1 || num_col<=1)throw("Invalid matrix dimensions");

  Matrix m(num_rows-1, num_col-1);

  for(int iR=0; iR<m.num_rows; iR++)
    for(int iC=0; iC<m.num_col; iC++)
    {
      int sR = (iR<r)? iR : iR+1;
      int sC = (iC<c)? iC : iC+1;
      m.values[iR][iC] = values[sR][sC];
    }
    return m;
}


double Matrix::getDeterminant()
{
  if(num_rows!=num_col)throw("Invalid matrix dimensions");
  if(num_rows==1 && num_col==1)return values[0][0];

  double value = 0 , m = 1;
  for(int iR=0; iR<num_rows; iR++)
  {
    value+= m * values[0][iR] * getCofactor(0, iR).getDeterminant(); m *= -1;
  }
  return value;
}

/*
istream& operator >> (istream &is, Matrix& m)
{
  string s;
  getline(is, s, ']');
  s+="]";
  m = Matrix(s);
  return is;
}

ostream& operator << (ostream &os, Matrix& m)
{
  os<<m.getString();
  return os;
}

*/

int main()
{
  Matrix m(2, 2, 5.0,7.0,6.0,9.0);
  Matrix n(2, 2, 3.0,2.0,3.0,4.0);
  Matrix e("1,2,3;1,2,3");


//   n.add(m);
//
//   for(int i=0; i<2; i++)
//   {
//     for(int j=0; j<2; j++)
//     {
//       cout<<m.values[i][j]<<endl;
//
//     }
//     cout<<endl;
//   }
// cout<<m.getDeterminant()<<endl;
//
// m.copy(n);
// for(int i=0; i<2; i++)
// {
//   for(int j=0; j<2; j++)
//   {
//     cout<<m.values[i][j]<<endl;
//
//   }
//   cout<<endl;
// }


  return 0;
}
