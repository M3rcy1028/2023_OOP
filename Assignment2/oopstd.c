#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h> //memset, memcpy, strcmp, strncmp, strcpy, strncpy, strlen
#include <stdlib.h> //atoi, atof
#include "oopstd.h"; //사용자지정 헤더파일 선언
using namespace std;

//함수 선언
void test_memset();
void test_memcpy();
void test_strcmp();
void test_strncmp();
void test_strcpy();
void test_strncpy();
void test_strlen();
void test_atoi();
void test_atof();

int main()
{
	test_memset(); //test_memset
	test_memcpy(); //test_memcpy
	test_strcmp(); //test_strcmp
	test_strncmp(); //test_strncmp
	test_strcpy(); //test_strcpy
	test_strncpy(); //test_strncpy
	test_strlen(); //test_strlen
	test_atoi(); //test_atoi
	test_atof(); //test_atof
	cout << "End test";
	return 0; //end program
} //main

/*memset 함수 테스트용*/
void test_memset()
{
	//oopstd.h
	cout << ">>Test oopstd::memset" << endl;
	char str[] = "Kwangwoon Department of computer engineering information";
	cout << "Original Data : " << str << endl;
	oopstd::memset(str, '*', 9); //oopstd.h
	cout << str << endl; //print
	//string.h
	cout << ">> std::memset" << endl;
	std::memset(str, '~', 9);  //string.h
	cout << str << endl << endl; //print
	return;
} //test_memset

/*memcpy 함수 테스트용*/
void test_memcpy()
{
	//oopstd.h
	cout << ">>Test oopstd::memcpy" << endl;
	char myname1[] = "Angela Ziegler";
	char myname_cpy[100] = { '\0' };
	oopstd::memcpy(myname_cpy, myname1, sizeof(myname1)); //oopstd.h
	cout << "myname_cpy(oopstd) : " << myname_cpy << endl; //print
	//string.h
	cout << ">> std::memcpy" << endl;
	char myname2[] = "Tomas Kelen";
	std::memcpy(myname_cpy, myname2, sizeof(myname2)); //string.h
	cout << "myname_cpy(std) : " << myname_cpy << endl << endl; // print
	return;
} //test_memcpy

/*strcmp 함수 테스트용*/
void test_strcmp()
{
	//oopstd.h
	cout << ">>Test oopstd::strcmp" << endl;
	char key1[] = "lime"; //answer
	char buffer1[80] = "\0"; //input
	do {
		cout << "Guess my favorite fruit? "; //question 1
		fflush(stdout); //입력버퍼 지우기
		cin >> buffer1; //input
	} while (oopstd::strcmp(key1, buffer1) != 0); //oopstrd.h
	cout << "Correct Answer!" << endl;
	//string.h
	cout << ">> std::strcmp" << endl;
	char key2[] = "Object_Oriented_Programming"; //answer
	char buffer2[80] = "\0"; //input
	do {
		cout << "Guess my favorite lecture? "; //question2
		fflush(stdout); //입력버퍼 지우기
		cin >> buffer2; //input
	} while (std::strcmp(key2, buffer2) != 0); //string.h
	cout << "Correct Answer!" << endl << endl;
	return;
} //test_strcmp

/*strncmp 함수 테스트용*/
void test_strncmp()
{
	//oopstd.h
	cout << ">>Test oopstd::strncmp" << endl;
	char str1[][6] = { "A6C0", "C3P0", "A6A6", "B4K4", "A6F8" }; //key
	int n = 0; //initial
	cout << "Looking for A6 astromech droids...." << endl;
	while (n < 5) //searchig
	{
		if (oopstd::strncmp(str1[n], "A6xx", 2) == 0)
			cout << "found " << str1[n] << endl; //print
		n++;
	} //while
	//string.h
	cout << endl << ">> std::strncmp" << endl;
	char str2[][6] = { "V4G2", "A5H3", "V9K1", "V4M6", "A0C5" }; //key
	n = 0; //initial
	cout << "Looking for V4 astromech droids...." << endl;
	while (n < 5) //searching
	{
		if (std::strncmp(str2[n], "V4xx", 2) == 0)
			cout << "found " << str2[n] << endl; //print
		n++;
	} //while
	cout << endl; //new line
	return;
} //test_strncmp

/*strcpy 함수 테스트용*/
void test_strcpy()
{
	//oopstd.h
	cout << ">>Test oopstd::strcpy" << endl;
	char str1[] = "Kwangwoon University"; //string
	char buffer1[50];
	char buffer2[50];
	oopstd::strcpy(buffer1, str1); //copy string
	oopstd::strcpy(buffer2, "oopstd::strcpy, Copy successful"); //copy string
	cout << str1 << endl << buffer1 << endl << buffer2 << endl; //print
	//string.h
	cout << ">> std::strcpy" << endl;
	char str2[] = "Kwangwoon Square"; //string
	char buffer3[50];
	char buffer4[50];
	std::strcpy(buffer3, str2); //copy string
	std::strcpy(buffer4, "std::strcpy, Copy successful"); //copy string
	cout << str2 << endl << buffer3 << endl << buffer4 << endl << endl; //print
	return;
} //test_strcpy

/*strncpy 함수 테스트용*/
void test_strncpy()
{
	//oopstd.h
	cout << ">>Test oopstd::strncpy" << endl;
	char str1[] = "Object Oriented Programming"; //복사할 문자열
	char buffer1[50];
	char buffer2[50];
	oopstd::strncpy(buffer1, str1, sizeof(buffer1)); //oopstd::strncpy
	oopstd::strncpy(buffer2, buffer1, 16); //oopstd::strncpy
	buffer2[16] = '\0'; //NULL
	cout << str1 << endl << buffer1 << endl << buffer2 << endl; //print
	//string.h
	cout << ">>Test oopstd::strncpy" << endl;
	char str2[] = "Image Processing Systems Laboratory"; //복사할 문자열
	char buffer3[50];
	char buffer4[50];
	std::strncpy(buffer3, str2, sizeof(buffer3)); //std::strncpy
	std::strncpy(buffer4, buffer3, 30); //std::strncpy	
	buffer4[6] = '\0'; //NULL
	cout << str2 << endl << buffer3 << endl << buffer4 << endl << endl; //print
	return;
} //test_strncpy

/*strlen 함수 테스트용*/
void test_strlen()
{
	//oopstd.h
	cout << ">>Test oopstd::strlen" << endl;
	char str1[1000]; //input
	cout << "Enter a sentence(oopstd) : ";  cin >> str1; //input
	cout << "The sentence entered is " << oopstd::strlen(str1) << " characters long." << endl; //print
	//string.h
	cout << ">> std::strlen" << endl;
	char str2[1000]; //input
	cout << "Enter a sentence(std) : ";  cin >> str2; //input
	cout << "The sentence entered is " << std::strlen(str2) << " characters long." << endl << endl; //print
	return;
}

/*atoi 함수 테스트용*/
void test_atoi()
{
	//oopstd.h
	cout << ">>Test oopstd::atoi" << endl;
	int i; //input
	char buffer1[256]; //input
	cout << "Enter a number(oopstd) : "; cin >> buffer1; //input
	i = oopstd::atoi(buffer1); //oopstd
	printf("The value entered is %d. Its double is %d\n", i, i * 2); //print
	//stdlib.h
	cout << ">> std::atoi" << endl;
	int j; //input
	char buffer2[256]; //input
	cout << "Enter a number(std) : "; cin >> buffer2; //input
	j = std::atoi(buffer2); //std
	printf("The value entered is %d. Its double is %d\n\n", j, j * 2); //print
	return;
} //test_atoi

/*atod 함수 테스트용*/
void test_atof()
{
	//oopstd.h
	cout << ">>Test oopstd::atof" << endl;
	double n1; //input
	char buffer1[256]; //input
	cout << "Enter a number(oopstd) : "; cin >> buffer1; //input
	n1 = oopstd::atof(buffer1); //oopstd
	printf("The value entered is %lf\n", n1); //print
	//stdlib.h
	cout << ">> std::atof" << endl;
	double n2; //input
	char buffer2[256]; //input
	cout << "Enter a number(std) : "; cin >> buffer2; //input
	n2 = std::atof(buffer2); //std
	printf("The value entered is %lf\n\n", n2); //print
	return;
} //test_atof
