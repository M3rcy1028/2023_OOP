#include <iostream>
#include <string.h>
#define SIZE 1000 // 입력받을 문자열이 크기 지정
using namespace std;
//결과를 저장할 배열 선언
unsigned int numbers[10][2];

//declare prototypes
void results(char arr[], int len);
int count_num(char arr[], int num, int len);
int check_overlap(char arr[], int x);

int main()
{
	char arr[SIZE]; //입력받을 배열 선언
	int arr_len = 0; //배열의 길이
	//공백을 포함하여 문자열 입력받기
	cin.getline(arr, SIZE, '\n');
	arr_len = strlen(arr); //배열의 길이 계산

	//initialize numbers array
	for (int i = 0; i < 10; i++)
	{
		numbers[i][0] = 0;
		numbers[i][1] = 0;
	}

	results(arr, arr_len); //call function

	//print results
	for (int i = 0; i < 10; i++)
	{
		if (numbers[i][0] != 0)
			cout << numbers[i][0] << numbers[i][1];
	}

	return 0; //end program
} //main


//결과값을 저장하는 함수
void results(char arr[], int len)
{
	/* 숫자의 중복 횟수, 중복 검사를 할 숫자,
	numbers 배열의 행 인덱스를 저장할 변수*/
	int rCnt = 0, num = 0, x = 0;

	for (int i = 0; i < len; i++) //배열의 길이 만큼 반복
	{
		num = check_overlap(arr, i); //call function
		if (-1 != num) //-1이 아닐 때 numbers 배열에 값 저장
		{
			numbers[x][0] = num; //개수를 셀 숫자 저장
			rCnt = count_num(arr, num, len); //call function
			numbers[x][1] = rCnt; //반복된 횟수 저장
			x++; //numbers의 인덱스값 +1
		}
	}
	return; //함수 종료
} //results

//개수를 셀 숫자가 중복되는지 확인하는 함수
int check_overlap(char arr[], int x)
{
	//배열에 저장된 숫자는 문자이므로 48로 나눈 몫이 숫자임.
	int num = arr[x] % 48;
	//numbers 배열의 길이만큼 반복하면서 중복 검사
	for (int i = 0; i < 10; i++)
	{
		if (num == numbers[i][0])
		{
			return -1; //이미 개수를 센 숫자이면 -1 반환
		}
		if (' ' == arr[x])
			return -1; //공백일 때 -1 반환
	}
	return num; //numbers에 저장된 숫자가 아니면 num 반환
} //check_overlap


//중복되지 않는 숫자의 개수 세는 함수
int count_num(char arr[], int num, int len)
{
	int cnt = 0; //개수를 저장할 변수

	for (int i = 0; i < len; i++)
	{
		//num과 같은 숫자가 있을 때 cnt값 +1
		if (arr[i] % 48 == num)
		{
			cnt++;
		}
	}
	return cnt; //개수를 센 cnt값 반환
} //count_num
