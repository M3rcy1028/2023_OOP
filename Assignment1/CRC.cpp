#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <stdlib.h> //rand()함수 사용
#include <time.h> //time을 통해 rand()의 seed값을 변경

using namespace std;

//전역변수 선언
char Original_Data[20] = { 0 }; //사용자로부터 입력받을 original data
char Data[20] = { 0 }; //사용자로부터 입력받아 Receiver에 보낼 데이터
char Coded_Frame[20] = { 0 }; //Transmission_Channel에서 받을 coded frame
char Received_Frame[20] = { 0 }; //Transmission_Channel에서 에러 수행후 저장할 배열
char FCS[5] = { 0 }; //Sender함수에서 XOR연산 후 남은 4bit를 Codede_Data 뒤에 붙일 배열
char cFCS[5] = { 0 };//Receiver함수에서 XOR의 결과로 얻은 FCS를 저장
char POLYNOMIAL[6] = { 49, 49, 48, 49, 49 }; //미리 지정된 5bits, 주어진 0b11011를 아스키코드값으로 저장함.
char Q[20] = { 0 }; //Sender함수에서 XOR연산으로 나온 몫
char Remainder[6] = { 0 }; //Sender함수에서 XOR연산 이후 남은 4bits

//함수 선언
void Sender(const char* Data);
void Receiver(const char* received_data);
void Transmission_Channel(const char* coded_data);

int main() 
{
    cout << "Data: "; //사용자로부터 입력받음
    cin >> Original_Data; //입력받은 데이터 (원본 데이터)

    //입력받은 데이터를 Sender에 보낼 Data에 저장
    strcpy(Data, Original_Data);
    strcat(Data, "0000"); //원래의 데이터를 왼쪽으로 4 옮김
    
    //5bits XOR 연산을 위해 받은 데이터의 왼쪽부터 5비트를 미리 받음
    for (int i = 0; i < 5; i++)
        Remainder[i] = Data[i];

    //Sender함수에 data 보냄
    Sender(Data); //함수 호출
    strcpy(Coded_Frame, Original_Data); //Coded_data 얻음
    strcat(Coded_Frame, FCS); // Coded_Data에 Sender에서 얻은 FCS 이어 붙임 
    cout << "Coded frame: " << Coded_Frame << endl; //Coded_Frame 출력

    srand((unsigned int)time(NULL)); //seed로 time을 받아 seed값이 일정한 값을 가지지 않게 함
    //Tansmission_Channel함수에 Sender로부터 받은 coded_frame을 보냄
    Transmission_Channel(Coded_Frame); //함수 호출
    //Transmission_Channel를 거친 coded_frame 출력
    cout << "Received frame: " << Coded_Frame << endl;

    //5bits XOR 연산을 위해 받은 데이터의 왼쪽부터 5비트를 미리 받음
    for (int j = 0; j < 5; j++)
        Remainder[j] = Coded_Frame[j];
    //Receiver함수 불러오기
    Receiver(Received_Frame); //함수 호출

    //Receiver로부터 계산된 결과 출력
    cout << "Reconstructed data: ";
    for (int i = 0; i < 12; i++) //맨 오른쪽의 4bits는 생략하고 출력
    {
        cout << Received_Frame[i];
    }
    cout << endl; //개행

    //오류가 없는 데이터의 맨 오른쪽 4자리는 0000
    if (0 != strcmp(cFCS, "0000")) //오류가 발생했을 때
    {
        cout << "Receiver has detected error" << endl; //오류발생 메세지 출력
    }
    else //오류가 발생하지 않았을 때
    {
        cout << "No detected error" << endl;
    }
    return 0; //end program
} //main

//Original_Data를 통해 FCS를 구하는 Sender함수
void Sender(const char* Data)
{
    //XOR 연산을 통해 FCS를 얻는 반복문
    for (int i = 0; i < 12; i++) 
    {
        // 1이 존재하면 XOR연산을 함
        // XOR 연산 : 1의 개수가 홀수개 일 때 1을 반환한다. 그외에는 0 반환
        if ('0' != Remainder[0])
        {
            Q[i + 5] = '1'; //몫 저장

            //5bits XOR 연산을 수행하는 반복문
            for (int j = 0; j < 5; j++) 
            {
                //char형으로 저장되었기에 문자 '0'으로 빼준 값이 숫자임.
                Remainder[j] = (Remainder[j] - '0') ^ (POLYNOMIAL[j] - '0') + '0'; //XOR 연산자 사용
            }
            //Remainder 내의 값을 하나씩 앞으로 당기기
            for (int j = 0; j < 4; j++)
                Remainder[j] = Remainder[j + 1];

            //빈 4번째 index에 다음 값 저장하기
            Remainder[4] = Data[i + 5];

        } //if ( '0' != Remainder[0])
        else 
        {
            Q[i] = '0';
            // 앞자리가 0일 경우 앞으로 당기기
            for (int j = 0; j < 4; j++)
                Remainder[j] = Remainder[j + 1];
            //빈 4번째 index에 다음 값 저장하기
            Remainder[4] = Data[i + 5];
        } //else
    } //for
    //XOR연산에서 남은 4bits 나머지를 FCS에 복사함
    strncpy(FCS, Remainder, 4);
} //Sender

//Sender함수에서 Coded_Data를 받아 각 비트당 5%의 확률로 bit error를 만드는 함수
void Transmission_Channel(const char* coded_data)
{
    //각 bit당 bit error가 일어날 확률은 5%임
    for (int i = 0; i < 16; i++) 
    {
        if (rand() % 100 + 1 <= 5) // 5이하이면 error발생
        {   
            if (coded_data[i] == '1')
                Received_Frame[i] = '0'; // 1이면 0으로 바꿈
            else
                Received_Frame[i] = '1'; //0이면 1로 바꿈
        } //if
        else //5%가 아닐 때
        {
            Received_Frame[i] = coded_data[i];
        } //else
    } //for
} //Transmission_Channel

//Sender와 똑같은 기능을 하면서 Tranmission_Channel의 결과값을 연산함
void Receiver(const char* received_data) 
{
    //XOR 연산을 통해 FCS를 얻는 반복문
    for (int i = 0; i < 12; i++)
    {
        // 1이 존재하면 XOR연산을 함
        // XOR 연산 : 1의 개수가 홀수개 일 때 1을 반환한다. 그외에는 0 반환
        if ('0' != Remainder[0])
        {
            Q[i + 5] = '1'; //몫 저장

            //5bits XOR 연산을 수행하는 반복문
            for (int j = 0; j < 5; j++)
            {
                //char형으로 저장되었기에 문자 '0'으로 빼준 값이 숫자임.
                Remainder[j] = (Remainder[j] - '0') ^ (POLYNOMIAL[j] - '0') + '0'; //XOR 연산자 사용
            }
            //Remainder 내의 값을 하나씩 앞으로 당기기
            for (int j = 0; j < 4; j++)
                Remainder[j] = Remainder[j + 1];
            //빈 4번째 index에 다음 값 저장하기
            Remainder[4] = received_data[i + 5];

        } //if ( '0' != Remainder[0])
        else
        {
            Q[i] = '0';
            // 앞자리가 0일 경우 앞으로 당기기
            for (int j = 0; j < 4; j++)
                Remainder[j] = Remainder[j + 1];
            // R의 나머지 자리 채우기
            Remainder[4] = received_data[i + 5];
        } //else
    } //for
    //XOR연산에서 남은 4bits 나머지를 FCS에 복사함
    strncpy(cFCS, Remainder, 4); //Coded_Frame에서 얻은 FCS저장
} //Receiver
