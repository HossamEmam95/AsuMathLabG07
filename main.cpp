#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>
#include<curses.h>
#include <ncurses.h>
#include <algorithm>
#include<fstream>
#include <climits>
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
	string *lines = new string[1000];
	if (infile.bad())
	{
		cout << "Error!" << endl;
	}
int linebegin=0;
int done =0;
	while (getline(infile, line))
	{
    //breaked=0;
		if (line.length() > 2)
		{
     if((line.find('[')!=string::npos) && done==0)
       {linebegin=1;
        lines[i]=line;
        if(line.find(']')!=string::npos)
      { i++;
        linebegin=0;}
        done=1;
       }
    if((linebegin==1) &&line.find(']')==string::npos  && (done==0))
			{lines[i]=lines[i]+line;
        done=1;
      }
    if((line.find(']')!=string::npos) && (linebegin==1)&& (done==0))
			{
      lines[i]=lines[i]+line;
      i++;
      linebegin=0;
      done=1;
      }
      if((linebegin==0) && done==0)
      {
        lines[i]=line;
        i++;
        done=1;

      }

		}

	done=0;
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
  char* spearators = (char*)"=[] ;,";
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

{ int location=0;
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
int main(int argc, char*argv[])
{


Matrix matrices[100];
int ptr = 0;
string *inputFileLines = new string[100]; //Array Of lines, """""""""""try to convert to dynamic""""""""""

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
                    print( matrices[ptr-1] );
                    matrices[ptr-1].name=out;




                      break;}
          			////////////////////////////put division function



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
											matrices[ptr-1].name=out;


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
              matrices[ptr-1].name=out;

            break;}


				}

			}

		}

	}

  return 0;
}
