#include <iostream>
using namespace std;

//함수 선언
void RepeatingDecimal(int, int);
void LPR(double, int, int, int, int);

int main()
{
	int Vs = 0, R1 = 0, R2 = 0; //회로에 공급되는 전압, 저항1, 저항2
	int RLoad = 0; //저항 Rload
	double Vout = 0; //전압 Vout

	cout << "Vs: "; cin >> Vs; //input
	cout << "R1: "; cin >> R1; //input 
	cout << "R2: "; cin >> R2; //input
	cout << "R(Load): "; cin >> RLoad; //input
	cout << endl; //new line
	if (0 == RLoad) //에너지를 소비하지 않을 때
	{
		RepeatingDecimal(Vs * R2, R1 + R2); //결과값 출력
	} //if (0 == RLoad)
	else //에너지를 소비할 때
	{
		double Rp = ((R2 * RLoad) / (R2 + RLoad)); //병렬 저항
		RepeatingDecimal(Vs * (R2 * RLoad), (R1 + Rp) * (R2 + RLoad)); //결과값 출력
		LPR(Rp, Vs, R1, R2, RLoad); //
	} //else
	cout << endl; //new line
	return 0; //end program
} //main

//순환소수점을 계산한 후 출력하는 함수
void RepeatingDecimal(int n1, int n2) //n1 : 분자, n2 : 분모
{
	int start, end; //순환소수의 시작 index와 끝 index
	int points[1000]; //순환되는 소수점을 저장할 배열
	int cnt = 0; //순환소수 위치 찾기
	int n1fig = n1; //n1의 값을 저장해둘 변수
    memset(points, -1, sizeof(points)); //배열의 모든 요소를 -1로 초기화
    start = end = 0; //index값 0으로 초기화
    printf("Vout : %d/%d", n1, n2); //Vout 분수 표현으로 출력
    int temp = n1 % n2 * 10; //정수부분

    while (1) //순환소수찾기
    {
        n1 = n1 % n2 * 10; //소수점이하 1자리 저장
        if (-1 != points[n1]) //소수점이 저장되었는지 확인
        { //해당 소수점이 이미 등장했을 때 -> 순환소수가 시작
            start = points[n1]; //이전의 위치 저장
            end = cnt; //현재 위치 저장
            break; //반복문 탈출
        } //if
        points[n1] = cnt; //소수점이 등장한 적이 없으므로 해당 index의 요소 +1
        cnt++; //다음 위치 저장하기 위해 +1
    } //while
    //나눈 몫이 0으로 딱 맞아 떨어질 때
    //20.00000 -> 20
    if (0 == n1fig % n2)
    {
        printf(" = %d", n1fig / n2);
        return; //함수 나가기
    } //if (0 == n1fig % n2)
    int r1 = end - start; 
    int r2 = (int)(n1fig / n2) % 10;
    int r3 = temp / n2 % n2;
    //13.333333 -> 1(3.)
    if ((1 == r1) && (r2 == r3))
    {
        printf(" = %d(%d.)", n1fig / n2 / 10, n1fig / n2 % 10);
        return; //함수 탈출
    } //if ((1 == r1) && (r2 == r3))
    //그외의 소수
    //정수부분 출력
    printf(" = %d.", (n1fig / n2));
    //순환소수부분이 나타날 때까지 나누기
    for (int i = 0; i < start; i++) 
    {
        printf("%d", temp / n2); //소수부분 출력
        temp = temp % n2 * 10;
    } 
    //순환소수부분 출력
    printf("(");
    for (int i = start; i < end; i++) 
    {
        printf("%d", temp / n2); //순환소수 출력
        temp = temp % n2 * 10;
    }
    printf(")\n"); //new line
    return; //함수 탈출
} //RepeatingDecimal

//Load Power Ratio를 계산하는 함수
void LPR(double Rp, int Vs, int R1, int R2, int RL)
{
	double I = Vs / (R1 + Rp); //전류 I
	double VL = (Vs - I * R1); //RLoad에 걸리는 전압 VL
	double Ps = Vs * I; //Ps = Vs * I
	double PL = VL * I * R2 / (R2 + RL); //PL = VL * IRL
	printf("\nLoad power ratio: %.2lf\%%", PL / Ps * 100); //소숫점 첫째자리까지 출력
	return;
} //LPR
