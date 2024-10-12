#include <iostream>
using namespace std;
#define MAX 30 //미로의 최대 사이즈
#define STACK_MAX MAX*MAX //경로를 입력받을 stack배열의 최대 사이즈

//전역 변수 선언
int maze[MAX][MAX]; //미로를 입력받을 배열
int trace[MAX][MAX]; //이동한 거리를 계산할 배열
int row, col; //입력받을 미로 행, 열 크기
//상하좌우
int Vector[][4] = { {0, 0 , 1, -1}, {1, -1, 0, 0 } };
int stack[STACK_MAX][2]; //이동한 위치의 index를 저장할 stack
int bottom = 0, top = 0; //스택의 아래/위 index

//함수선언
void FindExit(int, int, int, int);
void InputMaze();

int main()
{
    //배열 초기화
    memset(trace, -1, sizeof(trace)); //-1로 초기화
    memset(maze, 0, sizeof(maze)); //0으로 초기화
    memset(stack, 0, sizeof(stack)); //0으로 초기화
    InputMaze(); //함수 호출
    return 0; //end program
} //main

//미로의 기본 정보를 입력받는 함수
void InputMaze()
{
    int x1, y1; //미로 시작 주소
    int x2, y2; //미로 도착 주소
    cout << "row, column : ";
    cin >> row >> col; //input
    if (row > 30 || col > 30) //정해진 크기보다 큰 수를 입력하였을 때
    {
        cout << "Size over." << endl;
        exit(0);
    }
    cout << "Input maze : " << endl;
    string input; //입력받을 미로 문자열
    for (int i = 0; i < row; i++) //행
    {
        cin >> input; //input
        for (int j = 0; j < col; j++) //열
            maze[i][j] = input[j] - '0'; //입력은 문자열이므로 아스키코드값으로 뺴서 정수 변환
    }
    cin >> y1 >> x1 >> y2 >> x2; //input
    //프로그램의 배열은 0부터 계산하므로 값을 1씩 줄여줌
    FindExit(--x1, --y1, --x2, --y2); //함수 호출
    return; //함수 종료
} //InputMaze

//미로 길찾는 함수
void FindExit(int x, int y, int xDestin, int yDestin) //시작 위치, 도착 위치
{
    trace[x][y] = 1; //시작위치 거리 계산 
    stack[top][0] = x; //시작 x위치 저장
    stack[top++][1] = y; //시작 y위치 저장 & 저장할 위치 이동
    int xfig = x, yfig = y; //입력받은 시작 위치를 fig함

    while (1) //도착할 떄까지 반복
    {
        if (xDestin == xfig && yDestin == yfig) //입력받은 목적지에 도착하였을 때
            break; //while문 종료
        //스택에 저장한 좌표를 불러옴
        xfig = stack[bottom][0]; //현재 x좌표 위치
        yfig = stack[bottom++][1]; //현재 y좌표 위치
        int xTemp, yTemp; //이동할 위치의 index를 받을 변수
        for (int i = 0; i < 4; i++) //상하좌우로 이동할 위치 탐색
        {
            xTemp = xfig + Vector[0][i]; //이동할 x좌표 임시 저장
            yTemp = yfig + Vector[1][i]; //이동할 y좌표 임시 저장
            if ((0 == maze[xTemp][yTemp]) && (-1 == trace[xTemp][yTemp])) //지나갈 수 있는 길(0)이고 지나친 적 없는 길일 때(-1)
            {
                if ((xTemp < row && yTemp < col) && (xTemp >= 0 && yTemp >= 0)) //미로 범위 내이고 메모리 범위를 벗어나는 경우가 아닐 때
                {
                    stack[top][0] = xTemp; //x좌표 저장
                    stack[top++][1] = yTemp; //y좌표 저장
                    trace[xTemp][yTemp] = trace[xfig][yfig] + 1; //거리 길이 추가
                } //if : 범위를 벗어나지 않을 때
            } //if : 지나갈 길 탐색
        } //for-i
    } //while
    cout << "\nDistance : " << trace[xDestin][yDestin] << endl; //계산한 거리 출력
    return; //함수 종료
} //FindExit
