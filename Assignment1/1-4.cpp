#include <iostream>
#define size 3
using namespace std;

int main()
{
	//define and initialize matrix
	int matrix[size][size] = {(0, 0, 0),
							  (0, 0, 0),
							  (0, 0, 0)};
	//define and initialize cofactor matrix
	double cofactor_matrix[size][size] = { (0, 0, 0),
										  (0, 0, 0),
										  (0, 0, 0) }; //여인자 행렬
	//define and initialize transposed matrix
	double transposed_matrix[size][size] = {(0, 0, 0),
											(0, 0, 0),
											(0, 0, 0)}; //전치행렬
	//define and initialize inversed matrix
	double inversed_matrix[size][size] = {(0, 0, 0),
										  (0, 0, 0),
										  (0, 0, 0) };
	//define and initialize elements of the matrix
	int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0;
	double det = 0; //initialize determination to zero
	
	cout << "input matrix" << endl;
	//input elements of matrix
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			cin >> matrix[i][j];
	}

	//variables that store elements in the matrix
	a = matrix[0][0]; b = matrix[0][1]; c = matrix[0][2];
	d = matrix[1][0]; e = matrix[1][1]; f = matrix[1][2];
	g = matrix[2][0]; h = matrix[2][1]; i = matrix[2][2];

	//get determinant of the matrix
	for (int i = 0; i < size; i++)
	{
		det = det + (matrix[0][i]*(matrix[1][(i+1)%3]* matrix[2][(i+2)%3]
			- matrix[2][(i+1)%3]* matrix[1][(i + 2) % 3]));
	}

	//if the value of determinant of matrix is zero, the matrix does't have inversed matrix
	if (det == 0)
	{
		cout << "The inverse matrix does not exist." << endl;
	}
	else 
	{
		//get cofactor matrix
		cofactor_matrix[0][0] = e * i - f * h;
		cofactor_matrix[0][1] = -(d * i - f * g);
		cofactor_matrix[0][2] = d * h - e * g;
		cofactor_matrix[1][0] = -(b * i - c * h);
		cofactor_matrix[1][1] = a * i - c * g;
		cofactor_matrix[1][2] = -(a * h - b * g);
		cofactor_matrix[2][0] = b * f - c * e;
		cofactor_matrix[2][1] = -(a * f - c * d);
		cofactor_matrix[2][2] = a * e - b * d;

		//get transposed cofactor matrix
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				transposed_matrix[i][j] = cofactor_matrix[j][i];
			}
		}

		/*get inversed matrix by dividing transposed cofactor
		matrix into determinant of the matrix*/
		cout << endl; //new line
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				inversed_matrix[i][j] = (transposed_matrix[i][j] / det);
				//print inversed matrix
				printf("%10lf ", inversed_matrix[i][j]);
			}
			cout << endl; //new line
		}
	} //end of else statement
	return 0;
} //main
