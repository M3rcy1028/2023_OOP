#include <iostream>
using namespace std;

//Prototype Declarations
int GCD(int, int); //최대공약수
int LCM(int, int); //최소공배수

int main()
{
	int x, y;
	cout << "x : "; //input x
	cin >> x;
	cout << "y : "; //input y
	cin >> y;

	//if y is larger than x, swap x and y
	if (y < x)
		swap(x, y);

	//calculate gcd between x and y
	cout << "GCD of " << x << " and " << y << " is " << GCD(x, y) << endl; //call GCD
	//calculate lcm between x and y
	cout << "LCM of " << x << " and " << y << " is " << LCM(x, y); //call LCM

	return 0;
} //main

//calculate and return greatest common divisor
int GCD(int x, int y)
{
	//if y equals to 0, return x
	if (y == 0)
		return x;
	else //using Euclidean algorithm
		return GCD(y, x % y);
} //GCD

//calculate and return least common multiple
int LCM(int x, int y)
{
	return (x * y / GCD(x, y));
} //LCM
