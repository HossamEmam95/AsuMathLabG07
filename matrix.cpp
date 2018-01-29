#include "header.h"
#include "cmath"
#define EPS 1e-10

Matrix::Matrix()
{
  num_rows = num_col = 0;
  values = NULL;
    name='\0';
}

Matrix::~Matrix()
{
reset();
}
Matrix::Matrix(string s)
{
  num_rows=num_col=0;
  values=NULL;
  copy(s);
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
          case MI_ZEROS: values[iR][iC]= 0; break;
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
  this-> name = m.name;
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
    name='\0';
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


// void Matrix::setSubMatrix(int r, int c, Matrix& m)
// {
//   if ((r+m.num_rows)>num_rows||(c+m.num_col)>num_col)
//     throw("Invalid matrix dimensions for this operation");
//
//     for(int iR =0; iR < num_rows; iR++)
//       for(int iC=0; iC<num_col; iC++)
//         values[iR+r][iC+c] = m.values[iR][iC];
// }
void Matrix::setSubMatrix(int r, int c, Matrix &m) {/////////////////////////////////////////
  if ((r + m.num_rows) > num_rows || (c + m.num_col) > num_col)
    throw("Invalid matrix dimension");
  for (int iR = 0; iR < m.num_rows; iR++)
    for (int iC = 0; iC < m.num_col; iC++)
      values[r + iR][c + iC] = m.values[iR][iC];
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




void Matrix::addColumn(Matrix &m) {
  Matrix n(max(num_rows, m.num_rows), num_col + m.num_col);
  n.setSubMatrix(0, 0, *this);
  n.setSubMatrix(0, num_col, m);
  *this = n;
}

void Matrix::addRow(Matrix &m) {
  Matrix n(num_rows + m.num_rows, max(num_col, m.num_col));
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


Matrix Matrix::gaussianEliminate()
{
    Matrix Ab(*this);
    int rows = Ab.num_rows;
    int cols = Ab.num_col;
    int Acols = cols - 1;

    int i = 0; // row tracker
    int j = 0; // column tracker

    // iterate through the rows
    while (i < rows)
    {
        // find a pivot for the row
        bool pivot_found = false;
        while (j < Acols && !pivot_found)
        {
            if (Ab(i, j) != 0) { // pivot not equal to 0
                pivot_found = true;
            } else { // check for a possible swap
                int max_row = i;
                double max_val = 0;
                for (int k = i + 1; k < rows; ++k)
                {
                    double cur_abs = Ab(k, j) >= 0 ? Ab(k, j) : -1 * Ab(k, j);
                    if (cur_abs > max_val)
                    {
                        max_row = k;
                        max_val = cur_abs;
                    }
                }
                if (max_row != i) {
                    Ab.swapRows(max_row, i);
                    pivot_found = true;
                } else {
                    j++;
                }
            }
        }

        // perform elimination as normal if pivot was found
        if (pivot_found)
        {
            for (int t = i + 1; t < rows; ++t) {
                for (int s = j + 1; s < cols; ++s) {
                    Ab(t, s) = Ab(t, s) - Ab(i, s) * (Ab(t, j) / Ab(i, j));
                    if (Ab(t, s) < EPS && Ab(t, s) > -1*EPS)
                        Ab(t, s) = 0;
                }
                Ab(t, j) = 0;
            }
        }

        i++;
        j++;
    }

    return Ab;
}

Matrix Matrix::rowReduceFromGaussian()
{
    Matrix R(*this);
    int rows = R.num_rows;
    int cols = R.num_col;

    int i = rows - 1; // row tracker
    int j = cols - 2; // column tracker

    // iterate through every row
    while (i >= 0)
    {
        // find the pivot column
        int k = j - 1;
        while (k >= 0) {
            if (R(i, k) != 0)
                j = k;
            k--;
        }

        // zero out elements above pivots if pivot not 0
        if (R(i, j) != 0) {

            for (int t = i - 1; t >= 0; --t) {
                for (int s = 0; s < cols; ++s) {
                    if (s != j) {
                        R(t, s) = R(t, s) - R(i, s) * (R(t, j) / R(i, j));
                        if (R(t, s) < EPS && R(t, s) > -1*EPS)
                            R(t, s) = 0;
                    }
                }
                R(t, j) = 0;
            }

            // divide row by pivot
            for (int k = j + 1; k < cols; ++k) {
                R(i, k) = R(i, k) / R(i, j);
                if (R(i, k) < EPS && R(i, k) > -1*EPS)
                    R(i, k) = 0;
            }
            R(i, j) = 1;

        }

        i--;
        j--;
    }

    return R;
}

Matrix Matrix::createIdentity(int size)
{
    Matrix temp(size, size);
    for (int i = 0; i < temp.num_rows; ++i) {
        for (int j = 0; j < temp.num_col; ++j) {
            if (i == j) {
                temp.values[i][j] = 1;
            } else {
                temp.values[i][j] = 0;
            }
        }
    }
    return temp;
}

Matrix Matrix::augment(Matrix A, Matrix B)
{
    Matrix AB(A.num_rows, A.num_col + B.num_col);
    for (int i = 0; i < AB.num_rows; ++i) {
        for (int j = 0; j < AB.num_col; ++j) {
            if (j < A.num_col)
                AB(i, j) = A(i, j);
            else
                AB(i, j) = B(i, j - B.num_col);
        }
    }
    return AB;
}


Matrix Matrix::inverse()
{
    Matrix I = Matrix::createIdentity(num_rows);
    Matrix AI = Matrix::augment(*this, I);
    Matrix U = AI.gaussianEliminate();
    Matrix IAInverse = U.rowReduceFromGaussian();
    Matrix AInverse(num_rows, num_rows);
    for (int i = 0; i < AInverse.num_rows; ++i) {
        for (int j = 0; j < AInverse.num_col; ++j) {
            AInverse(i, j) = IAInverse(i, j + num_col);
        }
    }
    return AInverse;
}



string Matrix::getString()
{
  string s = "[";
  for(int iR=0;iR<num_rows;iR++)
  {
    for(int iC=0;iC<num_col;iC++)
    {
      char buffer[50];
      sprintf(buffer, "%g ", values[iR][iC]);
      s += buffer;
    }
    s = s.substr(0, s.length()-1);
    s += "; ";
  }
  s = s.substr(0, s.length()-2);
  s += "]";
  return s;
}


void Matrix::swapRows(int r1, int r2)
{
    double *temp = values[r1];
    values[r1] = values[r2];
    values[r2] = temp;
}


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
  Matrix m(num_rows,num_col,0);
   for(int i=0;i<num_rows;i++)

     for(int j=0;j<num_col ;j++)
     {
        m.values[i][j]=((*this).values[i][j])*d;
     }
   return m;


}



Matrix Matrix::division(Matrix a, Matrix b)
{
Matrix c;
c=b.inverse();
c=a*c;
return c;
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

Matrix EYE(int n,int m){
	Matrix temp(n,m,2);
	return temp;
}

Matrix OptimizedPower(Matrix m,int power){
	Matrix temp = EYE(m.num_rows,m.num_col);
	if(power%2){
		temp =m;
		power-=1;
	}
	while(power > 0){
		Matrix n = m;
		double logarithm = floor(log2(power));
		for(int i =0;i <logarithm;i++){
			n *= n;
		}
		temp *= n;
		power -= pow(2,logarithm);
		cout<<"\n "<<power;
	}
	return temp;
}

Matrix Matrix::operator^(int power)
{
  Matrix q = *this;
  Matrix r = OptimizedPower(q,power);
  return r;
}



CComplex::CComplex()
{
  R = I = 0.0;
 }
CComplex::CComplex(double R, double I)
{
   this->R = R;
   this->I = I;
  }
//Optional copy constructor and copy //All attributes are statically allocated
CComplex::CComplex(const CComplex& C)
 {
   copy(C);
  }

CComplex::CComplex(string s)
{
	if(s.find(",") != std::string::npos){
		string first = s.substr(0, s.find(","));
		string second = s.substr(s.find(",") + 1, s.length() - s.find(",") - 1);
		R = atof(first.c_str());
		I = atof(second.c_str());
	}
	else{
		if (s.find("i") == std::string::npos)
		{
			R = atof(s.c_str());
			I = 0.0;
		}
		else if (s.find("i") != std::string::npos)
		{
			if ((s.find("+") == std::string::npos) && (s.find("-") == std::string::npos))
			{
				I = atof(s.c_str());
				R = 0.0;
			}
			else if (s.find("+") != std::string::npos)
			{
				string first = s.substr(0, s.find("+"));
				string second = s.substr(s.find("+") + 1, s.length() - s.find("+") - 1);
				if (first.find("i") == std::string::npos)
				{
					R = atof(first.c_str());
				}
				else if (first.find("i") != std::string::npos)
				{
					I = atof(first.c_str());
				}
				if (second.find("i") == std::string::npos)
				{
					R = atof(second.c_str());
				}
				else if (second.find("i") != std::string::npos)
				{
					I = atof(second.c_str());
				}
			}
			else if (s.find("-") != std::string::npos)
			{
				string first = s.substr(0, s.rfind("-"));
				string second = s.substr(s.rfind("-"), s.length() - s.find("-"));
				if (first.find("i") == std::string::npos)
				{
					R = atof(first.c_str());
				}
				else if (first.find("i") != std::string::npos)
				{
					I = atof(first.c_str());
				}
				if (second.find("i") == std::string::npos)
				{
					R = atof(second.c_str());
				}
				else if (second.find("i") != std::string::npos)
				{
					I = atof(second.c_str());
				}
			}
		}
	}
}

void CComplex::copy(const CComplex& C)
 {
   R = C.R;
   I = C.I;
 }
string CComplex::getString()
{
  char text[100];
  if(I==0)
  sprintf(text, "%g", R);
  else if(R==0)
  sprintf(text, "%gi", I);
  else if(I>0)sprintf(text, "%g+%gi", R, I);
  else if(I<0)sprintf(text, "%g-%gi", R, -I);
  return string(text);
 }
 double CComplex::magnitude()
 {
   return sqrt(R*R+I*I);
  }
double CComplex::angle() {
  return atan2(I, R);
}
void CComplex::negative() {
   R*=-1; I*=-1;
  }
double CComplex::real() {
   return R;
  }
double CComplex::imaginary()
 {
   return I;
  }
CComplex CComplex::addComplex(const CComplex& A,const CComplex& B)
 { CComplex C;
   C.R = A.R + B.R;
   C.I = A.I + B.I;
   return C;
 }
void CComplex::add(const CComplex& C)
{
   R += C.R;
   I += C.I;
 }
 CComplex CComplex::operator=(const CComplex& C)
  {
     copy(C);
     return *this;
    }
CComplex CComplex::operator=(double D)
{
  R = D;
  I = 0;
  return *this;
 }
void CComplex::operator+=(CComplex& C)
{
  add(C);
 }
void CComplex::operator-=(CComplex& C){
	R -= C.real();
	I -= C.imaginary();
}
CComplex CComplex::operator+=(double D)
{
   R += D;
  }
CComplex CComplex::operator+(CComplex& C)
{
  return addComplex(*this, C);
 }
CComplex CComplex::operator-(CComplex& C){
	CComplex negC = -C;
	CComplex result = *this + negC;
	return result;
}
CComplex CComplex::operator+(double D)
{
  return addComplex(*this, CComplex(D, 0));
 }
 CComplex CComplex::operator-()
 {
   return CComplex(-R, -I);
 }
CComplex CComplex::operator*(CComplex& A){
	double R = A.real()*this->real() - A.imaginary()*this->imaginary();
	double I = A.real()*this->imaginary() + A.imaginary()*this->real();
	return CComplex(R, I);
}
CComplex CComplex::operator/(CComplex& A){
	double conReal = A.real();
	double conImg = A.imaginary()*-1;
	CComplex con (conReal,conImg);
	CComplex don = A * con; 
	CComplex nom = *this * con;
	double resultReal = (nom.real()/don.magnitude());
	double resultImg = (nom.imaginary()/don.magnitude());
	CComplex result (resultReal,resultImg);
	return result;
}
void CComplex::operator/=(CComplex& A){
	CComplex temp = *this/A;
	R=temp.real();
	I = temp.imaginary();
}
void CComplex::operator*=(CComplex& A){
	double r = A.real()*R - A.imaginary()*I;
	
	double i = A.real()*I + A.imaginary()*R;
	R = r; 
	I = i;
}
CComplex::operator const string()
{
  return getString();
}


CComplex CComplex::operator++()
{
  R++;
  return *this;
}
CComplex CComplex::operator++(int)
{
  CComplex C = *this;
   R+=1;
    return C;
   }
double CComplex::operator[](string name)
{
  if(name=="magnitude")
  return magnitude();
  if(name=="angle")
  return angle();
   if(name=="real")
   return real();
   if(name=="imaginary")
   return imaginary();
   return 0.0;
  }
double CComplex::operator()(string name, string info)
{ if(name=="angle")
{
   if(info=="degree")
   return angle()*180.0/PI;
   if(info=="radian" || info.length()==0)
   return angle();
 }
return (*this)[name];
 }
CComplex CComplex::operator^(double D){
        if((D-(int)D) == 0){
		CComplex C = *this;
		for(int i = 1;i<D;i++){
			C *= *this; 
		}
		return C;
	}
	else{
		double mag = magnitude();
		double r = pow(mag,D);
		CComplex C(r,0);
		return C;
	}
}
void CComplex::operator^=(double d){
	*this=*this^d;
}
bool CComplex::operator<(CComplex &A)
{
	return magnitude() < A.magnitude();
}
bool CComplex::operator>(CComplex &A)
{
	return magnitude() > A.magnitude();
}
bool CComplex::operator<=(CComplex &A)
{
	return magnitude() <= A.magnitude();
}
bool CComplex::operator>=(CComplex &A)
{
	return magnitude() >= A.magnitude();
}
bool CComplex::operator==(CComplex &A)
{
	return magnitude() == A.magnitude();
	
}
