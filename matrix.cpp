#include <iostream>
#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>
#include<curses.h>
#include <ncurses.h>
#include <fstream>
#include <cstring>
#include <algorithm>
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
  Matrix(int num_rows,int num_col,double data[]);
//rowan
  Matrix(int num_rows, int num_col, int initialization= MI_ZEROS, double initializationValue = 0.0 );
  Matrix(int num_rows, int num_col, double first, ...);
  Matrix(Matrix& m);
  Matrix(double d);
  Matrix(std::string s);


//rawan
  void copy(Matrix& m);
  void copy(double d);
  void copy(string s);
  void reset();

  string getString();

  Matrix operator=(Matrix& m);
  Matrix operator=(double d);
  Matrix operator=(string s);

//hossam
  void add(const Matrix& m);
  void operator+=(Matrix& m);
  void operator+=(double d);
  Matrix operator+(Matrix& m);
  Matrix operator+(double d);


  void sub(const Matrix& m);
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
Matrix::Matrix(int num_rows,int num_col,double data[])
{
    this->num_rows =num_rows;
    this->num_col =num_col;
    if((num_col*num_rows) == 0){values = NULL; return;}
    values=new double* [num_rows];
    int data_count=0;
    for (int iR=0;iR<num_rows;iR++)
    {
        values[iR] =new double[num_col];
        for (int iC=0;iC<num_col;iC++)
        {
            values[iR][iC] = data[data_count];
            data_count++;
        }
    }

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

/*
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
      char* token = strtok_r(line, separators, &context);
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

*/

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

void Matrix::add(const Matrix& m)
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


void Matrix::operator+=(double d)
{
  add(Matrix(num_rows, num_col, MI_VALUE, d));
}


Matrix Matrix::operator+(Matrix& m)
{
  Matrix r = *this;
  r += m;
  return r;
}


Matrix Matrix::operator+(double d)
{
  Matrix r = *this;
  r += d;
  return r;
}


void Matrix::sub(const Matrix& m)
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


void Matrix::operator-=(double d)
{
  sub(Matrix(num_rows, num_col, MI_VALUE, d));
}


Matrix Matrix::operator-(Matrix& m)
{
  Matrix r = *this;
  r -= m;
  return r;
}


Matrix Matrix::operator-(double d)
{
  Matrix r = *this;
  r -= d;
  return r;
}


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

Matrix Matrix::operator++(int)
{
  Matrix c = *this;
  add(Matrix(num_rows, num_col, MI_VALUE, 1.0));
  return  c;
}


Matrix Matrix::operator--()
{
  add(Matrix(num_rows, num_col, MI_VALUE, -1.0));
  return *this;
}

Matrix Matrix::operator--(int)
{
  Matrix c = *this;
  add(Matrix(num_rows, num_col, MI_VALUE, -1.0));
  return  c;
}

Matrix Matrix::operator-()
{
  for(int iR=0;iR<num_rows;iR++)
    for(int iC=0;iC<num_col;iC++)
      values[iR][iC] = -values[iR][iC];
  return *this;
}

Matrix Matrix::operator+()
{
  return *this;
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
void Write()
{
	string a = "A = [7.3 4.8; 3.8 7.2; 3.4 7.5];";
	string b = "B = [1.2 5.7 4.2 1.4; 6.3 2.5 8.1 3.1; 6.4 2.8 7.1 8.1; 3.2 5.1 7.2 6.2];";
	string c = "C = A + B";
	string d = "D = A - B";
	string e = "E = A * B";
	string f = "F = A / B";
	string g = "G = 1 ./ A";
	string h = "H = C'";
	ofstream myfile;
	myfile.open("E:\Learning\College\Software Engineering\TryAgain.txt");
	if (!myfile.bad())
	{
		myfile << a << "\n" << b << "\n\n" << c << endl << d << endl << e << endl << f << endl << g << endl << h << endl;
		myfile.close();
	}
	else
		cout << "File write failed." << endl;
}
string FirstMatrix, SecondMatrix, FirstOp, SecOp, ThirdOp, FourthOp, FifthOp, SixthOp;
string Rubbish;
void inputFile()
{
	ifstream infile;
	infile.open("E:\Learning\College\Software Engineering\TryAgain.txt");
	getline(infile, FirstMatrix);
	getline(infile, SecondMatrix);
	getline(infile, Rubbish);
	getline(infile, FirstOp);
	getline(infile, SecOp);
	getline(infile, ThirdOp);
	getline(infile, FourthOp);
	getline(infile, FifthOp);
	getline(infile, SixthOp);
	infile.close();
}
void getDimension(string s,int &nR,int &nC)
{
	nR = 0;
	int nSpaces = 0;
	nC = 1;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ';')
		{
			nR++;
		}
		if (s[i] == ' ')
		{
			nSpaces++;
		}
	}
	nC = nSpaces / nR;
}
string remove(char* charToRemove, string &str) {
	for (unsigned int i = 0; i < strlen(charToRemove); ++i)
	{
		str.erase(remove(str.begin(), str.end(), charToRemove[i]), str.end());
	}
	return str;
}
void MatrixOptimization(string s, double x[1024])
{
	int pos1 = s.find("[");
	int pos2 = s.find_last_of("]");
	s = s.substr(pos1 + 1, pos2 - pos1 - 1);
	remove(";", s);
	replace(s.begin(), s.end(), ' ', ',');
	char num[10];
	strcpy(num, s.c_str() + ',');
	for (int a = 0; a < s.length(); a++)
	{
		string o;
		int index;
		if (s[a] == ',')
		{
			static int count = -1;
			o = s.substr(count + 1, a - count - 1);
			count = a;
			index = 1;
		}
		while ((a < s.length()) && (index == 1))
		{
			static int i = 0;
			strcpy(num, o.c_str());
			x[i] = atof(num);
			index = 0;
			i++;
		}
	}
}
char OpCode(string s)
{
	char op = 'a';
	for (int i = 0; i < s.length(); i++)
	{
		if ((int)s[i] == 43)
		{
			op = '+';
		}
		if ((int)s[i] == 45)
		{
			op = '-';
		}
		if ((int)s[i] == 42)
		{
			op = '*';
		}
		if (((int)s[i] == 46)&& ((int)s[i+1] == 47))
		{
			op = '.';
		}
		if (((int)s[i] == 47)&& ((int)s[i-1] != 46))
		{
			op = '/';
		}
		if ((int)s[i] == 39)
		{
			op = '1';
		}
	}
	return op;
}
int main()
{
  Write();
	inputFile();
	double x[1024];
  int num_row, num_col;
	getDimension(FirstMatrix,num_row,num_col);
  MatrixOptimization(FirstMatrix,x);
  Matrix A(num_row,num_col,x);
  double y[1024];
  int num_row_B, num_col_B;
  getDimension(SecondMatrix,num_row_B,num_col_B);
  MatrixOptimization(SecondMatrix,y);
  Matrix B(num_row_B,num_col_B,y);
	cout << x[2] << endl;
	cout << "First Matrix: " << FirstMatrix << endl << "Second Matrix: " << SecondMatrix << endl << FirstOp << endl << SixthOp << endl;
  cout << num_row << endl << num_col << endl;
	cout << OpCode(FirstOp) << endl;
	cout << OpCode(SecOp) << endl;
	cout << OpCode(ThirdOp) << endl;
	cout << OpCode(FourthOp) << endl;
	cout << OpCode(FifthOp) << endl;
	cout << OpCode(SixthOp) << endl;
	return 0;
}
