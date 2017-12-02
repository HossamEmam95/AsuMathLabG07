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
//this method calculate operation represnted by string argument 
// the function perform power operation then mul & division then add & sub
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
int main(){

	double d = operationSolving("1+8*2/8-9/3+5");
	cout << d;
	return 0;
}
