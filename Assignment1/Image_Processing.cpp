#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <fstream> // 파일 입출력 사용
#include <string.h>
#define IMG_HEIGHT 512 //이미지 높이
#define IMG_WIDTH 512 //이미지 폭
using namespace std;

/*Memory를 할당하는 과정*/
char** memory_alloc2D(uint32_t height, uint32_t width)
{
	char** ppMem2D = new char* [height]; //동적할당
	if (ppMem2D == 0)
		return 0;
	uint32_t size = height * width;
	ppMem2D[0] = new char[size];
	if (ppMem2D[0] == 0)
	{
		delete[] ppMem2D;
		return 0;
	}
	for (int i = 1; i < height; i++) //image의 row마다 메모리 할당
		ppMem2D[i] = ppMem2D[i - 1] + width;
	return ppMem2D;
} // uint8_t** memory_alloc2D

/*할당한 memory 해제 과정*/
int memory_free2D(char** ppMemAllocated)
{
	if (ppMemAllocated == 0)
	{
		return -1;
	}
	if (ppMemAllocated[0])
		delete[] ppMemAllocated[0];
	delete[] ppMemAllocated;
	return 0;
} //memory_free2D

FILE* fpInputImage = 0; //불러올 image 파일
FILE* fpVerticalFilpImage = 0; //Vertically fliped image를 저장할 파일
FILE* fpHorizontalFilpImage = 0; //Horizontal fliped image를 저장할 파일
FILE* fpCroppedImage = 0; //Cropped image를 자른 크기로 저장할 파일
char** fpInputImageBuffer = 0; //ImageBuffer

int main()
{
	//"Couple_512x512_yuv400_8bit.raw";
	//"Barbara_512x512_yuv400_8bit.raw";
	//============================================
	char filename[1000] = { '\0' }; //file name을 입력받을 변수
	int x1, x2, y1, y2;
	cout << "Input file name : "; //input
	cin >> filename;
	cout << "1st coordinate : "; //1st input
	scanf_s("%d, %d", &x1, &y1);
	cout << "2nd coordinate : "; //2nd input
	scanf_s("%d, %d", &x2, &y2);

	const char* IMG_NAME = filename; //파일 이름 const char* 형식으로 저장
	int fidx = 0;
	for (int i = 0; i < strlen(filename); i++)
	{
		if ('_' == filename[i])
		{
			fidx = i;
			break;
		}
	}

	//입력한 이미지 파일 열기
	fpInputImage = fopen(IMG_NAME, "rb");
	if (!fpInputImage) //이미지 파일을 열지 못했을 때
	{
		cout << "Unable to open input file." << endl;
		return -1;
	}
	//Image를 임시 저장할 Buffer에 메모리 할당하기
	fpInputImageBuffer = memory_alloc2D(IMG_HEIGHT, IMG_WIDTH);
	//원본 이미지를 받아 fpInputImageBuffer에 저장
	for (int i = 0; i < IMG_HEIGHT; i++)
	{
		fread((char*)fpInputImageBuffer[i], sizeof(char), IMG_HEIGHT * IMG_WIDTH, fpInputImage);
	}
	//====================================두 좌표로 이미지 자르기==========================================
	filename[fidx] = '\0'; //배열이름 원래대로 바꾸기
	//좌표값 찍기
	int height = y2 - y1; //자른 사진의 높이
	int width = x2 - x1; //자른 사진의 폭
	int fheight = y2 - y1; //저장할 사진의 높이
	int fwidth = x2 - x1; //저장할 사진의 폭
	if (fheight < 0) //음수일 때
		fheight *= -1;
	if (fwidth < 0) //음수일 때
		fwidth *= -1;
	char* Cropped = filename; //자른 파일 이름
	sprintf(Cropped, "%s_cropped_%dx%d.raw", filename, fwidth, fheight);

	//자른 사진을 자른 크기로 저장할 파일 열기
	fpCroppedImage = fopen(Cropped, "wb");
	if (!fpCroppedImage) //파일이 안 열릴 때
	{
		cout << "Unable to open fpCroppedImage," << endl;
		return -1;
	}
	//자른 이미지 저장하는 배열
	unsigned char CroppedArr[IMG_HEIGHT][IMG_WIDTH] = { '\0' };

	if (height > 0 && width > 0) //좌상단 (x1, y1) 우하단 (x2, y2)
	{
		for (int i = y1; i <= y2; i++)
		{
			for (int j = x1; j <= x2; j++)
			{
				CroppedArr[i - y1][j - x1] = fpInputImageBuffer[i][j];
			}
		}
	} //if (height > 0 && width > 0)
	else if (height > 0 && width < 0) //우상단 (x1, y1) 좌하단 (x2, y2)
	{
		for (int i = y1; i <= y2; i++)
		{
			for (int j = x2; j <= x1; j++)
			{
				CroppedArr[i - y1][j - x2] = fpInputImageBuffer[i][j];
			}
		}
	} //else if (height > 0 && width < 0)
	else if (height < 0 && width < 0) //좌상단 (x2, y2) 우하단 (x1, y1)
	{
		for (int i = y2; i <= y1; i++)
		{
			for (int j = x2; j <= x1; j++)
			{
				CroppedArr[i - y2][j - x2] = fpInputImageBuffer[i][j];
			}
		}
	} //else if (height < 0 && width < 0)
	else if (height < 0 && width > 0) //우상단 (x2, y2) 좌하단 (x1, y1)
	{
		for (int i = y2; i <= y1; i++)
		{
			for (int j = x1; j <= x2; j++)
			{
				CroppedArr[i - y2][j - x1] = fpInputImageBuffer[i][j];
			}
		}
	} //else if (height < 0 && width > 0)

	if (height < 0) //음수일 때
		height *= -1;
	if (width < 0) //음수일 때
		width *= -1;

	int size = fwidth * fheight; //자른 사진의 크기
	fwrite((char*)CroppedArr, sizeof(char), size, fpCroppedImage); //원본 크기로 저장
	fclose(fpCroppedImage); //파일 닫기

	//====================================수평으로 사진 뒤집기==========================================
	filename[fidx] = '\0'; //배열이름 원래대로 바꾸기
	const char* horizontal = strcat(filename, "_horizontalflip.raw"); //수직으로 뒤집은 파일 이름
	//수직으로 뒤집은 사진을 저장할 파일 열기
	fpHorizontalFilpImage = fopen(horizontal, "wb");
	if (!fpHorizontalFilpImage) //파일이 안 열릴 때
	{
		cout << "Unable to open fpHorizontalFilpImage," << endl;
		return -1;
	}
	//이미지를 수직으로 뒤집기
	unsigned char HorizontallArr[IMG_HEIGHT][IMG_WIDTH] = { '\0' };
	for (int i = 0; i < IMG_HEIGHT; i++)
	{
		for (int j = 0; j < IMG_WIDTH; j++)
		{
			HorizontallArr[i][j] = fpInputImageBuffer[i][IMG_WIDTH - 1 - j];
		}
	}
	//수평으로 뒤집은 사진 저장하기
	fwrite((char*)HorizontallArr, sizeof(char), IMG_HEIGHT * IMG_WIDTH, fpHorizontalFilpImage);
	fclose(fpHorizontalFilpImage); //파일 닫기
	//====================================수직으로 사진 뒤집기==========================================
	filename[fidx] = '\0'; //배열이름 원래대로 바꾸기
	const char* vertical = strcat(filename, "_verticalflip.raw"); //수직으로 뒤집은 파일 이름
	//수직으로 뒤집은 사진을 저장할 파일 열기
	fpVerticalFilpImage = fopen(vertical, "wb");
	if (!fpVerticalFilpImage) //파일이 안 열릴 때
	{
		cout << "Unable to open fpVerticalFilpImage," << endl;
		return -1;
	}
	//이미지를 수직으로 뒤집기
	unsigned char VerticalArr[IMG_HEIGHT][IMG_WIDTH] = { '\0' };
	for (int i = 0; i < IMG_HEIGHT; i++)
	{
		for (int j = 0; j < IMG_WIDTH; j++)
		{
			VerticalArr[i][j] = fpInputImageBuffer[IMG_HEIGHT - i - 1][j];
		}
	}
	//수직으로 뒤집은 사진 저장하기
	fwrite((char*)VerticalArr, sizeof(char), IMG_HEIGHT * IMG_WIDTH, fpVerticalFilpImage);
	fclose(fpVerticalFilpImage); //파일 닫기
	//===============================================================================================

	memory_free2D(fpInputImageBuffer); //메모리 해제
	fclose(fpInputImage);
	cout << "Ouput images are stored!" << endl;
	return 0;
} //main
