#include <iostream>
using namespace std;

int operation = 0;  //입력받은 문자열을 변환할 진법을 입력받는 변수
int form = 0; //입력받은 문자의 진법을 입력받는 변수
char num[100] = {'\0'}; //입력받은 문자열을 저장하는 배열
int toDecimal = 0; //입력받은 문자열을 10진수로 변환한 값을 저장하는 변수
int idx = 1; //맨앞의 0 출력 없애기
//함수 선언
int ToDecimal();
void Binary(int);
void Octal(int);
void HexaDecimal(int);

int main()
{
	memset(num, '\0', sizeof(num)); //배열 내의 값을 -1로 초기화
	cin >> num; cin >> form >> operation;
	ToDecimal(); //문자열을 10진수로 바꾸는 함수 호출
	switch (operation)
	{
	case 10: //10진수로 출력
	{
		cout << toDecimal;
		break;
	} //case 10:
	case 2: //2진수로 출력
	{
		Binary(toDecimal);
		break;
	} //case 2:
	case 8: //8진수로 출력
	{
		Octal(toDecimal);
		break;
	} //case 8:
	case 16: //16진수로 출력
	{
		HexaDecimal(toDecimal);
		break;
	} //case 16:
	default:
		break;
	} //switch
	cout << endl;

	return 0; //end program
} //main

//입력받은 문자열을 10진수로 바꾸는 함수
int ToDecimal()
{
	int numlen = strlen(num); //입력받은 문자열의 길이
	switch (form)
	{
	case 2: //2진수를 10진수로 바꾸기
	{
		int binary = 1;
		for (int i = numlen - 1; i >= 0; i--)
		{
			int temp = num[i] - 48; //2진수로 입력된 정수의 맨 오른쪽부터 입력받기
			toDecimal += temp * binary; //문자를 10진수로 변환한 후 값 저장
			binary *= 2; //2진수이므로 2씩 곱하기
		} //for
		break;
	} //case 2:
	case 8: //8진수를 10진수로 바꾸기
	{
		int octal = 1;
		for (int i = numlen - 1; i >= 0; i--)
		{
			int temp = num[i] - 48; //8진수로 입력된 정수의 맨 오른쪽부터 입력받기
			toDecimal += temp * octal; //문자를 10진수로 변환한 후 값 저장
			octal *= 8; //8진수이므로 8씩 곱하기
		} //for
		break;
	} //case 8:
	case 10: //10진수일 때
	{
		int deci = 1;
		for (int i = numlen - 1; i >= 0; i--)
		{
			int temp = num[i] - 48; //10진수로 입력된 정수의 맨 오른쪽부터 입력받기
			toDecimal += temp * deci; //문자를 10진수로 변환한 후 값 저장
			deci *= 10; //10진수이므로 810씩 곱하기
		} //for
		break;
	} //case 10:
	case 16: //16진수를 10진수로 바꾸기
	{
		int hexa = 1;
		for (int i = numlen - 1; i >= 0; i--)
		{
			int temp = 0; //16진수로 입력된 정수의 맨 오른쪽부터 입력받기
			if (num[i] < 65) //숫자를 만났을 때
			{
				temp = num[i] - 48; //아스키코드 문자에 54를 빼주어 숫자를 얻음
			} //if
			else
			{
				temp = num[i] - 55; //아스키코드값에 55빼기
			} //else
			toDecimal += temp * hexa; //10진수로 변환한 후 값 저장
			hexa *= 16; //16진수이므로 16씩 곱하기
		} //for
		break;
	} //case 16:
	default: //이외의 숫자가 입력되었을 때
	{
		cout << "You've entered wrong radix." << endl;
		return -1;
		break;
	} //default:
	} //switch
	return toDecimal;
} //ToDecimal

//10진수를 2진수로 바꾸는 함수
void Binary(int n)
{
	if (n > 1)
	{
		Binary(n / 2); //재귀함수
	} //if
	if ((1 == idx) && (0 == n % 2))
		return;
	else
		cout << n % 2;
	idx++;
} //Binary

//10진수를 8진수로 바꾸는 함수
void Octal(int n)
{
	if (n > 1)
	{
		Octal(n / 8); //재귀함수
	} //if
	if ((1 != idx) && (0 != n % 8))
		cout << n % 8;
	idx++;
} //Octal

//10진수를 16진수로 바꾸는 함수
void HexaDecimal(int n)
{
	if (n > 1)
	{
		if (n % 16 > 9) //n % 16이 10보다 클때는 A,B,C,D,E,F를 출력함
		{
			if ((1 == idx) && (0 == n % 16))
				return;
			else
			{
				HexaDecimal(n / 16);
				cout << char((n % 16) + 55);
			}
			idx++;
		}
		else
		{
			if ((1 == idx) && (0 == n % 16))
				return;
			else
			{
				HexaDecimal(n / 16);
				cout << n % 16;
			}
			idx++;
		} //else
	} //if
	return;
} //HexaDecimal
