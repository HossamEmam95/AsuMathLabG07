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
	  for(int i=0; i<m.num_rows; i++)
	  {
	    for(int j=0; j<m.num_col; j++)
	    {
	      cout<<m.values[i][j]<<" ";
	    }
	    cout<<endl;
	  }
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

//functions that concat to matrices together.
string concat(string s){ //important : this string contains two matrices not more not less
	string output  = "[";
	Matrix matrix1("[]");
	Matrix matrix2("[]");
	char concatOperator;
	int i = 0;
	for(i;i < s.length();i++){
		string str = "";
		int num1 = 0;
		int num2 = 0;
		if(s[i] == '[')	{
			str += s[i];
			num1++;
			for(int t = i+1;t < s.length();t++){
				str += s[t];
				if(s[t] =='['){
					num1++;
				}
				else if(s[t] == ']'){
					num2++;
				}
				if(num1 == num2){
					i = t ;
					break;
				}
			}
			concatOperator = s[i+1];
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
				if(s[t] =='['){
					num1++;
				}
				else if(s[t] == ']'){
					num2++;
				}
				if(num1 == num2){
					i = t ;
					break;
				}
			}
			Matrix temp(str);
			matrix2 = temp;
			break;
		}
	}
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
		cout<<"==========="<<endl;
		cout<<"array: "<<array[i]<<endl;
		cout<<"before op: "<<output_string<<endl;

		output_string = output_string + array[i].substr(1, array[i].length()-2) + separator;
		cout<<"after op: "<<output_string<<endl;
		cout<<"==========="<<endl;
	}
	output_string += "]";
	return output_string ;
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
// for (int i = 0; i < nLines; i++)
// { cout<<inputFileLines[i]<<endl;}

		for (int i = 0; i < nLines; i++)
		{

			bool lineType = lineTest(inputFileLines[i]); //function returns true if line, false if operation

			int multiVariable = 0;

			multiVariable = testMultiVariables(inputFileLines[i]); //function tests if there multi variable in the same line and returns number of the variables

			if (lineType)

			{


				// new algorithm starts here

				string line_after_sub = matrix_substituation(inputFileLines[i], matrices, ptr);
				string line_after_replace = Replace(line_after_sub);//cout<<line_after_replace<<endl;
				int nr = 0;
				char name;
				string* raw_input = stringToArray(line_after_replace, nr, name);
				// for(int b =0; b<nr; b++)
				// cout<<raw_input[b]<<endl<<"-----------"<<endl;
				string* finlized_input = new string[nr];
				for(int k=0; k<nr; k++ )
					{
						int case_ = case_checker(raw_input[k]);

					if(case_ == 0)
						{
							finlized_input[k] = checkOperations(raw_input[k]);
						}
					if(case_== 1)
						{
							string temp = raw_input[k].substr(1, raw_input[k].length()-1);
							finlized_input[k] = checkOperations(temp);

						}
					if(case_ == 2)
						{
							string temp = concat(rereplace(raw_input[k]));
							finlized_input[k] = checkOperations(temp);

						}
					}

				string mat_string = str_conc(finlized_input, nr, ';');
				for(int b =0; b<nr; b++)
				cout<<finlized_input[b]<<endl<<"-----------"<<endl;
				// cout<<mat_string<<endl;
				// new algorithm ends here


          Matrix w(mat_string);
          matrices[ptr] = w;
          matrices[ptr].name = name;
          ptr++;
					// cout<<matrices[ptr-1].getString()<<endl;
					// cout<<matrices[ptr-1].num_rows<<" "<<matrices[ptr-1].num_rows<<endl;
					// print(matrices[ptr-1]);cout<<'\n';

}
			// else
			//
			// {
			//
  		// 		char in1, in2, out, operation;
			// 	operationParsing(inputFileLines[i], in1, in2, out, operation);//function parses operation line to in1,in2,out,operation
			//
      //   switch (operation)
			//
			// 	{
			//
			//
      //     				case '+':
      //             {////////////////////////////put function that subtract two matrices out = in1 - in2 and print
      //             string zero = "[]";
      //             Matrix first;
      //             Matrix second;
      //             Matrix output;
      //             output.name = out;
      //             matrices[ptr] = output;
      //             ptr++;
			//
			//
      //             for (int i = 0; i < ptr; i++)
      //             {
      //               if (matrices[i].name == in1) {first = matrices[i];}
      //               if (matrices[i].name == in2) second = matrices[i];
      //               if (matrices[i].name == out)
      //               {output = first + second;
      //                matrices[i] = output;
			//
      //                 }
      //             }
			//
      //               cout<<out<<" = "<<endl;
      //             //  cout<<matrices[ptr-1].name;
      //               print( matrices[ptr-1] );
      //               matrices[ptr-1].name=out;
			//
      //                 break;}
			//
      //     				case '-':
			//
      //     			{////////////////////////////put function that subtract two matrices out = in1 - in2 and print
      //           string zero = "[]";
      //           Matrix first;
      //           Matrix second;
      //           Matrix output;
      //           output.name = out;
      //           matrices[ptr] = output;
      //           ptr++;
			//
			//
      //           for (int i = 0; i < ptr; i++)
      //           {
      //             if (matrices[i].name == in1) {first = matrices[i];}
      //             if (matrices[i].name == in2) second = matrices[i];
      //             if (matrices[i].name == out)
      //             {output = first - second;
      //              matrices[i] = output;
			//
      //               }
      //           }
			//
      //             cout<<out<<" = "<<endl;
      //           //  cout<<matrices[ptr-1].name;
      //             print( matrices[ptr-1] );
      //             matrices[ptr-1].name=out;
			//
      //     					break;}
			//
      //     				case '*':
			//
      //     			/////////////////////////////put mulitplication function from matrix
      //           {////////////////////////////put function that subtract two matrices out = in1 - in2 and print
      //           string zero = "[]";
      //           Matrix first;
      //           Matrix second;
      //           Matrix output;
      //           output.name = out;
      //           matrices[ptr] = output;
      //           ptr++;
			//
			//
      //           for (int i = 0; i < ptr; i++)
      //           {
			//
      //             if (matrices[i].name == in1) {first = matrices[i];}
      //             if (matrices[i].name == in2) second = matrices[i];
      //             if (matrices[i].name == out)
      //             {output = first * second;
      //              matrices[i] = output;
			//
      //               }
      //           }
			//
      //             cout<<out<<" = "<<endl;
      //           //  cout<<matrices[ptr-1].name;
      //             print( matrices[ptr-1] );
      //             matrices[ptr-1].name=out;
			//
      //               break;}
			//
			//
      //     				case '/':
      //             {////////////////////////////put function that subtract two matrices out = in1 - in2 and print
      //             string zero = "[]";
      //             Matrix first;
      //             Matrix second;
      //             Matrix output;
      //             output.name = out;
      //             matrices[ptr] = output;
      //             ptr++;
			//
			//
      //             for (int i = 0; i < ptr; i++)
      //             {
      //               if (matrices[i].name == in1) {first = matrices[i];}
      //               if (matrices[i].name == in2) second = matrices[i];
      //               if (matrices[i].name == out)
      //               {output = first / second;
      //                matrices[i] = output;
			//
      //                 }
      //             }
			//
      //               cout<<out<<" = "<<endl;
      //             //  cout<<matrices[ptr-1].name;
      //               print( matrices[ptr-1] );
      //               matrices[ptr-1].name=out;
			//
      //                 break;}
			//
			//
      //     				case '1':
      //         {  string zero = "[]";
      //             Matrix first;
      //             Matrix second;
      //             Matrix output;
      //             output.name = out;
      //             matrices[ptr] = output;
      //             ptr++;
			//
			//
      //             for (int i = 0; i < ptr; i++)
      //             {
      //               if (matrices[i].name == in1) {first = matrices[i];}
      //               if (matrices[i].name == in2) second = matrices[i];
      //               if (matrices[i].name == out)
      //               {output =first.getTranspose();
      //                matrices[i] = output;
			//
      //                 }
      //             }
			//
      //               cout<<out<<" = "<<endl;
      //             //  cout<<matrices[ptr-1].name;
      //               print( matrices[ptr-1] );
      //               matrices[ptr-1].name=out;
			//
      //             break;}
			//
			//
			//
			//
      //     				case'.':
      //             {
      //                            int num = (int)in1 - 48;
			//
			//
			//
      //               /////////////////////////put division function tht divide num/matrix in2  = matrix out
      //               string zero = "[]";
      //               Matrix first(zero);
      //               Matrix output(zero);
      //               output.name = out;
      //               matrices[ptr] = output;
      //               ptr++;
      //               for (int i = 0; i < ptr; i++)
      //               {
      //                 if (matrices[i].name == in2) {first = matrices[i];}
      //               }
      //               output = first;
      //                 for(int r = 0; r<first.num_rows; r++ )
      //                 {
      //                     for(int c = 0; c<first.num_col; c++)
      //                     {
      //                       output.values[r][c] = num/first.values[r][c];
      //                     }
      //                 }
      //                 matrices[ptr-1]=output;
      //                 cout<<out<<" = "<<endl;
      //                 print(output);
			//
			//
      //               break;}
			//
				// }

			// }
			cout<<"loop"<<i<<"      "<<inputFileLines[i]<<endl;

		}
	}

	// for(int q=0; q<ptr; q++)
	// {cout<<endl; print(matrices[q]); cout<<"-----------"<<endl;}

// 	if (argc <= 1)
//
// 	{
//
// 		string line;
//
// 		while (getline(cin, line))
//
// 		{
//
// 			int multiVariable = 0;
//
// 			multiVariable = testMultiVariables(line); //function tests if there multi variable in the same line and returns number of the variables
//
// 			cout << ">";
//
// 			bool lineType = lineTest(line);
//
// 			if (lineType)
//
// 			{
//
// 				int nR, nC;
//
// 				char *name = new char[multiVariable];
//
// 				getMatrixDimension(line, nR, nC); //Function gets num_colums,num_row
//
// 				string m = ""; //array of values
//
// 				stringParsing(line, m, name); //function returns array of double values, name of the matrix
//
//
// 				for (int j = 0; j < multiVariable; j++)
//
// 				{
//
// 					///Put Matrix Constructor using nR,nC,"""""""""""""name[j]""""""""""""",value
//           Matrix w(m);
//           matrices[ptr] = w;
//           matrices[ptr].name = name[j];
//           ptr++;
//
//
// 				}
//
// 				if (line.rfind(';') < line.rfind(']'))
//
// 				{
//
// 					//////////////////////////////////////Get deteriment and print it
//           for (int i = 0; i<multiVariable; i++)
//           {
//             cout<<name[i]<<" = "<<endl;
//             print(matrices[ptr-1]);
//           }
// 				}
//
// 			}
//
// 			else
//
// 			{
//
// 				char in1, in2, out, operation;
//
// 				operationParsing(line, in1, in2, out, operation);//function parses operation line to in1,in2,out,operation
// 				switch (operation)
//
// 				{
//           case '+':{
//             ////////////////////////////put function that Adds 2 Matrices :D out = in1 + in2  and print them
//               string zero = "[]";
//               Matrix first;
//               Matrix second;
//               Matrix output;
//               output.name = out;
//               matrices[ptr] = output;
//               ptr++;
//
//
//               for (int i = 0; i < ptr; i++)
//               {
//                 if (matrices[i].name == in1) {first = matrices[i];}
//                 if (matrices[i].name == in2) second = matrices[i];
//                 if (matrices[i].name == out)
//                 {output = first + second;
//                  matrices[i] = output;
//
//                   }
//               }
//
//                 cout<<out<<" = ";
//               //  cout<<matrices[ptr-1].name;
//                 print( matrices[ptr-1] );
//                 matrices[ptr-1].name=out;
//
//
//
//
//             break;}
//
//           case '-':{
//
//             string zero = "[]";
//             Matrix first;
//             Matrix second;
//             Matrix output;
//             output.name = out;
//             matrices[ptr] = output;
//             ptr++;
//
//
//             for (int i = 0; i < ptr; i++)
//             {
//               if (matrices[i].name == in1) {first = matrices[i];}
//               if (matrices[i].name == in2) second = matrices[i];
//               if (matrices[i].name == out)
//               {output = first - second;
//                matrices[i] = output;
//
//                 }
//             }
//
//               cout<<out<<" = ";
//             //  cout<<matrices[ptr-1].name;
//               print( matrices[ptr-1] );
//               matrices[ptr-1].name=out;
//
//
//             break;}
//
//           case '*':{
//             string zero = "[]";
//             Matrix first;
//             Matrix second;
//             Matrix output;
//             output.name = out;
//             matrices[ptr] = output;
//             ptr++;
//
//
//             for (int i = 0; i < ptr; i++)
//             {
//               if (matrices[i].name == in1) {first = matrices[i];}
//               if (matrices[i].name == in2) second = matrices[i];
//               if (matrices[i].name == out)
//               {output = first * second;
//                matrices[i] = output;
//
//                 }
//             }
//
//               cout<<out<<" = ";
//             //  cout<<matrices[ptr-1].name;
//               print( matrices[ptr-1] );
//               matrices[ptr-1].name=out;
//
//
//
//
//           break;
//         }
//
//           case '/':{
//
//             string zero = "[]";
//             Matrix first;
//             Matrix second;
//             Matrix output;
//             output.name = out;
//             matrices[ptr] = output;
//             ptr++;
//
//
//             for (int i = 0; i < ptr; i++)
//             {
//               if (matrices[i].name == in1) {first = matrices[i];}
//               if (matrices[i].name == in2) second = matrices[i];
//               if (matrices[i].name == out)
//               {output = first / second;
//                matrices[i] = output;
//
//                 }
//             }
//
//               cout<<out<<" = ";
//             //  cout<<matrices[ptr-1].name;
//               print( matrices[ptr-1] );
//               matrices[ptr-1].name=out;
//
//
//
//
//
//             break;}
//
//           case '1':{
//             string zero = "[]";
//             Matrix first;
//             Matrix second;
//             Matrix output;
//             output.name = out;
//             matrices[ptr] = output;
//             ptr++;
//
//
//             for (int i = 0; i < ptr; i++)
//             {
//               if (matrices[i].name == in1) {first = matrices[i];}
//               if (matrices[i].name == in2) second = matrices[i];
//               if (matrices[i].name == out)
//               {output =first.getTranspose();
//                matrices[i] = output;
//
//                 }
//             }
//
//               cout<<out<<" = ";
//             //  cout<<matrices[ptr-1].name;
//               print( matrices[ptr-1] );
//               matrices[ptr-1].name=out;
//
//
//
//
//
//
//
//             break;}
//
//           case'.':{
//
//             int num = (int)in1 - 48;
//
//
//
//             /////////////////////////put division function tht divide num/matrix in2  = matrix out
//             string zero = "[]";
//             Matrix first(zero);
//             Matrix output(zero);
//             output.name = out;
//             matrices[ptr] = output;
//             ptr++;
//             for (int i = 0; i < ptr; i++)
//             {
//               if (matrices[i].name == in2) {first = matrices[i];}
//             }
//             output = first;
//               for(int r = 0; r<first.num_rows; r++ )
//               {
//                   for(int c = 0; c<first.num_col; c++)
//                   {
//                     output.values[r][c] = num/first.values[r][c];
//                   }
//               }
//               matrices[ptr-1]=output;
//               cout<<out<<" = "<<endl;
//               print(output);
//
//
//             break;}
//
//
// 				}
//
			// }

		// }

	// }

  return 0;
}
