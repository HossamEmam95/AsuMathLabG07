# AsuMathLabG07

**Our Library** 

our library is math library which based on matrix.It support all mathematical operation such as :

1.   Addition
2.   Subtraction
3.   Transpose
4.   Mulitiplication
5.   Division
6.   Inverse
7.   Determinant

In this Phase we support other function:

1.	Rand(n,m) : n,m are dim. Of matrix and generate random number& return matrix

2.	Eye(n,m) : n,m are dim. Of matrix and create identity matrix  & return it

3.	Zero(n,m) : n,m are dim. Of matrix and fill matrix with zero& return matrix

4.	One(n,m) : n,m are dim. Of matrix and fill matrix with one & return matrix

5.	Sin(D) : find sine value of each element in the matrix & return matrix

6.	Sqrt(D) : find square root value of each element in the matrix & return matrix

7.  Function support matrix power

8.  Function takes line contains mathematical operation as string returns the double value calculated from the expression 

9.	‘ ,’ : When you concatenate two matrices by separating those using commas, they are just appended horizontally. It is called horizontal concatenation.

10.	‘ ; ’ : if you concatenate two matrices by separating those usingsemicolons, they are appended vertically. It is called vertical concatenation.

Extra function will be added soon 

**How to configure**

**Examples :**

Example 1 

Input :

a =[10 12 23 ; 14 8 6 ; 27 8 9]

b =[12 31  45 ; 8  0 -9 ; 45 2 11]

c =[a, b]

d =[a; b]

a =

    10    12   23
    
    14    8     6
    
    27    8     9

b =

    12    31    45

     8     0    -9

     45     2    11

c =

    10    12    23    12    31    45

    14     8     6     8     0    -9

    27     8     9    45     2    11

d =
    
    10    12    23
    
    14     8     6
    
    27     8     9
    
    12    31    45
    
    8     0    -9
    
    45     2    11

Example 2    on   Sin(matrix)

Input :

a =[1,2;4,16] 

b=sin(a) 

sin(1)

sin(2)

sin(3)

sin(16)

output: 

a = 

     1	2
		
     4	16
    
b =	
 
     0.84147	0.90930
	   
     -0.75680	-0.28790

ans = 0.84147

ans = 0.90930

ans = -0.75680

ans = -0.28790

Example 3 on string parsing 

Input:

B = [1.2 2.3 A;[1.3 2.4;4.6 1.3],[3.2;7.8]];

C = [[b [3.4; 2.1; 3.5+9.1]]1.2^3 3+1.2 15/(2) 1.2]

Output:

a =  5

b =

     1.2000   2.3000   5.0000

     1.3000   2.4000   3.2000

     4.6000   1.3000   7.8000

C =

    1.2000    2.3000    5.0000    3.4000
    
    1.3000    2.4000    3.2000    2.1000
    
    4.6000    1.3000    7.8000   12.6000
    
    1.7280    4.2000    7.5000    1.2000

Example 4 on function takes line contains mathematical operation as string returns the double value calculated from the expression

L = (1.2 + 3.4 - 5.6)/(2.1*3.2 + 4.6) - 12.1*3.1 + (1.2 + 5.2)^(4/(3.2+5.6))

Output :

L = -35.273
