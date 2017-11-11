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
