#include <iostream>
#include <cmath> //cos(), sine(), floor()함수 사용
using namespace std;

double const PI = 3.1415922653; //PI를 전역 변수로 선언

//함수 선언
void Matrix_Multiple(double M[][3], double M1[][3], double M2[][3]);
void initialize(double M[3][3]);

int main()
{
	double T[3][3]; //T1, T2, T3 행렬을 곱한 결과를 저장할 배열
	double Temp[3][3]; //T3, T2 행렬을 곱한 결과를 임시 저장할 배열
	double T1[3][3]; //T1 배열 선언
	double T2[3][3]; //T2 배열
	double T3[3][3]; //T3 배열
	//배열 초기화
	initialize(T); initialize(Temp);
	initialize(T1); initialize(T2); initialize(T3);
	//T2 배열에 값 넣기
	T2[0][0] = -1; T2[1][1] = 1;
	//T3 배열에 값 넣기
	T3[0][0] = 1; T3[1][1] = 1;

	double degree; //사용자로부터 입력받을 각도
	double Radian; //입력받은 각도를 라디안으로 바꿔 저장할 변수
	double coordinate[3] = { 0, 0, 0 }; //사용자로부터 입력받는 x,y,z의 좌표를 저장하는 1차원 배열

	cout << "Degrees: "; 
	cin >> degree; //input
	cout << "Coordinate: ";
	scanf_s("%lf %lf %lf", &coordinate[0], &coordinate[1], &coordinate[2]); //input
	Radian = degree * PI / 180; //라디안으로 변환하기

	//T1 배열 내에 값 넣기
	T1[0][0] = (double)cos(Radian); T1[0][1] = -(double)sin(Radian);
	T1[1][0] = (double)sin(Radian); T1[1][1] = (double)cos(Radian);
	T1[2][2] = 1;

	Matrix_Multiple(Temp, T3, T2); //T3와 T2 행렬 곱해서 Temp에 임시 저장
	Matrix_Multiple(T, Temp, T1);  //Temp와 T1 행렬 곱해서 T에 저장

	//output 출력하기
	cout << endl; //개행
	for (int i = 0; i < 3; i++)
	{
		double output = 0; //output을 저장할 지역변수 0으로 초기화
		for (int j = 0; j < 3; j++)
		{
			output += T[i][j] * coordinate[j]; //T 배열내의 요소와 좌표를 곱한 것을 더해 output에 저장
		}
		cout << floor(output + 0.5) << "  "; //ouput 값을 반올림하여 출력
	}
	return 0; //end program
} //main

//3차원 행렬을 곱하는 함수
void Matrix_Multiple(double M[][3], double M1[][3], double M2[][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				M[i][j] += M1[i][k] * M2[k][j];
			} //for-k
		} //for-j
	} //for-i
} //Matrix_Multiple -> 다시 만들기

//내 요소를 0으로 초기화하는 함수
void initialize(double M[3][3])
{
	for (int i = 0; i < 3; i++) //행
	{
		for (int j = 0; j < 3; j++) //열
		{
			M[i][j] = 0; //0으로 초기화
		} //for-j
	} //for-i
} //initialize
