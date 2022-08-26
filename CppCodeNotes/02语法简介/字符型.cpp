#include "Transfer.h"

void Call_TypeChar() {
	char ch = 'a';		// ������ʽ
	std::cout << "�ַ����ڴ��д洢���Ƕ�Ӧ��ASCII��: a-" << int('a') << std::endl;	// 97
	std::cout << "�ַ����ڴ��д洢���Ƕ�Ӧ��ASCII��: A-" << int('A') << std::endl;	// 65
}

void Func_CharStar(char* ch) {
	std::cout << ch << std::endl;
}

void Call_CharStar() {
	char ch[] = "hello";
	std::cout << ch << std::endl;
	Func_CharStar(ch);		// ch �� char �����ָ��
}

void Research_CharArray() {
	char s1[] = "hello world";
	s1[0] = 'H';
	std::cout << s1 << std::endl;		// �ܹ�������ӡ����Ϊ s1 ������

	const char* s2 = "hello world";
	//s2[0] = 'H';		// ������Ϊ s2 ��һ��ָ��ָ�����ַ����ĵ�һ���ַ����ڵ�ַ
}

void Research_CharArray1() {
	const char* str1 = "abcd1234";
	char str2[] = "abcd1234";
	printf("%u  %u\n", strlen(str1), strlen(str2));

	const char* str3 = "abcd1234";
	char str4[] = "abcd1234";
	printf("%p  %p\n", str1, str3);		// 00007FF699FD2268  00007FF699FD2268
	printf("%p  %p\n", str2, str4);		// 0000006F96D6FCE0  0000006F96D6FCF0

	strncpy_s(str2, str4, 4);		// �� str4 ��ǰ 4 ���ַ����Ƶ� str2
	printf("%s\n%s\n", str2, str4);		// ���޸ģ����� char* �����޸�
}


