#include <iostream>
//#include <Windows.h>
using namespace std;

//전역변수 선언
int input[100]; //입력받을 배열
int Bubble[100] = { 0 }; //Bubble Sort를 위한 배열
int Insert[100] = { 0 }; //Insertion Sort를 위한 배열
int Merge[100] = { 0 }; //Merge Sort를 위한 배열
int mergetemp[100] = { 0 }; //Merge Sort에서 임시적으로 사용할 배열
int Quick[100] = { 0 }; //Quick Sort를 위한 배열

//함수선언
void PrintArr(int arr[], int); //배열 출력 함수
void BubbleSort(int); //Bubble 정렬 함수
void InsertionSort(int); //삽입정렬 함수
void MergeSort(int, int); //Merge 정렬 함수
void merge(int, int, int); //쪼갠 배열을 합칠 함수
void QuickSort(int, int); //Quick 정렬 함수

int main()
{
	/*
	//시간 측정에 사용할 변수
	LARGE_INTEGER frequency; //CPU의 주파수를 받을 변수
	LARGE_INTEGER StartTime; //시간 측정이 시작될 때의 값을 받을 변수
	LARGE_INTEGER EndTime; //시간 측정이 끝날 때의 값을 받을 변수
	_int64 elapsed; //EndTime - StartTime의 값을 저장할 변수
	double duringTime; //계산된 시간을 저장할 변수
	QueryPerformanceFrequency(&frequency); //CPU 주파수 측정
	*/
	//배열의 요소를 0으로 초기화
	memset(input, 0, sizeof(input));
	int idx = 0; //입력받을 숫자들의 개수
	cin >> idx; 
	if (1 != idx % 2) //입력된 값은 짝수여야 함.
	{
		cout << "the number of inputs is odd." << endl;
		return 0; //end program
	}
	for (int i = 0; i < idx; i++)
	{
		cin >> input[i]; //요소 입력받기
	} //for-i

	copy(input, input + idx, Bubble); //배열복사
	copy(input, input + idx, Insert); //배열복사
	copy(input, input + idx, Merge);
	copy(input, input + idx, Quick);

	/*Bubble Sort*/
	//QueryPerformanceCounter(&StartTime); //시간측정
	BubbleSort(idx); //함수 호출
	//QueryPerformanceCounter(&EndTime); //시간 측정 종료
	//elapsed = EndTime.QuadPart - StartTime.QuadPart; //시간 계산
	//duringTime = (double)elapsed / (double)frequency.QuadPart; //주파수값으로 나눠 속도를 얻음
	//duringTime *= 1000; //ms로 변환
	//cout << "Bubble Sort Time Complexity :" << duringTime << "ms" << endl; //Bubble Sort 시간복잡조 출력
	//cout << "Bubble Sort : "; PrintArr(Bubble, idx); //결과확인용
	
	/*Insertion Sort*/
	//QueryPerformanceCounter(&StartTime); //시간측정
	InsertionSort(idx); //함수호출
	//QueryPerformanceCounter(&EndTime); //시간 측정 종료
	//elapsed = EndTime.QuadPart - StartTime.QuadPart; //시간 계산
	//duringTime = (double)elapsed / (double)frequency.QuadPart; //주파수값으로 나눠 속도를 얻음
	//duringTime *= 1000; //ms로 변환
	//cout << "Insertion Sort Time Complexity :" << duringTime << "ms" << endl; //Insertion Sort 시간복잡조 출력
	//cout << "Insertion Sort : "; PrintArr(Insert, idx); //결과확인용

	/*Merge Sort*/
	//QueryPerformanceCounter(&StartTime); //시간측정
	MergeSort(0, idx-1);
	//QueryPerformanceCounter(&EndTime); //시간 측정 종료
	//elapsed = EndTime.QuadPart - StartTime.QuadPart; //시간 계산
	//duringTime = (double)elapsed / (double)frequency.QuadPart; //주파수값으로 나눠 속도를 얻음
	//duringTime *= 1000; //ms로 변환
	//cout << "Merge Sort Time Complexity :" << duringTime << "ms" << endl; //Merge Sort 시간복잡조 출력
	//cout << "Merge Sort : "; PrintArr(Merge, idx); //결과확인용

	/*Quick Sort*/
	//QueryPerformanceCounter(&StartTime); //시간측정
	QuickSort(0, idx - 1);
	//QueryPerformanceCounter(&EndTime); //시간 측정 종료
	//elapsed = EndTime.QuadPart - StartTime.QuadPart; //시간 계산
	//duringTime = (double)elapsed / (double)frequency.QuadPart; //주파수값으로 나눠 속도를 얻음
	//duringTime *= 1000; //ms로 변환
	//cout << "Quick Sort Time Complexity :" << duringTime << "ms" << endl; //Merge Sort 시간복잡조 출력
	//cout << "Quick Sort : "; PrintArr(Quick, idx); //결과확인용

	cout << "Sorted order: ";
	PrintArr(Quick, idx); //정렬된 함수 출력
	cout << "Median number: " << Quick[idx / 2] << endl; //배열의 중간값을 출력
	return 0; //end program
} //main

//배열안의 요소를 출력하는 함수
void PrintArr(int arr[], int idx)
{
	for (int i = 0; i < idx; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return;
} //PrintArr

//Bubble Sort를 수행하는 함수
void BubbleSort(int idx)
{
	for (int i = 0; i < idx; i++)
	{
		for (int j = 0; j < idx - 1; j++)
		{
			int temp = 0;
			if (Bubble[j] > Bubble[j + 1])
			{
				temp = Bubble[j];
				Bubble[j] = Bubble[j + 1];
				Bubble[j + 1] = temp;
			}
		} //for-j
	} //for-i
	return;
} //BubbleSort

//Insertion Sort를 수행하는 함수
void InsertionSort(int idx)
{
	int j;
	for (int i = 1; i < idx; i++)
	{
		int temp = Insert[i];
		for (j = i - 1; j >= 0; j--) //i번째 index보다 앞에 있는 원소들과 대소비교
		{
			if (temp < Insert[j]) //앞에 있는 원소가 더 클 경우
			{
				Insert[j + 1] = Insert[j]; 
			}
			else
			{
				break;
			}
		} //for-j
		Insert[j + 1] = temp; //j + 1번쨰에 temp저장
	} //for-i
	return; //함수반환
} //InsertionSort

//Merge Sort를 수행하기 위해 index를 다루는 함수
void MergeSort(int left, int right)
{
	//처음 - left : 배열의 첫번째, right : 배열의 마지막 index
	if (left < right) //left의 index가 right보다 커지면 종료
	{
		int mid = (left + right) / 2; //중앙 index
		MergeSort(left, mid); //중앙에서 오른쪽
		MergeSort(mid + 1, right); //중앙에서 왼쪽
		merge(left, mid, right); //배열 합치기
	}
	return; //함수반환
} //MergeSort

//MergeSort()함수로부터 index를 전달받아 Merge Sort를 수행함
void merge(int left, int mid, int right)
{
	int i = left; //왼쪽 index
 	int j = mid + 1; //중앙 index
	int ifig = left; //왼쪽 index 저장
	int temp;
	//분활된 배열에서 왼쪽 배열과 오른쪽 배열을 비교하며 정렬
	while (i <= mid && j <= right)
	{
		//오른쪽 배열의 원소가 더 클 때
		if (Merge[i] <= Merge[j]) 
		{
			mergetemp[ifig] = Merge[i]; //i index 위치에 저장
			i++; //i의 값 증가
		} //if
		else //왼쪽 배열의 원소가 더 클 때
		{
			mergetemp[ifig] = Merge[j]; //j index 위치에 저장
			j++; //j의 값 증가
		} //else
		ifig++; //mergetemp의 idx증가
	} //while
	
	//i의 값이 mid보다 크면 j사용
	if (i > mid)
		temp = j;
	else //i의 값이 mid보다 작으면 i사용
		temp = i;

	//ifig이후의 정렬되지 않은 요소를 배열 끝까지 저장
	while (ifig <= right)
	{
		mergetemp[ifig] = Merge[temp];
		ifig++;
		temp++;
	} //while

	for (int i = left; i <= right; i++)
		Merge[i] = mergetemp[i]; //정렬된 배열을 Merge배열에 저장
	return; //함수 반환
} //merge
 
//Quick Sort를 수행하는 함수
void QuickSort(int left,int right) //처음 Pivot = index / 2
{
	if (left >= right) //왼쪽 index의 값이 오른쪽보다 크면 종료
		return; //함수반환
	int Pivot = Quick[(left + right) / 2]; //Pivot을 중간값으로 설정
	int i = left; //왼쪽 index의 값 저장
	int j = right; //오른쪽 index의 값 저장
	
	while (i <= j) //맨 왼쪽의 index가 오른쪽 index의 값과 같아질때까지 반복
	{
		while (Quick[i] < Pivot) //왼쪽 요소가 Pivot 값보다 작으면
			i++; //i index의 값 더하기
		while (Quick[j] > Pivot) //왼쪽 요소가 Pivot 값보다 크면
			j--; //j index의 값 빼기
		if (i <= j) //값 서로 바꾸기
		{
			int temp = Quick[i];
			Quick[i] = Quick[j];
			Quick[j] = temp;
			i++; j--;
		}
	} //while
	QuickSort(i, right); //오른쪽 배열 정렬하기
	QuickSort(left , j); //왼쪽 배열 정렬하기
	return; //함수반환
} //QuickSort
