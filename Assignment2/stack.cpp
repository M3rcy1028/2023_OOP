#include <iostream>
#include <string.h>
using namespace std;
#define SIZE 128 //스택 사이즈 정의

int Stack[SIZE] = { 0 }; //Stack 정의
int Top = -1; //Stack 배열의 idx를 가리킬 변수

//함수 선언
void push(int);
void pop();
void top();
void print();
int empty();
void exite();

int main()
{
	while (1)
	{
		char arr[100] = { '\0' }; //명령어를 입력받을 배열
		cin >> arr; //input
		if (0 == strncmp("push", arr, 4)) //pust
		{
			int num = arr[5];
			cin >> num;
			push(num);
		} 
		if (0 == strncmp("pop", arr, 3)) //pop
			pop(); //함수 호출
		if (0 == strncmp("top", arr, 3)) //top
			top(); //함수 호출
		if (0 == strncmp("print", arr, 5)) //print
			print(); //함수 호출
		if (0 == strncmp("empty", arr, 5)) //empty
			cout << empty() << endl; //함수 호출 
		if (0 == strncmp("exit", arr, 4)) //exit
			exite(); //함수 호출
	} //while
	return 0; //end program
} //main

//스택 안에 요소를 넣음
void push(int n)
{
	Stack[++Top] = n;
} //push

//스택의 맨 위에 있는 요소를 출력하고 제거함
void pop()
{
	cout << Stack[Top] << endl;
	Stack[Top--] = 0;
	return;
} //pop

//스택에서 맨 위에 있는 요소를 출력함
void top()
{
	cout << Stack[Top] << endl;
	return;
} //top

//스택 안의 요소들을 출력하는 함수
void print()
{
	for (int i = 0; i <= Top; i++)
		cout << Stack[i] << " ";
	cout << endl;
	return;
} //print

//스택이 비어있는지 아닌지 알려주는 함수
int empty()
{
	if (-1 != Top)
		return 0;
	else
		return 1;
} //empty

//프로그램을 종료하는 함수
void exite()
{
	exit(1);
} //exite
