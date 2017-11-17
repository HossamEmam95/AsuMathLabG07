#include "header.h"

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

Matrix::Matrix(const Matrix& m)
{
  num_rows = num_rows = 0;
  values = NULL;
  copy(m);
}


void Matrix::copy(const Matrix& m)
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


Matrix Matrix::operator=(const Matrix& m)
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

void Matrix::operator*=(Matrix& m)
{
  mul(m);
}

void Matrix::operator*=(double d)
{
    for(int iR=0;iR<num_rows;iR++)
      for(int iC=0;iC<num_col;iC++)
        values[iR][iC] *= d;
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


Matrix Matrix::getSubMatrix(int r, int c, int nr, int nc)
{
  if((r+nr)>num_rows || (c+nc)>num_col  )throw("Invalid matrix dimension");

  Matrix m(nr, nc);
  for(int iR=0;iR<m.num_rows;iR++)
    for(int iC=0;iC<m.num_col;iC++)
      m.values[iR][iC] = values[r+iR][c+iC];
  return m;
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




Matrix Matrix::getMinormatrix()
{
Matrix c(num_rows,num_col,0);
Matrix m;
double d;
for(int i=0;i<num_rows;i++)
for(int j=0;j<num_col;j++)
{

m=this->getCofactor(i,j);
d=m.getDeterminant();
c.values[i][j]=d;




}

return c;


}


Matrix Matrix::cofactor()
{
 Matrix c(num_rows,num_col,0);
 c=this->getMinormatrix();



 for(int i=0;i<num_rows;i++)
  for(int j=0;j<num_col;j++)
   {
    if((i+j)%2==1)
    c.values[i][j]=-c.values[i][j];
    else
    c.values[i][j]=c.values[i][j];




   }
   return c;





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
string Matrix::getString()
{
string s;
for(int iR=0;iR<num_rows;iR++)
{
for(int iC=0;iC<num_col;iC++)
{
char buffer[50];
sprintf(buffer, "%g\t", values[iR][iC]);
s += buffer;
}
s+="\n";
}
return s;
}

// istream& operator >> (istream &is, Matrix& m)
// {
//   string s;
//   getline(is, s, ']');
//   s+="]";
//   m = Matrix(s);
//   return is;
// }
// ostream& operator << (ostream &os, Matrix& m)
// {
//   os<<m.getString();
//   return os;
// }

Matrix Matrix::getTranspose()

{

  Matrix temp(num_col, num_rows, 0);

  for(int iR=0;iR<num_rows;iR++)
 {
   for(int iC=0;iC<num_col;iC++)

   {
   temp.values[iC][iR] = values[iR][iC];
   }
 }
 return temp;
}

Matrix Matrix::multiply_by_no( double d)
{
  Matrix m;
  m=*this;
   for(int i=0;i<num_rows;i++)

     for(int j=0;j<num_col ;j++)
     {
        m.values[i][j]=(m.values[i][j])*d;
     }
   return m;


}




Matrix Matrix::inverse()
{
  Matrix c;
  Matrix s;
  Matrix inversed_mat;
  c=*this;

  double d,one_over_det;
  d=(*this).getDeterminant();

  one_over_det=1/d;

  c=this->cofactor();

  s=c.getTranspose();

  inversed_mat=s.multiply_by_no(one_over_det);

  return inversed_mat;






}

Matrix Matrix::division(Matrix a, Matrix b)
{
Matrix output;
Matrix c;
c=b.inverse();
output=a*c;
return output;
}


Matrix Matrix::operator/(Matrix b)
{
   Matrix c;
   c=this->division(*this,b);
   return c;


}

Matrix Matrix::operator/(double d)
{
Matrix c;
double number=1/d;
c=this->multiply_by_no(number);
return c;

}

void Matrix::operator/=( Matrix b)
{
*this=this->division(*this,b);


}

void Matrix::operator/=(double b)
{
  double number =1/b;

*this=this->multiply_by_no(number);


}
