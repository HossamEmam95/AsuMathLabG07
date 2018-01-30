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
#include "ctime"
#include <ostream>
#include "cmath"


using namespace std;


void print(Matrix m )
	{
		cout<<m.name<<" = "<<endl;
	  for(int i=0; i<m.num_rows; i++)
	  {
	    for(int j=0; j<m.num_col; j++)
	    {
	      cout<<m.values[i][j]<<" ";
	    }
	    cout<<endl;
	  }
		cout<<endl;
	}



// finstion that get an array of strings and concatenat them together to produce one string seprated by the given char

//function the replace the ; in the minor matrices with f to make cutting easier
string Replace(string z)
{
	int count = 0;
	int flag = 0;
	for (int i = 0; i < z.length(); i++)
	{

		if (z[i]=='[')
		{
			flag = 1;
			count++;
			if (count == 1)
				continue;
			else
				for (int g = i; g < z.length(); g++)
				{if(z[g] == ']') flag=0;
				if(z[g] == ';' && flag==1)
				z.replace(g, 1, "f");
			}}
		}
	return z;
}

int stringopenclosedOPERATIONERROR(string s)
{
	int counteropen=0;
	int counterclosed=0;
	int found1;
	int found2;
	if(s.find('(')!=string::npos)
	{found1=s.find('(');
    counteropen++;}


	while(s.find('(',found1+1)!=string::npos )
	{
		if(s.find('(',found1+1)!=string::npos)
		{found1=s.find('(',found1+1);
	counteropen++;}
}
	if(s.find(')')!=string::npos)
	{found2=s.find(')');
	counterclosed++;
}
	while(s.find(')',found2+1)!=string::npos )
	{
		if(s.find(')',found2+1)!=string::npos)
		{found2=s.find(')',found2+1);
	counterclosed++;}
	}

	if(counteropen==counterclosed)
	return 1;
	else
	return 0;
}
//helper functions to use in 	checkoperations function
double operationSolving(string s){

	double result;
	int op_counter = 0;

	for(int i =0;i<s.length();i++){
		if(s[i] =='+'||s[i] =='-'||s[i] =='*'||s[i] =='/'||s[i] =='^'||s[i] =='%') {
			op_counter++;
			i++;
		}
	}

	char* operations = new char[op_counter];
	double* numbers = new double [op_counter+1];
	int pos = 0;
	int counter = 0;
	string s1 ;
	char* s2;
	for(int i =0;i<s.length();i++){
		if(s[i] =='+'||s[i] =='-'||s[i] =='*'||s[i] =='/'||s[i] =='^'||s[i] =='%'){

			s1 = s.substr(pos,i-pos);
			s2 = new char[s1.length()];
			for(int k = 0;k<s1.length();k++){
				s2[k] = s1[k];
			}
			numbers[counter] = atof(s2);
			operations[counter] = s[i];
			pos = i+1;
			counter++;
			if(s[i+1] == '-'){i++;}
		}
	}

	s1 = s.substr(pos,s.length()-pos);
	s2 = new char[s1.length()];
	for(int k = 0;k<s1.length();k++){
		s2[k] = s1[k];
	}
	numbers[counter] = atof(s2);

	for(int i =0;i<op_counter;i++){
		if(operations[i] == '^'){
			numbers[i] = pow(numbers[i],numbers[i+1]);
			for(int j = i;j<op_counter-1;j++){
				numbers[j+1] = numbers[j+2];
				operations[j] = operations[j+1];
			}
			op_counter--;
			i--;
		}
	}

	for(int i =0;i<op_counter;i++){
		if(operations[i] == '*'){
			numbers[i] = numbers[i]*numbers[i+1];
			for(int j = i;j<op_counter-1;j++){
				numbers[j+1] = numbers[j+2];
				operations[j] = operations[j+1];
			}
			op_counter--;
			i--;
		}
		if(operations[i] == '/'){
			if(numbers[i+1]==0)
			throw 3;
			numbers[i] = numbers[i]/numbers[i+1];
			for(int j = i;j<op_counter-1;j++){
				numbers[j+1] = numbers[j+2];
				operations[j] = operations[j+1];
			}
			op_counter--;
			i--;
		}
		if(operations[i] == '%'){
			numbers[i] =((int) numbers[i])%((int)numbers[i+1]);
			for(int j = i;j<op_counter-1;j++){
				numbers[j+1] = numbers[j+2];
				operations[j] = operations[j+1];
			}
			op_counter--;
			i--;
		}
	}

	for(int i =0;i<op_counter;i++){
		if(operations[i] == '+'){
			numbers[i] = numbers[i]+numbers[i+1];
			for(int j = i;j<op_counter-1;j++){
				numbers[j+1] = numbers[j+2];
				operations[j] = operations[j+1];
			}
			op_counter--;
			i--;
		}
		if(operations[i] == '-'){
			numbers[i] = numbers[i]-numbers[i+1];
			for(int j = i;j<op_counter-1;j++){
				numbers[j+1] = numbers[j+2];
				operations[j] = operations[j+1];
			}
			op_counter--;
			i--;
		}
	}

	return numbers[0];
}


double bigOperationSolving(string s){
	string r = s;
int found;
	if(r.find(" ")!=string::npos)
	{
		found=r.find(" ");
		r.erase(found,1);
	}
		while(r.find(" ",found)!=string::npos)
		{
			if(r.find(" ",found)!=string::npos)
			{
				found=r.find(" ",found+1);
				r.erase(found,1);
			}
		}

	if(stringopenclosedOPERATIONERROR(s)!=1)
	throw 1;

	else if(r[r.length()-1]=='+'||r[r.length()-1]=='-'||r[r.length()-1]=='*'||r[r.length()-1]=='%'||r[r.length()-1]=='/'||r[r.length()-1]=='^')
	throw 2;


	// else if ((r[r.length()-1]==')')&& (([s.length()-2]=='+'||s[s.length()-2]=='-'||s[s.length()-2]=='*'||s[s.length()-2]=='%'||s[s.length()-2]=='/'||s[s.length()-2]=='^')))
	// throw 2;
	else if(r.find("+)")!=-1||r.find("*)")!=-1||r.find("-)")!=-1||r.find("^)")!=-1||r.find("%)")!=-1||r.find("/)")!=-1)
	throw 2;
	//
	// else if ((s[s.length()-1]==' ')&& ((s[s.length()-2]=='+'||s[s.length()-2]=='-'||s[s.length()-2]=='*'||s[s.length()-2]=='%'||s[s.length()-2]=='/'||s[s.length()-2]=='^')))
	// throw 2;
	//
	// else if ((s[s.length()-1]==' ')&&(s[s.length()-2]==' ')&& ((s[s.length()-3]=='+'||s[s.length()-3]=='-'||s[s.length()-3]=='*'||s[s.length()-3]=='%'||s[s.length()-3]=='/'||s[s.length()-2]=='^')))
	// throw 2;
	else{
	double result;
	int start = 0;
	int end = 0;
	string new_operation("");
	for(int i = 0; i <s.length();i++){
		int asci = (int) s[i];
		int num1 = 0;
		int num2 = 0;
		if (((asci >= 65) && (asci <= 90)) || ((asci >= 97) && (asci <= 122))){
			string tri_op ("");
			tri_op += s[i];
			int no1 = 0;
			int no2 = 0;
			for(int t = i+1;t < s.length();t++){
				tri_op += s[t];
				if(s[t] =='('){
					no1++;
				}
				else if(s[t] == ')'){
					no2++;
				}
				if(no1 > 0 && no1 == no2){
					i = t ;
					break;
				}
			}
			string tri_operator = tri_op.substr(0,tri_op.find("("));
			string inner_op = tri_op.substr(tri_op.find("(")+1,tri_op.length()-(tri_op.find("(")+2));
			double inner_result = bigOperationSolving(inner_op);
			double outer_result ;
			if(tri_operator == "sin"){
				outer_result = sin(inner_result);
			}
			else if (tri_operator == "cos"){
				outer_result = cos(inner_result);
			}
			else if (tri_operator == "tan"){
				outer_result = tan(inner_result);
			}
			else if (tri_operator == "sqrt"){
				outer_result = sqrt(inner_result);
			}
			char buffer[50];
			double n = snprintf(buffer,50,"%lf",outer_result);
			new_operation += buffer;
		}
		else if(s[i] == '('){
			num1++;
			start = i+1;
			for(int j = i+1;j<s.length();j++){
				if(s[j] == '('){
					num1++;
				}
				else if (s[j] == ')'){
					num2++;
					if(num1 == num2){
						end = j-1;
						i = j ;
						break;
					}
				}
			}
			string smallOperation = s.substr(start,(end-start+1));
			double solution;
			if(smallOperation.find('(') !=string::npos){

				solution = bigOperationSolving(smallOperation);
			}
			else{
				solution = operationSolving(smallOperation);
			}
			char buffer[50];
			double n = snprintf(buffer,50,"%lf",solution);
			new_operation += buffer;
		}
		else{
				new_operation += s[i];
		}
	}
	result = operationSolving(new_operation);
	return result;
}
}

string checkOperations(string s){
	string newString = "[";
	char* buffer = new char[s.length()+1];
	strcpy(buffer, s.c_str());
	char* lineContext;
	const char* lineSeparators = ";\r\n";
	char* line = strtok_r(buffer, lineSeparators, &lineContext);
	while(line){
		char* context;
		const char* separators = " []";
		char* token = strtok_r(line, separators, &context);
		while(token){
			string operation = "";
			operation += token;
			double result = bigOperationSolving(operation);
			char buffer[150];
			double n = snprintf(buffer,150,"%lf",result);
			newString += buffer;
			newString += ' ';
			token = strtok_r(NULL, separators, &context);
		}
		newString = newString.substr(0,newString.length()-1);
		newString += ';';
		line = strtok_r(NULL, lineSeparators, &lineContext);
	}
	newString = newString.substr(0,newString.length()-1);
	newString += "]";
	return newString;
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

//functions that concat to matrices together.
string concat(string s){ //important : this string contains two matrices not more not less
	//cout<<"string to concat: "<<s<<endl;
if(s[0]=='['&&s[1]=='[')
	s.erase(0,1);

	string output  = "[";
	Matrix matrix1("[]");
	Matrix matrix2("[5]");
	char concatOperator;
	int intchecker=0;
	int i = 0;
	for(i;i < s.length();i++)
	{
		string str = "";
		int num1 = 0;
		int num2 = 0;
		if(s[i] == '[')
		{
			str += s[i];
			num1++;
			for(int t = i+1;t < s.length();t++)
			{
				str += s[t];
        intchecker=stringopenclosed(str);
				if(s[t] == ']'&& intchecker==0)
				{
					s = s.substr(t, s.length());

					break;
				}

			}
			concatOperator = s[i+1];
			str = checkOperations(str);
			//cout<<"str 1: "<< str<<endl;
			Matrix temp(str);
			matrix1.copy(temp);
			break;
		}
	}

	for(i;i < s.length();i++){
		string str = "";
		int num1 = 0;
		int num2 = 0;
		if(s[i] == '[')	{
			str += s[i];
			num1++;
			for(int t = i+1;t < s.length();t++){
				str += s[t];

				if(s[t] == ']'){
					s = s.substr(t, s.length());
					break;
				}

			}
			str = checkOperations(str);
			//cout<<"str 2: "<<str<<endl;
			Matrix temp(str);
			matrix2 = temp;
			break;
		}
	}
	// cout<<"^^^^^^^^^^^"<<endl;
	// cout<<"matrix 1: "<<matrix1.getString()<<endl;
	// cout<<"matrix 2: "<<matrix2.getString()<<endl;
	// cout<<"^^^^^^^^^^^"<<endl;
	if(concatOperator == ','||concatOperator == ' '){
		matrix1.addColumn(matrix2);
	}
	else if(concatOperator == ';'){
		matrix1.addRow(matrix2);
	}
	for(int iR=0;iR<matrix1.num_rows;iR++){
		for(int iC=0;iC<matrix1.num_col;iC++){
			char buffer[50];
			double n = snprintf(buffer,50,"%lf",matrix1.values[iR][iC]);
			output += buffer;
			output += ' ';
		}
		output = output.substr(0,output.length()-1);
		output += ';';
	}
	output = output.substr(0,output.length()-1);
	output += ']';
	return output;
}


bool testnconstructors(string s)
{
	if ((s.find("zeros") != std::string::npos) || (s.find("ones") != std::string::npos) || (s.find("eye") != std::string::npos) || ((s.find("rand") != std::string::npos)))
	{
		return true;
	}
	else
		return false;
}


void dimnconstructors(string s, int &nRow, int &nCom,int &type)
{
	type = 10;
	if (s.find("zeros") != std::string::npos)
	{
		type = 0;
	}
	else if (s.find("ones") != std::string::npos)
	{
		type = 1;
	}
	else if (s.find("eye") != std::string::npos)
	{
		type = 2;
	}
	else if (s.find("rand") != std::string::npos)
	{
		type = 3;
	}
	if ((type >= 0) && (type <= 3))
	{
		 string row =s.substr(s.find("(")+1, s.find(",") - s.find("(")-1);
		 nRow= atoi(row.c_str());
		 string column = s.substr(s.find(",")+1, s.find(")") - s.find(",")-1);
		 nCom = atoi(column.c_str());
	}
	else
	{
		nRow=0;
		nCom=0;
	}

}

int lineTest(string s) //function returns 1 if line, 0 if pure operation,2 if operation between 2 matrices

{
	if (s.length() < 3) return 3;
	else if (testnconstructors(s))
	{
		return 4;
	}
	else {
	bool index = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '[')
		{
			index = 1;
		}
	}
	if(index == 0){
		int index2 = 0;
		string alpha = "ABCDEFGHIGKLMNOPQRSTUVWXYZ";
		for (int i = 0; i < s.length(); i++)
	{
		if (alpha.find(s[i])!=string::npos)
		{
			index2++;
		}
		if(index2>1){
			return 2;
		}
	}

	}


	return index;
}
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


string* stringToArray(string str, int &rows, char &name)
{
		name = str[0];
    int strLen = str.length();
    rows =0;
    char* line = new char[strLen];
    string* arr = new string[50];
    if (str[strLen-1] == ']')
        str.erase(strLen-1);
    strcpy(line, str.c_str() + str.find('[')+1);
    char* separetors = (char*)";";
    line = strtok(line,separetors);
    while (line)
    {
        arr[rows] = (string)line;
        rows++;
        line = strtok(NULL, separetors);
    }

    return arr;
}

string matrix_substituation(string line, Matrix* matrcies, int ptr)
{
	string output;
	for(int i=1; i<line.length()-1; i++)
	{
		if((int)line[i] > 64 && (int)line[i] < 91)
		{
			Matrix matrix = Matrix();
			int found = 0;
			for(int j=0; j<ptr; j++)
				if(matrcies[j].name == line[i])
				{
					matrix = matrcies[j];
					found = 1;
				}

			line.replace(i, 1, matrix.getString());

			// error handling here
		}
	}
	return line;
}

int case_checker(string line)
{
	int num = 0;
	int counter =0;
	for(int i=0; i<line.length()-1; i++)
	{
		if(line[i] == '[')
		counter += 1;
	}
	if(counter == 1) num = 1;
	if(counter > 1) num = 2;

	return num;
}

string rereplace(string line)
{
	for(int i=0; i<line.length()-1; i++)
		if(line[i] == 'f')
			line.replace(i, 1, ";");
	return line;

}

string str_conc(string* array ,int size, char separator)
{
	string output_string = "[" ;
	for(int i=0; i<size; i++)
	{
		// cout<<"==========="<<endl;
		// cout<<"array: "<<array[i]<<endl;
		// cout<<"before op: "<<output_string<<endl;

		output_string = output_string + array[i].substr(1, array[i].length()-2) + separator;

	}
	output_string += "]";
	// cout<<"after op: "<<output_string<<endl;
	// cout<<"==========="<<endl;
	return output_string ;
}

Matrix operationReduce(string s,Matrix* matrices,int ptr){
	int op_counter = 0;
	for(int i =0;i<s.length();i++){
		if(s[i] =='+'||s[i] =='-'||s[i] =='*'||s[i] =='/'||s[i] =='^'||s[i] =='%') {
			op_counter++;
			i++;
		}
	}
	int mat_counter = 0;
	for(int i =0;i<s.length();i++){
		int ascii = (int) s[i];
		if(((ascii >= 65) && (ascii <= 90)) || ((ascii >= 97) && (ascii <= 122))) {
			mat_counter++;
			i++;
		}
	}
////////////////////////////////////////////////
	char** operations = new char*[op_counter];
	double* numbers = new double [op_counter+2-mat_counter];
	Matrix* mats = new Matrix[mat_counter+1];
	int* keys = new int[op_counter+1];
	int pos = 0;
	int counter = 0;
	int counter1 = 1;
	int counter2 = 1;
	string s1 ;
	char* s2;
	for(int i =0;i<s.length();i++){
		if(s[i] =='+'||s[i] =='-'||s[i] =='*'||s[i] =='/'||s[i] =='^'||s[i] =='%'){

			s1 = s.substr(pos,i-pos);
			operations[counter] = new char[2];
			if(s1[s1.length()-1] == '.'){
				operations[counter][0] = '.';
				operations[counter][1] = s[i];
				s1 = s.substr(pos,i-pos-1);
			}
			else {
				operations[counter][0] = '!';
				operations[counter][1] = s[i];
			}

			int ascii = (int) s1[0];
			if(((ascii >= 65) && (ascii <= 90)) || ((ascii >= 97) && (ascii <= 122))) {
				for(int j=0;j<ptr;j++){
					if(matrices[j].name == s1[0])	{
						mats[counter1] = matrices[j];
						mats[counter1].name = matrices[j].name;
						break;
					}
				}
				keys[counter] = counter1;
				counter1++;
			}
else{
s2 = new char[s1.length()];
for(int k = 0;k<s1.length();k++){
	s2[k] = s1[k];
}
numbers[counter2] = atof(s2);
keys[counter] = -1*counter2;
counter2++;
}
counter++;
pos = i+1;
if(s[i+1] == '-'){i++;}
}
}

s1 = s.substr(pos,s.length()-pos);
int ascii = (int) s1[0];
if(((ascii >= 65) && (ascii <= 90)) || ((ascii >= 97) && (ascii <= 122))) {
for(int j=0;j<ptr;j++){
if(matrices[j].name == s1[0])	{
mats[counter1] = matrices[j];
mats[counter1].name = matrices[j].name;
break;
}
}
keys[counter] = counter1;
}
else{
s2 = new char[s1.length()];
for(int k = 0;k<s1.length();k++){
s2[k] = s1[k];
}
numbers[counter2] = atof(s2);
keys[counter] = -1*counter2;
}

///////////////////////////////////////////
for(int i =0;i<op_counter;i++){
if(operations[i][0] == '!'&&operations[i][1] == '^'){
if(keys[i]>0){
mats[keys[i]]=mats[keys[i]]^numbers[-1*keys[i+1]];
}
else if(keys[i] < 0){
numbers[-1*keys[i]] = pow(numbers[-1*keys[i]],numbers[-1*keys[i+1]]);
}
for(int j = i;j<op_counter-1;j++){
keys[j+1] = keys[j+2];
operations[j] = operations[j+1];
}
op_counter--;
i--;
}
else if(operations[i][0] == '.'&&operations[i][1] == '^'){
	if(keys[i]>0){
		mats[keys[i]]= mats[keys[i]].powerbyelement(numbers[-1*keys[i+1]]);
	}
	for(int j = i;j<op_counter-1;j++){
		operations[j] = operations[j+1];
		keys[j+1] = keys[j+2];
	}
	op_counter--;
	i--;
}
}

for(int i =0;i<op_counter;i++){
if(operations[i][0] == '!'&&operations[i][1] == '*'){
	if(keys[i]>0){
		if(keys[i+1]>0){
			mats[keys[i]]*=mats[keys[i+1]];
		}
		else if(keys[i+1]<0){
			mats[keys[i]]*=numbers[-1*keys[i+1]];
		}
		for(int j = i;j<op_counter-1;j++){
			keys[j+1] = keys[j+2];
			operations[j] = operations[j+1];
		}
		op_counter--;
		i--;
	}
	else if(keys[i] < 0){
		if(keys[i+1]>0){
			mats[keys[i+1]]*=numbers[-1*keys[i]];
		}
		else if(keys[i+1]<0){
			numbers[-1*keys[i+1]]*=numbers[-1*keys[i]];
		}
		for(int j = i;j<op_counter;j++){
			keys[j] = keys[j+1];
			if(j<op_counter-1)operations[j] = operations[j+1];
		}
		op_counter--;
		i--;
	}
}
else if(operations[i][0] == '.'&&operations[i][1] == '*'){
	if(keys[i]>0){
		if(keys[i+1]<0){
			mats[keys[i]]=mats[keys[i]].multiply_by_no(numbers[-1*keys[i+1]]);
			for(int j = i;j<op_counter-1;j++){
				keys[j+1] = keys[j+2];
				operations[j] = operations[j+1];
			}
op_counter--;
i--;
}
}
}
else if(operations[i][0] == '!'&&operations[i][1] == '/'){
if(keys[i]>0){
if(keys[i+1]>0){
mats[keys[i]]/=mats[keys[i+1]];
}
else if(keys[i+1]<0){
mats[keys[i]]/=numbers[-1*keys[i+1]];
}
for(int j = i;j<op_counter-1;j++){
keys[j+1] = keys[j+2];
operations[j] = operations[j+1];
}
op_counter--;
i--;
}
else if(keys[i] < 0){
if(keys[i+1]>0){
Matrix ma = mats[keys[i+1]];
mats[keys[i+1]] = Matrix(numbers[-1*keys[i]]);
mats[keys[i+1]]/= ma;
for(int j = i;j<op_counter;j++){
keys[j] = keys[j+1];
if(j<op_counter-1)operations[j] = operations[j+1];
}
op_counter--;
i--;
}
else if(keys[i+1]<0){
numbers[-1*keys[i]]/=numbers[-1*keys[i+1]];
for(int j = i;j<op_counter-1;j++){
keys[j+1] = keys[j+2];
operations[j] = operations[j+1];
}
op_counter--;
i--;
}

}
}
else if(operations[i][0] == '.'&&operations[i][1] == '/'){
if(keys[i]>0){
if(keys[i+1]>0){
mats[keys[i]] = mats[keys[i]].matrix_divbymatrix(mats[keys[i]],mats[keys[i+1]]);
for(int j = i;j<op_counter-1;j++){
keys[j+1] = keys[j+2];
operations[j] = operations[j+1];
}
op_counter--;
i--;
}
else if(keys[i+1]<0){
mats[keys[i]]=mats[keys[i]].divbyelement(numbers[-1*keys[i+1]]);
for(int j = i;j<op_counter-1;j++){
	keys[j+1] = keys[j+2];
	operations[j] = operations[j+1];
}
op_counter--;
i--;
}
}
else if(keys[i]<0){
if(keys[i+1]>0){
for(int ba=0;ba<mats[keys[i+1]].num_rows;ba++)
	for(int bb=0;bb<mats[keys[i+1]].num_col;bb++)
	{
		mats[keys[i+1]].values[ba][bb]=numbers[-1*keys[i]]/mats[keys[i+1]].values[ba][bb];

	}
for(int j = i;j<op_counter;j++){
	keys[j] = keys[j+1];
	if(j<op_counter-1)operations[j] = operations[j+1];
}
op_counter--;
i--;
}
}
}
}

for(int i =0;i<op_counter;i++){
if(operations[i][0] == '!'&&operations[i][1] == '+'){
if(keys[i]>0){
if(keys[i+1]>0){
mats[keys[i]]+=mats[keys[i+1]];
}
else if(keys[i+1]<0){
mats[keys[i]]+=numbers[-1*keys[i+1]];
}
for(int j = i;j<op_counter-1;j++){
keys[j+1] = keys[j+2];
operations[j] = operations[j+1];
}
op_counter--;
i--;
}
else if(keys[i] < 0){
if(keys[i+1]>0){
	mats[keys[i+1]]+=numbers[-1*keys[i]];
}
else if(keys[i+1]<0){
	numbers[-1*keys[i+1]]+=numbers[-1*keys[i]];
}
for(int j = i;j<op_counter;j++){
	keys[j] = keys[j+1];
	if(j<op_counter-1)operations[j] = operations[j+1];
}
op_counter--;
i--;
}
}
else if(operations[i][0] == '.'&&operations[i][1] == '+'){
if(keys[i]>0){
if(keys[i+1]<0){
	mats[keys[i]]=mats[keys[i]].addbyelement(numbers[-1*keys[i+1]]);
	for(int j = i;j<op_counter-1;j++){
		keys[j+1] = keys[j+2];
		operations[j] = operations[j+1];
	}
	op_counter--;
	i--;
}
}
}
else if(operations[i][0] == '!'&&operations[i][1] == '-'){
if(keys[i]>0){
if(keys[i+1]>0){
	mats[keys[i]]-=mats[keys[i+1]];
}
else if(keys[i+1]<0){
	mats[keys[i]]+=(-1*numbers[-1*keys[i+1]]);
}
for(int j = i;j<op_counter-1;j++){
	keys[j+1] = keys[j+2];
	operations[j] = operations[j+1];
}
op_counter--;
i--;
}
else if(keys[i] < 0){
if(keys[i+1]>0){
	mats[keys[i+1]]+=(-1*numbers[-1*keys[i]]);
}
else if(keys[i+1]<0){
	numbers[-1*keys[i+1]]+=(-1*numbers[-1*keys[i]]);
}
for(int j = i;j<op_counter;j++){
	keys[j] = keys[j+1];
	if(j<op_counter-1)operations[j] = operations[j+1];
}
op_counter--;
i--;
}
}
else if(operations[i][0] == '.'&&operations[i][1] == '-'){
if(keys[i]>0){
if(keys[i+1]<0){
	mats[keys[i]]=mats[keys[i]].addbyelement(-1*numbers[-1*keys[i+1]]);
	for(int j = i;j<op_counter-1;j++){
		keys[j+1] = keys[j+2];
		operations[j] = operations[j+1];
	}
	op_counter--;
	i--;
}
}
}

}
return mats[keys[0]];
}
Matrix bigOperationReduce(string s2,Matrix* matrices,int &ptr,int &taken){//don't pass ptr itself ,don't pass matrices itself,let taken zero
	int start = 0;
	int end = 0;
	string s("");
	int ss = 0;
	for(int i=0;i<s2.length();i++){
		if(s2[i]==' '){
			s+= s2.substr(ss,i-ss);
			ss=i+1;
		}
	}
	s+= s2.substr(ss,s2.length()-ss);
	//cout<<s<<endl;
	string alpha = "abcdefghijklmnopqrtuvwxyz";
	string new_operation("");
	for(int i = 0; i <s.length();i++){
		int asci = (int) s[i];
		int num1 = 0;
		int num2 = 0;
		if ((asci == 115)){
			string tri_op ("");
			tri_op += s[i];
			int no1 = 0;
			int no2 = 0;
			for(int t = i+1;t < s.length();t++){
				tri_op += s[t];
				if(s[t] =='('){
					no1++;
				}
				else if(s[t] == ')'){
					no2++;
				}
				if(no1 > 0 && no1 == no2){
					i = t ;
					break;
				}
			}
			string tri_operator = tri_op.substr(0,tri_op.find("("));
			string inner_op = tri_op.substr(tri_op.find("(")+1,tri_op.length()-(tri_op.find("(")+2));
			Matrix inner_result = bigOperationReduce(inner_op,matrices,ptr,taken);
			Matrix outer_result ;
			if(tri_operator == "sin"){
				outer_result = Sin(inner_result);
			}
			else if (tri_operator == "sqrt"){
				outer_result = Sqrt(inner_result);
			}
			outer_result.name = alpha[taken];
			taken++;
			matrices[ptr] = outer_result;
			ptr++;
			new_operation += outer_result.name;
		}
else if(s[i] == '('){
	num1++;
	start = i+1;
	for(int j = i+1;j<s.length();j++){
		if(s[j] == '('){
			num1++;
		}
		else if (s[j] == ')'){
			num2++;
			if(num1 == num2){
				end = j-1;
				i = j ;
				break;
			}
		}
	}
	string smallOperation = s.substr(start,(end-start+1));
	Matrix solution;
	if(smallOperation.find('(') !=string::npos){

		solution = bigOperationReduce(smallOperation,matrices,ptr,taken);
	}
	else{
		solution = operationReduce(smallOperation,matrices,ptr);
	}
	solution.name = alpha[taken];
	taken++;
	matrices[ptr] = solution;
	ptr++;
	new_operation += solution.name;
}
else{
		new_operation += s[i];
}

}
//cout<<new_operation<<endl;
Matrix result = operationReduce(new_operation,matrices,ptr);
return result;
}

int main(int argc, char*argv[])
{
	// Matrix m(2,2,1.0,2.0,3.0,4.0);
	// Matrix r(2,2,1.0,1.0,1.0,1.0);
	//
	// Matrix c=m.matrix_divbymatrix(m,r);
	// print(c);

try{

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
// for (int i = 0; i < nLines; i++)
// { cout<<inputFileLines[i]<<endl;}

		for (int i = 0; i < nLines; i++)
		{

			int lineType = lineTest(inputFileLines[i]); //function returns true if line, false if operation

			int multiVariable = 0;

			multiVariable = testMultiVariables(inputFileLines[i]); //function tests if there multi variable in the same line and returns number of the variables

// 			if (lineType == 1)
//
// 			{
//
//
// 				// new algorithm starts here
//
// 				string line_after_sub = matrix_substituation(inputFileLines[i], matrices, ptr);
// 				string line_after_replace = Replace(line_after_sub);
// 				// cout<<"============="<<endl;
// 				// cout<<"line before sub: "<<inputFileLines[i]<<endl;
// 				// cout<<"after sub: "<<line_after_sub<<endl;
// 				// cout<<"after replace: "<<line_after_replace<<endl;
// 				// cout<<"============="<<endl;
// 				int nr = 0;
// 				char name;
// 				string* raw_input = stringToArray(line_after_replace, nr, name);
// 				// cout<<"************ raw input: *************"<<endl;
// 				//for(int b =0; b<nr; b++)
// 				// cout<<"line: "<<b<<raw_input[b]<<endl;
// 				// cout<<"**************"<<endl;
// 				string* finlized_input = new string[nr];
// 				for(int k=0; k<nr; k++ )
// 					{
// 						int case_ = case_checker(raw_input[k]);
//
// 					if(case_ == 0)
// 						{
// 							finlized_input[k] = checkOperations(raw_input[k]);
// 							// cout<<"after case 0: "<< finlized_input[k]<<endl;
// 						}
// 					if(case_== 1)
// 						{
// 							//cout<<"raw_input: "<<raw_input[k]<<endl;
// 							string temp = raw_input[k].substr(0, raw_input[k].length()-1);
// 							//cout<<"case 1 temp: "<<temp<<endl;
// 							finlized_input[k] = checkOperations(temp);
// 							//cout<<"after case 1: "<< finlized_input[k]<<endl;
//
// 						}
// 					if(case_ == 2)
// 						{
// 							//cout<<"raw_input: "<<raw_input[k]<<endl;
// 							//cout<<"after rereplace: "<<rereplace(raw_input[k])<<endl;
// 							// string t = checkOperations(raw_input[k]);
// 							// cout<<"case 2 t: "<<t<<endl;
// 							string temp = concat(rereplace(raw_input[k].substr(0,raw_input[k].length())));
// 							//cout<<"case 2 temp: "<<temp<<endl;
// 							finlized_input[k] = checkOperations(temp);
// 							//cout<<"after case 2: "<< finlized_input[k]<<endl;
// 						}
// 					}
//
// 				string mat_string = str_conc(finlized_input, nr, ';');
// 				//cout<<"final input: #############"<<endl;
// 				//for(int b =0; b<nr; b++)
// 				//cout<<"line : "<< b << " "<<finlized_input[b]<<endl;
// 				// cout<<mat_string<<endl;
// 				// new algorithm ends here
// 				//cout<<"##########"<<endl;
//
//           Matrix w(mat_string);
//           matrices[ptr] = w;
//           matrices[ptr].name = name;
//           ptr++;
// 					// cout<<matrices[ptr-1].getString()<<endl;
// 					// cout<<matrices[ptr-1].num_rows<<" "<<matrices[ptr-1].num_rows<<endl;
// 					// print(matrices[ptr-1]);cout<<'\n';
//
// }
if (lineType == 1)

{


	// new algorithm starts here

	string line_after_sub = matrix_substituation(inputFileLines[i], matrices, ptr);
	string line_after_replace = Replace(line_after_sub);
	// cout<<"============="<<endl;
	// cout<<"line before sub: "<<inputFileLines[i]<<endl;
	// cout<<"after sub: "<<line_after_sub<<endl;
	// cout<<"after replace: "<<line_after_replace<<endl;
	// cout<<"============="<<endl;
	int nr = 0;
	char name;
	string* raw_input = stringToArray(line_after_replace, nr, name);
	// cout<<"************ raw input: *************"<<endl;
	//for(int b =0; b<nr; b++)
	// cout<<"line: "<<b<<raw_input[b]<<endl;
	// cout<<"**************"<<endl;
	string* finlized_input = new string[nr];
	for(int k=0; k<nr; k++ )
		{
			int case_ = case_checker(raw_input[k]);

		if(case_ == 0)
			{
				finlized_input[k] = checkOperations(raw_input[k]);
				// cout<<"after case 0: "<< finlized_input[k]<<endl;
			}
		if(case_== 1)
			{
				//cout<<"raw_input: "<<raw_input[k]<<endl;
				string temp = raw_input[k].substr(0, raw_input[k].length()-1);
				//cout<<"case 1 temp: "<<temp<<endl;
				finlized_input[k] = checkOperations(temp);
				//cout<<"after case 1: "<< finlized_input[k]<<endl;

			}
		if(case_ == 2)
			{
				//cout<<"raw_input: "<<raw_input[k]<<endl;
				//cout<<"after rereplace: "<<rereplace(raw_input[k])<<endl;
				// string t = checkOperations(raw_input[k]);
				// cout<<"case 2 t: "<<t<<endl;
				string temp = concat(rereplace(raw_input[k].substr(0,raw_input[k].length())));
				//cout<<"case 2 temp: "<<temp<<endl;
				finlized_input[k] = checkOperations(temp);
				//cout<<"after case 2: "<< finlized_input[k]<<endl;
			}
		}
		string mat_string = str_conc(finlized_input, nr, ';');
//cout<<"final input: #############"<<endl;
//for(int b =0; b<nr; b++)
//cout<<"line : "<< b << " "<<finlized_input[b]<<endl;
// cout<<mat_string<<endl;
// new algorithm ends here
//cout<<"##########"<<endl;

	Matrix w(mat_string);
	matrices[ptr] = w;
	matrices[ptr].name = name;
	ptr++;
	// cout<<matrices[ptr-1].getString()<<endl;
	// cout<<matrices[ptr-1].num_rows<<" "<<matrices[ptr-1].num_rows<<endl;
	// print(matrices[ptr-1]);cout<<'\n';

}
// else if(lineType == 0){
// 	//cout<<"i am type zero"<<endl;
// 	int start = inputFileLines[i].find('=');
// 	string opStr = inputFileLines[i].substr(start+1);
// 	double result = bigOperationSolving(opStr);
// 	Matrix w(result);
//           matrices[ptr] = w;
//           matrices[ptr].name = inputFileLines[i][0];
//           ptr++;
//
// }
else if(lineType == 0){
	int start = inputFileLines[i].find('=');
	string opStr = inputFileLines[i].substr(start+1);
	double result = bigOperationSolving(opStr);
	Matrix w(result);
          matrices[ptr] = w;
          matrices[ptr].name = inputFileLines[i][0];
          ptr++;

}


// else if(lineType == 3)
// {
// 	Matrix H ;
// 	for(int q=0; q<ptr; q++)
// 	if(matrices[q].name == inputFileLines[i][0]) print(matrices[q]);
// 	//ptr++;
// 	//cout<<H.name<<" ="<<endl;
// 		//print(H);// cout<<"-----------"<<endl;
// }
else if(lineType == 3)
{
	Matrix H ;
	for(int q=0; q<ptr; q++)
	if(matrices[q].name == inputFileLines[i][0]) print(matrices[q]);
	//ptr++;
	//cout<<H.name<<" ="<<endl;
		//print(H);// cout<<"-----------"<<endl;
}



// else if (lineType == 4)
// {
// 	int nRows, nCol, s_type;
// 	dimnconstructors(inputFileLines[i], nRows, nCol, s_type);
// 	//cout<<s_type<<endl;
// 	switch (s_type) {
// 		case 0:
// 		{
// 			Matrix w = Zero(nRows, nCol);
// 			matrices[ptr] = w;
// 			matrices[ptr].name = inputFileLines[i][0];
// 			ptr++;
// 			break;
// 		}
// 		case 1:
// 		{
// 			Matrix w = One(nRows, nCol);
// 			matrices[ptr] = w;
// 			matrices[ptr].name = inputFileLines[i][0];
// 			ptr++;
// 			break;
// 		}
// 		case 2:
// 		{
// 			Matrix w = Eye(nRows, nCol);
// 			matrices[ptr] = w;
// 			matrices[ptr].name = inputFileLines[i][0];
// 			ptr++;
// 			break;
// 		}
// 		case 3:
// 		{
// 			Matrix w = Rand(nRows, nCol);
// 			matrices[ptr] = w;
// 			matrices[ptr].name = inputFileLines[i][0];
// 			ptr++;
// 			break;
// 		}
// 	}
//
// }
else if (lineType == 4)
{
	int nRows, nCol, s_type;
	dimnconstructors(inputFileLines[i], nRows, nCol, s_type);
	//cout<<s_type<<endl;
	switch (s_type) {
		case 0:
		{
			Matrix w = Zero(nRows, nCol);
			matrices[ptr] = w;
			matrices[ptr].name = inputFileLines[i][0];
			ptr++;
			break;
		}
		case 1:
		{
			Matrix w = One(nRows, nCol);
			matrices[ptr] = w;
			matrices[ptr].name = inputFileLines[i][0];
			ptr++;
			break;
		}
		case 2:
		{
			Matrix w = Eye(nRows, nCol);
			matrices[ptr] = w;
			matrices[ptr].name = inputFileLines[i][0];
			ptr++;
			break;
		}
		case 3:
		{
			Matrix w = Rand(nRows, nCol);
			matrices[ptr] = w;
			matrices[ptr].name = inputFileLines[i][0];
			ptr++;
			break;
		}
	}

}

// else
//
// {
//
//
//
//
// 		char in1, in2, out, operation;
// 	operationParsing(inputFileLines[i], in1, in2, out, operation);//function parses operation line to in1,in2,out,operation
//
// 	switch (operation)
//
// 	{
//
//
// 						case '+':
// 						{////////////////////////////put function that subtract two matrices out = in1 - in2 and print
// 						string zero = "[]";
// 						Matrix first;
// 						Matrix second;
// 						Matrix output;
// 						output.name = out;
// 						matrices[ptr] = output;
// 						ptr++;
//
//
// 						for (int i = 0; i < ptr; i++)
// 						{
// 							if (matrices[i].name == in1) {first = matrices[i];}
// 							if (matrices[i].name == in2) second = matrices[i];
// 							if (matrices[i].name == out)
// 							{output = first + second;
// 							 matrices[i] = output;
//
// 								}
// 						}
//
// 							//cout<<out<<" = "<<endl;
// 						//  cout<<matrices[ptr-1].name;
// 							//print( matrices[ptr-1] );
// 							//matrices[ptr].name=out;
//
//
//
//
// 								break;}
//
//
//
//
// 						case '-':
//
// 					{////////////////////////////put function that subtract two matrices out = in1 - in2 and print
// 					string zero = "[]";
// 					Matrix first;
// 					Matrix second;
// 					Matrix output;
// 					output.name = out;
// 					matrices[ptr] = output;
// 					ptr++;
//
//
// 					for (int i = 0; i < ptr; i++)
// 					{
// 						if (matrices[i].name == in1) {first = matrices[i];}
// 						if (matrices[i].name == in2) second = matrices[i];
// 						if (matrices[i].name == out)
// 						{output = first - second;
// 						 matrices[i] = output;
//
// 							}
// 					}
//
// 						//cout<<out<<" = "<<endl;
// 					//  cout<<matrices[ptr-1].name;
// 						//print( matrices[ptr-1] );
// 						//matrices[ptr].name=out;
//
//
//
//
// 							break;}
//
// 						case '*':
//
// 					/////////////////////////////put mulitplication function from matrix
// 					{////////////////////////////put function that subtract two matrices out = in1 - in2 and print
// 					string zero = "[]";
// 					Matrix first;
// 					Matrix second;
// 					Matrix output;
// 					output.name = out;
// 					matrices[ptr] = output;
// 					ptr++;
//
//
// 					for (int i = 0; i < ptr; i++)
// 					{
//
// 						if (matrices[i].name == in1) {first = matrices[i];}
// 						if (matrices[i].name == in2) second = matrices[i];
// 						if (matrices[i].name == out)
// 						{output = first * second;
// 						 matrices[i] = output;
//
// 							}
// 					}
//
// 						//cout<<out<<" = "<<endl;
// 					//  cout<<matrices[ptr-1].name;
// 						//print( matrices[ptr-1] );
// 						//matrices[ptr-1].name=out;
//
//
//
//
// 							break;}
//
//
//
// 						case '/':
// 						{////////////////////////////put function that subtract two matrices out = in1 - in2 and print
// 						string zero = "[]";
// 						Matrix first;
// 						Matrix second;
// 						Matrix output;
// 						output.name = out;
// 						matrices[ptr] = output;
// 						ptr++;
//
//
// 						for (int i = 0; i < ptr; i++)
// 						{
// 							if (matrices[i].name == in1) {first = matrices[i];}
// 							if (matrices[i].name == in2) second = matrices[i];
// 							if (matrices[i].name == out)
// 							{output = first / second;
// 							 matrices[i] = output;
//
// 								}
// 						}
//
// 							//cout<<out<<" = "<<endl;
// 							//print( matrices[ptr-1] );
// 							//matrices[ptr-1].name=out;
//
//
//
//
// 								break;}
// 					////////////////////////////put division function
//
//
//
// 						case '1':
// 				{  string zero = "[]";
// 						Matrix first;
// 						Matrix second;
// 						Matrix output;
// 						output.name = out;
// 						matrices[ptr] = output;
// 						ptr++;
//
//
// 						for (int i = 0; i < ptr; i++)
// 						{
// 							if (matrices[i].name == in1) {first = matrices[i];}
// 							if (matrices[i].name == in2) second = matrices[i];
// 							if (matrices[i].name == out)
// 							{output =first.getTranspose();
// 							// matrices[i] = output;
//
// 								}
// 						}
//
// 							//cout<<out<<" = "<<endl;
// 						//  cout<<matrices[ptr-1].name;
// 							//print( matrices[ptr-1] );
// 							//matrices[ptr-1].name=out;
//
// 						break;}
//
//
//
//
// 						case'.':
// 						{
// 													 int num = (int)in1 - 48;
//
//
//
// 							/////////////////////////put division function tht divide num/matrix in2  = matrix out
// 							string zero = "[]";
// 							Matrix first(zero);
// 							Matrix output(zero);
// 							output.name = out;
// 							matrices[ptr] = output;
// 							ptr++;
// 							for (int i = 0; i < ptr; i++)
// 							{
// 								if (matrices[i].name == in2) {first = matrices[i];}
// 							}
// 							output = first;
// 								for(int r = 0; r<first.num_rows; r++ )
// 								{
// 										for(int c = 0; c<first.num_col; c++)
// 										{
// 											output.values[r][c] = num/first.values[r][c];
// 										}
// 								}
// 								//matrices[ptr-1]=output;
// 								//cout<<out<<" = "<<endl;
// 								//print(output);
// 								//matrices[ptr-1].name=out;
//
//
// 							break;}
//
// 	}
//
// }

else

{
	int newptr = ptr;
	int taken = 0;
	Matrix* newmatrices = new Matrix[100];
	for(int i9 =0;i9<ptr;i9++){
		newmatrices[i9] = matrices[i9];
	}
	int start = inputFileLines[i].find('=');
	string opStr = inputFileLines[i].substr(start+1);
	Matrix result = bigOperationReduce(opStr,newmatrices,newptr,taken);
          matrices[ptr] = result;
          matrices[ptr].name = inputFileLines[i][0];
          ptr++;
}
			// cout<<"loop mat_string: "<<i<<"      "<<matrices[i].getString()<<endl;
			// cout<<"loop"<<i<<"      "<<inputFileLines[i]<<endl;
			// cout<<"oooooooooooooooooooooooooooooooooooooooooo"<<endl;
		}
			// cout<<"loop mat_string: "<<i<<"      "<<matrices[i].getString()<<endl;
			// cout<<"loop"<<i<<"      "<<inputFileLines[i]<<endl;
			// cout<<"oooooooooooooooooooooooooooooooooooooooooo"<<endl;



	for(int q=0; q<ptr; q++)
	{//cout<<matrices[q].name<<" = "<<endl;
	 print(matrices[q]);} //cout<<"-----------"<<endl;}
 }

	if (argc <= 1)

	{

		string line;

		while (getline(cin, line))

		{
			int lineType = lineTest(line); //function returns true if line, false if operation

			int multiVariable = 0;

			multiVariable = testMultiVariables(line); //function tests if there multi variable in the same line and returns number of the variables

			if (lineType == 1)

			{


				// new algorithm starts here

				string line_after_sub = matrix_substituation(line, matrices, ptr);
				string line_after_replace = Replace(line_after_sub);
				// cout<<"============="<<endl;
				// cout<<"line before sub: "<<inputFileLines[i]<<endl;
				// cout<<"after sub: "<<line_after_sub<<endl;
				// cout<<"after replace: "<<line_after_replace<<endl;
				// cout<<"============="<<endl;
				int nr = 0;
				char name;
				string* raw_input = stringToArray(line_after_replace, nr, name);
				// cout<<"************ raw input: *************"<<endl;
				//for(int b =0; b<nr; b++)
				// cout<<"line: "<<b<<raw_input[b]<<endl;
				// cout<<"**************"<<endl;
				string* finlized_input = new string[nr];
				for(int k=0; k<nr; k++ )
					{
						int case_ = case_checker(raw_input[k]);

					if(case_ == 0)
						{
							finlized_input[k] = checkOperations(raw_input[k]);
							// cout<<"after case 0: "<< finlized_input[k]<<endl;
						}
					if(case_== 1)
						{
							//cout<<"raw_input: "<<raw_input[k]<<endl;
							string temp = raw_input[k].substr(0, raw_input[k].length()-1);
							//cout<<"case 1 temp: "<<temp<<endl;
							finlized_input[k] = checkOperations(temp);
							//cout<<"after case 1: "<< finlized_input[k]<<endl;

						}
					if(case_ == 2)
						{
							//cout<<"raw_input: "<<raw_input[k]<<endl;
							//cout<<"after rereplace: "<<rereplace(raw_input[k])<<endl;
							// string t = checkOperations(raw_input[k]);
							// cout<<"case 2 t: "<<t<<endl;
							string temp = concat(rereplace(raw_input[k].substr(0,raw_input[k].length())));
							//cout<<"case 2 temp: "<<temp<<endl;
							finlized_input[k] = checkOperations(temp);
							//cout<<"after case 2: "<< finlized_input[k]<<endl;
						}
					}

				string mat_string = str_conc(finlized_input, nr, ';');
				//cout<<"final input: #############"<<endl;
				//for(int b =0; b<nr; b++)
				//cout<<"line : "<< b << " "<<finlized_input[b]<<endl;
				// cout<<mat_string<<endl;
				// new algorithm ends here
				//cout<<"##########"<<endl;

          Matrix w(mat_string);
          matrices[ptr] = w;
          matrices[ptr].name = name;
					print(matrices[ptr]);
          ptr++;
					// cout<<matrices[ptr-1].getString()<<endl;
					// cout<<matrices[ptr-1].num_rows<<" "<<matrices[ptr-1].num_rows<<endl;
					// print(matrices[ptr-1]);cout<<'\n';

}
else if(lineType == 0){
	int start = line.find('=');
	string opStr = line.substr(start+1);
	double result = bigOperationSolving(opStr);
	Matrix w(result);
          matrices[ptr] = w;
          matrices[ptr].name = line[0];
					print(matrices[ptr]);

					ptr++;

}

else if(lineType == 3)
{
	Matrix H ;
	for(int q=0; q<ptr; q++)
	if(matrices[q].name == line[0]) print(matrices[q]);
	//ptr++;
	//cout<<H.name<<" ="<<endl;
		//print(H);// cout<<"-----------"<<endl;
}


else if (lineType == 4)
{
	int nRows, nCol, s_type;
	dimnconstructors(line, nRows, nCol, s_type);
	//cout<<s_type<<endl;
	switch (s_type) {
		case 0:
		{
			Matrix w = Zero(nRows, nCol);
			matrices[ptr] = w;
			matrices[ptr].name = line[0];
			print(matrices[ptr]);
			ptr++;
			break;
		}
		case 1:
		{
			Matrix w = One(nRows, nCol);
			matrices[ptr] = w;
			matrices[ptr].name = line[0];
			print(matrices[ptr]);
			ptr++;
			break;
		}
		case 2:
		{
			Matrix w = Eye(nRows, nCol);
			matrices[ptr] = w;
			matrices[ptr].name = line[0];
			print(matrices[ptr]);
			ptr++;
			break;
		}
		case 3:
		{
			Matrix w = Rand(nRows, nCol);
			matrices[ptr] = w;
			matrices[ptr].name = line[0];
			print(matrices[ptr]);
			ptr++;
			break;
		}
	}

}

// else
//
// {
//
// 		char in1, in2, out, operation;
// 	operationParsing(line, in1, in2, out, operation);//function parses operation line to in1,in2,out,operation
//
// 	switch (operation)
//
// 	{
//
//
// 						case '+':
// 						{////////////////////////////put function that subtract two matrices out = in1 - in2 and print
// 						string zero = "[]";
// 						Matrix first;
// 						Matrix second;
// 						Matrix output;
// 						output.name = out;
// 						matrices[ptr] = output;
// 						ptr++;
//
//
// 						for (int i = 0; i < ptr; i++)
// 						{
// 							if (matrices[i].name == in1) {first = matrices[i];}
// 							if (matrices[i].name == in2) second = matrices[i];
// 							if (matrices[i].name == out)
// 							{output = first + second;
// 							 matrices[i] = output;
//
// 								}
// 						}
// print(matrices[ptr]);
// 							//cout<<out<<" = "<<endl;
// 						//  cout<<matrices[ptr-1].name;
// 							//print( matrices[ptr-1] );
// 							//matrices[ptr].name=out;
//
//
//
//
// 								break;}
//
//
//
//
// 						case '-':
//
// 					{////////////////////////////put function that subtract two matrices out = in1 - in2 and print
// 					string zero = "[]";
// 					Matrix first;
// 					Matrix second;
// 					Matrix output;
// 					output.name = out;
// 					matrices[ptr] = output;
// 					ptr++;
//
//
// 					for (int i = 0; i < ptr; i++)
// 					{
// 						if (matrices[i].name == in1) {first = matrices[i];}
// 						if (matrices[i].name == in2) second = matrices[i];
// 						if (matrices[i].name == out)
// 						{output = first - second;
// 						 matrices[i] = output;
//
// 							}
// 					}
// print(matrices[ptr]);
// 						//cout<<out<<" = "<<endl;
// 					//  cout<<matrices[ptr-1].name;
// 						//print( matrices[ptr-1] );
// 						//matrices[ptr].name=out;
//
//
//
//
// 							break;}
//
// 						case '*':
//
// 					/////////////////////////////put mulitplication function from matrix
// 					{////////////////////////////put function that subtract two matrices out = in1 - in2 and print
// 					string zero = "[]";
// 					Matrix first;
// 					Matrix second;
// 					Matrix output;
// 					output.name = out;
// 					matrices[ptr] = output;
// 					ptr++;
//
//
// 					for (int i = 0; i < ptr; i++)
// 					{
//
// 						if (matrices[i].name == in1) {first = matrices[i];}
// 						if (matrices[i].name == in2) second = matrices[i];
// 						if (matrices[i].name == out)
// 						{output = first * second;
// 						 matrices[i] = output;
//
// 							}
// 					}
// print(matrices[ptr]);
// 						//cout<<out<<" = "<<endl;
// 					//  cout<<matrices[ptr-1].name;
// 						//print( matrices[ptr-1] );
// 						//matrices[ptr-1].name=out;
//
//
//
//
// 							break;}
//
//
//
// 						case '/':
// 						{////////////////////////////put function that subtract two matrices out = in1 - in2 and print
// 						string zero = "[]";
// 						Matrix first;
// 						Matrix second;
// 						Matrix output;
// 						output.name = out;
// 						matrices[ptr] = output;
// 						ptr++;
//
//
// 						for (int i = 0; i < ptr; i++)
// 						{
// 							if (matrices[i].name == in1) {first = matrices[i];}
// 							if (matrices[i].name == in2) second = matrices[i];
// 							if (matrices[i].name == out)
// 							{output = first / second;
// 							 matrices[i] = output;
//
// 								}
// 						}
// print(matrices[ptr]);
// 							//cout<<out<<" = "<<endl;
// 							//print( matrices[ptr-1] );
// 							//matrices[ptr-1].name=out;
//
//
//
//
// 								break;}
// 					////////////////////////////put division function
//
//
//
// 						case '1':
// 				{  string zero = "[]";
// 						Matrix first;
// 						Matrix second;
// 						Matrix output;
// 						output.name = out;
// 						matrices[ptr] = output;
// 						ptr++;
//
//
// 						for (int i = 0; i < ptr; i++)
// 						{
// 							if (matrices[i].name == in1) {first = matrices[i];}
// 							if (matrices[i].name == in2) second = matrices[i];
// 							if (matrices[i].name == out)
// 							{output =first.getTranspose();
// 							// matrices[i] = output;
//
// 								}
// 						}
// print(matrices[ptr]);
// 							//cout<<out<<" = "<<endl;
// 						//  cout<<matrices[ptr-1].name;
// 							//print( matrices[ptr-1] );
// 							//matrices[ptr-1].name=out;
//
// 						break;}
//
//
//
//
// 						case'.':
// 						{
// 													 int num = (int)in1 - 48;
//
//
//
// 							/////////////////////////put division function tht divide num/matrix in2  = matrix out
// 							string zero = "[]";
// 							Matrix first(zero);
// 							Matrix output(zero);
// 							output.name = out;
// 							matrices[ptr] = output;
// 							ptr++;
// 							for (int i = 0; i < ptr; i++)
// 							{
// 								if (matrices[i].name == in2) {first = matrices[i];}
// 							}
// 							output = first;
// 								for(int r = 0; r<first.num_rows; r++ )
// 								{
// 										for(int c = 0; c<first.num_col; c++)
// 										{
// 											output.values[r][c] = num/first.values[r][c];
// 										}
// 								}
// 								print(matrices[ptr]);
// 								//matrices[ptr-1]=output;
// 								//cout<<out<<" = "<<endl;
// 								//print(output);
// 								//matrices[ptr-1].name=out;
//
//
// 							break;}
//
// 	}
//
// }
else

{
	int newptr = ptr;
	int taken = 0;
	Matrix* newmatrices = new Matrix[100];
	for(int i9 =0;i9<ptr;i9++){
		newmatrices[i9] = matrices[i9];
	}
	int start = line.find('=');
	string opStr = line.substr(start+1);
	Matrix result = bigOperationReduce(opStr,newmatrices,newptr,taken);
          matrices[ptr] = result;
          matrices[ptr].name = line[0];
					print(matrices[ptr]);
          ptr++;
}
			// cout<<"loop mat_string: "<<i<<"      "<<matrices[i].getString()<<endl;
			// cout<<"loop"<<i<<"      "<<inputFileLines[i]<<endl;
			// cout<<"oooooooooooooooooooooooooooooooooooooooooo"<<endl;
		}
//
//
}
}
catch (int e){

	if(e==4)
	cout<<"matrix dimension inavlid"<<endl;
	if(e==1)
	cout<<"syntax error"<<endl;
	if(e==2)
	cout<<"operand missed"<<endl;
if(e==3)
cout<<"undefined"<<endl;

}

  return 0;
}
