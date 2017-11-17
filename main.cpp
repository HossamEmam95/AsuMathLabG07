#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>
//#include <curses.h>
//#include <ncurses.h>
#include "header.h"
using namespace std;

void print(Matrix m )
{
  for(int i=0; i<m.num_rows; i++)
  {
    for(int j=0; j<m.num_col; j++)
    {
      cout<<m.values[i][j]<<" ";
    }
    cout<<endl;
  }
}

int main()
{
  Matrix c(3, 3, -1.443, 0.3246, 1.82425, -1.663, -0.557, 3.9724, 0.409, 0.0868, 0.6839);
  Matrix n(3,3,3.0,0.0,2.0,2.0,0.0,-2.0,0.0,1.0,1.0);
  Matrix m(3, 3, 1.2, 2.1, 3.4, 4.1, 7.2, 3.4, 7.1, 5.2, 4.6);
  Matrix a(2,2,1.0,2.0,2.0,2.0);
  Matrix b(2,2,3.0,2.0,1.0,1.0);
  cout<<">>>"<<"Matrix A ="<<endl;;
  print(n);
  cout<<">>> "<<"Matrix B ="<<endl;;
  print(m);
  cout<<">>> "<<"A + B = "<<endl;
  print(m+n);
  cout<<">>> "<<"A - B = "<<endl;
  print(n-m);
  cout<<">>> "<<"A * B = "<<endl;
  print(m*n);
  cout<<">>> "<<"B / A = "<<endl;
  print(c);
  cout<<">>> "<<"A' = "<<endl;
  Matrix k = n.getTranspose();
  Matrix d = n.inverse();
  print(d);


  print(k);

Matrix l;
l=a/b;
print(l);

string s ="[7.3 4.8; 3.8 7.2; 3.4 7.5]";
//  Matrix w;
  Matrix w (s);
  print(w);


  return 0;
}
