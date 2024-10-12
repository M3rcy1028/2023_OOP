#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream> //파일입출력 사용
//#include <string>
#include <cstring> //strstr() 함수 사용
#include <algorithm> //copy() 함수 사용
using namespace std;
//declare Prototypes
int check_mark(char data[], int len);
int mark_index(char data[], int len);

int main()
{
	char filename[1000] = { '\0' }; //사용자로부터 검색받을 파일 이름
	int cnt; //찾을 문자열의 개수

	//filename_list.txt에 문자열을 넣는 함수
	ofstream initial;
	initial.open("filename_list.txt", ios::app);
	if (initial.fail()) //파일을 열지 못했을 때
	{
		cout << "Unable to open file" << '\n';
		return 0; //프로그램 종료
	}
	//파일에 내용 저장
	initial << "hello_word.cpp" << '\n';;
	initial << "oop_assignment1.zip" << '\n';
	initial << "oop_assignment2.zip" << '\n';
	initial << "hello.txt" << '\n';
	initial << "oop_assignment3.zip" << '\n';
	initial.close(); //close file
	
	cout << "Input file name : ";
	cin.getline(filename, 1000); //input filename
	cin >> cnt; //입력받을 패턴 개수
	
	ofstream start; //결과값을 저장하는 .txt파일
	start.open("filename_output.txt"); 
	if (start.fail()) //파일을 열 수 없을 때
	{
		cout << "Unable to open file" << endl;
		return 0; //프로그램 종료
	}
	while (0 != cnt) //찾는 문자열의 개수만큼만 반복
	{
		char data[1000]; //찾을 문자열을 받을 변수
		//read filename_list_origin.txt
		fstream origin(filename); //파일 이름이 저장되어 있는 파일 불러오기
		fstream output; //파일 이름을 저장할 파일 열기
		output.open("filename_output.txt", ios::app);
		if (output.fail()) //파일을 열 수 없을 때
		{
			cout << "Unable to open file" << endl;
			return 0; //프로그램 종료
		}
		cin.ignore(); //입력버퍼 지우기
		cin >> data; //찾을 문자열 입력받기
		int data_len = strlen(data); //배열의 길이
		int check = check_mark(data, data_len); //문자열에 있는 기호 확인
		// * 문자가 발견되었을 때
		if (1 == check)
		{
			string markstar; //filename_list.txt 파일의 내용을 받을 string
			int idx = mark_index(data, data_len); // * 이 있는 인덱스값 구하기
			char data_copy[100]; // * 을 제외한 문자열을 받을 변수
			copy(data, data + data_len, data_copy); //data를 data_copy에 *빼고 복사
			data_copy[idx] = '\0'; // *이 있던 index에 NULL 문자 삽입
			while (getline(origin, markstar)) //filename_list 안의 문자열 입력받기
			{
				const char* text = markstar.c_str(); //strstr 사용을 위해 string 문자열을 char형으로 변환
				if (NULL != strstr(text, data_copy)) //data_copy의 내용이 text에 있는지 확인
				{
					output << markstar << '\n'; //input string
				}
			} //while
		} //if (1 == check)
		// ? 문자가 발견되었을 때
		if (2 == check)
		{
			string markquestion; //filename_list.txt 파일의 내용을 받을 string
			int idx = mark_index(data, data_len); // ?의 인덱스값
			int correct = 0; //문자열이 ? 문자를 제외하고 같은지 판별할 변수
			while (getline(origin, markquestion)) //filename_list 안의 문자열 입력받기
			{
				const char* text = markquestion.c_str(); //string을 배열로 바꿈
				//두 문자열이 같은지 확인하는 반복문
				for (int i = 0; i < data_len; i++)
				{
					if (i == idx) // ?의 index에 도달하면 건너뛰기
					{
						i++;
					}
					if (data[i] != text[i]) //? 이외의 문자가 다르면 끝냄
					{
						correct = 0; //correct의 값 초기화하기
						break; //for문 끝내기
					}
					correct++; //문자가 같으면 correct의 값 +1
				}
				if (0 != correct) //cnt의 값이 0이 아니면 ? 이외의 문자가 같음
				{
					output << markquestion << '\n'; //output 파일에 넣기
				} // if (0 != correct)
			} //while
		} //if (2 == check)}
		cnt--; //반복 변수 -1
		origin.close(); //close filename_list.txt
		output.close(); //close file
	} //while

	//print results
	string result; //결과 파일 안의 문자열을 받을 string
	//output
	fstream res("filename_output.txt");
	cout << endl; //new line
	if (res.is_open()) //파일이 열렸을 때
	{
		while (getline(res, result)) //파일 안의 문자열 받기
		{
			cout << result << '\n'; //파일 안에 있는 string 출력
		}
		res.close(); //close file
	}
	else //파일을 열 수 없을 때
	{
		cout << "Unable to open file";
		return 1;
	}
	return 0; //end program
} //main

// ? 또는 * 문자가 있는지 검사하는 함수
int check_mark(char data[], int len)
{
	for (int i = 0; i < len; i++)
	{
		if ('*' == data[i])
			return 1;  // *이 있으면 1 반환
		if ('?' == data[i])
			return 2; // ?가 있으면 2 반환
	}
	return 0;
} //check_mark

// ? 또는 * 문자의 index값을 반환하는 함수
int mark_index(char data[], int len)
{
	for (int i = 0; i < len; i++)
	{
		if ('*' == data[i])
			return i; // *의 인덱스값 반환
		if ('?' == data[i])
			return i; // ?의 인덱스값 반환
	}
	return 0;
} //mark)indexs
