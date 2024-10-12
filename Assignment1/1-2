#include <iostream>
#include <cmath>
using namespace std;

//Prototype Declarations
float X1(float, float, float);
float X2(float, float, float);

int main()
{
	float a, b, c; //define variables
	float d; //root discriminant variable
	cout << "a: "; //input a
	cin >> a;
	cout << "b: "; //input b
	cin >> b;
	cout << "c: "; //input c
	cin >> c;

	//calulate root discriminant
	d = pow(b, 2) - 4 * a * c; 

	if (a == 0) //a should't be 0.
	{
		cout << "Unexpected fator of a quadratic term";
	} // if
	else //if a is not 0,
	{
		//if d is smaller than 0, x1 and x2 have imaginary roots.
		if (d < 0) 
		{
			cout << "The equation has no real number solutions.";
		}
		else
		{
			//if d equals to 0, x1 and x2 hvae double roots.
			if (d == 0)
			{
				cout << "X1, X2: " << X1(a, b, c) << " (double root)"; //call X1
			}
			//if d lager than 0, x1 and x2 hvae real roots.
			else
			{
				cout << "X1: " << X1(a, b, c) << ", X2: " << X2(a, b, c); //call X1 & X2
			}
		}
	} // else
} // main

//return the result of x1 
float X1 (float a, float b, float c)
{
	//return the value of x1
	return ((-b + sqrt(pow(b, 2) - 4 * a * c)) / 2 * a);
} // X1

//return the result of x2
float X2(float a, float b, float c)
{
	//return the vaule of x2
	return ((-b - sqrt(pow(b, 2) - 4 * a * c)) / 2 * a); 
} // X2
