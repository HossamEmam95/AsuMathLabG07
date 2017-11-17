#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>
#include <fstream>
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


bool lineTest(string s) //function returns true if line, false if operation

{

	bool index = false;

	for (int i = 0; i < s.length(); i++)

	{

		if (s[i] == '[')

		{

			index = true;

		}

	}

	return index;

}

string* inputfile(string s,int &nlines) //function returns lines from file (s) on array of strings

{

	std::ifstream infile;

	infile.open(s.c_str());

	string line;

	int i = 0;

	string *lines = new string[10];

	if (infile.bad())
	{
		cout << "Error opening the file!" << endl;
	}
	while (getline(infile, line))
	{
		if ((line.length() > 2))
		{
			lines[i] = line;
			i++;
		}
	}

	nlines = i;

	infile.close();

	return lines;

}

void getMatrixDimension(string s, int &nR, int &nC) //Function gets num_colums,num_rows

{
		nR = 1;
		int nSpaces = 1;
		nC = 1;
		for (int i = s.find('['); i < s.find(']'); i++)
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

void strignParsing(string s, string m, char *Name) //function returns array of double values, name of the matrices
{
	int n = 0, m = 0;
	char *newline = new char[100];
	char *variables = new char[100];
  strcpy(newline, s.c_str() + s.rfind('='))
	m = newline;
	s.erase(s.begin() + s.rfind("="), s.end());
	strcpy(variables, s.c_str());
	char* tokeName = strtok(variables, spearators);
	while (tokeName)//making array of variables names
	{
		Name[m] = *tokeName;
		m++;
		tokeName = strtok(NULL, spearators);
	}
}
void operationParsing(string s, char& in1, char& in2, char& out, char& operation) //function parses operation line to in1,in2,out,operation
{
	int nLoop = 0;
	int noOpcode = 0;
	for (int i = 0; i < s.length(); i++)
	{
		int ASCII = (int)s[i];
		if ((ASCII != 32) && (ASCII != 62)) //ascii code of "space" and "="
		{
			int op = 0;
			if (((ASCII >= 65) && (ASCII <= 90)) || ((ASCII >= 97) && (ASCII <= 122))) //ascii code of(letters Upper and lower)
			{
				op = 1;
				if (nLoop == 0)
				{
					out = (char)s[i];
				}
				else if ((nLoop == 1) && (!noOpcode))
				{
					in1 = (char)s[i];
				}
				else if (nLoop == 2)
				{
					in2 = (char)s[i];
				}
				nLoop++;
			}
			if ((!op) && (!noOpcode)) //assiging operation character
			{
				operation = (char)s[i];
			}
		}
		if ((ASCII >= 48) && (ASCII <= 57)) // ascii code of(1>>9) for divide by number as in1

		{

			in1 = (char)s[i];

			noOpcode = 1;

			operation = '.';
		}
		if (ASCII == 39) // ascii code for inverse becasue ' is a special character in c++
		{
			operation = '1';
			noOpcode = 1;
		}
	}
}
int testMultiVariables(string s) //tests if there is multiVariable in the same line and returns their number
{
	int numofequals = 0;
	for (int i = 0; i < s.length(); i++)
	{
		int ASCII = (int)s[i];
		if (ASCII == 61)
		{
			numofequals++;
		}
	}
	return numofequals;
}


int main(int argc, char*argv[])
{
//   Matrix c(3, 3, -1.443, 0.3246, 1.82425, -1.663, -0.557, 3.9724, 0.409, 0.0868, 0.6839);
//   Matrix n(3,3,3.0,0.0,2.0,2.0,0.0,-2.0,0.0,1.0,1.0);
//   Matrix m(3, 3, 1.2, 2.1, 3.4, 4.1, 7.2, 3.4, 7.1, 5.2, 4.6);
//   Matrix a(2,2,1.0,2.0,2.0,2.0);
//   Matrix b(2,2,3.0,2.0,1.0,1.0);
//   cout<<">>>"<<"Matrix A ="<<endl;;
//   print(n);
//   cout<<">>> "<<"Matrix B ="<<endl;;
//   print(m);
//   cout<<">>> "<<"A + B = "<<endl;
//   print(m+n);
//   cout<<">>> "<<"A - B = "<<endl;
//   print(n-m);
//   cout<<">>> "<<"A * B = "<<endl;
//   print(m*n);
//   cout<<">>> "<<"B / A = "<<endl;
//   print(c);
//   cout<<">>> "<<"A' = "<<endl;
//   Matrix k = n.getTranspose();
//   Matrix d = n.inverse();
//   print(d);
//
//
//   print(k);
//
// Matrix l;
// l=a/b;
// print(l);
//
// string s ="[7.3 4.8; 3.8 7.2; 3.4 7.5]";
// //  Matrix w;
//   Matrix w (s);
//   print(w);

string *inputFileLines = new string[10]; //Array Of lines, """""""""""try to convert to dynamic""""""""""
  int nLines; //number Of lines
  if (argc > 1)
  {
    inputFileLines = inputfile(argv[1], nLines); //function returns lines from file (s) on array of strings
    for (int i = 0; i < nLines; i++)
    {
      bool lineType = lineTest(inputFileLines[i]); //function returns true if line, false if operation
      int multiVariable = 0;
      multiVariable = testMultiVariables(inputFileLines[i]); //function tests if there multi variable in the same line and returns number of the variables
      if (lineType)
      {
        int nR, nC;
        char *name = new char[multiVariable];
        getMatrixDimension(inputFileLines[i], nR, nC); //Function gets num_colums,num_rows
        double *values = new double[nR*nC]; //array of values
        strignParsing(inputFileLines[i], values, name); //function returns array of double values, name of the matrix
        for (int j = 0; j < multiVariable; j++)
        {
          //////////////////////////	//Put Matrix Constructor using nR,nC,"""""""""""""name[j]""""""""""""",values
        }
        if (inputFileLines[i].rfind(';') < inputFileLines[i].rfind(']'))
        {
          //////////////////////////////////////Get deteriment and print it
        }
      }
      else
      {
        char in1, in2, out, operation;
        operationParsing(inputFileLines[i], in1, in2, out, operation);//function parses operation line to in1,in2,out,operation
        switch (operation)
        {
        case '+':
      ////////////////////////////put function that Adds 2 Matrices :D out = in1 + in2  and print them
          break;
        case '-':
      /////////////////////////////put function that subtract two matrices out = in1 - in2 and print
          break;
        case '*':
      /////////////////////////////put mulitplication function from matrix
          break;
        case '/':
      ////////////////////////////put division function
          break;
        case '1':
      ///////////////////////////put """""""inverse""""""" function of out = in1'
          break;
        case'.':
          int num = (int)in1 - 48;
      /////////////////////////put division function tht divide num/matrix in2  = matrix out
          break;
        }
      }
    }
  }
  if (argc <= 1)
  {
    string line;
    while (getline(cin, line))
    {
      int multiVariable = 0;
      multiVariable = testMultiVariables(line); //function tests if there multi variable in the same line and returns number of the variables
      cout << ">";
      bool lineType = lineTest(line);
      if (lineType)
      {
        int nR, nC;
        char *name = new char[multiVariable];
        getMatrixDimension(line, nR, nC); //Function gets num_colums,num_row
        double *values = new double[nR*nC]; //array of values
        strignParsing(line, values, name); //function returns array of double values, name of the matrix
        for (int j = 0; j < multiVariable; j++)
        {
          ////////////////////////////Put Matrix Constructor using nR,nC,"""""""""""""name[j]""""""""""""",values
        }
        if (line.rfind(';') < line.rfind(']'))
        {
          //////////////////////////////////////Get deteriment and print it
        }
      }
      else
      {
        char in1, in2, out, operation;
        operationParsing(line, in1, in2, out, operation);//function parses operation line to in1,in2,out,operation
        switch (operation)
        {
        case '+':
          ////////////////////////////put function that Adds 2 Matrices :D out = in1 + in2  and print them
          break;
        case '-':
          /////////////////////////////put function that subtract two matrices out = in1 - in2 and print
          break;
        case '*':
          /////////////////////////////put mulitplication function from matrix
          break;
        case '/':
          ////////////////////////////put division function
          break;
        case '1':
          ///////////////////////////put """""""inverse""""""" function of out = in1'
          break;
        case'.':
          int num = (int)in1 - 48;
          /////////////////////////put division function tht divide num/matrix in2  = matrix out
          break;
        }
      }
    }
  }
  return 0;
}
