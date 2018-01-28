#include <iostream>
#include <ostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <cstdarg>
#include "cmath"
#include "header.h"
#include "ctime"
using namespace std;
CComplex operationSolving(string s){

	CComplex result;
	int op_counter = 0;

	for(int i =0;i<s.length();i++){
		if(s[i] =='+'||s[i] =='-'||s[i] =='*'||s[i] =='/'||s[i] =='^'||s[i] =='%') {
			op_counter++;
			i++;
		}
	}

	char* operations = new char[op_counter];
	CComplex* numbers = new CComplex [op_counter+1];
	int pos = 0;
	int counter = 0;
	string s1 ;
	char* s2;
	for(int i =0;i<s.length();i++){
		if(s[i] =='+'||s[i] =='-'||s[i] =='*'||s[i] =='/'||s[i] =='^'||s[i] =='%'){
			
			s1 = s.substr(pos,i-pos);
			numbers[counter] = CComplex(s1);
			
			operations[counter] = s[i];
			pos = i+1;
			counter++;
			if(s[i+1] == '-'){i++;}
		}
	}
	
	s1 = s.substr(pos,s.length()-pos);
	
	numbers[counter] = CComplex(s1);
	
	for(int i =0;i<op_counter;i++){
		if(operations[i] == '^'){
			CComplex C = numbers[i];
			double d = numbers[i+1].magnitude();
			numbers[i] = C^d;
			cout<<numbers[i]<<endl;
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
			numbers[i] =((int) (numbers[i].magnitude()))%((int)(numbers[i+1].magnitude()));
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

CComplex bigOperationSolving(string s){
	CComplex result;
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
			CComplex inner_result = bigOperationSolving(inner_op);
			CComplex outer_result ;
			if(tri_operator == "sin"){
				outer_result = sin(inner_result.magnitude());
			}
			else if (tri_operator == "cos"){
				outer_result = cos(inner_result.magnitude());
			}
			else if (tri_operator == "tan"){
				outer_result = tan(inner_result.magnitude());
			}
			else if (tri_operator == "sqrt"){
				outer_result = sqrt(inner_result.magnitude());
			}
			char buffer[100];
			double n = snprintf(buffer,100,"%lf,%lfi",outer_result.real(),outer_result.imaginary());
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
			CComplex solution;
			if(smallOperation.find('(') !=string::npos){
				
				solution = bigOperationSolving(smallOperation);
			}
			else{
				solution = operationSolving(smallOperation);
			}
			char buffer[100];
			double n = snprintf(buffer,100,"%lf,%lfi",solution.real(),solution.imaginary());
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
	CComplex C = operationSolving("-1.000000,0.000000i/11.320000,0.000000i-12.1*3.1+6.400000,0.000000i^0.454545,0.000000i");
	cout <<C<<endl;
	return 0;
}
