// Constructors.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;
//function returns true if (rand,ones,zeros,eye) else false
bool testnconstructors(string s)
{
	if ((s.find("zeros") != std::string::npos) || (s.find("ones") != std::string::npos) || (s.find("eye") != std::string::npos) || ((s.find("rand") != std::string::npos)))
	{
		return true;
	}
	else
		return false;
}
//function takes (rand,ones,zeros,eye) as a string line returns type 0 if zeros, 1 if ones, 2 if eye, 3 if rand
// and also returns the number of rows and columns
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
}
//for testing
//int main()
//{
//	string A = "D = rand(4,4)";
//	string B = "E = eye(4, 4)";
//	string C = "F = zeros(2, 3)";
//	string D = "G = ones(3, 6)";
//	string E = "A = 5.5 + 12 * sin(0.4) + 2.2 ^ 4;";
//	string G = "B = [1.2 2.3 A; [1.3 2.4; 4.6 1.3], [3.2; 7.8]];";
//	if (testnconstructors(A))
//	{
//		int nRow, nCom;
//		int type;
//		dimnconstructors(A, nRow, nCom, type);
//		cout << nRow << "\t" << nCom << "\t" << type << endl;
//	}
//    return 0;
//}

