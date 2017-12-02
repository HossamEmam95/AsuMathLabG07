#include <iostream>
#include <ostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <cstdarg>
#include "cmath"
using namespace std;
double operationSolving(string s){

	double result;
	int op_counter = 0;

	for(int i =0;i<s.length();i++){
		if(s[i] =='+'||s[i] =='-'||s[i] =='*'||s[i] =='/'||s[i] =='^'||s[i] =='%') op_counter++;
	}

	char* operations = new char[op_counter];
	double* numbers = new double [op_counter+1];
	int pos = 0;
	int counter = 0;
	for(int i =0;i<s.length();i++){
		if(s[i] =='+'||s[i] =='-'||s[i] =='*'||s[i] =='/'||s[i] =='^'||s[i] =='%'){
			string s1 = s.substr(pos,i-pos);
			char* s2 = new char[s1.length()];
			for(int k = 0;k<s1.length();k++){
				s2[k] = s1[k];
			}
			numbers[counter] = atof(s2);
			operations[counter] = s[i];
			pos = i+1;
			counter++;
		}
	}
	string s1 = s.substr(pos,s.length()-1);
	char* s2 = new char[s1.length()];
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
		int num1 = 0;
		int num2 = 0;
		if(s[i] == '('){
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
			cout<<"("<<smallOperation<<")"<<endl;
			new_operation += buffer;
		}
		else{
				new_operation += s[i];
		}
	}
	result = operationSolving(new_operation);
	return result;	
}



int main(){

	double d = bigOperationSolving("(1.2 + 3.4 - 5.6)/(2.1*3.2 + 4.6) -12.1*3.1 + (1.2 + 5.2)^(4/(3.2+5.6))");
	cout << d<<endl;
	return 0;
}
