#include <stdio.h>
//#include "C_Basic_main.h"

#pragma region Point_���
void func_Point_Intro() {
	// һ��ָ��ָ��Ŀ��ܻ���ָ�룬��ʱ��Ҫ�������Ǻ�**��ʾ��
	int** foo;
}
#pragma endregion

#pragma region Point_*
void func_Point_SignStar() {
	// *������ȡַ
	int x = 10;
	int* p = &x;
	printf("ȡַ��Ľ��: %d", *p + 1);
}

void func_Point_SignAnd() {
	// *������ȡַ
	int x = 10;
	printf("x's address is %p\n", &x);
}
#pragma endregion

