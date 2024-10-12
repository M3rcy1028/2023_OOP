#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream> //파일 입출력
#define SIZE 1000 //입력받을 buffer의 사이즈 크기
using namespace std;

int main()
{
	FILE* fpBinaryFile = fopen("binary.txt", "r"); //디코딩할 문자열이 저장된 파일 열기
	FILE* fpAlphabetFile = fopen("alphabet.txt", "wt"); //디코딩한 결과를 저장할 파일 생성
	if (!fpBinaryFile)
	{
		cout << "Can't open binary.txt file." << endl;
		return 0;
	} //binary.txt를 열 수 없을 때
	if (!fpAlphabetFile)
	{
		cout << "Can't open alphabet.txt file." << endl;
		return 0;
	} //alphabet.txt를 열 수 없을 때
	char buffer[SIZE]; //파일 내의 binary text를 입력받을 배열
	memset(buffer, '\0', SIZE); //buffer 배열 초기화
	fgets(buffer, SIZE, fpBinaryFile); //파일 내의 문자열 입력받기
	int idx = 0; //buffer의 index
	int len = strlen(buffer); //buffer의 길이
	while (1) //개행문자 없애기
	{
		if (buffer[len - 1] == '\n') //개행문자가 발견되면
		{
			buffer[len - 1] = '\0'; //널문자로 대체
			len--; //배열의 길이 줄이기
		}
		else //개행문자가 없을 때
			break; //반복문 탈출
	} //while
	cout << "binary.txt : " << buffer << endl; //binary.txt에 저장된 문자열 출력
	cout << "Decoding result : "; 
	while (idx < len) //배열의 길이만큼 반복
	{
		int cnt = 0; //0의 개수를 셀 변수
		char input = '\0'; //디코딩 결과값을 저장할 변수
		//buffer[idx]의 값이 1이 되거나 cnt의 크기가 25를 넘어가면 종료
		while (('1' != buffer[idx++]) && (25 > cnt)) 
			cnt++;
		input = cnt + 97; //문자열 저장
		cout << input; //디코딩한 결과 출력
		fputc(input, fpAlphabetFile); //파일에 쳐넣기
	} //while
	fclose(fpBinaryFile); //close file
	fclose(fpAlphabetFile); //close file
	return 0; //end program
} //main
