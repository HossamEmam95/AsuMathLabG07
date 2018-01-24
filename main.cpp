#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>
//#include<curses.h>
//#include <ncurses.h>
#include <algorithm>
#include<fstream>
#include <climits>
#include "header.h"
#include "cmath"
#include "ctime";
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

int stringopenclosed(string s)
{
	int counteropen=0;
	int counterclosed=0;
	int found1;
	int found2;
	if(s.find('[')!=string::npos)
	{found1=s.find('[');
    counteropen++;}


	while(s.find('[',found1+1)!=string::npos )
	{
		if(s.find('[',found1+1)!=string::npos)
		{found1=s.find('[',found1+1);
	counteropen++;}
}
	if(s.find(']')!=string::npos)
	{found2=s.find(']');
	counterclosed++;
}
	while(s.find(']',found2+1)!=string::npos )
	{
		if(s.find(']',found2+1)!=string::npos)
		{found2=s.find(']',found2+1);
	counterclosed++;}
	}

	if(counteropen>counterclosed)
	return 1;
	else
	return 0;
}

string* inputfile(string s,int &nlines) //function returns lines from file (s) on array of strings
{
	std::ifstream infile;
	infile.open(s.c_str());
	string line;
	int i = 0;
	int intchecker=0;
	string *lines = new string[1000];
	int awel_line_fel_loop=0;
	string checker="";
	if (infile.bad())
	{
		cout << "Error!" << endl;
	}
int linebegin=0;
int done =0;
	while (getline(infile, line))
	{

		int x=line.length();
		if(line.find(';',(x-2))==string::npos)
		line.replace(x-1,2,";/0");
		else
		line.replace(x-1,1,"/0");
		if(awel_line_fel_loop==0)
		checker=line;
		else
		checker=lines[i]+line;
		awel_line_fel_loop=1;
		intchecker= stringopenclosed(checker);
		//cout<<line<<endl;
    //breaked=0;
		if (line.length() > 2)
		{
     if((line.find('[')!=string::npos) && done==0 && intchecker==1 && linebegin==0)
       {linebegin=1;
        lines[i]=line;
				// int r=line.find(';');
				// int l=line.length();
				// cout<<r<<endl<<l<<endl;
				// if(line.find(';',line.length()-3)<0)
				// line=line+";/0";
				//cout<<"ana_get"<<endl;
      //   if(line.find(']')!=string::npos)
      // { i++;
      //   linebegin=0;}
      done=1;
      }
    if((linebegin==1)  && (done==0) && intchecker==1)
			{




				lines[i]=lines[i]+line;
				//cout<<lines[i]<<endl;
        done=1;
      }
    if((line.find(']')!=string::npos) && (linebegin==1)&& (done==0) && intchecker==0)
			{
    //  lines[i]=lines[i]+line;
		// cout<<line<<endl;
		// s2=line+str;

		 //cout<<lines[i]<<endl;
		 //cout<<line<<endl;
		//  if(line.find(';',line.length()-3)<0)
 	// 	line=line+";/0";
		 lines[i]=lines[i]+line;
		//lines[i]=lines[i]+str;
		//cout<<lines[i]<<endl;

		// cout<<s2<<endl;
      i++;
      linebegin=0;
      done=1;
      }
			if((line.find('[')!=string::npos) && done==0 && intchecker==0 && linebegin==0)
        {

					lines[i]=line;
					i++;
					linebegin=0;
					done=1;
				}
      if((linebegin==0) && done==0)
      {
        lines[i]=line;
				if(line.find(';')!=string::npos)
				lines[i].erase(line.find(';'));

        i++;
        done=1;
           //breaked=1;
        //break;
      }
/*   if(breaked==1)
   break;*/
		}
	done=0;
}


int found;
	nlines = i;
	for(int j=0;j<i;j++)
	{
		if(lines[j].find("/0")!=string::npos)
		{
			found=lines[j].find("/0");
			lines[j].erase(found,2);
		}
			while(lines[j].find("/0",found+1)!=string::npos)
			{
				if(lines[j].find("/0",found+1)!=string::npos)
				{
					found=lines[j].find("/0",found+1);
					lines[j].erase(found,2);
				}
		}
	}
// cout<<lines[0]<<endl;
// cout<<lines[1]<<endl;
// cout<<lines[2]<<endl;
	infile.close();

	return lines;
}

void getMatrixDimension(string s, int &nR, int &nC) //Function gets num_colums,num_rows
{
		nR = 1;
		int nSpaces = 1;
		nC = 1;
		for (int i = s.find('['); i < s.length()-1; i++)
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

void stringParsing(string s, string &m, char *Name) //function returns array of double values, name of the matrices
{
  int num = 0;
  int length = m.length();
  char *newline = new char[1000000];
	char *variables = new char[100000];
  strcpy(newline, s.c_str() + s.find('['));
  m = newline;
  char* spearators = "=[] ;,";
	s.erase(s.begin() + s.rfind("="), s.end());
	strcpy(variables, s.c_str());
	char* tokeName = strtok(variables, spearators);
	while (tokeName)//making array of variables names
	{
		Name[num] = *tokeName;
		num++;
		tokeName = strtok(NULL, spearators);
	}
}


void operationParsing(string s, char& in1, char& in2, char& out, char& operation) //function parses operation line to in1,in2,out,operation
{
	int location=0;
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
        if(s.find('+')!=string::npos)
				operation = '+';
        else if(s.find('-')!=string::npos)
				operation = '-';
        else if(s.find('*')!=string::npos)
				operation = '*';
        else if(s.find('/')!=string::npos)
				operation = '/';
			}
		}
		if ((ASCII >= 48) && (ASCII <= 57)) // ascii code of(1>>9) for divide by number as in1
		{
			in1 = (char)s[i];
      nLoop =  2 ;
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

Matrix Rand(int n,int m){
	Matrix temp(n,m,3);
	return temp;
}

Matrix Eye(int n,int m){
	Matrix temp(n,m,2);
	return temp;
}

Matrix Zero(int n,int m){
	Matrix temp(n,m,0);
	return temp;
}

Matrix One(int n,int m){
	Matrix temp(n,m,1);
	return temp;
}

Matrix Sin(Matrix m){
	for(int i =0;i <m.num_rows;i++){
		for(int j =0;j <m.num_col;j++){
			m.values[i][j] = sin(m.values[i][j]);
		}
	}
	return m;
}

Matrix Sqrt(Matrix m){
	for(int i =0;i <m.num_rows;i++){
		for(int j =0;j <m.num_col;j++){
			m.values[i][j] = sqrt(m.values[i][j]);
		}
	}
	return m;
}

Matrix Power(Matrix m,int power){
	Matrix n = m;
	for(int i =1;i <power;i++){
		n *= m;

	}
	return n;
}
Matrix Rand(int n,int m){
	Matrix temp(n,m,3);
	return temp;
}

Matrix Eye(int n,int m){
	Matrix temp(n,m,2);
	return temp;
}

Matrix Zero(int n,int m){
	Matrix temp(n,m,0);
	return temp;
}

Matrix One(int n,int m){
	Matrix temp(n,m,1);
	return temp;
}


Matrix Sin(Matrix m){
	for(int i =0;i <m.num_rows;i++){
		for(int j =0;j <m.num_col;j++){
			m.values[i][j] = sin(m.values[i][j]);
		}
	}
	return m;
}

Matrix Sqrt(Matrix m){
	for(int i =0;i <m.num_rows;i++){
		for(int j =0;j <m.num_col;j++){
			m.values[i][j] = sqrt(m.values[i][j]);
		}
	}
	return m;
}

Matrix Power(Matrix m,int power){
	Matrix n = m;
	for(int i =1;i <power;i++){
		n *= m;

	}
	return n;
}



int main(int argc, char*argv[])
{

  // string strA = "[8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9; 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9 8.9 7.3 4.8 2.4 2.3 6.5 8.9 1.2 4.9 3.8 7.2 7.5 9.8 3.4 7.5 8.9]";
  // string strB = "[1.2 3.4 5.6 7.8 1.0 3.2 2.1 2.3 1.4 2.6 2.7 2.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 3.7 1.2 3.4 5.6 7.8 9.0 1.2 2.1 2.3 2.4 1.6; 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4; 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 7.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 4.1 2.3; 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 1.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1; 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2; 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 17.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0; 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8; 9.0 2.2 2.1 2.3 2.4 1.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 2.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6; 7.4 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4; 5.6 7.8 9.0 2.2 4.4 2.3 2.4 2.6 2.7 1.2 3.4 5.6 2.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2; 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 1.8 9.0 1.2 2.1 2.3 2.4 8.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7; 1.2 3.4 5.6 7.8 9.0 2.2 5.1 4.3 12.4 2.6 2.7 1.2 3.4 5.6 97.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 3.4 2.6; 2.7 1.2 3.4 5.6 7.5 9.0 2.2 2.1 3.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 5.1 2.3 2.4 5.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4; 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 8.2 2.1 2.3; 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 6.6 2.7 1.2 3.4 5.6 2.8 9.0 1.2 2.1; 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 5.1 2.3 2.4 0.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 0.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2; 0.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0; 4.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 5.2 2.1 2.3 2.4 9.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8; 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 5.3 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.3; 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 3.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 3.4 2.6 3.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 8.4 2.6 2.7 1.2 3.4; 5.6 7.8 9.0 2.2 2.1 2.3 3.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 1.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2; 3.4 1.6 7.8 9.0 2.2 3.1 6.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7; 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 4.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 1.6; 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 1.4 2.6 2.7 1.2 3.4 9.6 7.8 9.0 2.2 2.1 2.3 2.4; 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 1.4 2.6 2.7 2.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3; 2.4 2.6 2.7 1.2 3.4 5.6 7.8 1.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 8.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 2.6 7.8 9.0 2.2 2.1; 7.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 3.6 1.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2; 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 7.2 3.4 5.6 7.8 9.0; 2.2 2.1 2.3 2.4 2.6 7.7 9.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.9 2.4 2.6 2.7 1.2 3.4 5.6 7.8; 9.0 2.2 2.1 2.3 2.4 2.6 7.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6; 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4; 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 5.7 9.3 3.4 5.6 3.8 9.0 2.2 5.1 2.3 2.4 2.6 2.7 1.2]" ;
	//
  // Matrix A(strA);
  // Matrix B(strB);
	//
  // print(A/B);

//
Matrix matrices[100];
int ptr = 0;
string *inputFileLines = new string[100]; //Array Of lines, """""""""""try to convert to dynamic""""""""""

	int nLines; //number Of lines
//
if (argc > 1)
//
	{
//
		inputFileLines = inputfile(argv[1], nLines); //function returns lines from file (s) on array of strings
//
		for (int i = 0; i < nLines; i++)
		{

			bool lineType = lineTest(inputFileLines[i]); //function returns true if line, false if operation

			int multiVariable = 0;

			multiVariable = testMultiVariables(inputFileLines[i]); //function tests if there multi variable in the same line and returns number of the variables

			if (lineType)

			{
				char *name = new char[multiVariable];

				string m = "";

				stringParsing(inputFileLines[i], m, name); //function returns array of double values, name of the matrix

				for (int j = 0; j < multiVariable; j++)

				{

					//////////////////////////	//Put Matrix Constructor using nR,nC,"""""""""""""name[j]""""""""""""",values
          Matrix w(m);
          matrices[ptr] = w;
          matrices[ptr].name = name[j];
          ptr++;
				}

				if (inputFileLines[i].find(';') < inputFileLines[i].find(']'))

				{

					//////////////////////////////////////Get deteriment and print it
          for (int i = 0; i<multiVariable; i++)
          {
            cout<<name[i]<<" = "<<endl;
            print(matrices[ptr-1]);
          }
				}

			}

			else

			{

  				char in1, in2, out, operation;
				operationParsing(inputFileLines[i], in1, in2, out, operation);//function parses operation line to in1,in2,out,operation

        switch (operation)

				{


          				case '+':
                  {////////////////////////////put function that subtract two matrices out = in1 - in2 and print
                  string zero = "[]";
                  Matrix first;
                  Matrix second;
                  Matrix output;
                  output.name = out;
                  matrices[ptr] = output;
                  ptr++;


                  for (int i = 0; i < ptr; i++)
                  {
                    if (matrices[i].name == in1) {first = matrices[i];}
                    if (matrices[i].name == in2) second = matrices[i];
                    if (matrices[i].name == out)
                    {output = first + second;
                     matrices[i] = output;

                      }
                  }

                    cout<<out<<" = "<<endl;
                  //  cout<<matrices[ptr-1].name;
                    print( matrices[ptr-1] );
                    matrices[ptr-1].name=out;

                      break;}

          				case '-':

          			{////////////////////////////put function that subtract two matrices out = in1 - in2 and print
                string zero = "[]";
                Matrix first;
                Matrix second;
                Matrix output;
                output.name = out;
                matrices[ptr] = output;
                ptr++;


                for (int i = 0; i < ptr; i++)
                {
                  if (matrices[i].name == in1) {first = matrices[i];}
                  if (matrices[i].name == in2) second = matrices[i];
                  if (matrices[i].name == out)
                  {output = first - second;
                   matrices[i] = output;

                    }
                }

                  cout<<out<<" = "<<endl;
                //  cout<<matrices[ptr-1].name;
                  print( matrices[ptr-1] );
                  matrices[ptr-1].name=out;

          					break;}

          				case '*':

          			/////////////////////////////put mulitplication function from matrix
                {////////////////////////////put function that subtract two matrices out = in1 - in2 and print
                string zero = "[]";
                Matrix first;
                Matrix second;
                Matrix output;
                output.name = out;
                matrices[ptr] = output;
                ptr++;


                for (int i = 0; i < ptr; i++)
                {

                  if (matrices[i].name == in1) {first = matrices[i];}
                  if (matrices[i].name == in2) second = matrices[i];
                  if (matrices[i].name == out)
                  {output = first * second;
                   matrices[i] = output;

                    }
                }

                  cout<<out<<" = "<<endl;
                //  cout<<matrices[ptr-1].name;
                  print( matrices[ptr-1] );
                  matrices[ptr-1].name=out;

                    break;}


          				case '/':
                  {////////////////////////////put function that subtract two matrices out = in1 - in2 and print
                  string zero = "[]";
                  Matrix first;
                  Matrix second;
                  Matrix output;
                  output.name = out;
                  matrices[ptr] = output;
                  ptr++;


                  for (int i = 0; i < ptr; i++)
                  {
                    if (matrices[i].name == in1) {first = matrices[i];}
                    if (matrices[i].name == in2) second = matrices[i];
                    if (matrices[i].name == out)
                    {output = first / second;
                     matrices[i] = output;

                      }
                  }

                    cout<<out<<" = "<<endl;
                  //  cout<<matrices[ptr-1].name;
                    print( matrices[ptr-1] );
                    matrices[ptr-1].name=out;

                      break;}


          				case '1':
              {  string zero = "[]";
                  Matrix first;
                  Matrix second;
                  Matrix output;
                  output.name = out;
                  matrices[ptr] = output;
                  ptr++;


                  for (int i = 0; i < ptr; i++)
                  {
                    if (matrices[i].name == in1) {first = matrices[i];}
                    if (matrices[i].name == in2) second = matrices[i];
                    if (matrices[i].name == out)
                    {output =first.getTranspose();
                     matrices[i] = output;

                      }
                  }

                    cout<<out<<" = "<<endl;
                  //  cout<<matrices[ptr-1].name;
                    print( matrices[ptr-1] );
                    matrices[ptr-1].name=out;

                  break;}




          				case'.':
                  {
                                 int num = (int)in1 - 48;



                    /////////////////////////put division function tht divide num/matrix in2  = matrix out
                    string zero = "[]";
                    Matrix first(zero);
                    Matrix output(zero);
                    output.name = out;
                    matrices[ptr] = output;
                    ptr++;
                    for (int i = 0; i < ptr; i++)
                    {
                      if (matrices[i].name == in2) {first = matrices[i];}
                    }
                    output = first;
                      for(int r = 0; r<first.num_rows; r++ )
                      {
                          for(int c = 0; c<first.num_col; c++)
                          {
                            output.values[r][c] = num/first.values[r][c];
                          }
                      }
                      matrices[ptr-1]=output;
                      cout<<out<<" = "<<endl;
                      print(output);


                    break;}

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

				string m = ""; //array of values

				stringParsing(line, m, name); //function returns array of double values, name of the matrix


				for (int j = 0; j < multiVariable; j++)

				{

					///Put Matrix Constructor using nR,nC,"""""""""""""name[j]""""""""""""",value
          Matrix w(m);
          matrices[ptr] = w;
          matrices[ptr].name = name[j];
          ptr++;


				}

				if (line.rfind(';') < line.rfind(']'))

				{

					//////////////////////////////////////Get deteriment and print it
          for (int i = 0; i<multiVariable; i++)
          {
            cout<<name[i]<<" = "<<endl;
            print(matrices[ptr-1]);
          }
				}

			}

			else

			{

				char in1, in2, out, operation;

				operationParsing(line, in1, in2, out, operation);//function parses operation line to in1,in2,out,operation
				switch (operation)

				{
          case '+':{
            ////////////////////////////put function that Adds 2 Matrices :D out = in1 + in2  and print them
              string zero = "[]";
              Matrix first;
              Matrix second;
              Matrix output;
              output.name = out;
              matrices[ptr] = output;
              ptr++;


              for (int i = 0; i < ptr; i++)
              {
                if (matrices[i].name == in1) {first = matrices[i];}
                if (matrices[i].name == in2) second = matrices[i];
                if (matrices[i].name == out)
                {output = first + second;
                 matrices[i] = output;

                  }
              }

                cout<<out<<" = ";
              //  cout<<matrices[ptr-1].name;
                print( matrices[ptr-1] );
                matrices[ptr-1].name=out;




            break;}

          case '-':{

            string zero = "[]";
            Matrix first;
            Matrix second;
            Matrix output;
            output.name = out;
            matrices[ptr] = output;
            ptr++;


            for (int i = 0; i < ptr; i++)
            {
              if (matrices[i].name == in1) {first = matrices[i];}
              if (matrices[i].name == in2) second = matrices[i];
              if (matrices[i].name == out)
              {output = first - second;
               matrices[i] = output;

                }
            }

              cout<<out<<" = ";
            //  cout<<matrices[ptr-1].name;
              print( matrices[ptr-1] );
              matrices[ptr-1].name=out;


            break;}

          case '*':{
            string zero = "[]";
            Matrix first;
            Matrix second;
            Matrix output;
            output.name = out;
            matrices[ptr] = output;
            ptr++;


            for (int i = 0; i < ptr; i++)
            {
              if (matrices[i].name == in1) {first = matrices[i];}
              if (matrices[i].name == in2) second = matrices[i];
              if (matrices[i].name == out)
              {output = first * second;
               matrices[i] = output;

                }
            }

              cout<<out<<" = ";
            //  cout<<matrices[ptr-1].name;
              print( matrices[ptr-1] );
              matrices[ptr-1].name=out;




          break;
        }

          case '/':{

            string zero = "[]";
            Matrix first;
            Matrix second;
            Matrix output;
            output.name = out;
            matrices[ptr] = output;
            ptr++;


            for (int i = 0; i < ptr; i++)
            {
              if (matrices[i].name == in1) {first = matrices[i];}
              if (matrices[i].name == in2) second = matrices[i];
              if (matrices[i].name == out)
              {output = first / second;
               matrices[i] = output;

                }
            }

              cout<<out<<" = ";
            //  cout<<matrices[ptr-1].name;
              print( matrices[ptr-1] );
              matrices[ptr-1].name=out;





            break;}

          case '1':{
            string zero = "[]";
            Matrix first;
            Matrix second;
            Matrix output;
            output.name = out;
            matrices[ptr] = output;
            ptr++;


            for (int i = 0; i < ptr; i++)
            {
              if (matrices[i].name == in1) {first = matrices[i];}
              if (matrices[i].name == in2) second = matrices[i];
              if (matrices[i].name == out)
              {output =first.getTranspose();
               matrices[i] = output;

                }
            }

              cout<<out<<" = ";
            //  cout<<matrices[ptr-1].name;
              print( matrices[ptr-1] );
              matrices[ptr-1].name=out;







            break;}

          case'.':{

            int num = (int)in1 - 48;



            /////////////////////////put division function tht divide num/matrix in2  = matrix out
            string zero = "[]";
            Matrix first(zero);
            Matrix output(zero);
            output.name = out;
            matrices[ptr] = output;
            ptr++;
            for (int i = 0; i < ptr; i++)
            {
              if (matrices[i].name == in2) {first = matrices[i];}
            }
            output = first;
              for(int r = 0; r<first.num_rows; r++ )
              {
                  for(int c = 0; c<first.num_col; c++)
                  {
                    output.values[r][c] = num/first.values[r][c];
                  }
              }
              matrices[ptr-1]=output;
              cout<<out<<" = "<<endl;
              print(output);


            break;}


				}

			}

		}

	}

  return 0;
}
