#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>
#include <algorithm>
#include<fstream>
#include <climits>
#include "cmath"
#include "ctime"
using namespace std;

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
