#include <iostream>
#include <cmath>
using namespace std;

//최대 row길이와 column 길이 정의
#define row 3*128
#define column 2*3*128
//C6262 경고문 해결, 전역변수 선언
unsigned char Sierpinski[row][column];

///Prototype Declarations
void initial_Arr();
void print_Sierpinski(int, int);
void input_Tri(int, int);
void recursive(int, int, int, int);

int main()
{
	unsigned char k; //입력받을 변수
	cout << "Input: "; //k값 입력받기
	cin >> k; //변수 k에 값 전달

	k %= 48; //0의 아스키 코드값은 48이다.(9는 57)

	//k의 값은 1과 8을 포함한 사이 숫자여야 한다.
	if (k < 1 || k > 8)
	{
		cout << "Input k should be 1 <= k <= 8";
		return 0;
	}

	initial_Arr(); //배열 초기화

	int N = pow(2, k - 1); //자료에 주어진 N의 값 계산
	//입력받은 k 값의 최대 row와 column 길이 계산
	int k_row = 6 * N; 
	int k_col = 3 * N;

	//k의 값과 row와 column 초기 위치 전달
	recursive(1, k_row / 2 - 1, 0, k);
	print_Sierpinski(k_row, k_col); //Sierpinski 배열 출력

	return 0;
} //main

//Sierpinski 배열을 초기화 하는 함수
void initial_Arr()
{
	for (int i = 0; i < row; i++) //row
	{
		for (int j = 0; j < column; j++) //column
		{
			Sierpinski[i][j] = ' '; //공백으로 채우기
		}
	}
	return; //반환
} //initial_Arr

//Sierpinski triangle을 출력하는 함수
void print_Sierpinski(int x, int y)
{
	for (int i = 0; i < y; i++) //row
	{
		for (int j = 0; j < x; j++) //column
		{
			cout << Sierpinski[i][j]; //배열 요소 출력
		}
		cout << endl; //개행
	}
	return; //반환
} //print_Sierpinski

//Sierpinski 배열에 $을 넣는 함수
void input_Tri(int x, int y)
{
	//첫 번째 줄에 $ 1개 입력
	Sierpinski[y][x] = '$'; 
	//두 번째 줄에 $ 2개 입력
	Sierpinski[y + 1][x + 1] = '$';
	Sierpinski[y + 1][x - 1] = '$';
	//세 번째 줄에 $ 5개 입력
	for (int i = -2; i < 3; i++)
	{
		Sierpinski[y + 2][x + i] = '$';
	}
	return; //반환
} //input_Tri

//Sierpinski triangle pattern을 넣는 재귀함수
void recursive(int k, int x, int y, int kfig)
{
	/*
	k : 입력받은 변수
	x : Sierpinski triangle pattern을 찍을 행 index
	y : Sierpinski triangle pattern을 찍을 열 index
	kfig : Sierpinski triangle pattern 반복 변수
	*/
	while (kfig != 0) //kfig의 값이 0이면 반복을 끝냄
	{
		//Sierpinski triangle pattern을 찍을 row와 column 위치 전달
		input_Tri(x, y);
		kfig--;
		k++;
		
		//다음 삼각형을 만들 높이값 계산
		int z = 3 * pow(2, k - 2);
		/*
		z의 값을 빼고 더하면서 삼각형 밑에 만들 
		두개의 삼각형의 꼭짓점 row와 column 위치 전달
		*/
		recursive(k, x - z, y + z, kfig);
		recursive(k, x + z, y + z, kfig);
	}
	return; //반환
} //recursive
