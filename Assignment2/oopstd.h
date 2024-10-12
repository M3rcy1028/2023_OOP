
namespace oopstd {

	//string.h 함수 구현
	void* memset(void* ptr, int value, size_t num)
	{
		unsigned char* temp = (unsigned char*)ptr; //temp에 ptr저장
		for (int i = 0; i < num; i++)
			temp[i] = value; //요소 대체
		return (temp); //temp 반환
	} //memset

	void* memcpy(void* destination, const void* source, size_t num)	
	{
		unsigned char* temp = (unsigned char*)destination; //temp에 destination 저장
		const char* t = (const char*)source; //t에 source 저장
		int n = num; //반복변수
		while (n-- >= 0)
		{
			*temp = *t; //temp에 t저장
			temp++; t++; //index 옮기기
		} //while
		return (temp); //temp반환
	} //memcpy

	int strcmp(const char* str1, const char* str2)
	{
		while (*str1 && *str2) //문자열 끝까지 반복
		{
			if (*str1 != *str2) //두 문자열이 다를 때
				return (*str1 > *str2) ? 1 : -1; //str1이 크면 1 반환, 아니면 -1 반환
			str1++; str2++; //index 옮기기
		} //while	
		return 0; //두 문자열이 같으면 0 반환
	} //strcmp

	int strncmp(const char* str1, const char* str2, size_t num)
	{
		int cnt = 0; //반복 변수
		while (cnt < num)
		{
			if (*str1 != *str2) //두 문자열이 다를 때
				return (*str1 > *str2) ? 1 : -1; //str1이 크면 1 반환, 아니면 -1 반환
			str1++; str2++; cnt++; //index옮기기, cnt의 값 증가
		} //while
		return 0; //두 문자열이 같으면 0 반환
	} //strncmp

	char* strcpy(char* destination, const char* source)
	{
		while (*source) //문자열의 끝까지 반복
		{
			*destination = *source; //문자 복사
			destination++; source++; //index 이동
		} //while
		*destination = '\0'; //널문자 넣기
		return (destination); //반환
	} //strcpy

	char* strncpy(char* destination, const char* source, size_t num)
	{
		int cnt = 0; //반복변수
		while (cnt < num && *source) //num크기와 source 배열 끝까지 반복함
		{
			*destination = *source; //문자 복사
			destination++; source++; //index 이동
			cnt++; //반복변수 값 증가
		} //while
		*destination = '\0'; //널문자 넣기
		return (destination); //반환
	} //strncpy

	size_t strlen(const char* str)
	{
		int cnt = 0; //str의 길이
		while (*str)
		{
			str++; //index 이동
			cnt++; //길이 증가
		} //while
		return cnt; //길이 반환
	} //strlen
	
	//stdlib.h 함수 구현
	int atoi(const char* str)
	{	
		int sign = 1; //부호
		int cnt = 0; //결과값 저장
		if ('-' == *str) //마이너스 부호
		{
			sign *= -1;
			str++; //index 이동
		}
		while (*str) //문자열 끝까지 반복
		{
			if ((*str >= 48) && (*str <= 57)) //정수일 때
			{
				cnt = cnt *10 + *str - 48; //연산
				str++; //index 이동
			} //if
			else //정수 외의 값이 들어왔을 때
				break; //반복문 탈출
		} //while
		return (sign * cnt); //결과값 반환
	} //atoi

	double atof(const char* str)
	{
		double sign = 1; //부호
		double cnt = 0; //결과값 정수 부분 저장
		double floating = 0; //결과값 소수 부분 저장
		if ('-' == *str) //마이너스 부호
		{
			sign *= -1;
			str++; //index 이동
		}
		while (*str) //문자열 끝까지 반복
		{
			if ((*str >= 48) && (*str <= 57)) //정수일 때
			{
				cnt = cnt * 10 + *str - 48; //연산
				str++; //index 이동
			} //if
			else //정수 외의 값이 들어왔을 때
				break; //반복문 탈출
		} //while
		if ('.' == *str++) //만약에 .이 있을 경우 -> 소숫점 계산
		{
			double base = 10; //소숫점을 계산할 base
			while (*str) //문자열 끝까지 반복
			{
				if ((*str >= 48) && (*str <= 57)) //정수일 때
				{
					floating += (double)(*str - 48) / base; //floating에 정수 / base한 결과를 저장함
					str++; //index 이동
					base *= 10; //소숫점은 뒤로 이동하므로 10 곱해주기
				} //if
				else //정수 외의 값이 들어왔을 때
					break; //반복문 탈출
			} //while
		} //if
		return (sign * (cnt + floating)); //결과값 반환
	} //atof
} //namespace oopstd
